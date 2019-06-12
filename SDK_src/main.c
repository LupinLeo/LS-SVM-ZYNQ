#include "define.h"
#include "mmap.h"
#include <time.h>

int main()
{
		clock_t start1, end1;
		int i, j;
	
		FILE *fpin, *fpout, *ftest;
		void *data_x_vaddr = NULL, *data_y_vaddr = NULL,*data_out_vaddr = NULL, *ip_config_vaddr;
		int data_x_fd, data_y_fd,data_out_fd, ip_config_fd;
		
		data_x_fd = set_mapbase(DATA_X_SHMM_BASE_ADDR, &(data_x_vaddr), DATA_X_SHMM_SIZE);
		data_y_fd = set_mapbase(DATA_Y_SHMM_BASE_ADDR, &(data_y_vaddr), DATA_Y_SHMM_SIZE);
		data_out_fd = set_mapbase(DATA_OUT_SHMM_BASE_ADDR, &(data_out_vaddr), DATA_OUT_SHMM_SIZE);
		ip_config_fd = set_mapbase(IP_CONFIG_ADDR, &(ip_config_vaddr), IP_CONFIG_SHMM_SIZE);
		
		float in_x[Number][Dimension] = {{4.7,1.4}, {4.5,1.5}, {4.9,1.5},{6,2.5},{5.1,1.9},{5.9,2.1},{5.6,1.8}};
		signed char in_y[Number] = {1,1,1,-1,-1,-1,-1};
	
		fpin = fopen("i.txt", "wb");
		fpout = fopen("o.txt", "wb");
        ftest = fopen("t.txt","wb");
		printf("Initialize input data......\n"); fflush(stdout);
		for(i=0; i<Number; i++){
				for(j=0; j<Dimension; j++){
					write_float(data_x_vaddr,i*Dimension+j,in_x[i][j]);
					fprintf(fpin, "%3f ", read_float(data_x_vaddr,i*Dimension+j)); fflush(stdout);
				}
				fprintf(fpin, "\n");
			}
		printf("Completed!\n"); fflush(stdout);

		printf("Label:\n");
			for(i=0; i<Number; i++){
				write_int8(data_y_vaddr,i,in_y[i]);
				fprintf(fpin, "%2d ", read_int8(data_y_vaddr,i)); fflush(stdout);
				fprintf(fpin, "\n");
			}
		fclose(fpin);
	
		for(i=0; i<Outlength; i++){
			    write_double(data_out_vaddr,i,0);
				double tmp =read_double(data_out_vaddr,i);
				fprintf(ftest, "%f ", tmp);
				fprintf(ftest, "\n");
		}
		printf("[FPGA] Run 2D convolution......"); fflush(stdout);
		start1 = clock();

		write_uint32(ip_config_vaddr, DATA_X_BASE_ADDR_REG, DATA_X_SHMM_BASE_ADDR);
		write_uint32(ip_config_vaddr, DATA_Y_BASE_ADDR_REG, DATA_Y_SHMM_BASE_ADDR);
		write_uint32(ip_config_vaddr, DATA_OUT_BASE_ADDR_REG, DATA_OUT_SHMM_BASE_ADDR);
		write_uint32(ip_config_vaddr, AP_CTRL_REG, AP_START);
		while(read_uint32(ip_config_vaddr, AP_CTRL_REG)&AP_DONE!=AP_DONE);
		end1 = clock();
		printf("FPGA Accelerate Completed!\n");
		fflush(stdout);
	
		printf("Print results of 2D convolution:\n"); fflush(stdout);
		for(i=0; i<Outlength; i++){
				double tmp =read_double(data_out_vaddr,i);
				fprintf(fpout, "%f ", tmp);
				fprintf(fpout, "\n");
		}

		release_mapbase(data_x_vaddr, data_x_fd, DATA_X_SHMM_SIZE);
		release_mapbase(data_y_vaddr, data_y_fd, DATA_Y_SHMM_SIZE);
		release_mapbase(data_out_vaddr, data_out_fd, DATA_OUT_SHMM_SIZE);
		release_mapbase(ip_config_vaddr, ip_config_fd, IP_CONFIG_SHMM_SIZE);

    return 0;
}

                                                                                            
