/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/DigitalReadSerial
*/

// digital pin 2 has a pushbutton attached to it. Give it a name:
// int pushButton = 2;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  Serial.println(D7);
  
  // make the pushbutton's pin an input:
//   pinMode(pushButton, INPUT);
  for(int cf = D7; cf<= D13; cf++){
    pinMode(cf, INPUT);
  }
  delay(1000);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
//  int buttonState = digitalRead(pushButton);
//  // print out the state of the button:
//  Serial.println(buttonState);
//  delay(1);        // delay in between reads for stability

  for(int cf = D7; cf <= D13; cf++){
    Serial.print(digitalRead(cf));
    if(cf != D13)Serial.print("\t");
    else Serial.println();
  }
  readSerial();
  delay(100);
}

void readSerial(){
  if(Serial.available()){
    int kk = Serial.readStringUntil('\n').toInt();
    if(kk == 1){
      for(int cf = D7; cf<= D13; cf++){
        pinMode(cf, INPUT_PULLUP);
      }
      Serial.println("PULL UP");
    }else{
      for(int cf = D7; cf<= D13; cf++){
        pinMode(cf, INPUT);
      }
      Serial.println("OFF");
    }
    
  }
}
