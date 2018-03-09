#include "SoftwareSerial.h"
#include <ArduinoJson.h>
int anterior = 0;
int microphone = A0;
int viber = 5;
unsigned long inicioVibracao;

#define DURACAO_VIBRACAO 300
#define SENSIBILIDADE 100
#define INTERVALO_LEITURA 20

StaticJsonBuffer<100> jsonBuffer;
SoftwareSerial bluetooth(2, 3);
void setup()
{
  pinMode(viber, OUTPUT);
  pinMode(microphone, INPUT);
  Serial.begin(9600);
  bluetooth.begin(115200);
}
void loop()
{
  int now = analogRead(microphone);
  Serial.println(now);
  delay(INTERVALO_LEITURA);
  if (now > anterior + SENSIBILIDADE)
  {
    comecarVibrar();
  }

  // determinar se é pra parar
  if (inicioVibracao > 0 && inicioVibracao + DURACAO_VIBRACAO < millis())
  {
    pararVibrar();
  }

  anterior = now;
}

void enviarHistoricoVibracao()
{
  // formato da mensagem pode ser {"v":1}
  JsonObject &json = jsonBuffer.createObject();
  json["v"] = 1;

  // a biblioteca ArduinoJson já imprime para uma porta Serial/SoftwareSerial
  json.printTo(bluetooth);
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
