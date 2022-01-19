//  Student: Laurens De Wachter
//  Rolnummer: r0214686

#ifndef SCHAKEN_SCHAAKGUI_H
#define SCHAKEN_SCHAAKGUI_H

#include "guicode/ChessWindow.h"
#include "SchaakStuk.h"
#include <QMessageBox>
#include <QAction>
#include <sstream>

class SchaakGUI:public ChessWindow {
public:
    SchaakGUI();

    void update();

private:
    Game g;
    bool firstClick;
    SchaakStuk* selectedPiece;
    pair<int, int> selectedTile;
    vector<pair<int, int>> focusedTiles;
    vector<pair<int, int>> threatenedPieces;
    vector<pair<int, int>> threatenedTiles;

    void clearTiles();

    void clicked(int x, int y) override;
    void newGame() override;
    void open() override;
    void save() override;
    void undo() override;
    void redo() override;
    void visualizationChange() override;

/*  Overgeerfde functies van ChessWindow:

    void removeAllMarking();
    void clearBoard();
    void setItem(int i,int j,SchaakStuk* p);
    void setPieceThreat(int i,int j,bool b);
    void removeAllPieceThreats();
    void setTileSelect(int i,int j,bool b);
    void setTileFocus(int i,int j,bool b);
    void setTileThreat(int i,int j,bool b);

    bool displayKills();
    bool displayMoves();
    bool displayThreats();
*/
};


#endif //SCHAKEN_SCHAAKGUI_H
