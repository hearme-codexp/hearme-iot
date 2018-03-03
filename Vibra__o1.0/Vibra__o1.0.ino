float media;
int microphone = A0;
int viber = 2;

// Utilizar esses 2 valores como float para garantir que
// a divisão retorne um float
float soma;
float cont;

#define INTERVALO_LEITURA 200
unsigned long ultimaLeitura;

void setup() {
  pinMode(viber, OUTPUT);
  pinMode(microphone, INPUT);
  Serial.begin(9600);
}

void updateMedia(unsigned int leitura) {
  soma += leitura;
  media = soma / cont;
  cont++;
}

#define TEMPO_VIBRACAO 300
unsigned long inicioVibracao;
void vibrar() {
  inicioVibracao = millis();
  analogWrite(viber, HIGH);
}

// Verifica se é hora de parar de vibrar
void loopVibrar() {
  if (inicioVibracao > 0 && inicioVibracao - millis() > TEMPO_VIBRACAO) {
    analogWrite(viber, LOW);
  }
  inicioVibracao = 0;
} 

void loop() {
  if (ultimaLeitura - millis() > INTERVALO_LEITURA) {
    ultimaLeitura = millis();
    unsigned int leitura = analogRead(microphone);

    Serial.print(F("Leitura recebida"));
    Serial.println(leitura);

    updateMedia(leitura);
    if ( media < leitura ) {
      vibrar();
    }
  }

  loopVibrar();
}
