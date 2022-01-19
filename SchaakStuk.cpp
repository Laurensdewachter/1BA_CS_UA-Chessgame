//  Student: Laurens De Wachter
//  Rolnummer: r0214686

#include "SchaakStuk.h"
#include "game.h"

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

vector<pair<int, int>> Pion::geldige_zetten(Game &g) {
    vector<pair<int, int>> zetten;
    pair<int, int> loc = SchaakStuk::getLocation(g);
    int r = loc.first;
    int k = loc.second;
    pair<int, int> move;
    // onderscheid maken tussen zwart en wit
    if (SchaakStuk::getKleur() == wit) {
        // nakijken of de plaats voor de pion vrij is
        if (g.getPiece(r-1, k) == nullptr) {
            move.first = r - 1;
            move.second = k;
            zetten.push_back(move);
        }
        // nakijken of er een stuk schuin links voor de pion staat
        if (k > 0 && g.getPiece(r-1, k-1) != nullptr) {
            move.first = r-1;
            move.second = k-1;
            zetten.push_back(move);
        }
        // nakijken of er een stuk schuin rechts voor de pion staat
        if (k < 7 && g.getPiece(r-1, k+1) != nullptr) {
            move.first = r-1;
            move.second = k+1;
            zetten.push_back(move);
        }
        if (r == 6 && g.getPiece(r-2, k) == nullptr) {
            move.first = r-2;
            move.second = k;
            zetten.push_back(move);
        }
    } else {
        // nakijken of de plaats voor de pion vrij is
        if (g.getPiece(r+1, k) == nullptr) {
            move.first = r+1;
            move.second = k;
            zetten.push_back(move);
        }
        // nakijken of er een stuk schuin links voor de pion staat
        if (k > 0 && g.getPiece(r+1, k-1) != nullptr) {
            move.first = r+1;
            move.second = k-1;
            zetten.push_back(move);
        }
        // nakijken of er een stuk schuin rechts voor de pion staat
        if (k < 7 && g.getPiece(r+1, k+1) != nullptr) {
            move.first = r+1;
            move.second = k+1;
            zetten.push_back(move);
        }
        if (r == 1 && g.getPiece(r+2, k) == nullptr) {
            move.first = r+2;
            move.second = k;
            zetten.push_back(move);
        }
    }
    return zetten;
}

vector <pair<int, int>> Toren::geldige_zetten(Game &g) {
    vector<pair<int, int>> zetten;
    pair<int, int> loc = SchaakStuk::getLocation(g);
    int r = loc.first;
    int k = loc.second;
    pair<int, int> move;
    // stap naar onder op het bord
    if (r != 7) {
        for (int i = r+1; i <= 7; i++) {
            if (g.getPiece(i, k) == nullptr) {
                move.first = i;
                move.second = k;
                zetten.push_back(move);
            } else {
                if (g.getPiece(i, k)->getKleur() != SchaakStuk::getKleur()) {
                    move.first = i;
                    move.second = k;
                    zetten.push_back(move);
                }
                break;
            }
        }
    }
    // stap naar boven op het bord
    if (r != 0) {
        for (int i = r-1; i >= 0 ; i--) {
            if (g.getPiece(i, k) == nullptr) {
                move.first = i;
                move.second = k;
                zetten.push_back(move);
            } else {
                if (g.getPiece(i, k)->getKleur() != SchaakStuk::getKleur()) {
                    pair<int, int> up;
                    up.first = i;
                    up.second = k;
                    zetten.push_back(up);
                }
                break;
            }
        }
    }
    // stap naar links
    if (k != 0) {
        for (int i = k-1; i >= 0; i--) {
            if (g.getPiece(r, i) == nullptr) {
                move.first = r;
                move.second = i;
                zetten.push_back(move);
            } else {
                if (g.getPiece(r, i)->getKleur() != SchaakStuk::getKleur()) {
                    move.first = r;
                    move.second = i;
                    zetten.push_back(move);
                }
                break;
            }
        }
    }
    // stap naar rechts;
    if (k != 7) {
        for (int i = k+1; i <= 7; i++) {
            if (g.getPiece(r, i) == nullptr) {
                move.first = r;
                move.second = i;
                zetten.push_back(move);
            } else {
                if (g.getPiece(r, i)->getKleur() != SchaakStuk::getKleur()) {
                    move.first = r;
                    move.second = i;
                    zetten.push_back(move);
                }
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
    pair<int, int> move;
    // up-left
    if (r > 1 && k > 0 && (g.getPiece(r-2, k-1) == nullptr || g.getPiece(r-2, k-1)->getKleur() != SchaakStuk::getKleur())) {
        move.first = r-2;
        move.second = k-1;
        zetten.push_back(move);
    }
    // up-right
    if (r > 1 && k < 7 && (g.getPiece(r-2, k+1) == nullptr || g.getPiece(r-2, k+1)->getKleur() != SchaakStuk::getKleur())) {
        move.first = r-2;
        move.second = k+1;
        zetten.push_back(move);
    }
    // left-up
    if (r > 0 && k > 1 && (g.getPiece(r-1, k-2) == nullptr || g.getPiece(r-1, k-2)->getKleur() != SchaakStuk::getKleur())) {
        move.first = r-1;
        move.second = k-2;
        zetten.push_back(move);
    }
    // right-up
    if (r > 0 && k < 6 && (g.getPiece(r-1, k+2) == nullptr || g.getPiece(r-1, k+2)->getKleur() != SchaakStuk::getKleur())) {
        move.first = r-1;
        move.second = k+2;
        zetten.push_back(move);
    }
    // down-left
    if (r < 6 && k > 0 && (g.getPiece(r+2, k-1) == nullptr || g.getPiece(r+2, k-1)->getKleur() != SchaakStuk::getKleur())) {
        move.first = r+2;
        move.second = k-1;
        zetten.push_back(move);
    }
    // down-right
    if (r < 6 && k < 7 && (g.getPiece(r+2, k+1) == nullptr || g.getPiece(r+2, k+1)->getKleur() != SchaakStuk::getKleur())) {
        move.first = r+2;
        move.second = k+1;
        zetten.push_back(move);
    }
    // left-down
    if (r < 7 && k > 1 && (g.getPiece(r+1, k-2) == nullptr || g.getPiece(r+1, k-2)->getKleur() != SchaakStuk::getKleur())) {
        move.first = r+1;
        move.second = k-2;
        zetten.push_back(move);
    }
    // right-down
    if (r < 7 && k < 6 && (g.getPiece(r+1, k+2) == nullptr || g.getPiece(r+1, k+2)->getKleur() != SchaakStuk::getKleur())) {
        move.first = r+1;
        move.second = k+2;
        zetten.push_back(move);
    }
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
            if (g.getPiece(r-i, k-i) == nullptr) {
                pair<int, int> new_loc;
                new_loc.first = r-i;
                new_loc.second = k-i;
                zetten.push_back(new_loc);
            } else if (g.getPiece(r-i, k-i)->getKleur() != SchaakStuk::getKleur()) {
                pair<int, int> new_loc;
                new_loc.first = r-i;
                new_loc.second = k-i;
                zetten.push_back(new_loc);
                break;
            } else break;
        }
    }
    // right-up
    if (r != 0 || k != 7) {
        for (int i = 1; i <= 7; i++) {
            if (r-i < 0 || k+i > 7) break;
            if (g.getPiece(r-i, k+i) == nullptr) {
                pair<int, int> new_loc;
                new_loc.first = r-i;
                new_loc.second = k+i;
                zetten.push_back(new_loc);
            } else if (g.getPiece(r-i, k+i)->getKleur() != SchaakStuk::getKleur()) {
                pair<int, int> new_loc;
                new_loc.first = r-i;
                new_loc.second = k+i;
                zetten.push_back(new_loc);
                break;
            } else break;
        }
    }
    // left-down
    if (r != 7 || k != 0) {
        for (int i = 1; i <= 7; i++) {
            if (r+i > 7 || k-i < 0) break;
            if (g.getPiece(r+i, k-i) == nullptr) {
                pair<int, int> new_loc;
                new_loc.first = r+i;
                new_loc.second = k-i;
                zetten.push_back(new_loc);
            } else if (g.getPiece(r+i, k-i)->getKleur() != SchaakStuk::getKleur()) {
                pair<int, int> new_loc;
                new_loc.first = r+i;
                new_loc.second = k-i;
                zetten.push_back(new_loc);
                break;
            } else break;
        }
    }
    // right-down
    if (r != 0 || k != 0) {
        for (int i = 1; i <= 7; i++) {
            if (r+i > 7 || k+i > 7) break;
            if (g.getPiece(r+i, k+i) == nullptr) {
                pair<int, int> new_loc;
                new_loc.first = r+i;
                new_loc.second = k+i;
                zetten.push_back(new_loc);
            } else if (g.getPiece(r+i, k+i)->getKleur() != SchaakStuk::getKleur()) {
                pair<int, int> new_loc;
                new_loc.first = r+i;
                new_loc.second = k+i;
                zetten.push_back(new_loc);
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
    if (0 < r && r < 7 && 0 < k && k < 7) {
        pair<int,int> new_loc;
        new_loc.first = r+1;
        new_loc.second = k;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r+1;
        new_loc.second = k-1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r;
        new_loc.second = k-1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r-1;
        new_loc.second = k-1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r-1;
        new_loc.second = k;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r-1;
        new_loc.second = k+1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r;
        new_loc.second = k+1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r+1;
        new_loc.second = k+1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
    } else if (r == 0 && k == 0) {
        pair<int,int> new_loc;
        new_loc.first = 0;
        new_loc.second = 1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = 1;
        new_loc.second = 1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = 1;
        new_loc.second = 0;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
    } else if (r == 0 && k == 7) {
        pair<int,int> new_loc;
        new_loc.first = 0;
        new_loc.second = 6;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = 1;
        new_loc.second = 6;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = 1;
        new_loc.second = 7;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
    } else if (r == 7 && k == 0) {
        pair<int,int> new_loc;
        new_loc.first = 6;
        new_loc.second = 0;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = 6;
        new_loc.second = 1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = 7;
        new_loc.second = 1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
    } else if (r == 7 && k == 7) {
        pair<int,int> new_loc;
        new_loc.first = 7;
        new_loc.second = 6;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = 6;
        new_loc.second = 6;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = 6;
        new_loc.second = 7                                                                                                                                        ;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
    } else if (r > 0 && r < 7 && k == 0) {
        pair<int, int> new_loc;
        new_loc.first = r-1;
        new_loc.second = k;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r-1;
        new_loc.second = k+1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r;
        new_loc.second = k+1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r+1;
        new_loc.second = k+1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r+1;
        new_loc.second = k;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
    } else if (r > 0 && r < 7 && k == 7) {
        pair<int, int> new_loc;
        new_loc.first = r-1;
        new_loc.second = k;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r-1;
        new_loc.second = k-1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r;
        new_loc.second = k-1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r+1;
        new_loc.second = k-1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r+1;
        new_loc.second = k;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
    } else if (r == 0 && k > 0 && k < 7) {
        pair<int, int> new_loc;
        new_loc.first = r;
        new_loc.second = k-1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r+1;
        new_loc.second = k-1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r+1;
        new_loc.second = k;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r+1;
        new_loc.second = k+1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r;
        new_loc.second = k+1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
    } else if (r == 7 && k > 0 && k < 7) {
        pair<int, int> new_loc;
        new_loc.first = r;
        new_loc.second = k-1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r-1;
        new_loc.second = k-1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r-1;
        new_loc.second = k;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r-1;
        new_loc.second = k+1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
        new_loc.first = r;
        new_loc.second = k+1;
        if (g.getPiece(new_loc.first, new_loc.second) == nullptr || g.getPiece(new_loc.first, new_loc.second)->getKleur() != SchaakStuk::getKleur()) zetten.push_back(new_loc);
    }
    return zetten;
}

vector<pair<int, int>> Koningin::geldige_zetten(Game &g) {
    vector<pair<int, int>> zetten;
    pair<int, int> loc = SchaakStuk::getLocation(g);
    int r = loc.first;
    int k = loc.second;
    pair<int, int> move;
    // up
    if (r != 0) {
        for (int i = r-1; i >= 0; i--) {
            if (g.getPiece(i, k) == nullptr) {
                move.first = i;
                move.second = k;
                zetten.push_back(move);
            } else if (g.getPiece(i, k)->getKleur() != SchaakStuk::getKleur()) {
                move.first = i;
                move.second = k;
                zetten.push_back(move);
                break;
            } else break;
        }
    }
    // down
    if (r != 7) {
        for (int i = r+1; i < 8; i++) {
            if (g.getPiece(i, k) == nullptr) {
                move.first = i;
                move.second = k;
                zetten.push_back(move);
            } else if (g.getPiece(i, k)->getKleur() != SchaakStuk::getKleur()) {
                move.first = i;
                move.second = k;
                zetten.push_back(move);
                break;
            } else break;
        }
    }
    // left
    if (k != 0) {
        for (int i = k-1; i >= 0; i--) {
            if (g.getPiece(r, i) == nullptr) {
                move.first = r;
                move.second = i;
                zetten.push_back(move);
            } else if (g.getPiece(r, i)->getKleur() != SchaakStuk::getKleur()) {
                move.first = r;
                move.second = i;
                zetten.push_back(move);
                break;
            } else break;
        }
    }
    // right
    if (k != 7) {
        for (int i = k+1; i < 8; i++) {
            if (g.getPiece(r, i) == nullptr) {
                move.first = r;
                move.second = i;
                zetten.push_back(move);
            } else if (g.getPiece(r, i)->getKleur() != SchaakStuk::getKleur()) {
                move.first = r;
                move.second = i;
                zetten.push_back(move);
                break;
            } else break;
        }
    }
    // left-up
    if (r != 0 && k != 0) {
        for (int i = 1; i < 7; i++) {
            move.first = r - i;
            move.second = k - i;
            if (move.first < 0 || move.second < 0) break;
            if (g.getPiece(move.first, move.second) == nullptr) zetten.push_back(move);
            else if (g.getPiece(move.first, move.second)->getKleur() != SchaakStuk::getKleur()) {
                zetten.push_back(move);
                break;
            } else break;
        }
    }
    // right-up
    if (r != 0 && k != 7) {
        for (int i = 1; i < 7; i++) {
            move.first = r - i;
            move.second = k + i;
            if (move.first < 0 || move.second > 7) break;
            if (g.getPiece(move.first, move.second) == nullptr) zetten.push_back(move);
            else if (g.getPiece(move.first, move.second)->getKleur() != SchaakStuk::getKleur()) {
                zetten.push_back(move);
                break;
            } else break;
        }
    }
    // left-down
    if (r != 7 && k != 0) {
        for (int i = 1; i < 7; i++) {
            move.first = r + i;
            move.second = k - i;
            if (move.first > 7 || move.second < 0) break;
            if (g.getPiece(move.first, move.second) == nullptr) zetten.push_back(move);
            else if (g.getPiece(move.first, move.second)->getKleur() != SchaakStuk::getKleur()) {
                zetten.push_back(move);
                break;
            } else break;
        }
    }
    // right-down
    if (r != 7 && k != 7) {
        for (int i = 1; i < 7; i++) {
            move.first = r + i;
            move.second = k + i;
            if (move.first < 0 || move.second < 0) break;
            if (g.getPiece(move.first, move.second) == nullptr) zetten.push_back(move);
            else if (g.getPiece(move.first, move.second)->getKleur() != SchaakStuk::getKleur()) {
                zetten.push_back(move);
                break;
            } else break;
        }
    }
    return zetten;
}

char* Pion::type() const {
    if (SchaakStuk::getKleur() == wit) return "Pw";
    return "Pb";
}

char* Toren::type() const {
    if (SchaakStuk::getKleur() == wit) return "Rw";
    return "Rb";
}

char* Paard::type() const {
    if (SchaakStuk::getKleur() == wit) return "Hw";
    return "Hb";
}

char* Loper::type() const {
    if (SchaakStuk::getKleur() == wit) return "Bw";
    return "Bb";
}

char* Koning::type() const {
    if (SchaakStuk::getKleur() == wit) return "Kw";
    return "Kb";
}

char* Koningin::type() const {
    if (SchaakStuk::getKleur() == wit) return "Qw";
    return "Qb";
}