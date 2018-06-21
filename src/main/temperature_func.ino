uint32_t hCount = millis();
void getValueHiTemperatureSensors (){
//  int divide = 0;
//  int allTemp = 0;
  uint32_t currentMillis = millis();
  uint32_t offset = currentMillis - hCount;
  if(offset > mOffset){
    for (uint8_t i = 0; i < 2; i++){
      DHT dht(TemperatureSensorHiPins[i], DHTTYPE);
      dht.begin();
      if (TemperatureSensorHiSwitch[i]){
        if(dht.readHumidity() > 0 && dht.readTemperature() > 0){
          TemperatureSensorHiValueHumidity[i] = dht.readHumidity();
//          TemperatureSensorHiValueTemperature[i] = dht.readTemperature();
        }
      }
    }
    TemperatureSensorHiValueTemperature[0] = sensors.getTempC(TH0);
//    Serial.println(TemperatureSensorHiValueTemperature[0]);
    TemperatureSensorHiValueTemperature[1] = sensors.getTempC(TH1);
//    Serial.println(TemperatureSensorHiValueTemperature[1]);
    hCount = currentMillis;
    if (debug == 2){
      Serial.println("");
    }
  }
}

uint32_t lCount = millis();
void getValueLowTemperatureSensors (){
//  int divide;
//  int allTemp;
  uint32_t currentMillis = millis();
  uint32_t offset = currentMillis - lCount;
  if(offset > mOffset){
    for (uint8_t i = 0; i < 2; i++){
      DHT dht(TemperatureSensorLowPins[i], DHTTYPE);
      dht.begin();
      if (TemperatureSensorLowSwitch[i]){
        if(dht.readHumidity() > 0 && dht.readTemperature() > 0){
          TemperatureSensorLowValueHumidity[i] = dht.readHumidity();
//          TemperatureSensorLowValueTemperature[i] = dht.readTemperature();
        }
      } else {
        if (debug == 2){
          Serial.print("Low T");
          Serial.print(i);
          Serial.println(" sensor is OFF ");
	      }
      }
    }
    TemperatureSensorLowValueTemperature[0] = sensors.getTempC(TL0);
//    Serial.println(TemperatureSensorLowValueTemperature[0]);
    TemperatureSensorLowValueTemperature[1] = sensors.getTempC(TL1);
//    Serial.println(TemperatureSensorLowValueTemperature[1]);
    lCount = currentMillis;
    if (debug == 2){
      Serial.println("");
    }
  }
}

void getRealTemperatureHi () {
  int8_t divide = 0;
  int8_t allTemp = 0;
  for (uint8_t i = 0; i < 2; i++) {
    if(TemperatureSensorHiValueTemperature[i] > 0){
      if (TemperatureSensorHiSwitch[i]) {
        divide++;
        allTemp = allTemp + TemperatureSensorHiValueTemperature[i];
      }
    }
  }
  if (debug == 1) {
    Serial.print("Divide Hi: ");
    Serial.println(divide);
    Serial.print("Real allTemp Hi: ");
    Serial.println(allTemp);
  }
  if (divide != 0) {
    realTemperatureHi = allTemp / divide;
    if (debug == 1) {
      Serial.print("Real Temp Hi: ");
      Serial.println(realTemperatureHi);
    }
  }
  if (debug == 1) {
    Serial.println();
  }
}

void getRealTemperatureLow () {
  int8_t divide = 0;
  int8_t allTemp = 0;
  for (uint8_t i = 0; i < 2; i++) {
    if (TemperatureSensorLowSwitch[i]) {
      if(TemperatureSensorLowValueTemperature[i] > 0){
        divide++;
        allTemp = allTemp + TemperatureSensorLowValueTemperature[i];
      }
    }
  }
  if (debug == 1) {
    Serial.print("Divide Low: ");
    Serial.println(divide);
    Serial.print("Real allTemp Low: ");
    Serial.println(allTemp);
  }
  if (divide != 0) {
    realTemperatureLow = allTemp / divide;
    if (debug == 1) {
      Serial.print("Real Temp Low: ");
      Serial.println(realTemperatureLow);
    }
  }
  if (debug == 1) {
    Serial.println();
  }
}

void getRealHumidityLow () {
  int8_t divide = 0;
  int8_t allHum = 0;
  for (uint8_t i = 0; i < 2; i++) {
    if (TemperatureSensorLowSwitch[i]) {
      if(TemperatureSensorLowValueHumidity[i] > 0){
        divide++;
        allHum = allHum + TemperatureSensorLowValueHumidity[i];
      }
    }
  }
  if (debug == 1) {
    Serial.print("Divide Low: ");
    Serial.println(divide);
    Serial.print("Real allHum Low: ");
    Serial.println(allHum);
  }
  if (divide != 0) {
    realHumidity = allHum / divide;
    if (debug == 1) {
      Serial.print("Real Humidity: ");
      Serial.println(realHumidity);
    }
  }
  if (debug == 1) {
    Serial.println();
  }
}

void getTemperatureDifference () {
  realTemperatureDifference = realTemperatureHi - realTemperatureLow;
}
