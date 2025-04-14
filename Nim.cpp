using namespace std;

#include <iostream>
#include <cmath>
//#include "Particle.h"

//game state variables
int row1Sticks;
int row2Sticks;
int row3Sticks;
int row4Sticks;
int currentRow;
bool takenStick;
bool photonTurn; //could change this to enum instead of bool
bool gameWon;
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

        while(true)
        {
            if(photonTurn)
            {
                if(checkForLoss)
                {
                    cout << "photon player loses";
                    break; 
                }
                while(photonTurn)
                {
                    //let photon player take actions 
                }
            }
            
            if(!photonTurn)
            {
                if(checkForLoss)
                {
                    cout << "website player loses";
                    break; 
                } 
                while(!photonTurn)
                {
                    //let website player take actions 
                }
            }
        }

        cout << "would you like to play again? (y/n)"; //take this out later and just wait for newGame call 
        char input; 
        if(input == 'n')
            playAgain = false; 
    }
}

void removeStick(int rowNum)
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