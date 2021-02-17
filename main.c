#include <stdio.h>
#include <errno.h>
#include "tlpi_hrd.h"
#include <math.h>
#include <stdarg.h>
#include <setjmp.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>

//#include "chapter2/chapter2.h"
//#include "chapter3/chapter3.h"
//#include "chapter4/chapter4.h"
//#include "chapter5/chapter5.h"
//#include "chapter6/chapter6.h"
//#include "chapter7/chapter7.h"
#include "chapter10/chapter10.h"


int main(int argc,char** argv)
{
    printf("begin!\n");
    //printGlibcVersion();
    //printf("%d\n",EOWNERDEAD);

    //chapter3
    //copy1(argc,argv);
    //useOpen();

    //chapter4
    //seek_io(argc,argv);

    //chapter5
    //t_readv(argc,argv);

    //chapter6
    //printenv();
    //modify_env(argc,argv);
    //usejump(argc,argv);

    //chapter7
    //free_and_sbrk(argc,argv);

    //chapter8
    //check_password(argc,argv);
  
    //chapter9
    //idshow(argc,argv);

    //chapter10
    //calendar_time();
    //printf("%d\n",_XOPEN_SOURCE);
    //strtime(argc,argv);
    //show_time();
    //process_time(argc,argv);

    //chapter11
    t_sysconf();
    //t_fpathconf();

   
   

    printf("end!\n");
    return 0;
}
