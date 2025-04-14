using namespace std;

#include <iostream>
#include <cmath>
//#include "Particle.h"

//game state variables
int row1Sticks = 1;
int row2Sticks = 3;
int row3Sticks = 5;
int row4Sticks = 7;
int currentRow = 0;
bool takenStick = false;;
bool photonTurn; //could change this to enum instead of bool
bool gameWon = false;
bool playAgain = true; //might not be needed 

//game methods
void removeStick(int rowNum); 
void endTurn(); 
void forfeit(); 
void newGame(bool photonCall);   
bool checkForLoss(); 

//photon variables and methods 

//cloud variables and methods 

int main() //will be changed to loop method
{
    while(playAgain)
    {
        newGame(true); //should wait for someone to call new game

        while(!gameWon)
        {
            if(photonTurn)
            {
                if(checkForLoss())
                {
                    cout << "Player 1 loses" << endl;
                    break; 
                }
                cout << row1Sticks << " in row 1" << endl; 
                cout << row2Sticks << " in row 2" << endl; 
                cout << row3Sticks << " in row 3" << endl; 
                cout << row4Sticks << " in row 4" << endl << endl; 
                cout << "Player 1's turn" << endl;  
                while(photonTurn)
                {
                    cout << "1-4 to remove a stick, 5 to end turn, 6 to forfeit game" << endl;
                    int input; 
                    cin >> input; 

                    if(input <=4 && input >= 1)
                        removeStick(input); 
                    else if(input == 5)
                        endTurn(); 
                    else if(input == 6)
                    {
                        forfeit(); 
                        break; 
                    } 
                    else
                        cout << "please enter a valid input" << endl; 
                }
            }
            
            if(!photonTurn)
            {
                if(checkForLoss())
                {
                    cout << "Player 2 loses" << endl;
                    break; 
                } 
                cout << row1Sticks << " in row 1" << endl; 
                cout << row2Sticks << " in row 2" << endl; 
                cout << row3Sticks << " in row 3" << endl; 
                cout << row4Sticks << " in row 4" << endl << endl;
                cout << "Player 2's turn" << endl; 
                while(!photonTurn)
                {
                    cout << "1-4 to remove a stick, 5 to end turn, 6 to forfeit game" << endl; 
                    int input; 
                    cin >> input; 

                    if(input <=4 && input >= 1)
                        removeStick(input); 
                    else if(input == 5)
                        endTurn(); 
                    else if(input == 6)
                    {
                        forfeit(); 
                        break; 
                    }
                    else
                        cout << "please enter a valid input" << endl; 
                }
            }
        }

        cout << "would you like to play again? (y/n)" << endl; //take this out later and just wait for newGame call 
        char input; 
        cin >> input; 
        if(input == 'n')
            playAgain = false; 
    }
}

void removeStick(int rowNum)
{
    if(rowNum == 1 && (currentRow == 1 || currentRow == 0)) //could reformat this to read better
    {
        if(row1Sticks > 0)
        {
            currentRow = 1;
            row1Sticks--;
            takenStick = true; 
            cout << "Stick removed from row 1" << endl; 
        } 
    }
    if(rowNum == 2 && (currentRow == 2 || currentRow == 0)) 
    {
        if(row2Sticks > 0)
        {
            currentRow = 2;
            row2Sticks--;
            takenStick = true; 
            cout << "Stick removed from row 2" << endl; 
        } 
    }
    if(rowNum == 3 && (currentRow == 3 || currentRow == 0)) 
    {
        if(row3Sticks > 0)
        {
            currentRow = 3;
            row3Sticks--;
            takenStick = true; 
            cout << "Stick removed from row 3" << endl; 
        } 
    }
    if(rowNum == 4 && (currentRow == 4 || currentRow == 0)) 
    {
        if(row4Sticks > 0)
        {
            currentRow = 4;
            row4Sticks--;
            takenStick = true; 
            cout << "Stick removed from row 4" << endl; 
        }  
    }
}

void endTurn()
{
    if(takenStick)
    {
        cout << "turn ended" << endl << endl; 
        photonTurn = !photonTurn; 
        takenStick = false; 
        currentRow = 0; 
    }
    else
        cout << "you must take a stick before you can end your turn" << endl; 
}

void forfeit()
{
    gameWon = true; 
    if(photonTurn)
        cout << "Player 1 forfeits, player 2 wins!" << endl;
    else
        cout <<"Player 2 forfeits, player 1 wins!" << endl; 
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

bool checkForLoss()
{
    int sumSticks;
    sumSticks = row1Sticks + row2Sticks + row3Sticks + row4Sticks; 
    if(sumSticks <= 1) //there is one stick left, the player whos turn it is losses
    {
        gameWon = true;
        return true;  
    }
    else
        return false; 
}