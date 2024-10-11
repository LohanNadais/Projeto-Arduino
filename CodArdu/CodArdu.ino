const int sensorPin = A0;            // Pino analógico do sensor
const float limite = 2.0;             // Limite de força em Newtons
const unsigned long intervalo = 10 * 60 * 1000; // 10 minutos em milissegundos

unsigned long tempoUltimoEstado = 0;  // Armazena o tempo do último estado
bool estadoOcupado = false;            // Indica se está ocupado

// Comunicação Serial
void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {
  // Leitura do sensor e conversão para força
  float force = (analogRead(sensorPin) / 1023.0) * 10.0;

  unsigned long tempoAtual = millis();

  // Verifica se a força está acima do limite
  if (force >= limite) {
    // Se estava desocupado e agora está ocupado
    if (!estadoOcupado) {
      estadoOcupado = true;            // Atualiza o estado
      tempoUltimoEstado = tempoAtual;  // Registra o tempo
    } else if (tempoAtual - tempoUltimoEstado >= intervalo) {
      Serial.println("OCUPADO");       // Envia para o Python o estado de ocupado
    }
  } else {
    // Se estava ocupado e agora está desocupado
    if (estadoOcupado) {
      estadoOcupado = false;           // Atualiza o estado
      tempoUltimoEstado = tempoAtual;  // Registra o tempo
    } else if (tempoAtual - tempoUltimoEstado >= intervalo) {
      Serial.println("VAGO");           // Envia para o Python o estado de vago
    }
  }

  delay(1000); // Aguarda 1 segundo antes da próxima leitura
}
