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

public:
    Game();
    ~Game();

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
};


#endif //SCHAKEN_GAME_H
