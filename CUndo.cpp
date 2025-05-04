#pragma once
#include <iostream>

// Klasse zur Verwaltung eines Undo-Stacks für Sudoku-Zustände
class CUndoManager 
{
    private:
        
        struct BoardState                                                           // Ein gespeicherter Zustand des Sudoku-Boards
        {
            int board[9][9];                                                        // 9x9-Spielfeld
        };

        static const int MAX_UNDO = 1000;                                          // Maximale Anzahl speicherbarer Zustände
        BoardState undoStack[MAX_UNDO];                                            // Array für die Zustände (Stack-Prinzip)
        int undoIndex;                                                             // Zeigt auf den zuletzt gespeicherten Zustand (-1 = leer)

    public:

        CUndoManager();
        void speichern(int board[9][9]);                                          // Speichert den aktuellen Spielstand im Undo-Stack
        bool undo(int board[9][9]);                                               // Stellt den letzten Spielstand wieder her (Undo)
        bool canUndo() const;                                                     // Prüft, ob ein Undo überhaupt möglich ist
};

CUndoManager::CUndoManager()
{
    undoIndex = -1; 
}

// Funktion zum Speichern eines Zustands im Undo-Stack
void CUndoManager::speichern(int board[9][9]) 
{
    if (undoIndex < MAX_UNDO - 1)                                                // Prüft, ob noch Platz im Stack ist
    {
        undoIndex++;                                                             // Einen neuen Speicherplatz aktivieren

        for (int i = 0; i < 9; ++i)                                              // Aktuelles Spielfeld in den Undo-Stack kopieren
            for (int j = 0; j < 9; ++j)
                undoStack[undoIndex].board[i][j] = board[i][j];
    } 
    else 
    {
        throw runtime_error("Achtung, Stack voll!");                            // Hinweis, wenn Stack voll ist
    }
}

// Funktion zum Wiederherstellen des letzten gespeicherten Zustands
bool CUndoManager::undo(int board[9][9]) 
{
   
    if (undoIndex >= 0)                                                         // Prüft, ob ein Zustand vorhanden ist
    {
        
        for (int i = 0; i < 9; ++i)                                             // Kopiert das gespeicherte Board zurück ins aktuelle Spielfeld
            for (int j = 0; j < 9; ++j)
                board[i][j] = undoStack[undoIndex].board[i][j];

        undoIndex--;                                                            // Einen Schritt zurückgehen
        return true;
    }

   
    throw runtime_error("Alles wurde rückgängig gemacht.");                     // Wenn nichts mehr rückgängig gemacht werden kann
    return false;
}

// Gibt zurück, ob ein Undo möglich ist (Stack nicht leer)
bool CUndoManager::canUndo() const                                              
{
    return undoIndex >= 0;
}
