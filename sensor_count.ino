#define OLED_ADDR 0x3C
#define BH1750_ADDR 0x23
#define AHT10_ADDR 0x38
#define MPU6050_ADDR 0x68
#define SR04_ADDR 0x57

volatile bool OLED_ConnectFlag=0;
volatile bool BH1750_ConnectFlag=0;
volatile bool SR04_ConnectFlag=0;
volatile bool AHT10_ConnectFlag=0;
volatile bool MPU6050_ConnectFlag=0;

byte error, address;
int sensorCount=0;
int sensorInit_Fail=0;

void sensorSetup() {
  for(address=0; address<127; address++) {
    Wire.beginTransmission(address);
    error=Wire.endTransmission();

    if(error==0) {
      if(address==OLED_ADDR) {
        OLED_ConnectFlag=1;
        OLEDSetup();
      }else if(address==BH1750_ADDR) {
        BH1750_ConnectFlag=1;
        BH1750Setup();
      }else if(address==SR04_ADDR) {
        SR04_ConnectFlag=1;
        sr04Setup();
      }else if(address==AHT10_ADDR) {
        AHT10_ConnectFlag=1;
        AHT10Setup();
      }else if(address==MPU6050_ADDR) {
        MPU6050_ConnectFlag=1;
        MPU6050Setup();
      }
      sensorCount++;
    }else if(error==4) {
      sensorInit_Fail=1;
    }
  }
  Serial.print(sensorCount);
  Serial.println(" sensors detected!");
}

