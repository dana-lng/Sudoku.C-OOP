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
{

}


bool CFilemanager::load(int zahl, int uebergebensboard[9][9])
{
    string dateiname;
    switch(zahl)
    {
        case 1:
            dateiname = easy;
            break;
        case 2: 
            dateiname = medium;
            break;
        case 3: 
            dateiname = hard;
            break;

    }
    // Datei öffnen
    ifstream datei(dateiname);
    if (!datei.is_open()) 
    {
        cout << "Datei " << dateiname << " konnte nicht geöffnet werden." << endl;
        return false;
    }

    cout << "Datei " << dateiname << " wurde erfolgreich geöffnet." << endl;


    // aus Datei lesen
    int dateiBoard[81] = {};
    char c;
    int k = 0;

    while (datei.get(c))
    {
        if (isdigit(c)) 
        {
            dateiBoard[k++] = c - '0';
            if (k == 81) break;
        }
    }

    if (k < 81) {
        cout << "Fehler: Datei enthält weniger als 81 Ziffern." << endl;
        datei.close();
        return false;
    }

    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            uebergebensboard[i][j] = dateiBoard[i * 9 + j];


    //Datei schließen
    datei.close();

    if (!datei.is_open())
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

bool CFilemanager::save(string& dateiname, int board[9][9]) {
    std::ofstream datei(dateiname);
    if (!datei.is_open()) {
        std::cerr << "Datei konnte nicht geöffnet werden: " << dateiname << "\n";
        return false;
    }

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            datei << board[i][j] << ' ';
        }
        datei << '\n';
    }

    // Datei wird automatisch geschlossen beim Verlassen des Blocks
    std::cout << "Datei wurde erfolgreich gespeichert in: " << dateiname << "\n";
    return true;
}