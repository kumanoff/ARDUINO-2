

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;
double temp[11][2] = {{20, 12499.0}, {21, 11944.0},{22, 11416.0}, {23, 10916.0},{24, 10440.0}, {25, 10000.0},{26, 9556.0},{27, 9147.0},{28, 8757.0},{29, 8386.0},{30, 8033.0}}; 
float u[11];
float n;
int ledState = LOW; 


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(13, OUTPUT);//LED_BUILTIN
}

void loop() {

for( int i=0; i<11 ; i++){
  u[i] = 50000.0 / ( temp[i][1] + 10000.0);//R1*U - в знаменателе
}
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);
  n = (sensorValue * 5.0)/1023.0;
  //Serial.println("sensor = ");
  //Serial.print(n);
  for( int i=0; i<11 ; i++){
    if (n >= u[i] && n <= u[i+1]){
      Serial.print("температура в общажной берлоге:");
      Serial.print("\n");
      Serial.println(temp[i][0]);
      if (temp[i][0] > 20 && temp[i][0] < 30) {
          digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
          delay(1000);
      }
      digitalWrite(13, LOW);
      delay(1000);
      return;
    }
  }
  delay(2000);
}
