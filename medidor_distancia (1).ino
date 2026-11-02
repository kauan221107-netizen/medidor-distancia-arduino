/*
  Medidor de Distância com Arduino
  Sensor ultrassônico HC-SR04 + LCD 16x2

  Melhorias desta versão:
  - Média de várias leituras (valor mais estável)
  - Ignora leituras fora da faixa do sensor (2 a 400 cm)
  - Sem piscar o display (não usa lcd.clear() a cada ciclo)
  - Uma casa decimal na distância
  - Saída também no Monitor Serial (9600 baud)
  - Código organizado em funções e constantes
*/

#include <LiquidCrystal.h>

// ---------- Pinos (mesmas ligações da versão anterior) ----------
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // RS, E, D4, D5, D6, D7
const int trigPin = 9;
const int echoPin = 10;

// ---------- Configurações ----------
const unsigned long TIMEOUT_US   = 30000;  // tempo máximo de espera do eco
const float         DIST_MIN_CM  = 2.0;    // alcance mínimo do HC-SR04
const float         DIST_MAX_CM  = 400.0;  // alcance máximo do HC-SR04
const int           NUM_LEITURAS = 5;      // leituras usadas na média
const unsigned long INTERVALO_MS = 300;    // intervalo entre atualizações

// Escreve uma linha completa no LCD (preenche com espaços para apagar o resto)
void escreverLinha(uint8_t linha, const char *texto) {
  char buf[17];
  snprintf(buf, sizeof(buf), "%-16s", texto);
  lcd.setCursor(0, linha);
  lcd.print(buf);
}

// Faz uma única medição. Retorna a distância em cm, ou -1 se não houve eco.
float lerDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duracao = pulseIn(echoPin, HIGH, TIMEOUT_US);
  if (duracao == 0) return -1;

  return duracao * 0.0343 / 2.0;
}

// Média das leituras válidas. Retorna -1 se nenhuma for válida.
float distanciaMedia() {
  float soma = 0;
  int validas = 0;

  for (int i = 0; i < NUM_LEITURAS; i++) {
    float d = lerDistancia();
    if (d >= DIST_MIN_CM && d <= DIST_MAX_CM) {
      soma += d;
      validas++;
    }
    delay(10);  // pequena pausa para o eco anterior se dissipar
  }

  if (validas == 0) return -1;
  return soma / validas;
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);

  lcd.begin(16, 2);
  escreverLinha(0, "Medidor de dist.");
  escreverLinha(1, "Iniciando...");
  delay(2000);
  lcd.clear();
}

void loop() {
  float distancia = distanciaMedia();

  if (distancia < 0) {
    escreverLinha(0, "FORA DE FAIXA");
    escreverLinha(1, "Alcance 2-400cm");
    Serial.println("Fora de faixa");
  } else {
    char numero[10];
    char linha2[17];
    dtostrf(distancia, 1, 1, numero);          // 1 casa decimal
    snprintf(linha2, sizeof(linha2), "%s cm", numero);

    escreverLinha(0, "Distancia:");
    escreverLinha(1, linha2);

    Serial.print("Distancia: ");
    Serial.print(numero);
    Serial.println(" cm");
  }

  delay(INTERVALO_MS);
}
