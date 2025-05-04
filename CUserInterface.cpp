#include <iostream>
using namespace std;
#include "CSudoku.cpp"
#include "CUndo.cpp"
#include "CFilemanager.cpp"
#pragma once

class CUserInterface: public CSudoku, public CUndoManager, public CFilemanager                                          // Vererbt von drei Klassen
{
    public:
    CUserInterface();
    void menue(int uebergebenesboard[9][9], CSudoku& spielfeld, CUndoManager& undoManager, CFilemanager& filemanager); // Menüfunktion mit Referenzen auf Spielfeld, Undo und Filemanager
};

CUserInterface::CUserInterface()
{}                                                                                                                      // Leerer Konstruktor

void CUserInterface::menue(int uebergebenesboard[9][9], CSudoku& spielfeld, CUndoManager& undoManager, CFilemanager& filemanager)
{
    int e;                                                                                                              // Menüauswahl
    bool running = true;                                                                                                // Steuert die Hauptschleife
    string datei = "data.txt";                                                                                          // Standard-Dateiname zum Speichern

    while(running)                                                                                                      // Hauptmenüschleife
    {
        cout << "Menue:" << endl;
        cout << " 1 - Datei laden\n 2 - Spiel anzeigen\n 3 - Spiel spielen\n 4 - Rückgängig machen" << endl;
        cout << " 5 - Spiel speichern \n 6 - löse Sudoku\n 7 - Beenden" << endl;

        if (!(cin >> e))                                                                                                // Ungültige Eingabe prüfen
        {
            cout << "Falsche Eingabe\n";
            cin.clear();                                                                                                // Fehlerstatus löschen
            cin.ignore(1000, '\n');                                                                                     // Eingabepuffer leeren
            continue;                                                                                                   // Zurück zum Menü
        }

        switch (e)                                                                                                      // Menüauswahl
        {
            case 1: 
                cout << "Wählen Sie einen Schwierigkeitsgrad: " << endl;
                cout << " 1 - Easy\n 2 - Medium\n 3 - Hard\n" << endl;
                if (!(cin >> e))                                                                                         // Eingabe prüfen
                {
                    cout << "Falsche Eingabe\n";
                    cin.clear();                                                                                        // Fehlerstatus löschen
                    cin.ignore(1000, '\n');                                                                             // Puffer leeren
                    continue;                                                                                           // Zurück zum Menü
                }

                try 
                {
                    filemanager.load(e, uebergebenesboard);                                                             // Lade Datei je nach Schwierigkeitsgrad
                    spielfeld.printBoard(uebergebenesboard);                                                            // Zeige geladenes Board
                }
                catch (const exception& e) 
                {
                    cerr << "FEHLER: " << e.what() << endl;                                                             // Fehlerausgabe
                }
                break;

            case 2:
                spielfeld.printBoard(uebergebenesboard);                                                                // Zeige aktuelles Board
                break;

            case 3:
                spielfeld.set_number(uebergebenesboard, undoManager);                                                   // Benutzer setzt Zahl
                spielfeld.printBoard(uebergebenesboard);                                                                // Zeige aktualisiertes Board
                break;

            case 4:
                try
                {
                    undoManager.undo(uebergebenesboard);                                                               // Rückgängig machen
                    spielfeld.printBoard(uebergebenesboard);                                                           // Zeige aktuelles Board
                }
                catch (const exception& e) 
                {
                    cerr << "FEHLER: " << e.what() << endl;                                                             // Fehlerausgabe
                }
                break;

            case 5:
                try
                {
                    undoManager.speichern(uebergebenesboard);                                                           // Zustand speichern
                    filemanager.save(datei, uebergebenesboard);                                                         // Board in Datei schreiben
                    spielfeld.printBoard(uebergebenesboard);                                                            // Zeige gespeichertes Board
                }
                catch (const exception& e)
                {
                    cerr << "FEHLER: " << e.what() << endl;                                                             // Fehlerausgabe
                }
                break;

            case 6: 
                spielfeld.solve(uebergebenesboard, 0, 0, undoManager);                                                  // Sudoku automatisch lösen
                system("cls");                                                                                          // Konsole leeren (Windows-spezifisch)
                spielfeld.printBoard(uebergebenesboard);                                                                // Lösung anzeigen
                break;

            case 7:
                cout << "Spiel beendet" << endl;                                                                        // Beenden
                running = false;                                                                                        // Schleife verlassen
                break;

            default:
                cout << "Falsche Eingabe!" << endl;                                                                     // Ungültige Menüwahl
                break;
        }
    }    
}
