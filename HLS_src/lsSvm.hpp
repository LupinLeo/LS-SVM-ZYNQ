#ifndef _2DCONV_H
#define _2DCONV_H

#include <stdio.h>
#include <ap_int.h>
#include <stdint.h>
#include <hls_stream.h>


using namespace std;



void ls_Svm( float *x, int8_t *y,volatile double *out,double t,float r);

void HW_ls_Svm_Mmap_1(float *x,int8_t *y,volatile double *out, int32_t addr_reserved);



#endif
