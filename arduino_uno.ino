#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)      // Arduino UNO
    #include <AltSoftSerial.h>
    AltSoftSerial bc95serial;
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)   // Arduino MEGA2560
    #define bc95serial Serial1
#endif

#include <Arduino.h>
#include <DHT.h>
#include <BC95Udp.h>
#include <MicrogearNB.h>

#define SERVER_IP     IPAddress(34, 87, 33, 176)
#define SERVER_PORT   33333

BC95UDP udpclient;
Microgear microgear(&udpclient);
#define MAXBUFFSIZE 128


char payload[MAXBUFFSIZE];
//uint8_t udpdata[MAXBUFFSIZE];
uint8_t buff[MAXBUFFSIZE];

void printHEX(uint8_t *buff, size_t len) {
    for (int i=0; i<len; i++) {
        /*
        if (buff[i]<16) Serial.print(" 0");
        else Serial.print(" ");
        */
//        Serial.print(char(buff[i]));

        if (i == 0) {
          Serial.print("V1: ");
          Serial.print(char(buff[i]));
          Serial.print(" ");
          if (char(buff[i]) == '0') {
            Serial.println("OFF");
            digitalWrite(3, LOW);
          } else {
            Serial.println("ON");
            digitalWrite(3, HIGH);
          }
        }

        else if (i == 1) {
          Serial.print("V2: ");
          Serial.print(char(buff[i]));
          Serial.print(" ");
          if (char(buff[i]) == '0') {
            Serial.println("OFF");
            digitalWrite(4, LOW);
          } else {
            Serial.println("ON");
            digitalWrite(4, HIGH);
          }
        }

        else if (i == 2) {
          Serial.print("V3: ");
          Serial.print(char(buff[i]));
          Serial.print(" ");
          if (char(buff[i]) == '0') {
            Serial.println("OFF");
            digitalWrite(5, LOW);
          } else {
            Serial.println("ON");
            digitalWrite(5, HIGH);
          }
        }

        else if (i == 3) {
          Serial.print("V4: ");
          Serial.print(char(buff[i]));
          Serial.print(" ");
          if (char(buff[i]) == '0') {
            Serial.println("OFF");
            digitalWrite(6, LOW);
          } else {
            Serial.println("ON");
            digitalWrite(6, HIGH);
          }
        }

        else if (i == 4) {
          Serial.print("V5: ");
          Serial.print(char(buff[i]));
          Serial.print(" ");
          if (char(buff[i]) == '0') {
            Serial.println("OFF");
            digitalWrite(7, LOW);
          } else {
            Serial.println("ON");
            digitalWrite(7, HIGH);
          }
        }

        else if (i == 5) {
          Serial.print("V6: ");
          Serial.print(char(buff[i]));
          Serial.print(" ");
          if (char(buff[i]) == '0') {
            Serial.println("OFF");
            digitalWrite(8, LOW);
          } else {
            Serial.println("ON");
            digitalWrite(8, HIGH);
          }
        }

        else if (i == 6) {
          Serial.print("V7: ");
          Serial.print(char(buff[i]));
          Serial.print(" ");
          if (char(buff[i]) == '0') {
            Serial.println("OFF");
            digitalWrite(9, LOW);
          } else {
            Serial.println("ON");
            digitalWrite(9, HIGH);
          }
        }

        else if (i == 7) {
          Serial.print("V8: ");
          Serial.print(char(buff[i]));
          Serial.print(" ");
          if (char(buff[i]) == '0') {
            Serial.println("OFF");
            digitalWrite(10, LOW);
          } else {
            Serial.println("ON");
            digitalWrite(10, HIGH);
          }
        }

        else if (i == 8) {
          Serial.print("V9: ");
          Serial.print(char(buff[i]));
          Serial.print(" ");
          if (char(buff[i]) == '0') {
            Serial.println("OFF");
            digitalWrite(11, LOW);
          } else {
            Serial.println("ON");
            digitalWrite(11, HIGH);
          }
        }
    }
}

void setup() {
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    
    bc95serial.begin(9600);
    BC95.begin(bc95serial);
    BC95.reset();
    
    Serial.begin(9600);
    Serial.println(F("Microgear Arduino NB-IoT Start!"));
    Serial.print(F("IMEI: "));
    Serial.println(BC95.getIMEI());
    Serial.print(F("IMSI: "));
    Serial.println(BC95.getIMSI());
    Serial.print(F("Attach Network..."));
    while (!BC95.attachNetwork()) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println(F("\nNB-IOT attached!"));
    Serial.print(F("RSSI: "));
    // ค่าความแรงสัญญาณ NB-IoT
    Serial.println(BC95.getSignalStrength()); 
    Serial.print(F("IPAddress: "));
    Serial.println(BC95.getIPAddress());

    
}

void loop() {
    int cnt = 0;
    delay(10000);
    Serial.println(F("Start Send to UDP Server"));
    Serial.print(F("updData: "));

    udpclient.begin(SERVER_PORT);
    udpclient.beginPacket(SERVER_IP, SERVER_PORT);  
    uint8_t udpdata[] = "ACK:000000000";
    udpclient.write(udpdata, sizeof(udpdata));
    udpclient.endPacket();

    Serial.println(F("Send completed and Waiting for response"));
    while (udpclient.parsePacket() == 0) {
        cnt++;
        delay(500);
        if (cnt == 10) {
          break;
        }
    }

    Serial.println(F("Reading a response"));
    size_t len = udpclient.read(buff, MAXBUFFSIZE);

    Serial.println(F("\n\nReceive Message from Server : "));
    printHEX(buff, len);
    udpclient.stop();
    delay(5000);
    Serial.println();
}