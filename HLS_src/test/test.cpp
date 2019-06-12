#include <stdio.h>
#include <ap_int.h>
#include "lsSvm.hpp"
#include "define.hpp"
#include "math.h"


int main(int argc, char** argv){
	int i, j;

	FILE *fpin, *fpout;
	fpin = fopen("in.txt", "wb");
	fpout = fopen("out.txt", "wb");
	uint32_t length = Number;
	float r = R;
	double t = T;
    float *x;
    double *out_data;
	int8_t *y;

	x = (float*)malloc(Dimension*length*sizeof(float));
	y = (int8_t*)malloc(length*sizeof(int8_t));
	out_data = (double*)malloc((length+1)*sizeof(double));

	float in_x[Number][Dimension] = {{4.7,1.4}, {4.5,1.5}, {4.9,1.5},{6,2.5},{5.1,1.9},{5.9,2.1},{5.6,1.8}};
	int8_t in_y[Number] = {1,1,1,-1,-1,-1,-1};

	printf("Initialize input data......\n"); fflush(stdout);
	for(i=0; i<Number; i++){
		for(j=0; j<Dimension; j++){
			*(x+i*Dimension+j) = in_x[i][j];
			fprintf(fpin, "%3f ", *(x+i*Dimension+j)); fflush(stdout);
		}
		fprintf(fpin, "\n");
	}
	printf("Completed!\n"); fflush(stdout);

	printf("Label:\n");
	for(i=0; i<Number; i++){
		*(y+i)=in_y[i];
		fprintf(fpin, "%2d ", *(y+i)); fflush(stdout);
		fprintf(fpin, "\n");
	}
	fclose(fpin);

	memset(out_data, 0, (length+1)*sizeof(double));

	float buffer_x[length*Dimension];
	int8_t buffer_y[length];
	double buffer_out[length+1];

	float* x_data_ptr = buffer_x;
	int8_t* y_ptr = buffer_y;
	double* out_data_ptr = buffer_out;
	memcpy(x_data_ptr, x, length*sizeof(float));
	memcpy(y_ptr, y, length*sizeof(int8_t));


#ifndef FPGA   //Run CPU codes
	printf("Run LS-SVM......"); fflush(stdout);
	ls_Svm(x, y,out_data, t,r);
	printf("Completed!\n"); fflush(stdout);
#else
	printf("[HLS] Run LS-SVM......"); fflush(stdout);
	HW_ls_Svm_Mmap_1(x_data_ptr, y_ptr,out_data_ptr, 0);
	printf("Completed!\n"); fflush(stdout);
	memcpy(out_data, out_data_ptr, (length+1)*sizeof(double));
#endif
	printf("Print results of LS-Svm:\n"); fflush(stdout);
	for(i=0; i<length+1; i++){

		fprintf(fpout, "%f ", *(out_data+i));
		fprintf(fpout, "\n");
	}
	fclose(fpout);
	return 0;
}

