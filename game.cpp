//  Student: Laurens De Wachter
//  Rolnummer: r0214686
//  Opmerkingen:
//

#include "game.h"

Game::Game() : aanBeurt(wit), finished(false) {
    for (int i = 0; i < 64; i++) schaakbord[i] = nullptr;
}

Game::~Game() {}

// Zet het bord klaar; voeg de stukken op de jusite plaats toe
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

// Verplaats stuk s naar positie (r,k)
// Als deze move niet mogelijk is, wordt false teruggegeven
// en verandert er niets aan het schaakbord.
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
        // de huidige locatie van het te verplaatsen stuk opslaan als loc
        pair<int, int> loc = s->getLocation(*this);
        // de huidige locatie leeg maken
        Game::setPiece(loc.first, loc.second, nullptr);
        // het stuk verplaatsen naar de nieuwe locatie
        Game::setPiece(r, k, s);
        zw kleur = s->getKleur();
        // nakijken of de speler die juist (probeerde) te zetten zichzelf niet schaak heeft gezet/laten staan
        if (Game::schaak(kleur)) {
            // als de speler schaak staat moet de zet ongedaan gemaakt worden
            Game::setPiece(loc.first, loc.second, s);
            Game::setPiece(r, k, stuk_op_loc);
            // throw een schaakError
            throw schaakError();
        }
        zw kleur_inv = wit;
        if (kleur == wit) kleur_inv = zwart;
        // nakijken of de speler zijn tegenstander schaakmat heeft gezet
        if (Game::schaakmat(kleur_inv)) {
            delete stuk_op_loc;
            // throw een schaakMatError
            throw schaakMatError(kleur);
        }
        s->setEersteZet();
        delete stuk_op_loc;
        return true;
    }
    throw verplaatsingsError();
}

// Geeft true als kleur schaak staat
bool Game::schaak(zw kleur) {
    vector<SchaakStuk*> pieces;
    pair<int, int> loc;
    if (kleur == wit) {
        loc = koningWit->getLocation(*this);
        pieces = Game::getPieces(zwart);
    } else {
        loc = koningZwart->getLocation(*this);
        pieces = Game::getPieces(wit);
    }
    for (auto i : pieces) {
        vector<pair<int, int>> zetten = i->geldige_zetten(*this);
        if (any_of(zetten.begin(), zetten.end(), [loc](pair<int, int> i){return  i == loc;})) return true;
    }
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
    vector<SchaakStuk*> pieces = Game::getPieces(kleur);
    for (auto i : pieces) {
        vector<pair<int, int>> zetten = i->geldige_zetten(*this);
        for (auto j : zetten) {
            if (not Game::quickCheckSchaak(kleur, i, j.first, j.second)) return false;
        }
    }
    return true;
}

bool Game::quickCheckSchaak(zw kleur, SchaakStuk *s, int r, int k) {
    pair<int, int> loc = s->getLocation(*this);
    SchaakStuk* temp = Game::getPiece(r, k);
    Game::setPiece(r, k, s);
    Game::setPiece(loc.first, loc.second, nullptr);
    if (not schaak(kleur)) {
        Game::setPiece(loc.first, loc.second, s);
        Game::setPiece(r, k, temp);
        return false;
    }
    Game::setPiece(loc.first, loc.second, s);
    Game::setPiece(r, k, temp);
    return true;
}

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) {
    return false;
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