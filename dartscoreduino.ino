/********************************************************************************
*
*    DartScore: shows the dart score for 2 or more players 
*        on 7 segment display or LCD
*           http://www.adafruit.com/products/880
*           https://learn.adafruit.com/adafruit-led-backpack/
*
*       Wifi shield  
*         https://docs.arduino.cc/retired/shields/arduino-wifi-
*         https://github.com/arduino-libraries/WiFi/tree/master/examples
*
*
*     Connections
*           WIFI: just mount the wifi shield on the arduino
*
*           7 segments displays: 
*                 change the adress of the second one to 71 by soldering one of the address jumpers on the backpack
*                 connect arduino - shield
*                         SCL     - C
*                         SDA     - D
*                         GND     - - (minus symbol)
*                         5V      - + (plus symbol)
*           
*
********************************************************************************/
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment player1 = Adafruit_7segment();
Adafruit_7segment player2 = Adafruit_7segment();

int scorePlayer1 = 0;
int scorePlayer2 = 0;
int brightness = 0;

void setup() {
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("DartScore");
#endif
  player1.begin(0x70);
  player2.begin(0x71);  
}

void loop() {
  testScore();
}

void testScore(){
  brightness = brightness - 1;
  if (brightness < 0){
    brightness = 16;
  }

  player1.setBrightness(brightness);  
  player2.setBrightness(brightness);

  printScore(1, 501);
  printScore(2, 501);
  delay(2000);

  printScore(1, 450);
  printScore(2, 400);
  delay(2000);

  printScore(1, 380);
  printScore(2, 300);
  delay(2000);

  printScore(1, 250);
  printScore(2, 150);
  delay(2000);

  printScore(1, 200);
  printScore(2, 80);
  delay(2000);

  printScore(1, 100);
  printScore(2, 40);
  delay(2000);

  printScore(1, 50);
  printScore(2, 20);
  delay(2000);


  printScore(1, 0);
  printScore(2, 0);
  player1.blinkRate(HT16K33_BLINK_2HZ);
  player2.blinkRate(HT16K33_BLINK_2HZ);
  delay(5000);
  player1.blinkRate(HT16K33_BLINK_OFF);
  player2.blinkRate(HT16K33_BLINK_OFF);

}

void printScore(int player, int score){
  if(player == 1){
    int c = -1;    
    if(score > scorePlayer1){
      c = 1;
    }

    while(score != scorePlayer1){
      scorePlayer1 = scorePlayer1 + c;
      player1.print(scorePlayer1);
      player1.writeDisplay();
      delay(1);
    }
  } else {
    int c = -1;    
    if(score > scorePlayer2){
      c = 1;
    }

    while(score != scorePlayer2){
      scorePlayer2 = scorePlayer2 + c;
      player2.print(scorePlayer2);
      player2.writeDisplay();
      delay(1);
    }
  }
}