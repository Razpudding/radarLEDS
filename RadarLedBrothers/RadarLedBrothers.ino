/*
* This project was built off of this example:
* http://www.princetronics.com/supermariothemesong/
* Keep in mind the board it was built for (nodeMCU) has a weird bug explained here:
* https://github.com/esp8266/Arduino/issues/2491#issuecomment-268137743
* Which I worked around by making sure the frequency is never 0
* pitches has a mapping of notes to frequencies, radarTunes has a mapping of notes
* and durations to the song Radar Love by Golden Earring (aka one of the best songs ever made)
* The project makes use of the adafruit neopixel library as well
*/

/*************************************************
 * Public Constants and includes
 *************************************************/
#include "pitches.h"
#include "radarTunes.h"

//LEDstrip stuff
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
////

int nodeLED = D0;
int melodyPin = D2; //PIEZO pun
int PIN = D4; //LED pin
int ledPin = LED_BUILTIN;
int buttonPin = D3; //BUTTON PIN
//Ok so I actually only have 5 pixels in my strip, but I didnt realize this influences the timing
//So after I had all the timing correct I found out writing to these non existent leds takes TIME
//If I set this number to the actual LED number (5) the beat is now waaay too fast. Keep that in mind when changing this number
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800); 

boolean start = false;
boolean sense = false;
int plays = 0;
int song = 0;

void setup(void)
{
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  colorWipe(strip.Color(0, 0, 0), 1); // black
  
  Serial.begin(9600);
  pinMode(D2, OUTPUT);//buzzer
  pinMode(ledPin, OUTPUT);//led indicator when singing a note
  pinMode(buttonPin, INPUT);
  pinMode(nodeLED, OUTPUT);

  digitalWrite(nodeLED, HIGH);
  digitalWrite(ledPin, HIGH);
  
  
  Serial.println("program loaded");
}
void loop()
{
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  int buttonState = digitalRead(buttonPin);
  
  //Serial.println(sensorValue);
  //Serial.println(buttonState);

  if (sense)
  {
    showPower(sensorValue);
  }
  
  //Temp test to see if the floating value of the disconnected button ever gets to 0
  if (buttonState == 0)
  {
    //Serial.println("warning button at 0!!!");
    //Serial.println("");
  }

  //The button resets the number of plays
  if(buttonState == 0 && start)
  {
    plays = 0;
  }

  //(re)start the sensor
  else if(buttonState == 0 && !start )
  {
    
    Serial.println("Is it light?");
    sense = true;     
  }

  //If it's dark enough (600 is lights out in my room) and plays < 3, sing the song
  if (sensorValue < 600 && start && plays <3)
  {
    colorWipe(strip.Color(0, 0, 0), 1); // black
    plays++;
    Serial.println("start the music!");
    //sing the tunes
    sing();
  }
}

void showPower(int light){
  //Serial.println(light);
  int green = strip.Color(0,10,0);
  int black = strip.Color(0,0,0);
  
  if (light > 900)  { strip.setPixelColor(4, green); }
  else {strip.setPixelColor(4, black);}
  if (light > 800)  { strip.setPixelColor(3, green); }
  else {strip.setPixelColor(3, black);}
  if (light > 700)  { strip.setPixelColor(2, green); }
  else {strip.setPixelColor(2, black);}
  if (light > 600)  { strip.setPixelColor(1, green); }
  else {strip.setPixelColor(1, black);}
  if (light > 500)  { strip.setPixelColor(0, green); }
  else {strip.setPixelColor(0, black);}
  strip.show();
  
  if (light < 600)
  {
    start = true;
  }
}

void sing() {
  // iterate over the notes of the melody:

  Serial.println(" 'Radar Love'");
  int size = sizeof(radarMelody) / sizeof(int);
  for (int thisNote = 0; thisNote < size; thisNote++) {
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1;
    if (radarTempo[thisNote] > 100) //dirty little hack to allow tones longer than a full note
    {
      noteDuration = 1000 * (radarTempo[thisNote] - 100);
    }
    else {
      noteDuration = 1000 / radarTempo[thisNote];
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
  colorWipe(strip.Color(0, 0, 0), 1); // black
  if (plays ==2) { start = false; } //reset start so we can measure power again
}

void buzz(int targetPin, long frequency, long length) {
  //Lets add some color
  colorWipe(strip.Color(255, 0, 0), 1); // Red
  
  //Changed the following line, the code crashes when freq is allowed to be 0
  if (frequency == 0)
  {
    frequency = 1;
  }
  if (length == 1000)
  {
    length = 999;   //need to do this because 1000 generates a high beep
  }
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
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
