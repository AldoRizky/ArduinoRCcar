#include<nRF24L01.h>
#include<RF24.h>
#include<SPI.h>
#include <MX1508.h>
#include<Servo.h>

#define PIN_A1 9
#define PIN_B1 10
#define PIN_A2 4
#define PIN_B2 8
#define NUMPWM1 2
#define NUMPWM2 1
MX1508 motorA(PIN_A1,PIN_B1, FAST_DECAY, NUMPWM1);
//MX1508 motorB(PIN_A2,PIN_B2, FAST_DECAY, NUMPWM2);

int maju, belok;

RF24 rf24(5,6); // ESP (2,4) (CS, CSN) NANO (7, 8) ATMEGA8(5, 6)
const byte alamat = 255; //disesuaikan dengan transmitter
int pesan[6];
//pesan[0] potensio
//pesan[1] joystick kiri horizontal
//pesan[2] joystick kanan horizontal
//pesan[3] joystick kanan vertikal
//pesan[4] saklar
//pesan[5] joystick kiri vertikal

void setup(){
  pinMode(PIN_A2, OUTPUT);
  pinMode(PIN_B2, OUTPUT);
  delay(100);
  digitalWrite(PIN_A2, LOW);
  digitalWrite(PIN_B2, LOW);
  
  rf24.begin();
  rf24.openReadingPipe(1, alamat);
  rf24.startListening();
}

void loop(){
  while(rf24.available()){
    digitalWrite(4, HIGH);
    rf24.read(&pesan, sizeof(pesan));

      maju=map(pesan[5],1023,0,-99,99);
      motorA.motorGo(maju);
      
      if(pesan[2]<480){
        digitalWrite(PIN_A2, HIGH);
        digitalWrite(PIN_B2, LOW);
      }else if(pesan[2]>550){
        digitalWrite(PIN_A2, LOW);
        digitalWrite(PIN_B2, HIGH);
      }else{
        digitalWrite(PIN_A2, LOW);
        digitalWrite(PIN_B2, LOW);
      }
  }
  delay(15); 
}
