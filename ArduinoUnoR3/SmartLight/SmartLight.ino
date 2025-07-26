// https://wiki.dfrobot.com/SKU_SEN0539-EN_Gravity_Voice_Recognition_Module_I2C_UART
#include "DFRobot_DF2301Q.h"

DFRobot_DF2301Q_I2C asr;

const int ledPin = 13;

void setup() {
  Serial.begin(115200);

  while (!(asr.begin())) {
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Communication with device success");

  asr.setVolume(7);
  asr.setMuteMode(0);
  asr.setWakeTime(20);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
}

void loop() {
  uint8_t CMDID = asr.getCMDID();
  switch (CMDID) {
    case 103:
    case 5:
      digitalWrite(ledPin, LOW);
      Serial.println("Turn on the light");
      break;

    case 104:
    case 6:
      digitalWrite(ledPin, HIGH);
      Serial.println("Turn off the light");
      break;

    default:
      if (CMDID != 0) {
        Serial.print("CMDID = ");
        Serial.println(CMDID);
      }
  }
  delay(300);
}
