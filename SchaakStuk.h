//  Student: Laurens De Wachter
//  Rolnummer: r0214686
//  Opmerkingen:
//

#ifndef SCHAKEN_SCHAAKSTUK_H
#define SCHAKEN_SCHAAKSTUK_H
#include <guicode/chessboard.h>
#include <utility>
using namespace std;

class Game;

enum zw{zwart,wit};

class SchaakStuk {zw kleur;
protected:
    bool eersteZet;
public:
    SchaakStuk(zw kleur): kleur(kleur), eersteZet(true) {}
    ~SchaakStuk() {}

    void setEersteZet() {eersteZet = false;}

    virtual Piece piece() const=0;      // Verander deze functie niet!
                                        // Deze functie wordt gebruikt door
                                        // setItem(x,y,SchaakStuk*) van
                                        // SchaakGUI

    zw getKleur() const { return kleur; }

    virtual vector<pair<int, int>> geldige_zetten(Game &g) = 0;

    pair<int, int> getLocation(Game &g) const;
};

class Pion:public SchaakStuk {
public:
    Pion(zw kleur):SchaakStuk(kleur) {}
    virtual Piece piece() const override {
        return Piece(Piece::Pawn,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game &g) override;
};

class Toren:public SchaakStuk {
public:
    Toren(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Rook,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game &g) override;
};

class Paard:public SchaakStuk {
public:
    Paard(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Knight,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game &g) override;
};

class Loper:public SchaakStuk {
public:
    Loper(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Bishop,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game &g) override;
};

class Koning:public SchaakStuk {
public:
    Koning(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::King,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game &g) override;
};

class Koningin:public SchaakStuk {
public:
    Koningin(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Queen,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game &g) override;
};

#endif //SCHAKEN_SCHAAKSTUK_H
