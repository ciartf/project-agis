//sensor--------------------------------------------------

//di uji coba sesuai lab : kalibrasi
void pHInit(){
  int temp = analogRead(pHSensor);
  for(int i = 0; i < pHArrayLength; i++){
    pHArray[i] = temp;
  }
}

void pHSensorRead(){ 
  int pHTemp;
  //pHTemp = analogRead(pHSensor);
  //pHSensorValue = pHAverageArray(pHTemp, pHArrayLength);
  pHSensorValue = 7;
  Serial.print("pH sensor value : ");
  Serial.println(pHSensorValue);
}

int pHAverageArray(int value, int number){
  float avg;
  float sum = 0;
  for(int i = (number-1); i > 0; i--){
    pHArray[i] = pHArray[i-1];
    sum = sum + pHArray[i];
  }
  pHArray[0] = value;
  sum = sum + value;
  avg = sum / number;
  return (int)avg;
}
