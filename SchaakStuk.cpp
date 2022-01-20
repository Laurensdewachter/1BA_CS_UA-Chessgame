//  Student: Laurens De Wachter
//  Rolnummer: r0214686

#include "SchaakStuk.h"
#include "game.h"

zw SchaakStuk::getKleur() const {return kleur;}

pair<int, int> SchaakStuk::getLocation(Game &g) const {
    bool found = false;
    int r;
    int k;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (g.getPiece(i, j) == this) {
                r = i;
                k = j;
                found = true;
                break;
            }
        }
        if (found) break;
    }
    pair<int, int> loc;
    loc.first = r;
    loc.second = k;
    return loc;
}

bool SchaakStuk::getMoved() const {return hasMoved;}

void SchaakStuk::setMoved(bool m) {hasMoved = m;}


vector<pair<int, int>> Pion::geldige_zetten(Game &g) {
    vector<pair<int, int>> zetten;
    pair<int, int> loc = SchaakStuk::getLocation(g);
    int r = loc.first;
    int k = loc.second;
    // onderscheid maken tussen zwart en wit
    if (SchaakStuk::getKleur() == wit) {
        // nakijken of de plaats voor de pion vrij is
        if (g.getPiece(r-1, k) == nullptr) zetten.emplace_back(r-1, k);
        // nakijken of er een stuk schuin links voor de pion staat
        if (k > 0 && g.getPiece(r-1, k-1) != nullptr && g.getPiece(r-1, k-1)->getKleur() != SchaakStuk::getKleur())
            zetten.emplace_back(r-1, k-1);
        // nakijken of er een stuk schuin rechts voor de pion staat
        if (k < 7 && g.getPiece(r-1, k+1) != nullptr && g.getPiece(r-1, k+1)->getKleur() != SchaakStuk::getKleur())
            zetten.emplace_back(r-1, k+1);
        // nakijken of het de eerste zet van de pion is en of de 2 vakken voor de pion vrij zijn
        if (r == 6 && g.getPiece(r-1, k) == nullptr && g.getPiece(r-2, k) == nullptr) zetten.emplace_back(r-2, k);
        // nakijken of er links een stuk dat en passant gepakt kan worden
        if (k != 0 && r == 3 && g.getPiece(r, k-1) != nullptr && g.getPiece(r, k-1) == g.getPionVoorEP())
            zetten.emplace_back(r-1, k-1);
        // nakijken of er rechts een stuk dat en passant gepakt kan worden
        if (k != 7 && r == 3 && g.getPiece(r, k+1) != nullptr && g.getPiece(r, k+1) == g.getPionVoorEP())
            zetten.emplace_back(r-1, k+1);
    } else {
        // nakijken of de plaats voor de pion vrij is
        if (g.getPiece(r+1, k) == nullptr) zetten.emplace_back(r+1, k);
        // nakijken of er een stuk schuin links voor de pion staat
        if (k > 0 && g.getPiece(r+1, k-1) != nullptr && g.getPiece(r+1, k-1)->getKleur() != SchaakStuk::getKleur())
            zetten.emplace_back(r+1, k-1);
        // nakijken of er een stuk schuin rechts voor de pion staat
        if (k < 7 && g.getPiece(r+1, k+1) != nullptr && g.getPiece(r+1, k+1)->getKleur() != SchaakStuk::getKleur())
            zetten.emplace_back(r+1, k+1);
        // nakijken of het de eerste zet van de pion is en of de 2 vakken voor de pion vrij zijn
        if (r == 1 && g.getPiece(r+1, k) == nullptr && g.getPiece(r+2, k) == nullptr)
            zetten.emplace_back(r+2, k);
        // nakijken of er links een stuk dat en passant gepakt kan worden
        if (k != 0 && r == 4 && g.getPiece(r, k-1) != nullptr && g.getPiece(r, k-1) == g.getPionVoorEP())
            zetten.emplace_back(r+1, k-1);
        // nakijken of er rechts een stuk dat en passant gepakt kan worden
        if (k != 7 && r == 4 && g.getPiece(r, k+1) != nullptr && g.getPiece(r, k+1) == g.getPionVoorEP())
            zetten.emplace_back(r+1, k+1);
    }
    return zetten;
}

vector <pair<int, int>> Toren::geldige_zetten(Game &g) {
    vector<pair<int, int>> zetten;
    pair<int, int> loc = SchaakStuk::getLocation(g);
    int r = loc.first;
    int k = loc.second;
    // stap naar onder op het bord
    if (r != 7) {
        for (int i = r+1; i <= 7; i++) {
            if (g.getPiece(i, k) == nullptr) zetten.emplace_back(i, k);
            else {
                if (g.getPiece(i, k)->getKleur() != SchaakStuk::getKleur()) zetten.emplace_back(i, k);
                break;
            }
        }
    }
    // stap naar boven op het bord
    if (r != 0) {
        for (int i = r-1; i >= 0 ; i--) {
            if (g.getPiece(i, k) == nullptr) zetten.emplace_back(i, k);
            else {
                if (g.getPiece(i, k)->getKleur() != SchaakStuk::getKleur()) zetten.emplace_back(i, k);
                break;
            }
        }
    }
    // stap naar links
    if (k != 0) {
        for (int i = k-1; i >= 0; i--) {
            if (g.getPiece(r, i) == nullptr) zetten.emplace_back(r, i);
            else {
                if (g.getPiece(r, i)->getKleur() != SchaakStuk::getKleur()) zetten.emplace_back(r, i);
                break;
            }
        }
    }
    // stap naar rechts;
    if (k != 7) {
        for (int i = k+1; i <= 7; i++) {
            if (g.getPiece(r, i) == nullptr) zetten.emplace_back(r, i);
            else {
                if (g.getPiece(r, i)->getKleur() != SchaakStuk::getKleur()) zetten.emplace_back(r, i);
                break;
            }
        }
    }
    return zetten;
}

vector<pair<int, int>> Paard::geldige_zetten(Game &g) {
    vector<pair<int, int>> zetten;
    pair<int, int> loc = SchaakStuk::getLocation(g);
    int r = loc.first;
    int k = loc.second;
    // up-left
    if (r > 1 && k > 0 && (g.getPiece(r-2, k-1) == nullptr || g.getPiece(r-2, k-1)->getKleur() != SchaakStuk::getKleur()))
        zetten.emplace_back(r-2, k-1);
    // up-right
    if (r > 1 && k < 7 && (g.getPiece(r-2, k+1) == nullptr || g.getPiece(r-2, k+1)->getKleur() != SchaakStuk::getKleur()))
        zetten.emplace_back(r-2, k+1);
    // left-up
    if (r > 0 && k > 1 && (g.getPiece(r-1, k-2) == nullptr || g.getPiece(r-1, k-2)->getKleur() != SchaakStuk::getKleur()))
        zetten.emplace_back(r-1, k-2);
    // right-up
    if (r > 0 && k < 6 && (g.getPiece(r-1, k+2) == nullptr || g.getPiece(r-1, k+2)->getKleur() != SchaakStuk::getKleur()))
        zetten.emplace_back(r-1, k+2);
    // down-left
    if (r < 6 && k > 0 && (g.getPiece(r+2, k-1) == nullptr || g.getPiece(r+2, k-1)->getKleur() != SchaakStuk::getKleur()))
        zetten.emplace_back(r+2, k-1);
    // down-right
    if (r < 6 && k < 7 && (g.getPiece(r+2, k+1) == nullptr || g.getPiece(r+2, k+1)->getKleur() != SchaakStuk::getKleur()))
        zetten.emplace_back(r+2, k+1);
    // left-down
    if (r < 7 && k > 1 && (g.getPiece(r+1, k-2) == nullptr || g.getPiece(r+1, k-2)->getKleur() != SchaakStuk::getKleur()))
        zetten.emplace_back(r+1, k-2);
    // right-down
    if (r < 7 && k < 6 && (g.getPiece(r+1, k+2) == nullptr || g.getPiece(r+1, k+2)->getKleur() != SchaakStuk::getKleur()))
        zetten.emplace_back(r+1, k+2);
    return zetten;
}

vector<pair<int, int>> Loper::geldige_zetten(Game &g) {
    vector<pair<int, int>> zetten;
    pair<int, int> loc = SchaakStuk::getLocation(g);
    int r = loc.first;
    int k = loc.second;
    // left-up
    if (r != 0 || k != 0) {
        for (int i = 1; i <= 7; i++) {
            if (r-i < 0 || k-i < 0) break;
            if (g.getPiece(r-i, k-i) == nullptr) zetten.emplace_back(r-i, k-i);
            else if (g.getPiece(r-i, k-i)->getKleur() != SchaakStuk::getKleur()) {
                zetten.emplace_back(r-i, k-i);
                break;
            } else break;
        }
    }
    // right-up
    if (r != 0 || k != 7) {
        for (int i = 1; i <= 7; i++) {
            if (r-i < 0 || k+i > 7) break;
            if (g.getPiece(r-i, k+i) == nullptr) zetten.emplace_back(r-i, k+i);
            else if (g.getPiece(r-i, k+i)->getKleur() != SchaakStuk::getKleur()) {
                zetten.emplace_back(r-i, k+i);
                break;
            } else break;
        }
    }
    // left-down
    if (r != 7 || k != 0) {
        for (int i = 1; i <= 7; i++) {
            if (r+i > 7 || k-i < 0) break;
            if (g.getPiece(r+i, k-i) == nullptr) zetten.emplace_back(r+i, k-i);
            else if (g.getPiece(r+i, k-i)->getKleur() != SchaakStuk::getKleur()) {
                zetten.emplace_back(r+i, k-i);
                break;
            } else break;
        }
    }
    // right-down
    if (r != 0 || k != 0) {
        for (int i = 1; i <= 7; i++) {
            if (r+i > 7 || k+i > 7) break;
            if (g.getPiece(r+i, k+i) == nullptr) zetten.emplace_back(r+i, k+i);
            else if (g.getPiece(r+i, k+i)->getKleur() != SchaakStuk::getKleur()) {
                zetten.emplace_back(r+i, k+i);
                break;
            } else break;
        }
    }
    return zetten;
}

vector<pair<int, int>> Koning::geldige_zetten(Game &g) {
    vector<pair<int, int>> zetten;
    pair<int, int> loc = SchaakStuk::getLocation(g);
    int r = loc.first;
    int k = loc.second;
    // onder
    if (r != 7 && (g.getPiece(r+1, k) == nullptr || g.getPiece(r+1, k)->getKleur() != SchaakStuk::getKleur()))
        zetten.emplace_back(r+1, k);
    // links onder
    if (r != 7 && k != 0 && (g.getPiece(r+1, k-1) == nullptr || g.getPiece(r+1, k-1)->getKleur() != SchaakStuk::getKleur()))
        zetten.emplace_back(r+1, k-1);
    // links
    if (k != 0 && (g.getPiece(r, k-1) == nullptr || g.getPiece(r, k-1)->getKleur() != SchaakStuk::getKleur()))
        zetten.emplace_back(r, k-1);
    // links boven
    if (r != 0 && k != 0 && (g.getPiece(r-1, k-1) == nullptr || g.getPiece(r-1, k-1)->getKleur() != SchaakStuk::getKleur()))
        zetten.emplace_back(r-1, k-1);
    // boven
    if (r != 0 && (g.getPiece(r-1, k) == nullptr || g.getPiece(r-1, k)->getKleur() != SchaakStuk::getKleur()))
        zetten.emplace_back(r-1, k);
    // rechts boven
    if (r != 0 && k != 7 && (g.getPiece(r-1, k+1) == nullptr || g.getPiece(r-1, k+1)->getKleur() != SchaakStuk::getKleur()))
        zetten.emplace_back(r-1, k+1);
    // rechts
    if (k != 7 && (g.getPiece(r, k+1) == nullptr || g.getPiece(r, k+1)->getKleur() != SchaakStuk::getKleur()))
        zetten.emplace_back(r, k+1);
    // rechts onder
    if (r != 7 && k != 7 && (g.getPiece(r+1, k+1) == nullptr || g.getPiece(r+1, k+1)->getKleur() != SchaakStuk::getKleur()))
        zetten.emplace_back(r+1, k+1);
    return zetten;
}

vector<pair<int, int>> Koningin::geldige_zetten(Game &g) {
    vector<pair<int, int>> zetten;
    pair<int, int> loc = SchaakStuk::getLocation(g);
    int r = loc.first;
    int k = loc.second;
    // up
    if (r != 0) {
        for (int i = r-1; i >= 0; i--) {
            if (g.getPiece(i, k) == nullptr) zetten.emplace_back(i, k);
            else if (g.getPiece(i, k)->getKleur() != SchaakStuk::getKleur()) {
                zetten.emplace_back(i, k);
                break;
            } else break;
        }
    }
    // down
    if (r != 7) {
        for (int i = r+1; i < 8; i++) {
            if (g.getPiece(i, k) == nullptr) zetten.emplace_back(i, k);
            else if (g.getPiece(i, k)->getKleur() != SchaakStuk::getKleur()) {
                zetten.emplace_back(i, k);
                break;
            } else break;
        }
    }
    // left
    if (k != 0) {
        for (int i = k-1; i >= 0; i--) {
            if (g.getPiece(r, i) == nullptr) zetten.emplace_back(r, i);
            else if (g.getPiece(r, i)->getKleur() != SchaakStuk::getKleur()) {
                zetten.emplace_back(r, i);
                break;
            } else break;
        }
    }
    // right
    if (k != 7) {
        for (int i = k+1; i < 8; i++) {
            if (g.getPiece(r, i) == nullptr) zetten.emplace_back(r, i);
            else if (g.getPiece(r, i)->getKleur() != SchaakStuk::getKleur()) {
                zetten.emplace_back(r, i);
                break;
            } else break;
        }
    }
    // left-up
    if (r != 0 && k != 0) {
        for (int i = 1; i < 7; i++) {
            if (r-i < 0 || k-i < 0) break;
            if (g.getPiece(r-i, k-i) == nullptr) zetten.emplace_back(r-i, k-i);
            else if (g.getPiece(r-i, k-i)->getKleur() != SchaakStuk::getKleur()) {
                zetten.emplace_back(r-i, k-i);
                break;
            } else break;
        }
    }
    // right-up
    if (r != 0 && k != 7) {
        for (int i = 1; i < 7; i++) {
            if (r-i < 0 || k+i > 7) break;
            if (g.getPiece(r-i, k+i) == nullptr) zetten.emplace_back(r-i, k+i);
            else if (g.getPiece(r-i, k+i)->getKleur() != SchaakStuk::getKleur()) {
                zetten.emplace_back(r-i, k+i);
                break;
            } else break;
        }
    }
    // left-down
    if (r != 7 && k != 0) {
        for (int i = 1; i < 7; i++) {
            if (r+i > 7 || k-i < 0) break;
            if (g.getPiece(r+i, k-i) == nullptr) zetten.emplace_back(r+i, k-i);
            else if (g.getPiece(r+i, k-i)->getKleur() != SchaakStuk::getKleur()) {
                zetten.emplace_back(r+i, k-i);
                break;
            } else break;
        }
    }
    // right-down
    if (r != 7 && k != 7) {
        for (int i = 1; i < 7; i++) {
            if (r+i > 7 || k+i > 7) break;
            if (g.getPiece(r+i, k+i) == nullptr) zetten.emplace_back(r+i, k+i);
            else if (g.getPiece(r+i, k+i)->getKleur() != SchaakStuk::getKleur()) {
                zetten.emplace_back(r+i, k+i);
                break;
            } else break;
        }
    }
    return zetten;
}


const char* Pion::type() const {
    if (SchaakStuk::getKleur() == wit) return "Pw";
    return "Pb";
}

const char* Toren::type() const {
    if (SchaakStuk::getKleur() == wit) return "Rw";
    return "Rb";
}

const char* Paard::type() const {
    if (SchaakStuk::getKleur() == wit) return "Hw";
    return "Hb";
}

const char* Loper::type() const {
    if (SchaakStuk::getKleur() == wit) return "Bw";
    return "Bb";
}

const char* Koning::type() const {
    if (SchaakStuk::getKleur() == wit) return "Kw";
    return "Kb";
}

const char* Koningin::type() const {
    if (SchaakStuk::getKleur() == wit) return "Qw";
    return "Qb";
}