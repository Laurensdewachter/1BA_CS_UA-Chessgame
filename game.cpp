//  Student: Laurens De Wachter
//  Rolnummer: r0214686

#include "game.h"

Game::Game() : aanBeurt(wit), finished(false) {}

Game::~Game() {
    Game::clearBord();
}

// Zet het bord klaar; voeg de stukken op de juiste plaats toe
void Game::setStartBord() {
    schaakbord[0] = new Toren(zwart);
    schaakbord[1] = new Paard(zwart);
    schaakbord[2] = new Loper(zwart);
    schaakbord[3] = new Koningin(zwart);
    koningZwart = new Koning(zwart);
    schaakbord[4] = koningZwart;
    schaakbord[5] = new Loper(zwart);
    schaakbord[6] = new Paard(zwart);
    schaakbord[7] = new Toren(zwart);
    for (int i = 8; i < 16; i++) schaakbord[i] = new Pion(zwart);
    for (int i = 48; i < 56; i++) schaakbord[i] = new Pion(wit);
    schaakbord[56] = new Toren(wit);
    schaakbord[57] = new Paard(wit);
    schaakbord[58] = new Loper(wit);
    schaakbord[59] = new Koningin(wit);
    koningWit = new Koning(wit);
    schaakbord[60] = koningWit;
    schaakbord[61] = new Loper(wit);
    schaakbord[62] = new Paard(wit);
    schaakbord[63] = new Toren(wit);
}

// Verwijdert alle stukken van het schaakbord
void Game::clearBord() {
    for (int i = 0; i < 64; i++) {
        delete schaakbord[i];
        schaakbord[i] = nullptr;
    }
    koningWit = koningZwart = nullptr;
}

void Game::setKoning(zw kleur, SchaakStuk* koning) {
    if (kleur == wit) koningWit = koning;
    else koningZwart = koning;
}

// Verplaats stuk s naar positie (r,k)
// Als deze move niet mogelijk is, wordt de juiste soort error teruggegeven
// en verandert er niets aan het schaakbord (uitgezonderd bij schaakmat. Dan wordt de zet wel gemaakt).
// Anders wordt de move uitgevoerd en wordt true teruggegeven
bool Game::move(SchaakStuk* s, int r, int k) {
    // mogelijke zetten van het stuk verzamelen
    vector<pair<int, int>> mogelijke_zetten = s->geldige_zetten(*this);
    // aangeklikte locatie in een pair<int, int> zetten
    pair<int, int> vergelijker;
    vergelijker.first = r;
    vergelijker.second = k;
    // controleren of de aangeklikte locatie een geldige zet is
    if (any_of(mogelijke_zetten.begin(), mogelijke_zetten.end(), [vergelijker](pair<int, int> i){return i == vergelijker;})) {
        // het stuk dat eventueel gepakt zou worden opslaan als stuk_op_loc
        SchaakStuk *stuk_op_loc = Game::getPiece(r, k);
        // de huidige locatie van het te verplaatsen stuk opslaan in 'loc'
        pair<int, int> loc = s->getLocation(*this);
        // de huidige locatie leeg maken
        Game::setPiece(loc.first, loc.second, nullptr);
        // het stuk verplaatsen naar de nieuwe locatie
        Game::setPiece(r, k, s);
        zw kleur = s->getKleur();
        zw kleur_inv = wit;
        if (kleur == wit) kleur_inv = zwart;
        // nakijken of de speler die juist (probeerde) te zetten zichzelf niet schaak heeft gezet/laten staan
        if (Game::schaak(kleur)) {
            // nakijken of de speler zijn tegenstander schaakmat heeft gezet
            if (Game::schaakmat(kleur_inv)) {
                delete stuk_op_loc;
                // throw een schaakMatError
                throw schaakMatError(kleur);
            }
            // als de speler schaak staat moet de zet ongedaan gemaakt worden
            Game::setPiece(loc.first, loc.second, s);
            Game::setPiece(r, k, stuk_op_loc);
            // throw een schaakError
            throw schaakError();
        }
        // nakijken of de speler zijn tegenstander pat heeft gezet
        if (Game::pat(kleur_inv)) {
            delete stuk_op_loc;
            // throw een patError
            throw patError();
        }
        delete stuk_op_loc;
        return true;
    }
    throw verplaatsingsError();
}

// Geeft true als kleur schaak staat
bool Game::schaak(zw kleur) {
    vector<SchaakStuk*> pieces;
    pair<int, int> loc;
    // zet locatie van de koning in 'loc' en de stukken van de tegenstander in 'pieces'
    if (kleur == wit) {
        loc = koningWit->getLocation(*this);
        pieces = Game::getPieces(zwart);
    } else {
        loc = koningZwart->getLocation(*this);
        pieces = Game::getPieces(wit);
    }
    // itereer over elk stuk van de tegenstander
    for (auto i : pieces) {
        // verzamel alle mogelijke zetten van stuk i in 'zetten'
        vector<pair<int, int>> zetten = i->geldige_zetten(*this);
        // als één van de mogelijke zetten van i gelijk is aan de locatie van de koning staat de koning schaak en
        // wordt 'true' teruggegeven
        if (any_of(zetten.begin(), zetten.end(), [loc](pair<int, int> i){return  i == loc;})) return true;
    }
    // er is geen enkel stuk dat de koning schaak zet en er wordt 'false' teruggegeven
    return false;
}

// Geeft true als kleur schaakmat staat
bool Game::schaakmat(zw kleur) {
    // koning en locatie van koning in globale variabelen zetten
    SchaakStuk* koning;
    if (kleur == wit) koning = koningWit;
    else koning = koningZwart;
    pair<int, int> loc = koning->getLocation(*this);
    // nakijken of de koning kan verplaatsen
    for (auto i : koning->geldige_zetten(*this)) {
        if (not Game::quickCheckSchaak(kleur, koning, i.first, i.second)) return false;
    }
    // nakijken of een ander stuk het aanvallende stuk kan blokkeren
    // itereer over alle stukken van de "verdedigende" kleur
    for (auto i : Game::getPieces(kleur)) {
        // itereer over alle geldige zetten van stuk i
        for (auto j : i->geldige_zetten(*this)) {
            // kijk na of de koning als zet j gemaakt zou worden. Indien ja: de koning staat nog niet schaakmat
            // dus return 'false'
            if (not Game::quickCheckSchaak(kleur, i, j.first, j.second)) return false;
        }
    }
    return true;
}

// Kijkt na of de gegeven kleur schaak zou staan als stuk 's' verplaatst zou worden naar locatie 'r, k'
// deze functie verandert de locatie van het stuk niet
bool Game::quickCheckSchaak(zw kleur, SchaakStuk *s, int r, int k) {
    // plaats de huidige locatie van 's' in 'loc'
    pair<int, int> loc = s->getLocation(*this);
    // plaats het stuk dat momenteel op locatie 'r, k' staat (eventueel nullptr) in 'temp'
    SchaakStuk* temp = Game::getPiece(r, k);
    // verplaats 's' naar 'r, k'
    Game::setPiece(r, k, s);
    // maak de oude locatie van 's' leeg
    Game::setPiece(loc.first, loc.second, nullptr);
    // kijk na of de gegeven kleur schaak staat
    if (not schaak(kleur)) {
        // zet het schaakbord terug naar zijn originele vorm
        Game::setPiece(loc.first, loc.second, s);
        Game::setPiece(r, k, temp);
        // het stuk zou niet schaak staan dus return 'false'
        return false;
    }
    // zet het schaakbord terug naar zijn originele vorm
    Game::setPiece(loc.first, loc.second, s);
    Game::setPiece(r, k, temp);
    // het stuk zou wel schaak staan dus return 'true'
    return true;
}

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) {
    for (auto i : Game::getPieces(kleur)) {
        vector<pair<int, int>> zetten = i->geldige_zetten(*this);
        if (not zetten.empty()) {
            for (auto j : zetten) {
                if (not Game::quickCheckSchaak(kleur, i, j.first, j.second)) return false;
            }
        }
    }
    return true;
}

// Geeft een pointer naar het schaakstuk dat op rij r, kolom k staat
// Als er geen schaakstuk staat op deze positie, geef nullptr terug
SchaakStuk* Game::getPiece(int r, int k) {
    return schaakbord[r*8 + k];
}

// Zet het schaakstuk waar s naar verwijst neer op rij r, kolom k.
// Als er al een schaakstuk staat, wordt het overschreven.
// Bewaar in jouw datastructuur de *pointer* naar het schaakstuk,
// niet het schaakstuk zelf.
void Game::setPiece(int r, int k, SchaakStuk* s) {
    schaakbord[r*8 + k] = s;
}

void Game::changeBeurt() {
    if (aanBeurt == wit) aanBeurt = zwart;
    else aanBeurt = wit;
}

void Game::setBeurt(zw kleur) {aanBeurt = kleur;}

vector<SchaakStuk*> Game::getPieces(zw kleur) {
    vector<SchaakStuk*> pieces;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            SchaakStuk* piece = Game::getPiece(i, j);
            if (piece != nullptr && piece->getKleur() == kleur) pieces.push_back(piece);
        }
    }
    return pieces;
}