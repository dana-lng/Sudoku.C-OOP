#include <iostream>
using namespace std;
#include "CSudoku.cpp"
#include "CUndo.cpp"
#include "CFilemanager.cpp"
#pragma once

class CUserInterface: public CSudoku, public CUndoManager, public CFilemanager
{
    public:
    CUserInterface();
    void menue(int uebergebenesboard[9][9], CSudoku& spielfeld, CUndoManager& undomanager, CFilemanager& filemanager);
};

CUserInterface::CUserInterface()
{

}

void CUserInterface::menue(int uebergebenesboard[9][9], CSudoku& spielfeld, CUndoManager& undomanager, CFilemanager& filemanger)
{
    int e;
    bool running = true;
    string datei = "data.txt";
  
    while(running)
    {
        cout << "Menue:" << endl;
        cout << " 1 - Datei laden\n 2 - Spiel anzeigen\n 3 - Spiel spielen\n 4 - Rückgängig machen" << endl;
        cout << " 5 - Spiel speichern \n 6 - löse Sudoku\n 7 - Beenden" << endl;

        if (!(cin >> e)) // Überprüft, ob die Eingabe eine gültige Zahl ist
        {
            cout << "Falsche Eingabe\n";
            cin.clear();              // Eingabefehler zurücksetzen
            cin.ignore(1000, '\n');   // Eingabepuffer leeren
            continue; // Zurück zum Menü
        }


        switch (e)
        {
            case 1: 
                cout << "Wählen Sie einen Schwierigkeitsgrad: " << endl;
                cout << " 1 - Easy\n 2 - Medium\n 3 - Hard\n 4 - Zufall" << endl;
                if (!(cin >> e)) // Überprüft, ob die Eingabe eine gültige Zahl ist
                {
                    cout << "Falsche Eingabe\n";
                    cin.clear();              // Eingabefehler zurücksetzen
                    cin.ignore(1000, '\n');   // Eingabepuffer leeren
                    continue; // Zurück zum Menü
                }
    
                filemanger.load(e, uebergebenesboard);
                spielfeld.printBoard(uebergebenesboard);
                break;
            
            case 2:
                spielfeld.printBoard(uebergebenesboard);
                break;
    
            case 3:
                spielfeld.set_number(uebergebenesboard, undomanager);
                spielfeld.printBoard(uebergebenesboard);
                break;
    
            case 4:
                undomanager.undo(uebergebenesboard);
                spielfeld.printBoard(uebergebenesboard);
                break;
    
            case 5: 
                undomanager.speichern(uebergebenesboard);
                filemanger.save(datei, uebergebenesboard);
                spielfeld.printBoard(uebergebenesboard);
                break;
    
            case 6: 
                // solve funktion 
                break;
            
            case 7:
                cout << "Spiel beendet" << endl;
                running = false;
                break;
                
            default:
                cout << "Falsche Eingabe!" << endl;
                break;
        }
    }
   
            
        
}
