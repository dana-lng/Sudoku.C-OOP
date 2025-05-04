#include <iostream>
using namespace std;
#include <limits>
#include <sstream>
#include <fstream>
#include <string>
#pragma once

class CFilemanager
{
    private:
        string easy = "easy.txt";
        string medium = "medium.txt";
        string hard = "hard.txt";

    public:
        CFilemanager();
        bool load(int zahl, int uebergebensboard[9][9]);
        bool save(string& filename, int uebergebensboard[9][9]);

};

CFilemanager::CFilemanager()
{}

bool CFilemanager::load(int zahl, int uebergebensboard[9][9])
{
   
    string dateiname;                                                                   // Variable zur Speicherung des Dateinamens je nach Schwierigkeitsgrad

    switch (zahl)                                                                       // Auswahl des Dateinamens basierend auf dem Schwierigkeitsgrad
    {
        case 1:
            dateiname = easy;                                                           // Leichtes Sudoku
            break;
        case 2:
            dateiname = medium;                                                         // Mittleres Sudoku
            break;
        case 3:
            dateiname = hard;                                                           // Schweres Sudoku
            break;
        default:
            
            throw invalid_argument("Ungueltiger Schwierigkeitsgrad!");                  // Ungültiger Schwierigkeitsgrad -> Ausnahme werfen
    }

    ifstream datei(dateiname);                                                          // Öffne die Datei zum Lesen
    if (!datei.is_open()) 
    {
        throw runtime_error("Datei konnte nicht geoeffnet werden: " + dateiname);       // Wenn die Datei nicht geöffnet werden kann, Ausnahme werfen
    }

    cout << "Datei " << dateiname << " wurde erfolgreich geöffnet." << endl;

    
    int dateiBoard[81] = {};                                                            // Array zur Speicherung der 81 Sudoku-Werte
    char c;                                                                             // Eingelesenes Zeichen
    int k = 0;                                                                          // Zählvariable für das Array

   
    while (datei.get(c))                                                                // Zeichenweise aus Datei lesen
    {
       
        if (isdigit(c))                                                                 // Nur Ziffern ('0' bis '9') speichern
        {
            dateiBoard[k++] = c - '0';                                                  // ASCII zu int konvertieren
            if (k == 81) break;                                                         // Stop, wenn 81 Ziffern gelesen wurden
        }
    }

   
    if (k < 81)                                                                         // Prüfen, ob Datei zu wenige Ziffern enthielt
    {
        throw runtime_error("Fehler: Datei enthält weniger als 81 Ziffern.");
    }

   
    for (int i = 0; i < 9; ++i)                                                         // Übertrage 1D-Array in 2D-Board
        for (int j = 0; j < 9; ++j)
            uebergebensboard[i][j] = dateiBoard[i * 9 + j];

   
    datei.close();

    
    if (!datei.is_open())                                                               // Prüfung, ob die Datei korrekt geschlossen wurde
    {
        cout << "Datei " << dateiname << " geschlossen.\n\n";
    } 
    else 
    {
        cout << "Datei " << dateiname << " konnte nicht korrekt geschlossen werden.\n\n";
        return false;
    }

    return true;
}


// Funktion zum Speichern eines Sudoku-Boards in eine Datei
bool CFilemanager::save(string& dateiname, int board[9][9]) 
{
    ofstream datei(dateiname);                                                          // Öffne Datei zum Schreiben
    if (!datei.is_open()) 
    {
        throw runtime_error("Datei konnte nicht geoeffnet werden: " + dateiname);
    }

    
    for (int i = 0; i < 9; ++i)                                                         // Schreibe Sudoku-Zahlen zeilenweise in die Datei
    {
        for (int j = 0; j < 9; ++j) 
        {
            datei << board[i][j] << ' ';
        }
        datei << '\n';                                                                  // Neue Zeile nach jeder Board-Zeile
    }

    
    cout << "Datei wurde erfolgreich gespeichert in: " << dateiname << "\n";            // Datei wird automatisch beim Verlassen des Gültigkeitsbereichs geschlossen
    return true;
}
