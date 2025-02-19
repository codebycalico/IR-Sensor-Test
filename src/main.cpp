#include <Arduino.h>
#include <Bounce2.h>

#define GREEN_BUTTON_PIN 1
#define RED_BUTTON_PIN 0
#define KEY KEY_UP

bool prevPressed = false;

Bounce2::Button greenButton = Bounce2::Button();
Bounce2::Button redButton = Bounce2::Button();

void setup() {
  // Button setups
  greenButton.attach(GREEN_BUTTON_PIN, INPUT_PULLUP);
  redButton.attach(RED_BUTTON_PIN, INPUT_PULLUP);
  greenButton.interval(5);
  redButton.interval(5);
  greenButton.setPressedState(LOW);
  redButton.setPressedState(LOW);

  // Serial and keyboard starts
  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  greenButton.update();
  redButton.update();

  //This code alternates between presses.
  //If it is pressed once that turns it on, if it is pressed again,
  //that turns it off. This is taken care of in the Unity script
  //but I added the functionality here too if we need it in the future.
  // if(greenButton.pressed()){
  //   if(prevPressed == false) {
  //     prevPressed = true;
  //     Keyboard.press(KEY);
  //     Serial.println("UP key pressed.");
  //     delay(20);
  //   } else {
  //     prevPressed = false;
  //     Serial.println("UP key released.");
  //     Keyboard.releaseAll();
  //     delay(20);
  //   }
  // }

  // if(greenButton.pressed()){
  //   Keyboard.press(KEY);
  //   Keyboard.releaseAll();
  // }

// If green button is pressed, then press the mouse
// In the Unity program, this coordinates to creating water
// in the simulation (adds more water when the "mouse" is pressed)
  if(greenButton.pressed() && !prevPressed){
    prevPressed = true;
    Mouse.press();
  } else if(greenButton.pressed() && prevPressed){
    prevPressed = false;
    Mouse.release();
  }

// If red button is pressed, press the key "up"
// In the Unity program, this coordinates to clearing the water
// from the simulation
  if(redButton.pressed()){
    Keyboard.press(KEY);
    delay(20);
    Keyboard.releaseAll();
  }
}