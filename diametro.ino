#include <WiFiS3.h>

volatile long contadorEncoder = 0;
volatile long contadorSensorMag = 0;
volatile bool sensorDetectado = false;
volatile long ultimoContadorEncoder = 0;

const byte pinA = 2;
const byte pinB = 3;
const byte sensorMag = 12;

const int D_CILINDRO = 160;
const int PPR = 2500;
const float CIRCUNF_CILINDRO = PI * D_CILINDRO;
const float FATOR_CONTATO = 0.48; // No cilindo de cima nao tem 100% de contato com o papel e sim 48%
const float FATOR_CORRECAO = 0.891 * (1/FATOR_CONTATO); // Fator de correção para o diâmetro real da bobina pq na maquina tava dando diferença 

int voltas = 0;
long comprimentoFio = 0;
int diametroBobina = 0;
bool sentidoHorario = true;

void setup() {
  Serial.begin(115200);
  Serial.println("Sistema de Medição - Máquina de Papelão");
  Serial.println("----------------------------------------");

  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinMode(sensorMag, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinA), lerEncoder, RISING);
}

void loop() {
  if (contadorEncoder != ultimoContadorEncoder) {
    sentidoHorario = (contadorEncoder > ultimoContadorEncoder);
    ultimoContadorEncoder = contadorEncoder;
  }

  if (digitalRead(sensorMag) == LOW && !sensorDetectado) {
    contadorSensorMag++;
    
    if (sentidoHorario) {
      voltas++;
    } else {
      voltas--;
      if (voltas < 0) voltas = 0;
    }
    
    sensorDetectado = true;

    float rotacoesCilindro = abs(float(contadorEncoder) / PPR);
    comprimentoFio = long(rotacoesCilindro * CIRCUNF_CILINDRO);

    if (voltas > 0) {
      diametroBobina = int((comprimentoFio / (voltas * PI)) * FATOR_CORRECAO);
    } else {
      diametroBobina = 0;
    }

    Serial.println("----------------------------------------");
    Serial.print("Diâmetro atual da bobina: ");
    Serial.print(diametroBobina);
    Serial.println(" mm");
    Serial.println("----------------------------------------");
  } else if (digitalRead(sensorMag) == HIGH) {
    sensorDetectado = false;
  }
}

void lerEncoder() {
  if (digitalRead(pinB)) {
    contadorEncoder++;
  } else {
    contadorEncoder--;
  }
}
