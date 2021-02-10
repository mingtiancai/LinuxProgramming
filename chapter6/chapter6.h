#ifndef CHAPTER6_H
#define CHAPTER6_H
#include <setjmp.h>

static jmp_buf env;

void printenv();

void modify_env(int argc,char** argv);

void usejump(int argc,char** argv);

#endif