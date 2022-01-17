//  Student: Laurens De Wachter
//  Rolnummer: r0214686
//  Opmerkingen:
//

#include "game.h"

Game::Game() : aanBeurt(wit) {
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
    vector<pair<int, int>> mogelijke_zetten = s->geldige_zetten(*this);
    pair<int, int> vergelijker;
    vergelijker.first = r;
    vergelijker.second = k;
    if (any_of(mogelijke_zetten.begin(), mogelijke_zetten.end(), [vergelijker](pair<int, int> i){return i == vergelijker;})) {
        SchaakStuk *stuk_op_loc = Game::getPiece(r, k);
        pair<int, int> loc = s->getLocation(*this);
        Game::setPiece(loc.first, loc.second, nullptr);
        Game::setPiece(r, k, s);
        if (s->getKleur() == wit) {
            if (Game::schaak(wit)) {
                Game::setPiece(loc.first, loc.second, s);
                Game::setPiece(r, k, stuk_op_loc);
                return false;
            }
        } else {
            if (Game::schaak(zwart)) {
                Game::setPiece(loc.first, loc.second, s);
                Game::setPiece(r, k, stuk_op_loc);
                return false;
            }
        }
        s->eersteZet = false;
        delete stuk_op_loc;
        return true;
    }
    return false;
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
    // nakijken of de gegeven kleur schaak staat
    if ((kleur == wit && not schaak(wit)) || (kleur == zwart) && not schaak(zwart)) return false;

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