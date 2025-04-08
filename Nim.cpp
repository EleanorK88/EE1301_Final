using namespace std;

#include <iostream>

int row1Sticks;
int row2Sticks;
int row3Sticks;
int row4Sticks;
int currentRow;
bool takenStick;
bool photonTurn; //could change this to enum instead of bool
bool gameWon;
//could add bool/enum to track winner 

void removeRow(int rowNum); 
void endTurn(); 
void forfeit(); 
void newGame(bool photonCall);   

int main()
{

}

void removeRow(int rowNum)
{
    if(currentRow == 0)
        currentRow = rowNum; 

    if(rowNum == 1 && currentRow == 1) //could reformat this to read better
    {
        if(row1Sticks > 0)
        {
            row1Sticks--;
            takenStick = true; 
        } 
    }
    if(rowNum == 2 && currentRow == 2) 
    {
        if(row2Sticks > 0)
        {
            row2Sticks--;
            takenStick = true; 
        } 
    }
    if(rowNum == 3 && currentRow == 3) 
    {
        if(row3Sticks > 0)
        {
            row3Sticks--;
            takenStick = true; 
        } 
    }
    if(rowNum == 4 && currentRow == 4) 
    {
        if(row4Sticks > 0)
        {
            row4Sticks--;
            takenStick = true; 
        }  
    }
}

void endTurn()
{
    if(takenStick)
    {
        photonTurn = !photonTurn; 
        takenStick = false; 
        currentRow = 0; 
    }
}

void forfeit()
{
    gameWon = true; 
    if(photonTurn)
        cout << "Website Player Wins!";
    else
        cout << "Photon Player Wins!"; 
}

void newGame(bool photonCall)
{
    row1Sticks = 1;
    row2Sticks = 3;
    row3Sticks = 5;
    row4Sticks = 7;

    photonTurn = photonCall;
    takenStick = 0;
    currentRow = 0; 
    gameWon = false; 
}