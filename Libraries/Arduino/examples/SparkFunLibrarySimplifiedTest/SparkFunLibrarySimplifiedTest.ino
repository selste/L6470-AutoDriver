#include <SparkFunAutoDriver.h>
#include <SPI.h>
#include "SparkFunNotes.h"

// Test sketch for the L6470 AutoDriver library. This program instantiates one
//  AutoDriver board and uses it to play Jonathon Coulton's "Want You Gone" from
//  the Portal 2 soundtrack. In a more general sense, it adds support for playing
//  music with stepper motors. Not all notes can be played, of course- at too high
//  a steps/sec rate, the motors will slip and dogs and cats will live together.

#define CS_PIN 10
#define RESET_PIN 6

// Create our AutoDriver instance. The parameters are the position in the chain of
//  boards (with board 0 being located at the end of the chain, farthest from the
//  controlling processor), CS pin, and Reset pin.
AutoDriver board(0, CS_PIN, RESET_PIN);

void setup() {
  Serial.begin(9600);
  Serial.println("Hello world");
  // Start by setting up the SPI port and pins. The
  //  Autodriver library does not do this for you!
  pinMode(RESET_PIN, OUTPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(MISO, INPUT);
  pinMode(SCK, OUTPUT);
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);
  digitalWrite(RESET_PIN, LOW);       // This low/high is a reset of the L6470 chip on the
  digitalWrite(RESET_PIN, HIGH);      //  Autodriver board, and is a good thing to do at
                                      //  the start of any Autodriver sketch, to be sure
                                      //  you're starting the Autodriver from a known state.
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  dSPINConfig();
}

// loop() waits for a character- any character- and then plays the song.
void loop() {
  if (0!=Serial.available()) {
    Serial.read();
    Serial.println("Play it!");
    wantYouGone();
    Serial.println("Done playing!");
  }
}
