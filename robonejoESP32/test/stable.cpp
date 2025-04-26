#include <Arduino.h>
#include <Ps3Controller.h>

#define PUL 12
#define DIR 14


void motor(bool dir, int vel){
    digitalWrite(DIR, dir);
    //delayMicroseconds(200);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(1000-vel);
    digitalWrite(PUL, LOW);
    delayMicroseconds(1000-vel);
}

// Variável para armazenar o comando atual
int motorCommand = 0;
int y = 0;

// Callback quando o botão do controle é pressionado
void onPs3Event() {
    // Comando de velocidade

    if (Ps3.data.button.up) {
        motorCommand = 100; // Velocidade positiva
        motor(HIGH,500);
    } else if (Ps3.data.button.down) {
        motorCommand = -100; // Velocidade negativa
        motor(LOW,500);
    } else {
        motorCommand = 0; // Parado
    }

    // Envia comando pela Serial
    //Serial.println(motorCommand);

    //if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ){
        //Serial.print("Moved the left stick:");
        //Serial.print(" x="); Serial.print(Ps3.data.analog.stick.lx, DEC);
        //Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ly, DEC);
        y = map(int(Ps3.data.analog.stick.ly), -130, 130, -600, 600);
        //Serial.println();
        Serial.println(y);
        /*
        while(y<0){
            motor(HIGH,y);
        }
        while(y>0){
            motor(LOW,y);
        }
        while(y == 0){
            Serial.println("motor parado");
        }
        */
     //}
 /*
    //if( abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 ){
        Serial.print("Moved the right stick:");
        Serial.print(" x="); Serial.print(Ps3.data.analog.stick.rx, DEC);
        Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ry, DEC);
        int x = map(int(Ps3.data.analog.stick.ry), -130, 130, 0, 900);
        Serial.println();
        Serial.println(x);
        motor(LOW,x);
    //}
    */
}
    

void setup() {
    pinMode(DIR, OUTPUT);
    pinMode(PUL, OUTPUT);
    Serial.begin(115200); // Comunicação com Arduino
    Ps3.begin();
    Ps3.attach(onPs3Event);
    Serial.println("Controle PS3 conectado!");
}

void loop() {
    if(y<0){
        motor(HIGH,-y);
    }
    else if(y>0){
        motor(LOW,y);
    }
    else{
        Serial.println("motor parado");
    }
}