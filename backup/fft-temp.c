#include "math.h"
#include "fft.h"
#include "stdio.h"

/**
 * Purpose: Calculate the twiddle factors needed by the FFT.
 * Input: n: length of FFT, W: array to store twiddle factors
 * Returns: values are stored in array W
 * Notes: Floats used rather than double as this is inded for a DSPU CPU target. Could change to double.
 */
void init_W(int n, COMPLEX* W){
	int i;
	float a = 2.0*PI/n;
	for(i = 0; i<n; i++){
		float k = -i*a;
		W[i].real = (float) cos(-i*a);
		W[i].imag = (float) sin(-i*a);
	}
}

void fft_c(int n, COMPLEX* x, COMPLEX* W){
	COMPLEX u, temp, tm;
	COMPLEX* Wptr;
	int i,j,k,len,Windex;
	//perform fft butterfly
	Windex = 1;

	for(len=n/2; len>0; len/=2){
		Wptr = W;
		for(j = 0; j<len; j++){
			u = *(Wptr+j); //pick the twiddle factor
			//pointer to the beginning of twiddle factors
			for(i=j;i<n;i=i+2*len){
				temp.real = x[i].real + x[i+len].real;
				temp.imag = x[i].imag + x[i+len].imag;
				tm.real = x[i].real-x[i+len].real;
				tm.imag = x[i].imag - x[i+len].imag;
				x[i+len].real = tm.real*u.real - tm.imag*u.imag;
				x[i+len].imag = tm.real*u.imag + tm.imag*u.real;
				x[i] = temp;
			}
		}
		// BIT-reversal
		// rearrange data by bit reserved addressing
		// this step must occur after the fft butterfly
		j = 0;
		for(i=1;i<(n-1);i++){
			k = n/2;
			while(k<=j){
				j-=k; k/=2;
			}
			j+=k;
			if(i<j){
				temp = x[j]; x[j] = x[i]; x[i] = temp;
			}
		}
		
	}
}
