//  Student: Laurens De Wachter
//  Rolnummer: r0214686

#ifndef SCHAKEN_GAME_H
#define SCHAKEN_GAME_H

#include <iostream>
#include <map>
#include "SchaakStuk.h"
using namespace std;

struct Log;

class Game {
// variabelen om de status van het spel/bord te bewaren
    map<int, SchaakStuk*> schaakbord;
    SchaakStuk* koningWit;
    SchaakStuk* koningZwart;
    zw aanBeurt;
    bool finished;
    int time;
    map<int, Log*> history;
    SchaakStuk* pionVoorEP;

    SchaakStuk* getKoning(zw kleur) const;

    bool schaak(zw kleur);
    bool schaakmat(zw kleur);
    bool pat(zw kleur);
    bool quickCheckSchaak(zw kleur, SchaakStuk* s, int r, int k);

    bool madePassantMove(pair<int, int> move, SchaakStuk* s);

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

    bool bedreigdVak(int r, int k, zw kleur);

    void logState();
    void goBack();
    void goForward();
    void deleteHistory();
};

struct Log {
    map<int, const char*> schaakbord;
    map<int, bool> eersteZetten;
    zw aanBeurt;
    int time;

    Log(map<int, SchaakStuk*> &s, zw b, int t);
    ~Log() = default;
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
