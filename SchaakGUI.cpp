//  Student: Laurens De Wachter
//  Rolnummer: r0214686

#include "SchaakGUI.h"
#include "guicode/message.h"
#include "guicode/fileIO.h"

// Constructor
SchaakGUI::SchaakGUI():ChessWindow(nullptr), firstClick(true) {
    g.setStartBord();
    SchaakGUI::update();
}


// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom
void SchaakGUI::clicked(int r, int k) {
    if (g.getFinished()) return;
    if (firstClick) {
        if (g.getPiece(r, k) != nullptr && g.getPiece(r, k)->getKleur() == g.getBeurt()) {
            selectedPiece = g.getPiece(r, k);
            selectedTile = {r, k};
            SchaakGUI::setTileSelect(r, k, true);
            for (auto i : selectedPiece->geldige_zetten(g)) {
                if (g.getPiece(i.first, i.second) == nullptr) {
                    SchaakGUI::setTileFocus(i.first, i.second, true);
                    focusedTiles.push_back(i);
                } else {
                    setPieceThreat(i.first, i.second, true);
                    threatenedPieces.push_back(i);
                }
            }
            firstClick = false;
        }
    } else {
        pair<int, int> temp = {r, k};
        if (temp != selectedPiece->getLocation(g)) {
            try {
                g.move(selectedPiece, r, k);
            } catch (schaakError& e) {
                message("Deze zet is ongeldig");
                return;
            } catch (schaakMatError& e) {
                SchaakGUI::update();
                if (e.getWinner() == wit) message("Schaakmat! Wit heeft gewonnen");
                else message("Schaakmat! Zwart heeft gewonnen");
                g.setFinished();
                SchaakGUI::clearTiles();
                return;
            } catch (verplaatsingsError& e) {return;}
            catch (patError& e) {
                SchaakGUI::update();
                message("Gelijkspel!");
                SchaakGUI::clearTiles();
                g.setFinished();
            }
            g.changeBeurt();
        }
        SchaakGUI::clearTiles();
        firstClick = true;
    }
    SchaakGUI::update();
}

void SchaakGUI::clearTiles() {
    SchaakGUI::setTileSelect(selectedTile.first, selectedTile.second, false);
    for (auto i : focusedTiles) SchaakGUI::setTileFocus(i.first, i.second, false);
    for (auto i : threatenedPieces) SchaakGUI::setPieceThreat(i.first, i.second, false);
    for (auto i : threatenedTiles) SchaakGUI::setTileThreat(i.first, i.second, false);
}

void SchaakGUI::newGame()
{}


void SchaakGUI::save() {
    QFile file;
    if (openFileToWrite(file)) {
        QDataStream out(&file);
        if (g.getBeurt() == wit) out << QString("w");
        else out << QString("b");
        for (int r = 0; r < 8; r++) {
            for (int k = 0; k < 8; k++) {
                SchaakStuk* piece = g.getPiece(r, k);
                if (piece == nullptr) out << QString(".");
                else out << QString(piece->type());
            }
        }
    }
}

void SchaakGUI::open() {
    QFile file;
    if (openFileToRead(file)) {
        try {
            QDataStream in(&file);
            QString debugstring;
            QString turn;
            in >> turn;
            for (int r = 0; r < 8; r++) {
                for (int k = 0; k < 8; k++) {
                    QString piece;
                    in >> piece;
                    debugstring += "\t" + piece;
                    if (in.status() != QDataStream::Ok) {
                        throw QString("Invalid File Format");
                    }
                }
                debugstring += "\n";
            }
            if (turn == "w") g.setBeurt(wit);
            else g.setBeurt(zwart);
            g.clearBord();
            for (int r = 0; r < 8; r++) {
                for (int k = 0; k < 8; k++) {
                    debugstring.remove(0, 1);
                    QChar front = debugstring.front();
                    debugstring.remove(0, 1);
                    QChar colour;
                    zw kleur;
                    if (front != ".") {
                        colour = debugstring.front();
                        debugstring.remove(0, 1);
                        if (colour == "w") kleur = wit;
                        else kleur = zwart;
                    } else {
                        g.setPiece(r, k, nullptr);
                    }
                    if (front == "P") g.setPiece(r, k, new Pion(kleur));
                    else if (front == "R") g.setPiece(r, k, new Toren(kleur));
                    else if (front == "H") g.setPiece(r, k, new Paard(kleur));
                    else if (front == "B") g.setPiece(r, k, new Loper(kleur));
                    else if (front == "K") {
                        Koning* koning = new Koning(kleur);
                        g.setPiece(r, k, koning);
                        g.setKoning(kleur, koning);
                    }
                    else if (front == "Q") g.setPiece(r, k, new Koningin(kleur));
                }
                debugstring.remove(0, 1);
            }
        } catch (QString& Q) {
            message(Q);
        }
    }
    update();
    if (g.getBeurt() == wit) message("Wit is aan beurt");
    else message("Zwart is aan beurt");
}


void SchaakGUI::undo() {
    message("Je hebt undo gekozen");
}

void SchaakGUI::redo() {}


void SchaakGUI::visualizationChange() {
    QString visstring = QString(displayMoves()?"T":"F")+(displayKills()?"T":"F")+(displayThreats()?"T":"F");
    message(QString("Visualization changed : ")+visstring);
}


// Update de inhoud van de grafische weergave van het schaakbord (scene)
// en maak het consistent met de game state in variabele g.
void SchaakGUI::update() {
    SchaakGUI::clearBoard();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (g.getPiece(i, j) != nullptr) SchaakGUI::setItem(i, j, g.getPiece(i, j));
        }
    }
}

