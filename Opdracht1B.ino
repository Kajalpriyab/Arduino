#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
/*
  State change detection (edge detection)
  Often, you don't need to know the state of a digital input all the time, but
  you just need to know when the input changes from one state to another.
  For example, you want to know when a button goes from OFF to ON. This is called
  state change detection, or edge detection.
  This example shows how to detect when a button or button changes from off to on
  and on to off.
  The circuit:
  - pushbutton attached to pin A1 from +5V
  - 10 kilohm resistor attached to pin A1 from ground
  - LED attached from pin 13 to ground (or use the built-in LED on most
    Arduino boards)
  created  27 Sep 2005
  modified 30 Aug 2011
  by Tom Igoe
  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ButtonStateChange
*/

//Programma ButtinStateChange bewerkt en verder uitgebreid voor opdracht 1B Embedded Systems.
//Koppel:1 (Simra en Angel)

char hexDigits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
// this constant won't change:
const int  buttonPin = A1;    // the pin that the pushbutton is attached to
const int ledPin1 = 13;       // the pin that the LED is attached to
const int ledPin2 = 12;
const int ledPin3 = 11;
const int ledPin4 = 10;

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
void setup() {
  MFS.initialize(0);
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  // read the pushbutton input pin:
  buttonState = !digitalRead(buttonPin);


  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is LOW then the button went from off to on:
      if (buttonPushCounter >= 0 && buttonPushCounter <= 14) {
        buttonPushCounter++;
        Serial.println (" ");
        Serial.println("on");
        Serial.println (" ");
        Serial.print("number of button pushes: ");
        Serial.println(buttonPushCounter);
        int number = buttonPushCounter;
        Serial.print ("Binary representation: "  );
        Serial.print(number, BIN);
        Serial.println (" ");


        int getal = buttonPushCounter; //Hulpvariabele

        MFS.write(hexDigits[getal], 3); //De hexadecimale getallen worden hier gekoppeld aan het aantal knopdrukken.

      } else {
        // if the current state is HIGH then the button went from on to off:
        Serial.println("off");
        buttonPushCounter = -1;
        buttonPushCounter++;
        Serial.println("on");
        Serial.print("number of button pushes: ");
        Serial.println(buttonPushCounter);
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }

    // save the current state as the last state, for next time through the loop
    lastButtonState = buttonState;
    int getal = buttonPushCounter; //Hulpvariabele


    if (getal == 0) {           // Hierdoor branden 0 lampjes als de buttonPushCounter 0 is, en is 0 te zien op de display.
      MFS.write(hexDigits[0], 3);
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin3, HIGH);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin4, HIGH);
    }
    else {
      MFS.write(hexDigits[getal], 3); //Hexadecimale getallen getoond op de display.

      // 8 4 2 1

      if (getal >= 8) {
        digitalWrite(ledPin4, LOW); //1
        getal = getal - 8;

      } else {
        digitalWrite(ledPin4, HIGH); //1
      }

      if (getal >= 4 && getal <= 7)   {
        digitalWrite(ledPin3, LOW); //1
        getal = getal - 4;
      }
      else {
        digitalWrite(ledPin3, HIGH); //1

      }

      if (getal >= 2 && getal <= 3) {
        digitalWrite(ledPin2, LOW); //1
        getal = getal - 2;
      }
      else {
        digitalWrite(ledPin2, HIGH); //1

      }
      if (getal == 1) {
        digitalWrite(ledPin1, LOW); //1
      }
      else {
        digitalWrite(ledPin1, HIGH); //1

      }

    }

  }
}

