
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h> 
//#include "printf.h"

RF24 radio (9, 10);

const uint64_t pipe = 0xF0F0F0F0AA;
int data;
struct dataStruct
{
  int flex_4_val;
  int flex_3_val;
  int flex_2_val;
  int flex_1_val;
  int button_1_val;
  int button_2_val;
} transmitter1_data;

const int M10 = 0;
const int M11 = 1;
const int M20 = 2;
const int M21 = 3;
const int M30 = 4;
const int M31 = 5;
const int M40 = 6;
const int M41 = 7;
const int M50 = A0;
const int M51 = A1;
const int led = 8;


void setup()
{
  radio.begin();
 // printf_begin();
  Serial.begin(115200);
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  //radio.printDetails();
  delay(500);
  
  pinMode(M10,OUTPUT);
  pinMode(M11,OUTPUT);
  pinMode(M20,OUTPUT);
  pinMode(M21,OUTPUT);
  pinMode(M30,OUTPUT);
  pinMode(M31,OUTPUT);
  pinMode(M40,OUTPUT);
  pinMode(M41,OUTPUT);
  pinMode(M50,OUTPUT);
  pinMode(M51,OUTPUT);
  pinMode(led,OUTPUT);
}

void loop()
{
  while (radio.available())
  {
    //till tx-rx connection is successful, and there is data available to read, read the data and store it in the struct transmitter1_data
    
    radio.read(&data, sizeof(data));
    Serial.println("aadf");
  }

  //if connection fails or no data is available to read, print "no radio"
  Serial.println("no radio");



/*  while (1)
    {

    //          Serial.print(" // ");
    //          Serial.print(transmitter1_data.t1);
    //          Serial.print(" // ");
    //          Serial.print(transmitter1_data.s1);

    

    //   if(pip==2&&pload_width_now==sizeof(transmitter2_data))
    //  {
    //   memcpy(&transmitter2_data, rx_buf, sizeof(transmitter2_data));
    //
    //
    //
    //
    //          Serial.print(" Pressure//temp//status ");
    //          Serial.print(transmitter2_data.p1);
    //          Serial.print(" // ");
    //          Serial.print(transmitter2_data.t1);
    //          Serial.print(" // ");
    //          Serial.print(transmitter2_data.s1);
    //
    //   }
    //
    //   if(pip==3&&pload_width_now==sizeof(transmitter3_data))
    //  {
    //   memcpy(&transmitter3_data, rx_buf, sizeof(transmitter3_data));
    //
    //
    //
    //
    //          Serial.print(" Pressure//temp//status ");
    //          Serial.print(transmitter3_data.p1);
    //          Serial.print(" // ");
    //          Serial.print(transmitter3_data.t1);
    //          Serial.print(" // ");
    //          Serial.print(transmitter3_data.s1);
    //
    //   }
    //
    //


    //delay(500);*/

    
  

//////////////////////////////GRIPPER OPEN

if(transmitter1_data.button_1_val && transmitter1_data.button_2_val == 0)             //LED ON
  {
    digitalWrite(led,HIGH);
    delay(500);
  }
  else 
  {
    digitalWrite(led,LOW);
    delay(500);
  }

//////////////////////////////GRIPPER OPEN


if(transmitter1_data.button_1_val == 0)                                               //GRIPPER MOTOR CLOCKWISE
  {
    digitalWrite(M50,HIGH);
    digitalWrite(M51,LOW);
    delay(500);
  }
  else 
  {
    digitalWrite(M50,LOW);
    digitalWrite(M51,LOW);
    delay(500);
  }

//////////////////////////////GRIPPER CLOSE

if(transmitter1_data.button_2_val == 0)                                               //GRIPPER MOTOR ANTI-CLOCKWISE
  {
    digitalWrite(M50,LOW);
    digitalWrite(M51,HIGH);
    delay(500);
  }
  else 
  {
    digitalWrite(M50,LOW);
    digitalWrite(M51,LOW);
    delay(500);
  }
//////////////////////////////WRIST MOTOR

if(transmitter1_data.flex_1_val > 100 && transmitter1_data.flex_1_val < 200)          //WRIST MOTOR CLOCKWISE
  {
    digitalWrite(M10,HIGH);
    digitalWrite(M11,LOW);
    delay(500);
  }
  else if(transmitter1_data.flex_1_val > 200 && transmitter1_data.flex_1_val < 300)   //WRIST MOTOR ANTI-CLOCKWISE
  {
    digitalWrite(M10,LOW);
    digitalWrite(M11,HIGH);
    delay(500);
  }
  else                                                                                //WRIST MOTOR STOP
  {
    digitalWrite(M10,LOW);

    digitalWrite(M11,LOW);
    delay(500);
  }

//////////////////////////////ELBOW MOTOR

  if(transmitter1_data.flex_2_val > 70 && transmitter1_data.flex_2_val < 170)         //ELBOW MOTOR CLOCKWISE
  {
    digitalWrite(M20,HIGH);
    digitalWrite(M21,LOW);
    delay(500);
  }
  else if(transmitter1_data.flex_2_val > 170 && transmitter1_data.flex_2_val < 270)   //ELBOW MOTOR ANTI-CLOCKWISE
  {
    digitalWrite(M20,LOW);
    digitalWrite(M21,HIGH);
    delay(500);
  }
  else                                                                                //ELBOW MOTOR STOP
  {
    digitalWrite(M20,LOW);
    digitalWrite(M21,LOW);
    delay(500);;
  }

//////////////////////////////SHOULDER MOTOR 

  if(transmitter1_data.flex_3_val > 230 && transmitter1_data.flex_3_val < 280)        //SHOULDER MOTOR CLOCKWISE
  {
    digitalWrite(M30,HIGH);
    digitalWrite(M31,LOW);
    delay(500);
  }
  else if(transmitter1_data.flex_3_val > 280 && transmitter1_data.flex_3_val < 310)   //SHOULDER MOTOR ANTI-CLOCKWISE
  {
    digitalWrite(M30,LOW);
    digitalWrite(M31,HIGH);
    delay(500);
  }
  else                                                                                //SHOULDER MOTOR STOP
  {
    digitalWrite(M30,LOW);
    digitalWrite(M31,LOW);
    delay(500);;
  }

//////////////////////////////BASE MOTOR
 
  if(transmitter1_data.flex_4_val > 110 && transmitter1_data.flex_4_val < 210)        //BASE MOTOR CLOCKWISE
  {
    digitalWrite(M40,HIGH);
    digitalWrite(M41,LOW);
    delay(500);
  }
  else if(transmitter1_data.flex_4_val > 210 && transmitter1_data.flex_4_val < 310)   //BASE MOTOR ANTI-CLOCKWISE
  {
    digitalWrite(M40,LOW);
    digitalWrite(M41,HIGH);
    delay(500);
  }
  else                                                                                ////BASE MOTOR STOP
  {
    digitalWrite(M40,LOW);
    digitalWrite(M41,LOW);
    delay(500);
  }
}

void printValues()
{
  Serial.print("Gripper Motor Open ");
  Serial.print(transmitter1_data.button_1_val); Serial.println();

  Serial.print("Gripper Motor Close ");
  Serial.print(transmitter1_data.button_2_val); Serial.println();

  Serial.print("Wrist Motor ");
  Serial.print(transmitter1_data.flex_1_val); Serial.println();

  Serial.print("Elbow Motor ");
  Serial.print(transmitter1_data.flex_2_val); Serial.println();

  Serial.print("Shoulder Motor ");
  Serial.print(transmitter1_data.flex_3_val); Serial.println();

  Serial.print(" Base Motor ");
  Serial.print(transmitter1_data.flex_4_val); Serial.println();
  Serial.println();
  //delay(500);
  
}

