#include <SPI.h>
#include "RF24.h"

//nRF24L01------------------------------
RF24 radio(7,8); //CE, CS
byte addresses[][8] = {"node_1","node_2"}; //address

//moist------------------------------
#define moistSensor A0
#define moistArrayLength 10
int moistArray[moistArrayLength];
int moistSensorValue;

//pH------------------------------
#define pHSensor A1
#define pHArrayLength 10
int pHArray[pHArrayLength];
int pHSensorValue;

//message------------------------------
struct data{
  int id;
  int pH;
  int moist;
}dataTrans;

int ack = 0;
bool timeout = false;
unsigned long startWait = 0;

//setup------------------------------
void setup() {
  //serial
  Serial.begin(9600);
  
  //pin mode
  pinMode(moistSensor, INPUT);
  pinMode(pHSensor, INPUT);

  //sensor init
  moistInit();
  pHInit();
  
  //nRF setup
  radio.begin();
  radio.setPALevel(RF24_PA_LOW); //prevent power supply issue
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1,addresses[1]);
  radio.startListening(); //start
  dataTrans.id = 1;
}

//run process------------------------------
void loop() {
  //sensor measurement
  pHSensorRead();
  moistSensorRead();

  //send data : pH, moist
  radio.stopListening();
  Serial.println("Now sending");
  dataTrans.pH = pHSensorValue;
  dataTrans.moist = moistSensorValue;
  if(!radio.write(&dataTrans, sizeof(data))){
    Serial.println("Message failed");
  }else{
    Serial.print("Message transmitted: ");
    Serial.print(dataTrans.pH);
    Serial.print(", ");
    Serial.println(dataTrans.moist);
  }
  
  //receive : ack
  radio.startListening();
  startWait = micros();
  while(!radio.available()){
    if(micros() - startWait > 200000){
      timeout = true;
      break;
    }
  }
  if(timeout){
    Serial.println("Time out");
  }else{
    radio.read(&ack, sizeof(int));
    Serial.print("Ack received: ");
    Serial.println(ack);
  }
  timeout = false;
  delay(1000);
}
