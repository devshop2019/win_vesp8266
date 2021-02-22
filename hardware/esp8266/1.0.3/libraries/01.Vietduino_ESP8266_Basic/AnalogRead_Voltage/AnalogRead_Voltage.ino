/*
  AnalogRead_Voltage

  Reads an analog input on pin from A0 to A4, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0 (A1, A2, A3, A4), and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.electronoobs.com/eng_arduino_tut83.php
  https://www.youtube.com/watch?v=5mDl-bScrkU
  Dung bieu do scater trong Excel noi suy ra ham: Volt = 0.0284*sensorValue - 0.2148
  678	19.06
  670	18.84
  637	17.88
  537	15.04
  462	12.87
  394	11.02

*/

// #define tyle ((5*1000/1023)) // Uno
#define tyle (0.1875) // Ads1115
#define hamSo(a,x, b)   (a*(float)x + b)

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
//  // print out the value you read:
  Serial.print(sensorValue);
  Serial.print("\t");
//  float voltageValue1 = (sensorValue * tyle)/1000;
  float voltageValue1 = ((float)sensorValue * 4.88 / 1000);
  Serial.print(voltageValue1);
  Serial.print("\t");

  // float voltageValue1b = ((float)sensorValue * 16.52 / 1000);
  // float voltageValue1b = ((float)sensorValue * 27.8587 / 1000);
  // float voltageValue1b = ( -2 * (float)sensorValue * (float)sensorValue/1000000 + 0.0293 * (float)sensorValue -0.23);

  // float voltageValue1b = ( 0.0281 * (float)sensorValue - 0.062);
  float voltageValue1b = hamSo(0.0284, sensorValue,-0.2148);

  Serial.print(voltageValue1b);
  Serial.print("\t");
  
  sensorValue = analogRead(A2);
  // print out the value you read:
  Serial.print(sensorValue);
  Serial.print("\t");

//  sensorValue = analogRead(A2);
//  // print out the value you read:
//  Serial.print(sensorValue);
//  Serial.print("\t");
//
//  sensorValue = analogRead(A3);
//  // print out the value you read:
//  Serial.print(sensorValue);
//  Serial.print("\t");
//  
//  sensorValue = analogRead(A4);
//  // print out the value you read:
//  Serial.print(sensorValue);
//  Serial.print("\t");
  
  // 0.1875 = 6.144/32768  (datasheet ADS1115)
 float voltageValue = (sensorValue * tyle)/1000;
  // float voltageValue = ((float)sensorValue * 5 / 1023);
  Serial.println(voltageValue);
  delay(100);        // delay in between reads for stability
}
