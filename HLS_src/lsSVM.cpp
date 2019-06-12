// Author: lupin
// Email: lupinleo.lulo@gmail.com 
#include "string.h"
#include "lsSvm.hpp"
#include "define.hpp"
#include "math.h"

void ls_Svm(float *x, int8_t *y,volatile double *out,double t,float r){
	double kernel[Number][Number];
	double a[Number],det_b,det_a[Number],b;
	uint8_t i,j,d,flag=0;
	for(i=0;i<Number;i++){
		for(j=0;j<Number;j++){
			double index = 0;
			for(d=0;d<Dimension;d++){
				double sum = (*(x+i*Dimension+d)-(*(x+j*Dimension+d)));
				index = sum*sum+index;
			}
			kernel[i][j] = *(y+i)*(*(y+j))*expf((-1)*index/(0.5));
		}
	}

	while(flag==0){
		for(i=0;i<Number;i++){
				det_b +=*(out+i)*(*(y+i));
			}
		det_b = det_b*t;
		*(out+Number)=*(out+Number)+det_b;
		for(i=0;i<Number;i++){
			double sum =0;
			for(j=0;j<Number;j++){
				sum +=*(out+j)*kernel[i][j];
			}
			det_a[i] = t*(1-*(out+Number)*(*(y+i))-sum-(*(out+i)*(1/r)));
		}
		for(j=0;j<Number;j++){
			*(out+j)=*(out+j)+det_a[j];
		}
		for(i=0;i<Number;i++){
			if((det_a[i]>1e-5)||(det_a[i]<-1e-5)){
				flag =0;
				break;
			}
			flag =1;
		}
		if((flag==1)&&((det_b<1e-5)&&(det_b>-1e-5))){
			flag =1;
		}
		else{
			flag=0;
		}

	}


}


void HW_ls_Svm_Mmap_1( float *x, int8_t *y,volatile double *out, int32_t addr_reserved)
{
#pragma HLS INTERFACE m_axi depth = 2*7*4 port = x offset = slave bundle = user_axi_x register
#pragma HLS INTERFACE m_axi depth = 7 port = y offset = slave bundle = user_axi_y register
#pragma HLS INTERFACE m_axi depth = 8*8 port = out offset = slave bundle = user_axi_out register

#pragma HLS INTERFACE s_axilite port = x bundle = user_axi4lite_config  register
#pragma HLS INTERFACE s_axilite port = y bundle = user_axi4lite_config  register
#pragma HLS INTERFACE s_axilite port = out bundle = user_axi4lite_config  register
#pragma HLS INTERFACE s_axilite port = addr_reserved offset = 0xFFF0 bundle = user_axi4lite_config  register
#pragma HLS INTERFACE s_axilite port = return bundle = user_axi4lite_config  register



	ls_Svm(x, y, out, T, R);
}
