/************************************  Header Section  *********************************************
 --
 -- NAME       : OpenHEC
 -- Data       : 2017.5
 -- E-mail     : support@iopenhec.com
 -- Website    : www.iopenhec.com

 -- Filename   : mmap.c
 -- Description: 
 --
*********************************** End Header Section  *********************************************/

#include "mmap.h"

int set_mapbase(off_t phy_addr, void **virt_addr, unsigned long map_size){
		int fd;
    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    printf("/dev/mem opened.\n");   fflush(stdout);
    
    (*virt_addr) = mmap(0, map_size, PROT_READ | PROT_WRITE , MAP_SHARED, fd, phy_addr);
    
    if((*virt_addr) == (void *) -1) FATAL;
    printf("Memory mapped at address %p.\n", (*virt_addr)); fflush(stdout);
    
    return fd;
}

void write_int8(void *virt_addr, volatile off_t offset, signed char data){
	  void *addr = virt_addr + offset;
	  *((signed char*) addr) = data;
}

signed char read_int8(void *virt_addr, volatile off_t offset){
		void *addr = virt_addr + offset;
    return *((signed char*) addr);
}
void write_float(void *virt_addr, volatile off_t offset, float data){
	  void *addr = virt_addr + offset;
	  *((float*) addr) = data;
}

float read_float(void *virt_addr, volatile off_t offset){
		void *addr = virt_addr + offset;
    return *((float*) addr);
}

void write_double(void *virt_addr, volatile off_t offset, double data){
	  void *addr = virt_addr + offset;
	  *((double*) addr) = data;
}

double read_double(void *virt_addr, volatile off_t offset){
		void *addr = virt_addr + offset;
    return *((double*) addr);
}

void write_uint32 (void *virt_addr, volatile off_t offset, unsigned int data){
	  void *addr = virt_addr + offset;
    *((unsigned int *) addr) = data;
}

unsigned int read_uint32(void *virt_addr, volatile off_t offset){
		void *addr = virt_addr + offset;
    return *((unsigned int*) addr);
}

void release_mapbase(void* virt_addr, int fd, unsigned long map_size){
	  munmap(virt_addr, map_size);
	  close(fd);
}
