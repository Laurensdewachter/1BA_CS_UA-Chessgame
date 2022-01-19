//  Student: Laurens De Wachter
//  Rolnummer: r0214686
//  Opmerkingen:
//

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

    bool getFinished() const {return finished;}
    void setFinished() {finished = true;}

    bool move(SchaakStuk* s,int r, int k); // Verplaats stuk s naar rij r en kolom k

    bool schaak(zw kleur);
    bool schaakmat(zw kleur);
    bool pat(zw kleur);
    void setStartBord();

    SchaakStuk* getPiece(int r, int k);
    void setPiece(int r, int k, SchaakStuk* s);

    zw getBeurt() const {return aanBeurt;}
    void changeBeurt();

    vector<SchaakStuk*> getPieces(zw kleur);
    bool quickCheckSchaak(zw kleur, SchaakStuk* s, int r, int k);
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
