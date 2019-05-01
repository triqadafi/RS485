#include <SoftwareSerial.h>

#define TLMT_RS485_RO 12 //RX
#define TLMT_RS485_DI 9 //TX

#define TLMT_RS485_DE 11  //RS485 Direction control
#define TLMT_RS485_RE 10  //RS485 Direction control

#define TLMT_RS485_TRANSMIT HIGH
#define TLMT_RS485_RECEIVE LOW

#define TLMT_LED  13

SoftwareSerial RS485Serial(TLMT_RS485_RO, TLMT_RS485_DI); // RX, TX

int byteReceived;
int byteSend;

void setup(){
  // Start the built-in serial port, probably to Serial Monitor
  Serial.begin(9600);
  Serial.println("Test");

  pinMode(TLMT_LED, OUTPUT); digitalWrite(TLMT_LED, HIGH);
  pinMode(TLMT_RS485_DE, OUTPUT); digitalWrite(TLMT_RS485_DE, LOW);
  pinMode(TLMT_RS485_RE, OUTPUT); digitalWrite(TLMT_RS485_RE, LOW);

  RS485Serial.begin(4800);
}

void loop(){
  if (Serial.available()){
    digitalWrite(TLMT_LED, HIGH);

    beginTransmission();
    RS485Serial.write(Serial.read());
    endTransmission();
    
    delay(10); digitalWrite(TLMT_LED, LOW);
  }

  if (RS485Serial.available()){
    digitalWrite(TLMT_LED, HIGH);
    
    Serial.write(RS485Serial.read());
    
    delay(10); digitalWrite(TLMT_LED, LOW);
  }

}

void beginTransmission(){
  digitalWrite(TLMT_RS485_DE, TLMT_RS485_TRANSMIT);
  digitalWrite(TLMT_RS485_RE, TLMT_RS485_TRANSMIT);
}
void endTransmission(){
  digitalWrite(TLMT_RS485_DE, TLMT_RS485_RECEIVE);
  digitalWrite(TLMT_RS485_RE, TLMT_RS485_RECEIVE);
}