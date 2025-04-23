// Include Particle Device OS APIs
#include "Particle.h"
#include "C:\Users\elean\EE1301\FinalProject\EE1301_Final\NimPhoton\lib\neopixel\src\neopixel.h"
#include "C:\Users\elean\EE1301\FinalProject\EE1301_Final\NimPhoton\lib\Adafruit_GFX_RK\src\Adafruit_GFX_RK.h"
#include "C:\Users\elean\EE1301\FinalProject\EE1301_Final\NimPhoton\lib\Adafruit_LEDBackpack_RK\src\Adafruit_LEDBackpack_RK.h"

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
bool photonTurn; //could change this to enum instead of bool
bool gameWon;
bool playAgain = false; //might not be needed 

//game methods
void removeStick(int rowNum); 
void endTurn(); 
void forfeit(); 
void newGame(bool photonCall);   
bool checkForLoss(); 

//Photon display methods 
void displaySticks(); 
void updateSitcks(); 

//photon control variables 
#define PIXEL_PIN SPI; 
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
int row1Pin = D2;
int row2Pin = D3;
int row3Pin = D4;
int row4Pin = D5;
int endTurnPin = D6;
int forfeitPin = D7;
bool row1Pressed = false; 
bool row2Pressed = false;
bool row3Pressed = false;
bool row4Pressed = false;
bool endTurnPressed = false;
bool forfeitPressed = false;

void setup() 
{
  Serial.begin(9600);
  matrix.begin(0x70); 

  pinMode(row1Pin, INPUT_PULLDOWN);
  pinMode(row2Pin, INPUT_PULLDOWN);
  pinMode(row3Pin, INPUT_PULLDOWN);
  pinMode(row4Pin, INPUT_PULLDOWN);
  pinMode(endTurnPin, INPUT_PULLDOWN);
  pinMode(forfeitPin, INPUT_PULLDOWN);
}

void loop() 
{
  //start new game
  if(digitalRead(endTurnPin) && !endTurnPressed)
  {
    Serial.println("Button end turn pressed"); 
    newGame(true);
    playAgain = true;  
    endTurnPressed = true; 
  }
  else if(!digitalRead(endTurnPin))
  {
    endTurnPressed = false; 
  }

  //quit program 
  if(digitalRead(forfeitPin) && !forfeitPressed)
  {
    Serial.println("Button forfeit pressed"); 
    playAgain = false; 
    //add some way to end program
    forfeitPressed = true; 
  }
  else if(!digitalRead(forfeitPin))
  {
    forfeitPressed = false; 
  }

  while(playAgain)
  {
    while(true)
    {
      if(photonTurn)
      {
        if(checkForLoss)
        {
          Serial.println("Photon player loses!"); 
          playAgain = false; 
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
          Serial.println("Website player loses"); 
          playAgain = false; 
          break; 
        } 
        while(!photonTurn)
        {
          //let website player take actions 
        }
      }
    }
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
      Serial.println("Stick removed from row 1"); 
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
    Serial.print("Website Player Wins"); 
  else
    Serial.print("Photon Player Wins"); 
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

  displaySticks(); 
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

void updateSticks()
{

}