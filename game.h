//  Student: Laurens De Wachter
//  Rolnummer: r0214686

#ifndef SCHAKEN_GAME_H
#define SCHAKEN_GAME_H

#include <iostream>
#include <map>
#include "SchaakStuk.h"
using namespace std;

struct log;

class Game {
// variabelen om de status van het spel/bord te bewaren
    map<int, SchaakStuk*> schaakbord;
    SchaakStuk* koningWit;
    SchaakStuk* koningZwart;
    zw aanBeurt;
    bool finished;
    int time;
    map<int, log*> history;
    SchaakStuk* pionVoorEP;

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
    SchaakStuk* getPionVoorEP();

    void clearBord();

    bool move(SchaakStuk* s,int r, int k);
    void changeBeurt();

    bool schaak(zw kleur);
    bool schaakmat(zw kleur);
    bool pat(zw kleur);
    bool quickCheckSchaak(zw kleur, SchaakStuk* s, int r, int k);

    bool bedreigdVak(int r, int k, zw kleur);

    void logState();
    void goBack();
    void goForward();
    void deleteHistory();
};

struct log {
    map<int, SchaakStuk*> schaakbord;
    zw aanBeurt;
    int time;

    log(map<int, SchaakStuk*> s, zw b, int t) : schaakbord(s), aanBeurt(b), time(t) {}
    ~log() = default;
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

class undoRedoError : public exception {
public:
    undoRedoError() {}
};

#endif //SCHAKEN_GAME_H
