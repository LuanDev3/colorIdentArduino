// Site de apoio -> https://www.savageelectronics.com/blog/arduino-biblioteca-dynamixel
#include "DynamixelSerial.h"

int ldrPin = 0;                       // Analógico pino 0
int ldrRedValor = 0;                     // Valor do LDR
int ldrGreenValor = 0;                //
int ledVermelho = 2;                  // Led vermelho
int ledVerde = 7;                     //Led verde     

void setup(){
  Dynamixel.setSerial(&Serial); // Seta o serial
  Dynamixel.begin(1000000,2);   // Inicializa a comunicação com Br 1 Mbps
  delay(1000);                  // Tempo de setagem
  Dynamixel.setTempLimit(1, 80);           // Seta a temperatura máxima para 80
  Dynamixel.setVoltageLimit(1, 65, 160);   // Seta a tensao entre 6.5v to 16v
  Dynamixel.setMaxTorque(1,512);           // limite de torque de 50 %
  Dynamixel.setSRL(1,2);                   // Seta o SRL
}

void ldr(){
  ldrGreenValor = 0;
  ldrRedValor = 0;
  digitalWrite(ledVermelho, HIGH);
  digitalWrite(ledVerde, LOW);
  for (int i=0; i<10; i++){
    ldrGreenValor += analogRead(ldrPin);
  }
  ldrGreenValor = ldrGreenValor/10;
  delay(500);
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledVerde, HIGH);
  for (int i=0; i<10; i++){
    ldrRedValor += analogRead(ldrPin);
  }
  ldrRedValor = ldrRedValor/10;
  delay(500);
  digitalWrite(ledVerde, LOW);
  Serial.print("Vermelho -> ");
  Serial.print(ldrRedValor);
  Serial.print("\n");
  Serial.print("Verde -> ");
  Serial.print(ldrGreenValor);
  Serial.print("\n");
}

void controlServo(){
  if (ldrGreenValor > 800 and ldrRedValor < 550){
    Dynamixel.ledStatus(1, ON);              // Liga a luz do servo
    Dynamixel.move(1, 0);                  // Move to Servo para 200
    delay(2000);
  }
  Dynamixel.move(1, 400);
  Dynamixel.ledStatus(1, OFF);               // Desliga o LED
}

void loop(){
  ldr();
  controlServo();
}
