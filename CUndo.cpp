#pragma once
#include <iostream>

// Klasse zur Verwaltung eines Undo-Stacks für Sudoku-Zustände
class CUndoManager 
{
    private:
        // Ein gespeicherter Zustand des Sudoku-Boards
        struct BoardState 
        {
            int board[9][9]; // 9x9-Spielfeld
        };

        static const int MAX_UNDO = 1000; // Maximale Anzahl speicherbarer Zustände
        BoardState undoStack[MAX_UNDO];  // Array für die Zustände (Stack-Prinzip)
        int undoIndex = -1;              // Zeigt auf den zuletzt gespeicherten Zustand (-1 = leer)

    public:
        // Speichert den aktuellen Spielstand im Undo-Stack
        void speichern(int board[9][9]);

        // Stellt den letzten Spielstand wieder her (Undo)
        bool undo(int board[9][9]);

        // Prüft, ob ein Undo überhaupt möglich ist
        bool canUndo() const;
};

// Funktion zum Speichern eines Zustands im Undo-Stack
void CUndoManager::speichern(int board[9][9]) 
{
    // Prüft, ob noch Platz im Stack ist
    if (undoIndex < MAX_UNDO - 1) 
    {
        undoIndex++; // Einen neuen Speicherplatz aktivieren

        // Aktuelles Spielfeld in den Undo-Stack kopieren
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                undoStack[undoIndex].board[i][j] = board[i][j];
    } 
    else 
    {
        std::cout << "Undo-Speicher ist voll!\n"; // Hinweis, wenn Stack voll ist
    }
}

// Funktion zum Wiederherstellen des letzten gespeicherten Zustands
bool CUndoManager::undo(int board[9][9]) 
{
    // Prüft, ob ein Zustand vorhanden ist
    if (undoIndex >= 0)         
    {
        // Kopiert das gespeicherte Board zurück ins aktuelle Spielfeld
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                board[i][j] = undoStack[undoIndex].board[i][j];

        undoIndex--; // Einen Schritt zurückgehen
        return true;
    }

    // Wenn nichts mehr rückgängig gemacht werden kann
    std::cout << "Keine weiteren Undo-Schritte verfügbar!\n";
    return false;
}

// Gibt zurück, ob ein Undo möglich ist (Stack nicht leer)
bool CUndoManager::canUndo() const 
{
    return undoIndex >= 0;
}
