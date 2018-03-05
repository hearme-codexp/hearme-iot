int anterior = 0;
int microphone = A0;
int viber = 3;
unsigned long inicioVibracao;

#define DURACAO_VIBRACAO 300
#define SENSIBILIDADE 100
#define INTERVALO_LEITURA 20

void setup() {
  // put your setup code here, to run once:
  pinMode(viber, OUTPUT);
  pinMode(microphone, INPUT);
  Serial.begin(9600);
  // vibrar = map(vibrar, 0, 1023, 0, 255);
}
void loop() {
  int now = analogRead(microphone);
  Serial.println(now);
  delay(INTERVALO_LEITURA);
  if (now > anterior + SENSIBILIDADE) {
    comecarVibrar();
  }

  // determinar se é pra parar
  if (inicioVibracao > 0 && inicioVibracao + DURACAO_VIBRACAO < millis()) {
    pararVibrar();
  }

  anterior = now;
}

void comecarVibrar() {
  inicioVibracao = millis();
  digitalWrite(viber, HIGH);
}
void pararVibrar() {
  digitalWrite(viber, LOW);
  inicioVibracao = 0;
