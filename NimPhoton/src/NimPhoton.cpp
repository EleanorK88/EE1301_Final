// Include Particle Device OS APIs
#include "Particle.h"
#include "neopixel.h"
#include "Adafruit_GFX_RK.h"
#include "LEDBackpack_RK.h"
#include <string>
using namespace std; 

SYSTEM_MODE(AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_INFO);

//game state variables
int row1Sticks;
int row2Sticks;
int row3Sticks;
int row4Sticks;
int currentRow;
bool takenStick;
bool photonTurn; 
bool gameWon;
bool playAgain = false; //tracks if a game is active, the name is carryover from old structure

//game methods
int removeStick(String rowNumS); 
int endTurn(String dummy); 
int forfeit(String dummy); 
int newGame(String photonCall);   
int checkForLoss(String dummy); 

//Photon display methods 
void displaySticks(); 
void displaySmile();
void displayFrown(); 

//photon variables 
#define PIXEL_PIN SPI; 
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
int row1Pin = D2;
int row2Pin = D3;
int row3Pin = D4;
int row4Pin = D5;
int endTurnPin = D6;
int forfeitPin = D7;
int LEDPin = D10; 
bool row1Pressed = false; 
bool row2Pressed = false;
bool row3Pressed = false;
bool row4Pressed = false;
bool endTurnPressed = false;
bool forfeitPressed = false;

void setup() 
{
  Serial.begin(9600);

  //settup and clear matrix
  matrix.begin(0x70); 
  matrix.clear(); 
  matrix.writeDisplay();

  //configure photon pins
  pinMode(row1Pin, INPUT_PULLDOWN);
  pinMode(row2Pin, INPUT_PULLDOWN);
  pinMode(row3Pin, INPUT_PULLDOWN);
  pinMode(row4Pin, INPUT_PULLDOWN);
  pinMode(endTurnPin, INPUT_PULLDOWN);
  pinMode(forfeitPin, INPUT_PULLDOWN);
  pinMode(LEDPin, OUTPUT);  

  //register cloud variables 
  Particle.variable("numSticks1", row1Sticks); 
  Particle.variable("numSticks2", row2Sticks); 
  Particle.variable("numSticks3", row3Sticks); 
  Particle.variable("numSticks4", row4Sticks); 
  Particle.variable("otherTurn", photonTurn); 
  Particle.variable("winner", gameWon);
  Particle.variable("currentGame", playAgain); 

  //regiser cloud functions
  //note: these function are all int function(string input){} since that is what cloud functions need to be
  Particle.function("takeStick", removeStick); 
  Particle.function("endTurn", endTurn);
  Particle.function("quit", forfeit);
  Particle.function("startGame", newGame);   
}

void loop() 
{ 
  //start new game
  if(digitalRead(endTurnPin) && !endTurnPressed)
  {
    Serial.println("Button end turn pressed"); 
    newGame("true");
    playAgain = true;  
    endTurnPressed = true; 
  }
  else if(!digitalRead(endTurnPin))
  {
    endTurnPressed = false; 
  }

  while(playAgain) //game is active
  {
      if(photonTurn)
      {
        if(checkForLoss("dummy") == 1) //breadboard player has lost
        {
          Serial.println("Photon player loses!"); 
          displayFrown(); 
          playAgain = false; 
          gameWon = true; 
          break; 
        }

        while(photonTurn) //breadboard player takes actions
        {
          Particle.process(); 

          //remove sticks from row 1 (top)
          if(digitalRead(row1Pin) && !row1Pressed)
          {
            Serial.println("Button 1 pressed"); 
            removeStick("1"); 
            row1Pressed = true; 
          }
          else if(!digitalRead(row1Pin))
          {
            row1Pressed = false; 
          }

          //remove sticks from row 2 
          if(digitalRead(row2Pin) && !row2Pressed)
          {
            Serial.println("Button 2 pressed"); 
            removeStick("2"); 
            row2Pressed = true; 
          }
          else if(!digitalRead(row2Pin))
          {
            row2Pressed = false; 
          }

          //remove sticks from row 3
          if(digitalRead(row3Pin) && !row3Pressed)
          {
            Serial.println("Button 3 pressed"); 
            removeStick("3"); 
            row3Pressed = true; 
          }
          else if(!digitalRead(row3Pin))
          {
            row3Pressed = false; 
          }

          //remove sticks from row 4 (bottom)
          if(digitalRead(row4Pin) && !row4Pressed)
          {
            Serial.println("Button 4 pressed"); 
            removeStick("4"); 
            row4Pressed = true; 
          }
          else if(!digitalRead(row4Pin))
          {
            row4Pressed = false; 
          }

          //end turn
          if(digitalRead(endTurnPin) && !endTurnPressed)
          {
            Serial.println("Button end turn pressed"); 
            endTurn("dummy"); 
            endTurnPressed = true; 
          }
          else if(!digitalRead(endTurnPin))
          {
            endTurnPressed = false; 
          }

          //forfeit
          if(digitalRead(forfeitPin) && !forfeitPressed)
          {
            Serial.println("Button forfeit pressed"); 
            forfeit("dummy");  
            break; 
            forfeitPressed = true; 
          }
          else if(!digitalRead(forfeitPin))
          {
            forfeitPressed = false; 
          }
        }
      }
            
      if(!photonTurn)
      {
        if(checkForLoss("dummy") == 1) //website player has lost 
        {
          Serial.println("Website player loses"); 
          displaySmile(); 
          playAgain = false; 
          gameWon = true; 
          break; 
        } 
        while(!photonTurn) //website player can take actions
        {
          Particle.process(); //get function calls from HTML site  

          if(gameWon) 
            break; //exit while loop so new game can be started
        }
      }
  }
}

int removeStick(String rowNumS)
{
  int rowNum = stoi((string)rowNumS); //convert sting input to integer 

  if(rowNum == 1 && (currentRow == 1 || currentRow == 0)) //stick has not been removed from a different row on this turn
  {
    if(row1Sticks > 0) //there is at least one stick to be removed
    {
      currentRow = 1;
      row1Sticks--;
      takenStick = true; //turn can only be ended is takenStick is true
      Serial.println("Stick removed from row 1"); 
      matrix.drawPixel(0,4, LED_OFF); //update LED matrix
      matrix.drawPixel(1,4, LED_OFF);
    } 
  }
  if(rowNum == 2 && (currentRow == 2 || currentRow == 0)) 
  {
    if(row2Sticks > 0)
    {
      currentRow = 2;
      row2Sticks--;
      takenStick = true; 
      Serial.println("Stick removed from row 2");  
      matrix.drawPixel(2,row2Sticks+3, LED_OFF); 
      matrix.drawPixel(3,row2Sticks+3, LED_OFF);
    } 
  }
  if(rowNum == 3 && (currentRow == 3 || currentRow == 0)) 
  {
    if(row3Sticks > 0)
    {
      currentRow = 3;
      row3Sticks--;
      takenStick = true; 
      Serial.println("Stick removed from row 3"); 
      matrix.drawPixel(4,row3Sticks+2, LED_OFF); 
      matrix.drawPixel(5,row3Sticks+2, LED_OFF); 
    } 
  }
  if(rowNum == 4 && (currentRow == 4 || currentRow == 0)) 
  {
    if(row4Sticks > 0)
    {
      currentRow = 4;
      row4Sticks--;
      takenStick = true; 
      Serial.println("Stick removed from row 4");  
      matrix.drawPixel(6,row4Sticks+1, LED_OFF); 
      matrix.drawPixel(7,row4Sticks+1, LED_OFF);
    }  
  }

  matrix.writeDisplay(); 
  return 1; 
}

int endTurn(String dummy)
{
  if(takenStick) //a stick has been removed this turn
  {
    photonTurn = !photonTurn; 
    takenStick = false; 
    currentRow = 0; 

    if(photonTurn)
      digitalWrite(LEDPin, HIGH); 
    else
      digitalWrite(LEDPin, LOW);

    Serial.print("Photon Turn:");
    Serial.println(photonTurn); 
  }
  return 1; 
}

int forfeit(String dummy)
{
  gameWon = true; 
  playAgain = false; 
  if(photonTurn)
  {
    Serial.print("Website Player Wins");
    displayFrown(); 
  } 
  else
  {
    Serial.print("Photon Player Wins");
    displaySmile(); 
  }  
  return 1; 
}

int newGame(String photonCall)
{
  row1Sticks = 1;
  row2Sticks = 3;
  row3Sticks = 5;
  row4Sticks = 7;

  takenStick = 0;
  currentRow = 0; 
  gameWon = false; 
  playAgain = true; 

  if(photonCall == "true") //method called from breadboard
  {
    digitalWrite(LEDPin, HIGH);
    photonTurn = true; 
  } 
  else //method called from website
  {
    digitalWrite(LEDPin, LOW);
    photonTurn = false; 
  } 

  displaySticks(); 
  return 1; 
}

int checkForLoss(String dummy)
{
  int sumSticks;
  sumSticks = row1Sticks + row2Sticks + row3Sticks + row4Sticks; 
  if(sumSticks <= 1) //there is one stick left, the player whos turn it is losses
  {
    Serial.println("Win found"); 
    gameWon = true;
    return 1;  
  }
  else
    return 0; 
}

//display starting configuration of sticks on LED matrix
void displaySticks()
{
  matrix.clear(); 

  //row 1
  matrix.drawPixel(7, 7, LED_ON); matrix.drawPixel(7, 1, LED_ON); matrix.drawPixel(7, 2, LED_ON); 
  matrix.drawPixel(7, 3, LED_ON); matrix.drawPixel(7, 4, LED_ON); matrix.drawPixel(7, 5, LED_ON);matrix.drawPixel(7, 6, LED_ON);
  //row 2
  matrix.drawPixel(6, 7, LED_ON); matrix.drawPixel(6, 1, LED_ON); matrix.drawPixel(6, 2, LED_ON); 
  matrix.drawPixel(6, 3, LED_ON); matrix.drawPixel(6, 4, LED_ON); matrix.drawPixel(6, 5, LED_ON);matrix.drawPixel(6, 6, LED_ON);

  //row 3
  matrix.drawPixel(5, 6, LED_ON); matrix.drawPixel(5, 2, LED_ON); matrix.drawPixel(5, 3, LED_ON); 
  matrix.drawPixel(5, 4, LED_ON); matrix.drawPixel(5, 5, LED_ON); 
  //row 4
  matrix.drawPixel(4, 6, LED_ON); matrix.drawPixel(4, 2, LED_ON); matrix.drawPixel(4, 3, LED_ON); 
  matrix.drawPixel(4, 4, LED_ON); matrix.drawPixel(4, 5, LED_ON); 

  //row 5
  matrix.drawPixel(3, 5, LED_ON); matrix.drawPixel(3, 3, LED_ON); matrix.drawPixel(3, 4, LED_ON); 
  //row 6
  matrix.drawPixel(2, 5, LED_ON); matrix.drawPixel(2, 3, LED_ON); matrix.drawPixel(2, 4, LED_ON);

  //row 7
  matrix.drawPixel(1, 4, LED_ON);
  //row 8
  matrix.drawPixel(0, 4, LED_ON);

  matrix.writeDisplay(); 
}

//display smiley face on LED matrix, used when breadboard player wins 
void displaySmile()
{
  matrix.clear(); 

  //mouth
  matrix.drawPixel(6,2, LED_ON); matrix.drawPixel(6,3, LED_ON); matrix.drawPixel(6,4, LED_ON); matrix.drawPixel(6,5, LED_ON); 
  matrix.drawPixel(5,1, LED_ON); matrix.drawPixel(5,6, LED_ON); 

  //eyes
  matrix.drawPixel(1,2, LED_ON); matrix.drawPixel(2,2, LED_ON); matrix.drawPixel(1,5, LED_ON); matrix.drawPixel(2,5, LED_ON); 

  matrix.writeDisplay(); 
}

//display frowny face on LED matrix, used when breadboard player loses 
void displayFrown()
{
  matrix.clear(); 

  //mouth
  matrix.drawPixel(5,2, LED_ON); matrix.drawPixel(5,3, LED_ON); matrix.drawPixel(5,4, LED_ON); matrix.drawPixel(5,5, LED_ON); 
  matrix.drawPixel(6,1, LED_ON); matrix.drawPixel(6,6, LED_ON); 

  //eyes
  matrix.drawPixel(1,2, LED_ON); matrix.drawPixel(2,2, LED_ON); matrix.drawPixel(1,5, LED_ON); matrix.drawPixel(2,5, LED_ON); 

  matrix.writeDisplay(); 
}