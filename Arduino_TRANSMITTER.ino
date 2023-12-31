#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
const int buttonPin = 4;//pinTombolMode
int buttonState = 0;
int x1, x2, y1, y2, motorVal;
int pesan [6];
RF24 rf24(7,8);
const byte alamat = 255;

void setup(){
  //Serial.begin(9600);
  pinMode(buttonPin, INPUT); 
  rf24.begin();
  rf24.openWritingPipe(alamat);
  rf24.setPALevel(RF24_PA_MAX);
  rf24.stopListening();
}
void loop() {
  
  x1=analogRead(A0);
  x2=analogRead(A2);
  y1=analogRead(A1);
  y2=analogRead(A3);
  motorVal=analogRead(A4);
  buttonState=digitalRead(buttonPin); //tombolMode
  //Serial.println(buttonState);
  pesan [0] = motorVal;
  pesan [1] = x1;
  pesan [2] = x2;
  pesan [3] = y2;
  pesan [4] = buttonState;
  pesan [5] = y1;
  rf24.write(pesan, sizeof(pesan));
  //Serial.println(pesan[4]); //paket yg dikirim sesuai 1 dan 0
  delay(15);

}
