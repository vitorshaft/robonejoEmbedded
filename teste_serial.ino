void setup() {
  // Inicializar a comunicação serial com a taxa de transmissão de 9600 bps
  Serial.begin(9600);
}

void loop() {
  // Verificar se há dados disponíveis para leitura na porta serial
  if (Serial.available() > 0) {
    // Ler o dado recebido do Raspberry Pi
    char receivedChar = Serial.read();

    // Enviar uma resposta de volta para o Raspberry Pi
    Serial.println("Received: " + String(receivedChar));

    // Aguardar um breve intervalo antes de enviar a próxima resposta
    delay(1000);
  }
}
