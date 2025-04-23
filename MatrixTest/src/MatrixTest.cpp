/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "C:\Users\elean\EE1301\FinalProject\EE1301_Final\MatrixTest\lib\neopixel\src\neopixel.h"
#include "C:\Users\elean\EE1301\FinalProject\EE1301_Final\MatrixTest\lib\Adafruit_GFX_RK\src\Adafruit_GFX_RK.h"
#include "C:\Users\elean\EE1301\FinalProject\EE1301_Final\MatrixTest\lib\Adafruit_LEDBackpack_RK\src\Adafruit_LEDBackpack_RK.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

#define PIXEL_PIN SPI; 

//Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
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


// setup() runs once, when the device is first turned on
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

  Serial.println("8x8 LED Matrix Test");
}

void loop() 
{
  matrix.drawPixel(0, 0, LED_ON);  
  matrix.writeDisplay();  
  //delay(500);
  matrix.drawPixel(1, 1, LED_ON);  
  matrix.writeDisplay();  
  //delay(500);
  /*matrix.drawPixel(0, 0, LED_OFF);  
  matrix.writeDisplay();  
  delay(500);
  matrix.drawPixel(1, 1, LED_OFF);  
  matrix.writeDisplay();  
  delay(500);*/ 

  //button 1 test
  if(digitalRead(row1Pin) && !row1Pressed)
  {
    Serial.println("Button 1 pressed"); 
    row1Pressed = true; 
  }
  else if(!digitalRead(row1Pin))
  {
    row1Pressed = false; 
  }

  //button 2 test 
  if(digitalRead(row2Pin) && !row2Pressed)
  {
    Serial.println("Button 2 pressed"); 
    row2Pressed = true; 
  }
  else if(!digitalRead(row2Pin))
  {
    row2Pressed = false; 
  }

  //button 3 test
  if(digitalRead(row3Pin) && !row3Pressed)
  {
    Serial.println("Button 3 pressed"); 
    row3Pressed = true; 
  }
  else if(!digitalRead(row3Pin))
  {
    row3Pressed = false; 
  }

  //button 4 test 
  if(digitalRead(row4Pin) && !row4Pressed)
  {
    Serial.println("Button 4 pressed"); 
    row4Pressed = true; 
  }
  else if(!digitalRead(row4Pin))
  {
    row4Pressed = false; 
  }

  //end turn button test 
  if(digitalRead(endTurnPin) && !endTurnPressed)
  {
    Serial.println("Button end turn pressed"); 
    endTurnPressed = true; 
  }
  else if(!digitalRead(endTurnPin))
  {
    endTurnPressed = false; 
  }

  //forfeit button test
  if(digitalRead(forfeitPin) && !forfeitPressed)
  {
    Serial.println("Button forfeit pressed"); 
    forfeitPressed = true; 
  }
  else if(!digitalRead(forfeitPin))
  {
    forfeitPressed = false; 
  }
}
