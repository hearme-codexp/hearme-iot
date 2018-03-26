#include "SoftwareSerial.h"
int microphone = A0;
int viber = 5;
SoftwareSerial bluetooth(3, 2);
unsigned long inicioVibracao;

#define DURACAO_VIBRACAO 300
#define SENSIBILIDADE 100
#define INTERVALO_LEITURA 10
#define BAUD_RATE 9600
#define PORCENTAGEM_DE_GIRO_ALTO 1.15
#define PORCENTAGEM_DE_GIRO_BAIXO 1.1
#define THRESHOLD 6
//Media
const int numReadings = 50;

int readings[numReadings];
int readIndex = 0;
int total = 0;
float average = 0.0;
int counter = 0;
bool validator = false;
//


void setup()
{
  pinMode(viber, OUTPUT);
  pinMode(microphone, INPUT);
  Serial.begin(9600);
  bluetooth.begin(BAUD_RATE);
  //
  int valorInicial = analogRead(microphone);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = valorInicial;
  }
  total = valorInicial * numReadings;

  //
}
void loop()
{
  counter++;
  ///
  // subtract the last reading:
  int old = readings[readIndex];
  total = total - old;
  // read from the sensor:
  int now = analogRead(microphone);
  readings[readIndex] = now;

  // add the reading to the total:
  total = total + now;
  // advance to the next position in the array:
  readIndex++;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  float oldAverage = average;
  average = total / numReadings;

  float variance = (now - old) * (now - average + old - oldAverage) / (numReadings - 1);
  float stddev = sqrt(variance);

  /*
    Serial.print(now);
    Serial.print(',');
    Serial.print(average);
    Serial.print(',');
  */

  Serial.println(stddev);

  if ( ( stddev > THRESHOLD )  && validator == false )
  {
    if ( average  > 0 ) {
      comecarVibrar();
      validator = true;
    }
  }
  // determinar se é pra parar
  if (inicioVibracao > 0 && inicioVibracao + DURACAO_VIBRACAO < millis())
  {
    pararVibrar();
  }

  // TODO: calibrar valor abaixo
  if (counter == 100) {
    validator = false;
    counter = 0;
  }
  delay(INTERVALO_LEITURA);
}

void enviarHistoricoVibracao()
{
  bluetooth.println("[v]=1");
}

void comecarVibrar()
{
  inicioVibracao = millis();
  digitalWrite(viber, HIGH);
  enviarHistoricoVibracao();
}
void pararVibrar()
{
  digitalWrite(viber, LOW);
  inicioVibracao = 0;
}
