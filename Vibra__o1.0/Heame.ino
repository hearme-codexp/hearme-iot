#include "SoftwareSerial.h"

int anterior = 0;
int microphone = A0;
int viber = 5;
unsigned long inicioVibracao;

#define DURACAO_VIBRACAO 300
#define SENSIBILIDADE 100
#define INTERVALO_LEITURA 20
#define BAUD_RATE 9600

SoftwareSerial bluetooth(2, 3);
void setup()
{
  pinMode(viber, OUTPUT);
  pinMode(microphone, INPUT);
  Serial.begin(9600);
  bluetooth.begin(BAUD_RATE);
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
