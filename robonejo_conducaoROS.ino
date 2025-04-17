/*    _              __  _   
     | |            / _|| |  
 ___ | |__    __ _ | |_ | |_ 
/ __|| '_ \  / _` ||  _|| __|
\__ \| | | || (_| || |  | |_ 
|___/|_| |_| \__,_||_|   \__|
                          
 *   DESENVOLVIDO POR VITOR SHAFT EM 17-JAN-2023
 *   ULTIMO UPDATE: 07-MAI-2024
 * https://github.com/vitorshaft/
 * https://instagram.com/shaftrobotica
 * shaftrobotica@gmail.com
 */

//IMPLEMENTAR THREADING
/*
#include <Thread.h>
#include <ThreadController.h>

//inicia controlador das threads a serem criadas
ThreadController controle = ThreadController();

*/
#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 9); // RX, TX

long tempo = 0;
int tempoE = 0;
int tempoD = 0;
int posicao = 0;  //inicia com valor de parada

void direito(int tempo){
  for(int i = 0; i<tempo; i++){
    digitalWrite(3, HIGH);
    delayMicroseconds(100);
    digitalWrite(3, LOW);
    delayMicroseconds(100);
  }
}

void esquerdo(int tempo){
  for(int i = 0; i<tempo; i++){
    digitalWrite(5, HIGH);
    delayMicroseconds(100);
    digitalWrite(5, LOW);
    delayMicroseconds(100);
  }
}

void conducaoEsq(int periodo){
  if((tempoE+periodo)< millis()){
    digitalWrite(5, HIGH);
    delayMicroseconds(periodo);
    digitalWrite(5, LOW);
    delayMicroseconds(periodo);
    tempoE = millis();
  }
}

void conducaoDir(int periodo){
  if((tempoD+periodo)< millis()){
    digitalWrite(3, HIGH);
    delayMicroseconds(periodo);
    digitalWrite(3, LOW);
    delayMicroseconds(periodo);
    tempoD = millis();
  }
}

void setup() {
  tempo = millis();
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  mySerial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);
}

void loop() {
  long tempo = millis();
  
  if(Serial.available()){
    posicao = Serial.parseInt(SKIP_ALL, '\n');
    //digitalWrite(13,!digitalRead(13));
    //delay(50);
    //Serial.println("comando recebido: "+ String(posicao));
  }
  if(posicao > 0){
    for(int dif = int(posicao); dif > 0; dif--){
      digitalWrite(3, !digitalRead(3));
    delayMicroseconds(100);
    }
    digitalWrite(5, !digitalRead(5));
  }
  else if(posicao < 0){
    for(int dif = int(posicao); dif < 0; dif++){
      digitalWrite(5, !digitalRead(5));
    delayMicroseconds(100);
    }
    digitalWrite(3, !digitalRead(3));
  }
  else{
    digitalWrite(3, LOW);
    digitalWrite(5, LOW);
    delayMicroseconds(100);
  }
  /*
  if(Serial.available()){
    
    Serial.println(posicao);
  }
  
  switch (posicao){
    case 8:
    digitalWrite(3, !digitalRead(3));
    delayMicroseconds(100);
    break;
    
    case 1:
    digitalWrite(3, !digitalRead(3));
    delayMicroseconds(100);
    digitalWrite(5, !digitalRead(5));
    digitalWrite(3, !digitalRead(3));
    delayMicroseconds(100);
    break;
    
    case 2:
    digitalWrite(3, !digitalRead(3));
    digitalWrite(5, !digitalRead(5));
    delayMicroseconds(100);
    digitalWrite(5, !digitalRead(5));
    digitalWrite(3, !digitalRead(3));
    delayMicroseconds(100);
    break;
    
    case 3:
    digitalWrite(5, !digitalRead(5));
    delayMicroseconds(100);
    digitalWrite(5, !digitalRead(5));
    digitalWrite(3, !digitalRead(3));
    delayMicroseconds(100);
    break;

    case 4:
    digitalWrite(5, !digitalRead(5));
    delayMicroseconds(100);
    break;
    
    case 5:
    digitalWrite(3, LOW);
    digitalWrite(5, LOW);
    delayMicroseconds(100);
    break;
    //para engatar a re
    case 6:
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    delayMicroseconds(100);
    break;
    //para voltar para frente
    case 7:
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
    delayMicroseconds(100);
    break;
  }
  //Serial.println(posicao);
  */
  
}
