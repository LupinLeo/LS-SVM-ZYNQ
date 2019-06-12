/************************************  Header Section  *********************************************
 --
 -- NAME       : OpenHEC
 -- Data       : 2017.5
 -- E-mail     : support@iopenhec.com
 -- Website    : www.iopenhec.com

 -- Filename   : define.h
 -- Description: 
 --
*********************************** End Header Section  *********************************************/

#ifndef DEFINE_H
#define DEFINE_H

#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


#define Number          7
#define Dimension       2
#define Outlength       8


#define FATAL do { fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", \
  __LINE__, __FILE__, errno, strerror(errno)); exit(1); } while(0)

#define IP_CONFIG_ADDR           0x43C00000
#define DATA_X_BASE_ADDR_REG    0x0010
#define DATA_Y_BASE_ADDR_REG   0x0018
#define DATA_OUT_BASE_ADDR_REG   0x0020
#define AP_CTRL_REG              0x0000

#define DATA_X_SHMM_BASE_ADDR    0x20000000
#define DATA_Y_SHMM_BASE_ADDR   0x28000000
#define DATA_OUT_SHMM_BASE_ADDR   0x30000000

#define DATA_X_SHMM_SIZE       (Number*Dimension*4)
#define DATA_Y_SHMM_SIZE       Number
#define DATA_OUT_SHMM_SIZE     (Outlength*8)
#define IP_CONFIG_SHMM_SIZE      160

#define AP_START 0x1
#define AP_DONE  0x2

#endif /* define.h */
