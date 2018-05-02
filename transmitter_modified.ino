
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
//#include "printf.h"
#include <Wire.h>

#define button_1_  3      //Gripper Open
#define button_2_  4      //Gripper Close
#define flex_4    A4      //Base Motor Control
#define flex_3    A3      //Shoulder Motor Control
#define flex_2    A2      //Elbow Motor Control
#define flex_1    A1      //Wrist Motor Control

int address = 0x28;
byte byte1, byte2, byte3, byte4;


RF24 radio(9, 10);
const uint64_t pipe = 0xF0F0F0F0AA;

struct dataStruct
{
  int flex_4_val;
  int flex_3_val;
  int flex_2_val;
  int flex_1_val;
  int button_1_val;
  int button_2_val;
} transmitter1_data;


void setup()
{
  pinMode(button_1_, INPUT);        //LED button
  pinMode(button_2_, INPUT);       //GRIPPER button
  pinMode(flex_1, INPUT);
  pinMode(flex_2, INPUT);
  pinMode(flex_3, INPUT);
  pinMode(flex_4, INPUT);


  Wire.begin();
  radio.begin();
  Serial.begin(115200);
  //printf_begin();

  radio.setRetries(15, 15);
  radio.openWritingPipe(pipe);
  //radio.printDetails();
}


void loop()
{

   Wire.requestFrom(address, 4); // byte is 4;

  if (Wire.available() <= 4 <= 4)
  { //
    byte1 = Wire.read();
    byte2 = Wire.read();
    byte3 = Wire.read();
    byte4 = Wire.read();
  }

  long unsigned p_counts = (long unsigned)byte1 << 8
                           | (long unsigned)byte2;
  long unsigned t_counts = (long unsigned)byte3 << 8
                           | (long unsigned)byte4;


  transmitter1_data.flex_1_val = analogRead(A1);
  transmitter1_data.flex_1_val = map(transmitter1_data.flex_1_val, 700, 900, 0, 255);

  transmitter1_data.flex_2_val = analogRead(A2);
  transmitter1_data.flex_2_val = map(transmitter1_data.flex_2_val, 700, 900, 0, 255);

  transmitter1_data.flex_3_val = analogRead(A3);
  transmitter1_data.flex_3_val = map(transmitter1_data.flex_3_val, 700, 900, 0, 255);

  transmitter1_data.flex_4_val = analogRead(A4);
  transmitter1_data.flex_4_val = map(transmitter1_data.flex_4_val, 700, 900, 0, 255);

  transmitter1_data.button_1_val = digitalRead(3);

  transmitter1_data.button_2_val = digitalRead(4);



  //int data = 9999;
  /*keep on sending data till either Rx doesnt acknowledge or timeout doesnt occur*/
  radio.write(&transmitter1_data, sizeof(transmitter1_data));
    

  Serial.println("DATA SENT!");
  printValues();

  //delay(1000);


}



void printValues()
{
  Serial.print("fLEX_1: ");
  Serial.print(transmitter1_data.flex_1_val); Serial.println();
  Serial.print("fLEX_2: ");
  Serial.print(transmitter1_data.flex_2_val); Serial.println();
  Serial.print("fLEX_3: ");
  Serial.print(transmitter1_data.flex_3_val); Serial.println();
  Serial.print("fLEX_4: ");
  Serial.print(transmitter1_data.flex_4_val); Serial.println();
  Serial.print("button_1: ");
  Serial.print(transmitter1_data.button_1_val); Serial.println();
  Serial.print("button_2: ");
  Serial.print(transmitter1_data.button_2_val); Serial.println();
  Serial.println();
  delay(1000);
}

