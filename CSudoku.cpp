#include <iostream>
using namespace std;
#include <limits>
#include <sstream>
#include <string>
#include "CUndo.cpp"
#pragma once

class CSudoku
{
    // Attribute der Klasse
    public:
        int test;
        // nicht definiert 
    public:
        CSudoku();
        void printBoard(int uebergebenesBoard[9][9]);
        void erstelleNullboard(int uebergebenesBoard[9][9]);
        void set_number(int uebergebenesBoard[9][9], CUndoManager& undoManager);
        int check_double_felder(int uebergebenesBoard[9][9], int zeile, int spalte, int wert);
        int check_double_zeilen_spalten(int uebergebenesBoard[9][9], int zeile, int spalte, int wert);
        int check_if_occupied(int uebergebenesBoard[9][9], int zeile, int spalte);
        int solve(int uebergebensBoard[9][9], int zeile, int spalte, CUndoManager& undoManager);
};

CSudoku::CSudoku()
{}

void CSudoku::printBoard(int uebergebenesBoard[9][9])
{
    for(int i = 0; i < 9; i++)
    {
        if(i % 3 == 0)
        {
            cout << "+-------+-------+-------+" << endl;
        }

        for(int j = 0; j < 9; j++)
        { 
            if(j % 3 == 0)
            {
                cout << "| "; 
            }
            
            cout << uebergebenesBoard[i][j] << " ";

            if(j == 8)
            {
                cout << "|" << endl;
            }
        }
    }
    cout << "+-------+-------+-------+" << endl;
}

void CSudoku::erstelleNullboard(int uebergebenesBoard[9][9])
{
    for(int i = 0; i<9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            uebergebenesBoard[i][j] = 0;
        }
    }
}

void CSudoku::set_number(int uebergebenesBoard[9][9], CUndoManager& undoManager)
{

    int zeile, spalte, wert;
    string eingabe;

    // Eingabe Zeile
    while (true) 
    {
        cout << "\nIn welcher Zeile wollen Sie die Zahl setzen (1 bis 9)?" << endl;
        getline(cin, eingabe);
        stringstream ss(eingabe);

        if ((ss >> zeile) && ss.eof() && zeile >= 1 && zeile <= 9) 
        {
            break;
        } 
        else 
        {
            cout << "Falsche Eingabe. Bitte geben Sie eine Zahl zwischen 1 und 9 ein." << endl;
        }
    }

    // Eingabe Spalte
    while (true) {
        cout << "In welcher Spalte wollen Sie die Zahl setzen (1 bis 9)?" << endl;
        getline(cin, eingabe);
        stringstream ss(eingabe);

        if ((ss >> spalte) && ss.eof() && spalte >= 1 && spalte <= 9) {
            break;
        } else {
            cout << "Falsche Eingabe. Bitte geben Sie eine Zahl zwischen 1 und 9 ein." << endl;
        }
    }

    // Eingabe Wert
    while (true) {
        cout << "Welche Zahl möchten Sie setzen (1 bis 9)?" << endl;
        getline(cin, eingabe);
        stringstream ss(eingabe);

        if ((ss >> wert) && ss.eof() && wert >= 1 && wert <= 9) {
            break;
        } else {
            cout << "Falsche Eingabe. Bitte geben Sie eine Zahl zwischen 1 und 9 ein." << endl;
        }
    }

    // Addiert alle return Werte der Funktionen
    int wahrheitswert = check_double_zeilen_spalten(uebergebenesBoard, zeile, spalte, wert) + check_double_felder(uebergebenesBoard, zeile, spalte, wert);
  
    // wenn 0, dann ist die Eingabe gültig
    if (wahrheitswert == 0)
    {
        undoManager.speichern(uebergebenesBoard);
        uebergebenesBoard[zeile - 1][spalte - 1] = wert; // Setzt die Zahl in das Board
    }

}

int CSudoku::check_double_felder(int uebergebenesBoard[9][9], int zeile, int spalte, int wert)
{
    // Durch Division der Zeile und Spalte durch 3 und Multiplikation mit 3 wird die obere linke Ecke des Blocks ermittelt.
    int feld_start_zeile = ((zeile - 1) / 3) * 3; 
    int feld_start_spalte = ((spalte - 1) / 3) * 3; 

    for (int i = 0; i < 3; i++) // Iteriert über die 3 Zeilen des Blocks
    {
        for (int j = 0; j < 3; j++) // Iteriert über die 3 Spalten des Blocks
        {
           
            if (uebergebenesBoard[feld_start_zeile + i][feld_start_spalte + j] == wert)  // Prüft, ob die Zahl wert bereits in einer der Zellen des Blocks vorhanden ist
            {
              
                cout << "Die Zahl " << wert << " ist bereits in diesem Feldblock vorhanden.\n" << endl;
                return 1; 
            }
        }
    }

    // Wenn die Zahl in keinem der Felder gefunden wurde, ist sie zulässig
    return 0; 
}

int CSudoku::check_double_zeilen_spalten(int uebergebenesBoard[9][9], int zeile, int spalte, int wert)
{
    // Prüft ob im Array zeilen_elemente die Zahl vorkommt  
    // oder ob im Array spalten_elemente die Zahl vorkommt
    for (int i = 0; i < 9; i++)
    {   
        
        if (uebergebenesBoard[zeile - 1][i] == wert)
        {
            cout << "Die Zahl " << wert << " ist bereits in Zeile " << zeile << " und Spalte " << i + 1 << " vorhanden." << endl;
            return 1;
        }
        else if (uebergebenesBoard[i][spalte - 1] == wert)
        {
            cout << "Die Zahl " << wert << " ist bereits in Zeile " << i+1 << " und Spalte " << spalte << " vorhanden." << endl;
            return 1;
        }
    }

    return 0;
}

int CSudoku::check_if_occupied(int uebergebenesBoard[9][9], int zeile, int spalte)
{
     // Prüft ob die Position bereits belegt ist
     if(uebergebenesBoard[zeile - 1][spalte - 1] == 0)
     {
         return 0; 
     }
     else
     {
         cout << "Diese Position ist bereits besetzt. Bitte wählen Sie eine andere Position." << endl;
         return 1;
     }
}

int CSudoku::solve(int uebergebenesBoard[9][9], int zeile, int spalte, CUndoManager& undoManager)
{
    int wert; 
    
    if (zeile == 9) // Wenn alle Zeilen abgearbeitet sind, ist das Sudoku vollständig gelöst
    {
        return 1; 
    }
    else if (spalte == 9)  // Wenn alle Spalten in der aktuellen Zeile abgearbeitet sind, springt zur nächsten Zeile
    {
        return solve(uebergebenesBoard, zeile + 1, 0, undoManager); // Wechselt zur nächsten Zeile und starte bei Spalte 0
    }
    else if (uebergebenesBoard[zeile][spalte] != 0)    // Wenn die aktuelle Zelle bereits einen festen Wert hat, wird übersprungen
    {
        return solve(uebergebenesBoard, zeile, spalte + 1, undoManager); 
    }
    else 
    {
        for (wert = 1; wert < 10; wert++) //geht alle Werte von 1 bis 9 durch
        {
            if (check_double_zeilen_spalten(uebergebenesBoard, zeile + 1, spalte + 1, wert) == 0 &&  // Prüft, ob der Wert in der aktuellen Zeile, Spalte oder dem 3x3-Block gültig ist
                check_double_felder(uebergebenesBoard, zeile + 1, spalte + 1, wert) == 0) 
            {
                undoManager.speichern(uebergebenesBoard); // Speichert den aktuellen Zustand des Boards (für "Undo"-Funktion
                
                uebergebenesBoard[zeile][spalte] = wert;  // Setzt den Wert in das Board

                if (solve(uebergebenesBoard, zeile, spalte + 1, undoManager) == 1) // Prüft, ob das Sudoku mit diesem Wert lösbar ist
                {
                    return 1; // Sudoku erfolgreich gelöst 
                }

                uebergebenesBoard[zeile][spalte] = 0; // Rückgängigmachen der Änderung (Backtracking), wenn der aktuelle Wert nicht zur Lösung führt
            }
        }
        return 0;
    }
}