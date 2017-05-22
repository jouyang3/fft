#include "fft.h"
#include "stdio.h"
#include "math.h"

int main(int argc, char** argv){
	int n = 1024;
	
	COMPLEX x[n];
	int i;
	for(i=0;i<n/2;i++){
		x[i].real = 2.0/n*i; x[i].imag = 0;
	}
	for(i=n/2; i<n;i++){
		x[i].real = 1-2.0/n*(i-n/2.0); x[i].imag = 0;
	}
	fft(x,n*1000);

	FILE* temp = fopen("data.temp","w");
	FILE* gnuplotPipe = popen("gnuplot -persistent","w");

	int j;
	for(j=0;j<n;j++){
		float r = x[j].real;
		float i = x[j].imag;
		float mag = sqrt(r*r + i*i);
		fprintf(temp, "%i %lf \n",j,mag);
	}

	fprintf(gnuplotPipe, "set title\"FFT(x)\"\n");
	fprintf(gnuplotPipe, "set terminal pngcairo\n");
	fprintf(gnuplotPipe, "set output \"plot.png\"\n");
	fprintf(gnuplotPipe, "set grid ytics lt 0 lw 1 lc rgb \"#bbbbbb\"\n");
	fprintf(gnuplotPipe, "set grid xtics lt 0 lw 1 lc rgb \"#bbbbbb\"\n");
	fprintf(gnuplotPipe, "plot 'data.temp' smooth csplines\n");

	return 0;
}
