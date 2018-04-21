//sensor--------------------------------------------------

//di uji coba sesuai lab : kalibrasi
void moistInit(){
  int temp = analogRead(moistSensor);
  for(int i = 0; i < moistArrayLength; i++){
    moistArray[i] = temp;
  }
}

void moistSensorRead(){ 
  int moistTemp;
  //moistTemp = analogRead(moistSensor);
  //moistSensorValue = moistAverageArray(moistTemp, moistArrayLength);
  moistSensorValue = 400;
  Serial.print("moist sensor value : ");
  Serial.println(moistSensorValue);
}

int moistAverageArray(int value, int number){
  float avg;
  float sum = 0;
  for(int i = (number-1); i > 0; i--){
    moistArray[i] = moistArray[i-1];
    sum = sum + moistArray[i];
  }
  moistArray[0] = value;
  sum = sum + value;
  avg = sum / number;
  return (int)avg;
}
