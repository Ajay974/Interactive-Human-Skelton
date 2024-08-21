#include <SD.h>
#include <TMRpcm.h>
#include <SPI.h>

// Pin definitions
const int button1Pin = 22;
const int button2Pin = 24;
const int button3Pin = 26;
const int button4Pin = 28;
const int button5Pin = 30;
const int button6Pin = 32;
const int button7Pin = 34; // New button pin
const int button8Pin = 36; // New button pin
const int button9Pin = 38; // New button pin
const int button10Pin = 40; // New button pin
const int button11Pin = 42; // New button pin
const int button12Pin = 44; // New button pin

const int led1Pin = A9;
const int led2Pin = A1;
const int led3Pin = A4; 
const int led4Pin = A7;
const int led5Pin = A8;
const int led6Pin = A3;
const int led7Pin = A10; // New LED pin
const int led8Pin = A11; // New LED pin
const int led9Pin = A6; // New LED pin
const int led10Pin = A0; // New LED pin
const int led11Pin = A2; // New LED pin
const int led12Pin = A5; // New LED pin

const int SD_ChipSelectPin = 10; // Change to match your SD module wiring

TMRpcm audio; // Create an object for TMRpcm

bool buttonStates[12] = {false};
bool lastButtonStates[12] = {false};
bool isPlaying = false;  // To store if audio is currently playing
int currentPlayingButton = 0;  // To track which button's song is currently playing

void handleButtonPress(int buttonNumber, const char* filename, int ledPinToToggle, int otherLedPins[], int otherLedCount);

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Set up pins
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);
  pinMode(button5Pin, INPUT);
  pinMode(button6Pin, INPUT);
  pinMode(button7Pin, INPUT);
  pinMode(button8Pin, INPUT);
  pinMode(button9Pin, INPUT);
  pinMode(button10Pin, INPUT);
  pinMode(button11Pin, INPUT);
  pinMode(button12Pin, INPUT);

  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
  pinMode(led5Pin, OUTPUT);
  pinMode(led6Pin, OUTPUT);
  pinMode(led7Pin, OUTPUT);
  pinMode(led8Pin, OUTPUT);
  pinMode(led9Pin, OUTPUT);
  pinMode(led10Pin, OUTPUT);
  pinMode(led11Pin, OUTPUT);
  pinMode(led12Pin, OUTPUT);

  // Initialize SD card
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD card initialization failed!");
    return;
  }

  // Initialize audio
  audio.speakerPin = 12; // Set the speaker output pin

  Serial.println("Setup complete");
}

void loop() {
  // Read button states
  buttonStates[0] = digitalRead(button1Pin) == HIGH;
  buttonStates[1] = digitalRead(button2Pin) == HIGH;
  buttonStates[2] = digitalRead(button3Pin) == HIGH;
  buttonStates[3] = digitalRead(button4Pin) == HIGH;
  buttonStates[4] = digitalRead(button5Pin) == HIGH;
  buttonStates[5] = digitalRead(button6Pin) == HIGH;
  buttonStates[6] = digitalRead(button7Pin) == HIGH;
  buttonStates[7] = digitalRead(button8Pin) == HIGH;
  buttonStates[8] = digitalRead(button9Pin) == HIGH;
  buttonStates[9] = digitalRead(button10Pin) == HIGH;
  buttonStates[10] = digitalRead(button11Pin) == HIGH;
  buttonStates[11] = digitalRead(button12Pin) == HIGH;

  // Check if any two buttons are pressed simultaneously
  int pressedCount = 0;
  for (int i = 0; i < 12; i++) {
    if (buttonStates[i]) {
      pressedCount++;
    }
  }

  if (pressedCount > 1) {
    // If any two buttons are pressed, do nothing
    Serial.println("Multiple buttons pressed, doing nothing");
  } else {
    // Check button presses and handle them
    if (buttonStates[0] && !lastButtonStates[0]) {
      int otherLeds[] = {led2Pin, led3Pin, led4Pin, led5Pin, led6Pin, led7Pin, led8Pin, led9Pin, led10Pin, led11Pin, led12Pin};
      handleButtonPress(1, "kneecap.wav", led1Pin, otherLeds, 11);
    }
    if (buttonStates[1] && !lastButtonStates[1]) {
      int otherLeds[] = {led1Pin, led3Pin, led4Pin, led5Pin, led6Pin, led7Pin, led8Pin, led9Pin, led10Pin, led11Pin, led12Pin};
      handleButtonPress(2, "spinal.wav", led2Pin, otherLeds, 11);
    }
    if (buttonStates[2] && !lastButtonStates[2]) {
      int otherLeds[] = {led1Pin, led2Pin, led4Pin, led5Pin, led6Pin, led7Pin, led8Pin, led9Pin, led10Pin, led11Pin, led12Pin};
      handleButtonPress(3, "pelvis.wav", led3Pin, otherLeds, 11);
    }
    if (buttonStates[3] && !lastButtonStates[3]) {
      int otherLeds[] = {led1Pin, led2Pin, led3Pin, led5Pin, led6Pin, led7Pin, led8Pin, led9Pin, led10Pin, led11Pin, led12Pin};
      handleButtonPress(4, "fibula.wav", led4Pin, otherLeds, 11);
    }
    if (buttonStates[4] && !lastButtonStates[4]) {
      int otherLeds[] = {led1Pin, led2Pin, led3Pin, led4Pin, led6Pin, led7Pin, led8Pin, led9Pin, led10Pin, led11Pin, led12Pin};
      handleButtonPress(5, "ribs.wav", led5Pin, otherLeds, 11);
    }
    if (buttonStates[5] && !lastButtonStates[5]) {
      int otherLeds[] = {led1Pin, led2Pin, led3Pin, led4Pin, led5Pin, led7Pin, led8Pin, led9Pin, led10Pin, led11Pin, led12Pin};
      handleButtonPress(6, "ulna.wav", led6Pin, otherLeds, 11);
    }
    if (buttonStates[6] && !lastButtonStates[6]) {
      int otherLeds[] = {led1Pin, led2Pin, led3Pin, led4Pin, led5Pin, led6Pin, led8Pin, led9Pin, led10Pin, led11Pin, led12Pin};
      handleButtonPress(7, "jawbone.wav", led7Pin, otherLeds, 11);
    }
    if (buttonStates[7] && !lastButtonStates[7]) {
      int otherLeds[] = {led1Pin, led2Pin, led3Pin, led4Pin, led5Pin, led6Pin, led7Pin, led9Pin, led10Pin, led11Pin, led12Pin};
      handleButtonPress(8, "skull.wav", led8Pin, otherLeds, 11);
    }
    if (buttonStates[8] && !lastButtonStates[8]) {
      int otherLeds[] = {led1Pin, led2Pin, led3Pin, led4Pin, led5Pin, led6Pin, led7Pin, led8Pin, led10Pin, led11Pin, led12Pin};
      handleButtonPress(9, "tibia.wav", led9Pin, otherLeds, 11);
    }
    if (buttonStates[9] && !lastButtonStates[9]) {
      int otherLeds[] = {led1Pin, led2Pin, led3Pin, led4Pin, led5Pin, led6Pin, led7Pin, led8Pin, led9Pin, led11Pin, led12Pin};
      handleButtonPress(10, "humerus.wav", led10Pin, otherLeds, 11);
    }
    if (buttonStates[10] && !lastButtonStates[10]) {
      int otherLeds[] = {led1Pin, led2Pin, led3Pin, led4Pin, led5Pin, led6Pin, led7Pin, led8Pin, led9Pin, led10Pin, led12Pin};
      handleButtonPress(11, "radius.wav", led11Pin, otherLeds, 11);
    }
    if (buttonStates[11] && !lastButtonStates[11]) {
      int otherLeds[] = {led1Pin, led2Pin, led3Pin, led4Pin, led5Pin, led6Pin, led7Pin, led8Pin, led9Pin, led10Pin, led11Pin};
      handleButtonPress(12, "femur.wav", led12Pin, otherLeds, 11);
    }
  }

  // Update last button states
  for (int i = 0; i < 12; i++) {
    lastButtonStates[i] = buttonStates[i];
  }

  // Check if the music has stopped playing and turn off the LED
  if (isPlaying && !audio.isPlaying()) {
    isPlaying = false;
    Serial.print("Stopping playback, turning off LED: ");
    Serial.println(currentPlayingButton);
    switch (currentPlayingButton) {
      case 1:
        digitalWrite(led1Pin, LOW);
        break;
      case 2:
        digitalWrite(led2Pin, LOW);
        break;
      case 3:
        digitalWrite(led3Pin, LOW);
        break;
      case 4:
        digitalWrite(led4Pin, LOW);
        break;
      case 5:
        digitalWrite(led5Pin, LOW);
        break;
      case 6:
        digitalWrite(led6Pin, LOW);
        break;
      case 7:
        digitalWrite(led7Pin, LOW);
        break;
      case 8:
        digitalWrite(led8Pin, LOW);
        break;
      case 9:
        digitalWrite(led9Pin, LOW);
        break;
      case 10:
        digitalWrite(led10Pin, LOW);
        break;
      case 11:
        digitalWrite(led11Pin, LOW);
        break;
      case 12:
        digitalWrite(led12Pin, LOW);
        break;
    }
  }
}

void handleButtonPress(int buttonNumber, const char* filename, int ledPinToToggle, int otherLedPins[], int otherLedCount) {
  Serial.print("Button ");
  Serial.print(buttonNumber);
  Serial.println(" pressed");

  // Stop any currently playing audio
  if (audio.isPlaying()) {
    audio.stopPlayback();
  }

  // Turn off all other LEDs
  for (int i = 0; i < otherLedCount; i++) {
    digitalWrite(otherLedPins[i], LOW);
  }

  // Play the new audio file
  audio.play(filename);
  isPlaying = true;  // Mark audio as playing
  currentPlayingButton = buttonNumber;  // Set the current button as the one playing

  // Turn on the current LED
  digitalWrite(ledPinToToggle, HIGH);
}
