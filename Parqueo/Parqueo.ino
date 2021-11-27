

//-------Proyecto 3 Electrónica Digital 2---------//
//--------------Parqueo--------------//

#include <stdint.h>
#include <stdbool.h>
#include <TM4C123GH6PM.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

//***************************************************************************************************************************************
// Prototipos
//***************************************************************************************************************************************

//***************************************************************************************************************************************
// Variables
//***************************************************************************************************************************************
uint8_t Indicador1 = 0;
uint8_t Indicador2 = 0;
uint8_t Indicador3 = 0;
uint8_t Indicador4 = 0;
uint8_t Indicador5 = 0;
uint8_t Indicador6 = 0;
uint8_t Indicador7 = 0;
uint8_t Indicador8 = 0;
String inputString = "";
const char separador = ',';
int verificador[4];
bool stringComplete = false;

void setup() {
  // put your setup code here, to run once:
  // start serial port at 9600 bps:
  Serial2.begin(115200);
  Serial3.begin(115200);
  //Salidas de los indicadores
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  
  pinMode(23, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(23), Indicador_1, RISING);
  attachInterrupt(digitalPinToInterrupt(24), Indicador_2, RISING);
  attachInterrupt(digitalPinToInterrupt(25), Indicador_3, RISING);
  attachInterrupt(digitalPinToInterrupt(26), Indicador_4, RISING); 

  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);

  inputString.reserve(200);
}

void loop() {
  // put your main code here, to run repeatedly: 
  //1001
  if(Serial3.available()){
    char inChar = (char)Serial3.read();
    inputString = inChar;
    if(inputString == "-"){
      inputString = "";
      for(int n = 0; n < 4; n++){
        char inChar = (char)Serial3.read();
        inputString += inChar;     
      }
   }
    Serial2.println(inputString);
  }

   for(size_t i = 0; i < inputString.length(); i++){
        verificador[i] = inputString.charAt(i);
   }
    
  /*Serial2.println(verificador[0]);
  Serial2.println(verificador[1]);
  Serial2.println(verificador[2]);
  Serial2.println(verificador[3]);*/
    
  Serial2.println(Indicador1);
  Serial2.println(Indicador2);
  Serial2.println(Indicador3);
  Serial2.println(Indicador4);
  Serial2.println(Indicador5);
  Serial2.println(Indicador6);
  Serial2.println(Indicador7);
  Serial2.println(Indicador8);
}

void Indicador_1(){
  if(digitalRead(2)==1){
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    Indicador1 = 1;
  }
  else if(digitalRead(2)==0){
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    Indicador1 = 0;
  }
}

void Indicador_2(){
  if(digitalRead(4)==1){
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    Indicador2 = 1;
  }
  else if(digitalRead(4)==0){
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    Indicador2 = 0;
  }
}

void Indicador_3(){
  if(digitalRead(6)==1){
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    Indicador3 = 1;
  }
  else if(digitalRead(6)==0){
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    Indicador3 = 0;
  }
}

void Indicador_4(){
  if(digitalRead(8)==1){
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    Indicador4 = 1;
  }
  else if(digitalRead(8)==0){
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    Indicador4 = 0;
  }
}
