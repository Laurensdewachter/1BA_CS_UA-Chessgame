//  Student: Laurens De Wachter
//  Rolnummer: r0214686

#ifndef SCHAKEN_GAME_H
#define SCHAKEN_GAME_H

#include <iostream>
#include <map>
#include "SchaakStuk.h"
using namespace std;

class Game {
// variabelen om de status van het spel/bord te bewaren
    map<int, SchaakStuk*> schaakbord;
    zw aanBeurt;
    SchaakStuk* koningWit;
    SchaakStuk* koningZwart;
    bool finished;

public:
    Game();
    ~Game();

    // Getters & setters
    void setStartBord();
    zw getBeurt() const;
    void setBeurt(zw kleur);
    bool getFinished() const;
    void setFinished(bool f);
    SchaakStuk* getPiece(int r, int k);
    void setPiece(int r, int k, SchaakStuk* s);
    vector<SchaakStuk*> getPieces(zw kleur);
    void setKoning(zw kleur, SchaakStuk* koning);

    void clearBord();

    bool move(SchaakStuk* s,int r, int k);
    void changeBeurt();

    bool schaak(zw kleur);
    bool schaakmat(zw kleur);
    bool pat(zw kleur);
    bool quickCheckSchaak(zw kleur, SchaakStuk* s, int r, int k);

    bool bedreigdVak(int r, int k, zw kleur);
};

class schaakError : public exception {
public:
    schaakError() {}
};

class schaakMatError : public exception {
    zw winner;
public:
    schaakMatError(zw k) : winner(k) {}
    zw getWinner() const {return winner;}
};

class patError : public exception {
public:
    patError() {}
};

class verplaatsingsError : public exception {
public:
    verplaatsingsError() {}
};


#endif //SCHAKEN_GAME_H
