const int potenciometro = A0 ;
const int viber = 3 ;
int valorP ;
int valorM ;
void setup() {
  // put your setup code here, to run once:

  pinMode(potenciometro, INPUT);
  pinMode(viber, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  valorP =  analogRead(potenciometro);
  //Serial.println("valorP");
  Serial.println(valorM);
 // Serial.println(valorP);
 valorM = map( valorP, 0, 1023, 0, 255 );
 analogWrite(viber, valorM );
 delay(100);
}

