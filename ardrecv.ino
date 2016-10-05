#include<VirtualWire.h>
#define recvp 17
#define rlp 16
#define cmdl 2
#define ascii0 48
#define ascii1 49

void dcdr(uint8_t buf[]){
  switch(buf[0]){
    case ascii1:
      if(buf[1]==ascii0)
        digitalWrite(rlp,LOW);
      else if(buf[1]==ascii1)
        digitalWrite(rlp,HIGH);
      break;
  }
}

void setup(){
  Serial.begin(115200);
  pinMode(rlp,OUTPUT);
  vw_set_rx_pin(recvp);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);   // Bits per sec
  vw_rx_start();       // Start the receiver PLL running
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if (vw_get_message(buf, &buflen)){
    for(byte i=0;i<cmdl;i++) Serial.print((buf[i]==48)?0:1);
    dcdr(buf);
    Serial.println();
  }
}
