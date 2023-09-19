//Arduino requires computer to have Ch340 driver    https://sparks.gogo.co.nz/ch340.html
//This code is for a custom electronic system for an art exhibit. Each system has a switch
//wired to a payphone receiver dock. The artist will upload up to 5 .ogg audio files and
//when a patron picks up the phone, one of the files is randomly selected and played.

#include <SoftwareSerial.h>       //loads program for software serial
#include "Adafruit_Soundboard.h"  //loads library for soundboard
#define SFX_TX 5                  //defines pin 2 as transmit to soundboard
#define SFX_RX 6                  //defines pin 3 as receive from soundboard
#define SFX_RST 4                 //defines pin 4 as the reset pin
#define receiverSwitch 12         //receiver switch
 
byte select;                      //variable for track selection
bool reset = false;               //variable for reset
bool readyPlay = true;            //variable to control playback
uint8_t files;                    //variable for sound files

//software serial object for communication with soundboard
SoftwareSerial ss = SoftwareSerial(SFX_TX, SFX_RX);
//soundboard object
Adafruit_Soundboard sfx = Adafruit_Soundboard(&ss, NULL, SFX_RST);

void setup() {
  Serial.begin(115200);           // opens serial monitor
  ss.begin(9600);                 // communication bitrate between arduino and sound module
  pinMode(receiverSwitch, INPUT_PULLUP);
  files = sfx.listFiles();
}

void loop() {
  //check if phone receiver is picked up
  if (digitalRead(receiverSwitch) == LOW) {
    //check if a file should play
    if (readyPlay == true) {
      playRandomTrack();
      // turn off playmode
      readyPlay = false;
    }
    reset = true;
  }
  //if phone receiver is in cradle
  else {
    //stop current track from playing
    if (reset == true) {
      sfx.reset();
      readyPlay = true;
      reset = false;
    }
  }
  //print values to console for debugging
  displayValues(); 
}

void playRandomTrack() {
  if (files == 1) {
    select = random(0, 1);     //random track 0
  }
  if (files == 2) {
    select = random(0, 2);     //random track 0, 1
  }
  if (files == 3) {
    select = random(0, 3);     //random track 0, 1, 2
  }
  if (files == 4) {
    select = random(0, 4);     //random track 0, 1, 2, 3
  }
  if (files == 5) {
    select = random(0, 5);     //random track 0, 1, 2, 3, 4
  }
  if (select == 0) {
    sfx.playTrack((uint8_t)00);
  }
  if (select == 1) {
    sfx.playTrack((uint8_t)01);
  }
  if (select == 2) {
    sfx.playTrack((uint8_t)02);
  }
  if (select == 3) {
    sfx.playTrack((uint8_t)03);
  }
  if (select == 4) {
    sfx.playTrack((uint8_t)04);
  }
}

void displayValues() {
  Serial.print("Sw = ");
  Serial.print(digitalRead(receiverSwitch));
  Serial.print(" | reset = ");
  Serial.print(reset);
  Serial.print(" | Ready = ");
  Serial.print(readyPlay);
  Serial.print(" | Files = ");
  Serial.print(files);
  Serial.print(" | Select = ");
  Serial.println(select);
}
