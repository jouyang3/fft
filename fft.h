#ifndef _FFT_H
#define _FFT_H

#define PI 3.14156

typedef struct {
	float real;
	float imag;
} COMPLEX;

void init_W(COMPLEX*, int);

void fft(COMPLEX*, int);

#endif
