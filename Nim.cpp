using namespace std;

#include <iostream>

int row1Sticks;
int row2Sticks;
int row3Sticks;
int row4Sticks;
int currentRow;
bool takenStick;
bool currentTurn;
bool gameWon;

void removeRow(int rowNum); 
void endTurn(); 

void newGame()
{
    row1Sticks = 1;
    row2Sticks = 3;
    row3Sticks = 5;
    row4Sticks = 7; 
} 

int main()
{

}