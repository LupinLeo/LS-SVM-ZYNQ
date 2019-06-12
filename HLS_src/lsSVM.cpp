#include "string.h"
#include "lsSvm.hpp"
#include "define.hpp"
#include "math.h"


/*void _2DConv(int8_t *in, int8_t *out, int8_t *filter, uint32_t nrows, uint32_t ncols, uint8_t k, uint8_t stride){
	uint16_t r, c, i, j;
	uint32_t nrows_i = nrows*stride+k-1;
	uint32_t ncols_i = ncols*stride+k-1;

	for(r=0; r<nrows; r++){
		for(c=0; c<ncols; c++){
#pragma HLS PIPELINE II=1
			for(i=0; i<k; i++){
				for(j=0; j<k; j++){
					uint32_t offset = (r*stride+i)*ncols_i+(c*stride+j);
					int32_t in_tmp = *(in+offset);
					int32_t filter_tmp = *(filter+i*k+j);
					*(out+r*ncols+c) += in_tmp*filter_tmp;
				}
			}
		}
	}
}*/
/*double b_det(double t,int8_t *y,double a[Number],double b){
	uint8_t i;
	for(i=0;i<Number;i++){
		b +=a[i]*(*(y+i));
	}
	b = b*t;
	return b;
}*/
/*void a_det(double t,float r,int8_t *y,double *out,double b,double q[Number][Number]){
	uint8_t i,j;
	for(i=0;i<Number;i++){
		double sum =0;
		for(j=0;j<Number;j++){
			sum +=*(out+i)*q[i][j];
		}
		*(out+i) = t*(1-b*(*(y+i))-sum-(*(out+i)*(1/r)));
	}
}*/

/*double _Kernel(float *x,int8_t*y,){
	double kernel[Number][Number];
	uint8_t i,j,d;
	for(i=0;i<Number;i++){
		for(j=0;j<Number;j++){
			double index = 0;
			for(d=0;d<Dimension;d++){
				double sum = (*(x+i*Dimension+d)-(*(x+j*Dimension+d)));
				index = pow(sum,2)+index;
			}
			kernel[i][j] = *(y+i)*(*(y+j))*exp(index/2*pow(0.5,2));
		}
	}
return kernel;
}*/

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

/*void _2DConv_OP(int8_t *in, int8_t *out,  uint32_t nrows, uint32_t ncols, uint8_t k, uint8_t stride){
	uint16_t r, c, i, j;
	uint32_t nrows_i = nrows*stride+k-1;
	uint32_t ncols_i = ncols*stride+k-1;

	int8_t *filter_base = in + ROWS_I*COLS_I;

    int8_t filter_buffer[FILTER_SIZE][FILTER_SIZE];
#pragma HLS ARRAY_PARTITION variable=filter_buffer complete dim=0
    memcpy(&filter_buffer[0][0], filter_base, FILTER_SIZE*FILTER_SIZE*sizeof(int8_t));

	for(r=0; r<nrows; r++){
		for(c=0; c<ncols; c++){
#pragma HLS PIPELINE II=1
			int8_t store_data = 0;
			for(i=0; i<k; i++){
				for(j=0; j<k; j++){
					uint32_t offset = (r*stride+i)*ncols_i+(c*stride+j);
					int8_t val = *(in+offset);
					int8_t res = 0;

					if(filter_buffer[i][j]==0){
							res = 0;
					}else if(filter_buffer[i][j]==1){
							res = val;
					}else if(filter_buffer[i][j]==-1){
							res = -val;
					}
					store_data += res;


					*(out+r*ncols+c) = store_data;
				}
			}
		}
	}
}*/


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



/*void HW_2DConv_Mmap_2(int8_t *pixel_in, int8_t *pixel_out, int32_t addr_reserved)
{
#pragma HLS INTERFACE m_axi depth = 482*272+3*3 port = pixel_in offset = slave bundle = user_axi_in register
#pragma HLS INTERFACE m_axi depth = 480*270 port = pixel_out offset = slave bundle = user_axi_out register

#pragma HLS INTERFACE s_axilite port = pixel_in bundle = user_axi4lite_config  register
#pragma HLS INTERFACE s_axilite port = pixel_out bundle = user_axi4lite_config  register
#pragma HLS INTERFACE s_axilite port = addr_reserved offset = 0xFFF0 bundle = user_axi4lite_config  register
#pragma HLS INTERFACE s_axilite port = return bundle = user_axi4lite_config  register

	_2DConv_OP(pixel_in, pixel_out,  ROWS_O, COLS_O, FILTER_SIZE, STRIDE);
}


void HW_2DConv_Mmap_3(int8_t *pixel_in, int8_t *pixel_out, int32_t addr_reserved){
#pragma HLS INTERFACE m_axi depth = 482*272+3*3 port = pixel_in offset = slave bundle = user_axi_in register
#pragma HLS INTERFACE m_axi depth = 480*270 port = pixel_out offset = slave bundle = user_axi_out register

#pragma HLS INTERFACE s_axilite port = pixel_in bundle = user_axi4lite_config  register
#pragma HLS INTERFACE s_axilite port = pixel_out bundle = user_axi4lite_config  register
#pragma HLS INTERFACE s_axilite port = addr_reserved offset = 0xFFF0 bundle = user_axi4lite_config  register
#pragma HLS INTERFACE s_axilite port = return bundle = user_axi4lite_config  register

	uint16_t ii;
	uint16_t r, c, i, j;

	int8_t *in_base = pixel_in;
	int8_t *filter_base = pixel_in + ROWS_I*COLS_I;
	int8_t *out_base = pixel_out;

    int8_t filter_buffer[FILTER_SIZE][FILTER_SIZE];
#pragma HLS ARRAY_PARTITION variable=filter_buffer complete dim=0
    memcpy(&filter_buffer[0][0], filter_base, FILTER_SIZE*FILTER_SIZE*sizeof(int8_t));

    ap_linebuffer<int8_t, FILTER_SIZE, COLS_I> line_buffer;

	ROW_LOOP: for(r=0; r<ROWS_I; r++){
		ap_window<int8_t,FILTER_SIZE,FILTER_SIZE> window_buffer;

		//fill the line buffer
		COL_LOOP: for(c=0; c<COLS_I; c++){
#pragma HLS PIPELINE II=1
            int8_t store_data = 0;
			int8_t load_data = *(in_base+r*COLS_I+c);

			line_buffer.shift_up(c);
			line_buffer.insert_bottom(load_data, c);

			if(r>=2)
			{
				window_buffer.shift_right();
				window_buffer.insert(line_buffer.getval(2,c), 0, 2);
				window_buffer.insert(line_buffer.getval(1,c), 1, 2);
				window_buffer.insert(line_buffer.getval(0,c), 2, 2);
			}

			if(r>=2 && c>=2)
			{
				for(i=0; i<FILTER_SIZE; i++){
					for(j=0; j<FILTER_SIZE; j++){
						int8_t res = 0;
						int8_t val = window_buffer.getval(i,j);
						if(filter_buffer[i][j]==0){
							res = 0;
						}else if(filter_buffer[i][j]==1){
							res = val;
						}else if(filter_buffer[i][j]==-1){
							res = -val;
						}
						store_data += res;
					}
				}
				*(out_base+(r-2)*COLS_O+(c-2)) = store_data;
			}
		}
	}
}*/
