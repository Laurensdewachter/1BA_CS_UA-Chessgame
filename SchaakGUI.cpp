//  Student: Laurens De Wachter
//  Rolnummer: r0214686

#include "SchaakGUI.h"
#include "guicode/message.h"
#include "guicode/fileIO.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// Constructor
SchaakGUI::SchaakGUI():ChessWindow(nullptr), firstClick(true), promotie(false), AIOn(true) {SchaakGUI::update();}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

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

// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom
void SchaakGUI::clicked(int r, int k) {
    if (g.getFinished()) return;
    if (promotie) {
        if ((promotieKleur == wit && r == 4 && (k == 2 || k == 3 || k == 4 || k == 5))
        || (promotieKleur == zwart && r == 3 && (k == 2 || k == 3 || k == 4 || k == 5))) {
            g.promotie(k);
            update();
            g.changeBeurt();
            promotie = false;
            if (AIOn) g.AIMove();
            firstClick = true;
        } else return;
    }
    if (firstClick) {
        // nakijken of het aangeklikte vak een stuk van de juiste kleur bevat
        if (g.getPiece(r, k) != nullptr && g.getPiece(r, k)->getKleur() == g.getBeurt()) {
            selectedPiece = g.getPiece(r, k);
            SchaakGUI::visualize(r, k, selectedPiece);
            firstClick = false;
        }
    }
    else {
        pair<int, int> temp = {r, k};
        // kijken of het aangeklikte cak niet hetzelfde vak is als bij de eerste klik
        if (temp != selectedPiece->getLocation(g)) {
            // als een ander stuk (van de kleur) die aan de beurt is wordt aangeklikt, dan wordt dat stuk het
            // geselecteerde stuk
            if (g.getPiece(r, k) != nullptr && g.getPiece(r, k)->getKleur() == g.getBeurt()) {
                selectedPiece = g.getPiece(r, k);
                SchaakGUI::visualize(r, k, selectedPiece);
                return;
            }
            // probeer het stuk te verplaatsen
            try {g.move(selectedPiece, r, k);}
            // de speler zet zichzelf schaak of laat zichzelf schaak staan
            catch (schaakError& e) {
                return;
            }
            // schaakmat: het spel is gedaan
            catch (schaakMatError& e) {
                SchaakGUI::update();
                SchaakGUI::removeAllMarking();
                if (e.getWinner() == wit) {
                    message("Schaakmat! Wit heeft gewonnen");
                }
                else {
                    message("Schaakmat! Zwart heeft gewonnen");
                }
                return;
            }
            // gelijkspel
            catch (patError& e) {
                SchaakGUI::update();
                SchaakGUI::removeAllMarking();
                message("Gelijkspel!");
            }
            // de zet zorgt ervoor dat een van hun pionnen gepromoveerd kan worden
            catch (promotieError& e) {
                if (e.what() == zwart && AIOn) {
                    g.promotie(5);
                    SchaakGUI::update();
                }
                promotieKleur = e.what();
                promotie = true;
                SchaakGUI::update();
                SchaakGUI::removeAllMarking();
                return;
            }
            // het aangeklikte vak is geen geldige zet
            catch (verplaatsingsError& e) {
                SchaakGUI::removeAllMarking();
                firstClick = true;
                return;
            }

            // als de AI aan staat maakt de AI een zet
            if (AIOn && not g.getFinished()) {
                try {g.AIMove();}
                catch (schaakMatError& e) {
                    SchaakGUI::update();
                    SchaakGUI::removeAllMarking();
                    if (e.getWinner() == wit) {
                        message("Schaakmat! Wit heeft gewonnen");
                    }
                    else {
                        message("Schaakmat! Zwart heeft gewonnen");
                    }
                    return;
                }
                catch (patError& e) {
                    SchaakGUI::update();
                    SchaakGUI::removeAllMarking();
                    message("Gelijkspel!");
                }
                catch (promotieError& e) {
                    if (e.what() == zwart) {
                        g.promotie(5);
                        SchaakGUI::update();
                    }
                    promotieKleur = e.what();
                    promotie = true;
                    SchaakGUI::update();
                    SchaakGUI::removeAllMarking();
                    return;
                }
            }
            // als de AI niet aanstaat, wordt de kleur die aan beurt is verwisselt
            else g.changeBeurt();
        }
        SchaakGUI::removeAllMarking();
        firstClick = true;
    }
    SchaakGUI::update();
}

// Kleurt de juiste vakken en stukken op het bord
void SchaakGUI::visualize(int r, int k, SchaakStuk* s) {
    SchaakGUI::removeAllMarking();
    selectedTile = {r, k};
    SchaakGUI::setTileSelect(r, k, true);
    for (auto i : selectedPiece->geldige_zetten(g)) {
        if (SchaakGUI::displayMoves() && g.getPiece(i.first, i.second) == nullptr) {
            SchaakGUI::setTileFocus(i.first, i.second, true);
            focusedTiles.push_back(i);
        } if (SchaakGUI::displayKills() && g.getPiece(i.first, i.second) != nullptr) {
            setPieceThreat(i.first, i.second, true);
            threatenedPieces.push_back(i);
        } if (SchaakGUI::displayThreats() && g.bedreigdVak(i.first, i.second, s->getKleur())) {
            SchaakGUI::setTileFocus(i.first, i.second, true);
            SchaakGUI::setTileThreat(i.first, i.second, true);
            threatenedTiles.push_back(i);
        }
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void SchaakGUI::newGame() {
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Nieuw spel"),
                                                  tr("Bent u zeker dat u een nieuw spel wilt starten?\nNiet opgeslagen wijzigingen gaan verloren."))) {
        g.deleteHistory();
        g.clearBord();
        g.setStartBord();
        g.setFinished(false);
        firstClick = true;
        SchaakGUI::removeAllMarking();
        SchaakGUI::update();
    }
}

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
    g.setFinished(false);
    g.deleteHistory();
    g.logState();
    if (g.getBeurt() == wit) message("Wit is aan beurt");
    else message("Zwart is aan beurt");
}

void SchaakGUI::undo() {
    try {
        g.goBack(AIOn);
    } catch (undoRedoError& e) {return;}
    firstClick = true;
    SchaakGUI::update();
    SchaakGUI::removeAllMarking();
}

void SchaakGUI::redo() {
    try {
        g.goForward(AIOn);
    } catch (undoRedoError& e) {return;}
    firstClick = true;
    SchaakGUI::update();
    SchaakGUI::removeAllMarking();
}


void SchaakGUI::visualizationChange() {SchaakGUI::visualize(selectedTile.first, selectedTile.second, selectedPiece);}

void SchaakGUI::AIChange() {
    if (SchaakGUI::AIPlayer()) AIOn = true;
    else AIOn = false;
}