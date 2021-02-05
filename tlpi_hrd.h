#ifndef TLPI_HRD_H
#define TLPI_HRD_H

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "get_num.h"
#include "error_function.h"

typedef enum {FALSE,TRUE} Boolean;

#define min(m,n) ((m)<(n) ? (m):(n))
#define max(m,n) ((m)>(n) ? (m):(n))

#endif