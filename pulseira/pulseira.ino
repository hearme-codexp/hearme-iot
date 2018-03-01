// # de amostras mínimas antes de apitar?

// Talvez usar std.dev invés de multiplicacao
// https://math.stackexchange.com/questions/595541/rolling-standard-deviations

void setup() {

}

float media = 0.0;
int n = 0;

void loop() {
	unsigned int volume = getVolume();

	atualizarMedia(volume);

	if(volume > media * ESCALA) {
		vibrar();
	}
}

void vibrar() {
}
