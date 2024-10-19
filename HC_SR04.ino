#define SR04_ADDR 0x57

byte ds[3];
int SR04_buf;
unsigned long sr04_distance=0;

void sr04Setup() {
  ds[0]=0;
  ds[1]=0;
  ds[2]=0;
}

void getSR04data() {
  Wire.beginTransmission(SR04_ADDR);
  Wire.write(1);
  Wire.endTransmission();
  delay(150); //1 cycle approx. 100mS.
  SR04_buf=0;
  Wire.requestFrom(SR04_ADDR,3); //read distance       
  while (Wire.available()) {
    ds[SR04_buf++] = Wire.read();
  }

  sr04_distance = (unsigned long)(ds[0]) * 65536;
  sr04_distance = sr04_distance + (unsigned long)(ds[1]) * 256;
  sr04_distance = (sr04_distance + (unsigned long)(ds[2])) / 10000;
  
  if(sr04_distance>=900) {
    sr04_distance=0;
  }

  // Serial.print("Distance:");
  // Serial.print(distance);
  // Serial.println("cm");
}
