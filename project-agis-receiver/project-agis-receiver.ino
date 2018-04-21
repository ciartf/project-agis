#include <SPI.h>
#include "RF24.h"

//nRF24L01------------------------------
RF24 radio(7,8); //CE, CS
byte addresses[][8] = {"node_1","node_2"}; //address

//message------------------------------
struct data{
  int id;
  int pH;
  int moist;
}dataRecv;

int ack = 1;

//setup------------------------------
void setup() {
  //serial
  Serial.begin(9600);
  
  //nRF setup
  radio.begin();
  radio.setPALevel(RF24_PA_LOW); //prevent power supply issue
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);
  radio.startListening(); //start
}

//run process------------------------------
void loop() {
  //receive : pH, moist
  if(radio.available()){
    while(radio.available()){
      radio.read(&dataRecv, sizeof(data));
      Serial.print("!");
      Serial.print(dataRecv.id);
      Serial.print(",");
      Serial.print(dataRecv.pH);
      Serial.print(",");
      Serial.println(dataRecv.moist);
    }
    
    //send : ack
    radio.stopListening();
    radio.write(&ack, sizeof(int));
    radio.startListening();
  }
}
