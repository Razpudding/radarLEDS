/*
  Arduino Mario Bros Tunes
  With Piezo Buzzer and PWM

  Connect the positive side of the Buzzer to pin 3,
  then the negative side to a 1k ohm resistor. Connect
  the other side of the 1 k ohm resistor to
  ground(GND) pin on the Arduino.

  by: Dipto Pratyaksa
  last updated: 31/3/13
*/

/*************************************************
 * Public Constants
 *************************************************/
#include "pitches.h"
#include "radarTunes.h"

//LEDstrip stuff
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
////

int melodyPin = D2; //PIEZO pun
int PIN = D4; //LED pin
int ledPin = LED_BUILTIN;
int buttonPin = D3; //BUTTON PIN
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

boolean start = false;
int plays = 0;
int song = 0;

void setup(void)
{
  // initialize digital pin LED_BUILTIN as an output.
 
  Serial.begin(9600);
  pinMode(D2, OUTPUT);//buzzer
  pinMode(ledPin, OUTPUT);//led indicator when singing a note
  pinMode(buttonPin, INPUT);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.println("program loaded");
}
void loop()
{
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  int buttonState = digitalRead(buttonPin);
  //Serial.println(sensorValue);
  //Serial.println(buttonState);

  //Temp test to see if the floating value of the disconnected button ever gets to 0
  if (buttonState == 0)
  {
    Serial.println("warning button at 0!!!");
    Serial.println("");
  }

  //The button resets the number of plays
  if(buttonState == 0 && start)
  {
    plays = 0;
  }

  //Log the first start
  else if(buttonState == 0 && !start )
  {
    
    Serial.println("Here we go!");
    start = true;     
  }

  //If it's dark enough (600 is lights out in my room) and plays < 3, sing the song
  if (sensorValue < 600 && start && plays <3)
  {
    plays++;
    Serial.println("start the music!");
    //sing the tunes
    sing();
  }
}


void sing() {
  // iterate over the notes of the melody:


  Serial.println(" 'Radar Theme'");
  int size = sizeof(radarMelody) / sizeof(int);
  for (int thisNote = 0; thisNote < size; thisNote++) {

    
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1;
    if (radarTempo[thisNote] > 100) //dirty little hack to allow tones longer than a full note
    {
      noteDuration = 500 * (radarTempo[thisNote] - 100);
    }
    else {
      noteDuration = 500 / radarTempo[thisNote];
    }

    buzz(melodyPin, radarMelody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    //int pauseBetweenNotes = noteDuration * 1.30; //ORIGINAL
    int pauseBetweenNotes = noteDuration * .1; 
    delay(pauseBetweenNotes);

    // stop the tone playing (this was in the original code but made pauses seem very long  
    //buzz(melodyPin, 0, noteDuration);
  }
}

void buzz(int targetPin, long frequency, long length) {
  //Lets add some color
  colorWipe(strip.Color(255, 0, 0), 1); // Red
  
  //Changed the following line, the code crashes when freq is allowed to be 0
  long delayValue = 1000000 / (frequency+1) / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  //Change color
  colorWipe(strip.Color(0, 0, 250), 1); // blue

}

//Helper function for wiping colors
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    //delay(wait);
  }
}
