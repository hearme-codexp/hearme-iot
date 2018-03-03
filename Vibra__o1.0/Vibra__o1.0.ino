float media ;
int total = 0 ;
int microphone = 'A0' ;
int viber = 2 ;
int now ;
int valores[60];
int cont = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(viber, OUTPUT);
  pinMode(microphone, INPUT);
  Serial.begin(9600);
}
void updatemedia() {
  for (int i = 0; i < 60 ; i++) {
    total = total + valores[i];
  }
  media = total / 60;

}
void limpaValores() {
  valores[60] = 0 ;
  
}
void loop() {

  long mil = millis();
  if (mil % 1000 == 0 && mil > 0) {
    if (cont > 59) {
      limpaValores();
      cont=1;
    }
    valores[cont] = analogRead( microphone );
    now = analogRead( microphone );

    cont++;
  }
  updatemedia();
  if ( media < now ) {
    analogWrite( viber, HIGH );
  }
 // Serial.println(total);
   Serial.println(media);
   Serial.println(now);
}
