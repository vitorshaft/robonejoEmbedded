#include <Arduino.h>
#include <Ps3Controller.h>

// Pinos do motor esquerdo
#define PUL_ESQ 12
#define DIR_ESQ 14

// Pinos do motor direito
#define PUL_DIR 26
#define DIR_DIR 27

// Variáveis de controle
int velocidadeEsq = 0;
int velocidadeDir = 0;

// Função para controlar motor individual
void motor(int pulPin, int dirPin, bool dir, int vel) {
    digitalWrite(dirPin, dir);
    digitalWrite(pulPin, HIGH);
    delayMicroseconds(1000 - vel);
    digitalWrite(pulPin, LOW);
    delayMicroseconds(1000 - vel);
}

// Callback quando houver evento do PS3
void onPs3Event() {
    int ly = Ps3.data.analog.stick.ly;  // Frente/Trás
    int lx = Ps3.data.analog.stick.lx;  // Curva
    int rx = Ps3.data.analog.stick.rx;  // Rotação axial

    // Inicializa velocidades baseadas no LY
    int baseSpeed = map(ly, -128, 127, -600, 600);  // mapa de -600 a 600

    // Curvas diferenciais (LX)
    int curvaAdjust = map(lx, -128, 127, -300, 300); // diminui/ajusta motor para curva

    // Rotação axial (RX)
    int rotacao = map(rx, -128, 127, -600, 600);

    // Se o stick direito estiver mexido (rotação pura), ignora LY e LX
    if (abs(rx) > 10) {
        velocidadeEsq = rotacao;
        velocidadeDir = -rotacao;
    }
    else {
        // Stick esquerdo para mover normal e fazer curvas
        velocidadeEsq = baseSpeed + curvaAdjust;
        velocidadeDir = baseSpeed - curvaAdjust;
    }

    // (Opcional) Debug:
    Serial.print("LY: "); Serial.print(ly);
    Serial.print(" LX: "); Serial.print(lx);
    Serial.print(" RX: "); Serial.print(rx);
    Serial.print(" | VEL_ESQ: "); Serial.print(velocidadeEsq);
    Serial.print(" VEL_DIR: "); Serial.println(velocidadeDir);
}

void setup() {
    pinMode(DIR_ESQ, OUTPUT);
    pinMode(PUL_ESQ, OUTPUT);
    pinMode(DIR_DIR, OUTPUT);
    pinMode(PUL_DIR, OUTPUT);

    Serial.begin(115200);
    Ps3.begin();
    Ps3.attach(onPs3Event);
    Serial.println("Controle PS3 conectado!");
}

void loop() {
    // Controle motor esquerdo
    if (abs(velocidadeEsq) > 10) {  // deadzone pra evitar motor vibrando parado
        motor(PUL_ESQ, DIR_ESQ, (velocidadeEsq > 0) ? LOW : HIGH, abs(velocidadeEsq));
    }

    // Controle motor direito
    if (abs(velocidadeDir) > 10) {
        motor(PUL_DIR, DIR_DIR, (velocidadeDir > 0) ? LOW : HIGH, abs(velocidadeDir));
    }

    delay(1);  // Pequeno delay para não sobrecarregar o loop
}
