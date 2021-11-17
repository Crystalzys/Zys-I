/*
 * This sample program demonstrates how to use a push button (and Arduino's built-in pullup resistor mode)
 * to toggle the state of an LED on and off. The program begins with the LED in the on state.  When the user pushes the button,
 * it toggles the LED logic so if the LED is currently on, then it turns off.  Or if the LED is currently off, it turns on.
 * There is also logic to debounce the button.  In otherwords, the debounce logic is designed so that the state of teh LED only toggles 
 * once per button press. The user has to release the button and then press it again to toggle the state of the LED a second time after the first button press.
 */

 int speakerPin = 12;

 int photocellPin = 0;

int numTones = 24;
int tones[] = {261, 277, 294, 311, 329, 349, 370, 392, 415, 440, 466, 493, 523, 554, 587, 622, 659, 698, 739, 783, 830, 880, 932, 987};
//            mid C  C#   D    D#   E    F    F#   G    G#   A   #A    B    C   #C    D    #D   E    F   #F    G    #G   A    #A   B


// change the following value if your button is not connected to digital pin #2.
#define BUTTON_PIN 2

// this program assumes you are using the built-in LED on pin 13.
#define LED_PIN 13

// the following global variable keeps track of the state of the button.
// it's value is true if the button is currently pressed.
boolean buttonState;


// we need a second state variable to keep track of the state of our LED.
// the following variable is true if the LED is turned on.  It is false if the LED is off.
boolean ledState;

void setup() {
  // start the serial connection for debug purposes.
  Serial.begin(9600);
  
  // put the button pin into pull up resistor mode.
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // set the built-in LED pin (13) to OUTPUT mode.
  pinMode(LED_PIN, OUTPUT);

  // assume button is not pressed initially.
  buttonState = false;

  // have the LED initially be turned on.
  ledState = true;

  for (int i = 0; i < numTones; i++) //enter the loop until the element a [i] gets 0
  {
    tone(speakerPin, tones[i]);
    delay(500);
  }
}

void loop() {
  int sensorVal = digitalRead(BUTTON_PIN);
  
  // check to see if the button was just pressed.
  if (sensorVal == HIGH && buttonState == false) {
    // the button was just pressed.
    
    // set the buttonState variable to true.
    buttonState = true;

    // print debug info.
    Serial.println("button was just pressed.  Toggling ledState.");
    
    // toggle the value of the ledState.
    if (ledState == true) {
      ledState = false;
    } else {
      ledState = true;
    }
    // print debug info.
    Serial.print("ledState = ");
    Serial.println(ledState);
  } else if (sensorVal == LOW && buttonState == true) {
    // the button was just released.

    // set the buttonState variable to false.
    buttonState = false;
    
  }

  
  
  // decide whether to turn on or turn off the LED.
  if (ledState == true) {
    // turn on LED.
    digitalWrite(LED_PIN, HIGH);
    //tone(speakerPin, 261);

    int reading = analogRead(photocellPin);
    int pitch = 200 + reading / 4;
    tone(speakerPin, pitch);
    
  } else {
    // turn off the LED since the buttonState is equal to false.
    digitalWrite(LED_PIN, LOW);
    noTone(speakerPin);
  }
}
