uint32_t lxCount = millis();
void getLight () {
  uint32_t currentMillis = millis();
  uint32_t offset = currentMillis - lxCount;
  if(offset > mOffset){
    lux = lightMeter.readLightLevel();
    lxCount = currentMillis;
  }
}

