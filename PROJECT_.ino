int speakerPin = 12;
int photocellPin = 0;

int numTones = 10;
int tones[] = {261, 277, 294, 311, 329, 349, 370, 392, 415, 440, 466, 493, 523, 554, 587, 622, 659, 698, 739, 783, 830, 880, 932, 987};
//            mid C  C#   D    D#   E    F    F#   G    G#   A   #A    B    C   #C    D    #D   E    F   #F    G    #G   A    #A   B

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
for (int i = 0; i < 24; i++) // iterate over the notes of the melody
  {
    tone(speakerPin, tones[i]);
    delay(500);
  }
  noTone(speakerPin);
}


void loop() {
  // put your main code here, to run repeatedly:
  
  int reading = analogRead(photocellPin);
  int pitch = 200 + reading / 4; 
  //Add 200 to the original value to make 200Hz the lowest frequency, and then simply divide the reading by 4 and add to this value to get the 200Hz to 370Hz range.
  tone(speakerPin, pitch);
}
