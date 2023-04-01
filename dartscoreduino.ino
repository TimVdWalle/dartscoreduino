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

#include <SPI.h>
#include <WiFi.h>
#include "env.h"

char ssid[] = WIFI_SSID;               //  your network SSID (name)
char pass[] = WIFI_PASSWORD;           // your network password
int status = WL_IDLE_STATUS;      // the WiFi radio's status

Adafruit_7segment player1 = Adafruit_7segment();
Adafruit_7segment player2 = Adafruit_7segment();

int scorePlayer1 = 0;
int scorePlayer2 = 0;

void setup() {
  Serial.begin(9600);
  while(!Serial) ;
  
  Serial.println("DartScore V0.1");

  initDisplays();
  initWifi();
}

void initDisplays(){
    // set address for 7 segment displays
  player1.begin(0x70);
  player2.begin(0x71);  
}

void initWifi(){
  printMacAddress();
  connectToNetwork();
}

void connectToNetwork(){
    // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

   // you're connected now, so print out the data:
   Serial.print("You're connected to the network");
   printCurrentNet();
//   printWifiData();
}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  Serial.print(bssid[5], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.println(bssid[0], HEX);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}


void loop() {
  testScore();
}

void testScore(){
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

void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);

}

void printMacAddress() {

  // the MAC address of your Wifi shield

  byte mac[6];

  // print your MAC address:

  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
}