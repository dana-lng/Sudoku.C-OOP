#include "CSudoku.cpp"
#include "CFilemanager.cpp"
#include "CUserInterface.cpp"

int main()
{
    // initialisieren der Objekte
    CSudoku spielfeld;
    CFilemanager filemanager;
    CUndoManager undomanager;
    CUserInterface menue;


    



    // main 
    int board[9][9];
    menue.menue(board, spielfeld, undomanager, filemanager);
      

}