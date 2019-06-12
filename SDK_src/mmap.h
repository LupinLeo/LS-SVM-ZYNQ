#ifndef MMAP_H
#define MMAP_H

#include "define.h"

int set_mapbase(off_t phy_addr, void **virt_addr, unsigned long map_size);

void write_int8(void *virt_addr, volatile off_t offset, signed char data);

signed char read_int8(void *virt_addr, volatile off_t offset);

void write_float(void *virt_addr, volatile off_t offset, float data);

float read_float(void *virt_addr, volatile off_t offset);

void write_double(void *virt_addr, volatile off_t offset, double data);

double read_double(void *virt_addr, volatile off_t offset);

void write_uint32 (void *virt_addr, volatile off_t offset, unsigned int data);

unsigned int read_uint32(void *virt_addr, volatile off_t offset);

void release_mapbase(void* virt_addr, int fd, unsigned long map_size);


#endif /* mmap.h */
