#include <Wire.h>
#include<VirtualWire.h>
typedef unsigned short int usi;
#define ardaddr 10
#define txpin 2
String cmnd="";
bool i2crecv=false;
 
void setup() {
  Serial.begin(115200);
  Wire.begin(ardaddr);
  Wire.onReceive(onesprecv);
  vw_set_tx_pin(txpin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);
}

void loop() {
  usi strtt=millis();
  if(i2crecv){
    /*Serial.println(cmnd.c_str());
    Serial.println(cmnd.length());*/
    vw_send((uint8_t *)cmnd.c_str(),cmnd.length());
    vw_wait_tx(); // Wait until the whole message is gone;
    i2crecv=false;
    Serial.println("trtd");
  }
}

void onesprecv(int amnt){
  cmnd=""; i2crecv=true;
  while (Wire.available()){
    cmnd+=Wire.read();
  }
  Serial.println(cmnd);
}

