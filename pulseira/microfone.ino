#define TESTING
#ifndef TESTING

#define PIN_MICROFONE 3
int getVolume() {
	return analogRead(PIN_MICROFONE);
}

#else

static unsigned int pico[] = {0, 0, 0, 100, 400, 100, 0, 0, 0};

int getVolumeIdx = 0;

int getVolume() {
	return pico[getVolumeIdx++];
}

#endif
