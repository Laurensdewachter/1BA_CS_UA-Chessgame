//  Student: Laurens De Wachter
//  Rolnummer: r0214686

#ifndef SCHAKEN_SCHAAKSTUK_H
#define SCHAKEN_SCHAAKSTUK_H
#include <guicode/chessboard.h>
#include <utility>
using namespace std;

class Game;

enum zw{zwart,wit};

class SchaakStuk {
    zw kleur;
    bool hasMoved;
public:
    SchaakStuk(zw kleur): kleur(kleur), hasMoved(false) {}
    ~SchaakStuk() {}

    // Getters
    zw getKleur() const;
    pair<int, int> getLocation(Game &g) const;
    bool getMoved() const;
    void setMoved(bool m);

    virtual Piece piece() const=0;

    virtual vector<pair<int, int>> geldige_zetten(Game &g, bool intern = false) = 0;
    virtual const char* type() const = 0;   // https://www.geeksforgeeks.org/char-vs-stdstring-vs-char-c/
};

class Pion:public SchaakStuk {
public:
    Pion(zw kleur):SchaakStuk(kleur) {}
    virtual Piece piece() const override {
        return Piece(Piece::Pawn,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game &g, bool intern = false) override;
    const char* type() const;
};

class Toren:public SchaakStuk {
public:
    Toren(zw kleur):SchaakStuk(kleur) {}
    Piece piece() const override {
        return Piece(Piece::Rook,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game &g, bool intern = false) override;
    const char* type() const;
};

class Paard:public SchaakStuk {
public:
    Paard(zw kleur):SchaakStuk(kleur) {}
    Piece piece() const override {
        return Piece(Piece::Knight,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game &g, bool intern = false) override;
    const char* type() const;
};

class Loper:public SchaakStuk {
public:
    Loper(zw kleur):SchaakStuk(kleur) {}
    Piece piece() const override {
        return Piece(Piece::Bishop,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game &g, bool intern = false) override;
    const char* type() const;
};

class Koning:public SchaakStuk {
public:
    Koning(zw kleur):SchaakStuk(kleur) {}
    Piece piece() const override {
        return Piece(Piece::King,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game &g, bool intern = false) override;
    const char* type() const;
};

class Koningin:public SchaakStuk {
public:
    Koningin(zw kleur):SchaakStuk(kleur) {}
    Piece piece() const override {
        return Piece(Piece::Queen,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game &g, bool intern = false) override;
    const char* type() const;
};

#endif //SCHAKEN_SCHAAKSTUK_H
