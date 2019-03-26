#include <Wire.h>

#define ADC_PIN 5
#define SDA 0
#define SCK 2
#define START_PIN 3
#define DISPLAY_ADRESS 0x71
#define R_LOAD 200000 //Load resistance of 200k


char tmp_str[4];

int sensor_read;
int V_sensor;
int BAC_VALUE;
int R_Ratio;
int ConversionFactorToBac = 520;
int Conversion;
int R_0;
int startButton;
int loopTime;
int R_AIR;
int R_S;

void setup() 
{
  Wire.begin();
  Wire.beginTransmission(DISPLAY_ADRESS);
  Wire.write(0x76); //clear screen
  Wire.endTransmission();
  V_sensor = (5-(analogRead(ADC_PIN)*5/1024));
  R_AIR = V_sensor/(1-V_sensor)*R_LOAD;
  R_0 = R_AIR/2.51;
}

void loop() 
{
/*  while (startButton < 512) {
    startButton = analogRead(START_PIN);
  }
*/ 
  startButton = 0; 
  while (startButton < 512) {
  startButton = analogRead(START_PIN);
  V_sensor = (5-(analogRead(ADC_PIN)*5/1024));
  R_S = V_sensor/(1-V_sensor)*R_LOAD; 
  R_Ratio = R_S/R_0;
  BAC_VALUE = R_Ratio*2;
  BAC_VALUE = BAC_VALUE*524;
  Wire.beginTransmission(DISPLAY_ADRESS);
  for (int i =0; i < 4; i++){
    Wire.write(tmp_str[i]);
  }
  loopTime++;

  }
  sprintf(tmp_str, "%d", BAC_VALUE);
  
  Wire.beginTransmission(DISPLAY_ADRESS);
  for (int i =0; i < 4; i++){
    Wire.write(tmp_str[i]);
  }
}
