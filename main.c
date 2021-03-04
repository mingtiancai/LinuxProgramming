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
//#include "chapter10/chapter10.h"
//#include "chapter11/chapter11.h"
//#include "chapter12/chapter12.h"
//#include "chapter13/chapter13.h"
//#include "chapter20/chapter20.h"
//#include "chapter21/chapter21.h"
//#include "chapter22/chapter22.h"
// #include "chapter23/chapter23.h"
#include "chapter24/chapter24.h"



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
    //t_sysconf();
    //t_fpathconf();

    //chapter12
    //procfs_pidmax(argc,argv);
    //t_uname();

    //chapter13
    //direct_read(argc,argv);

    //chapter14
    //t_mount(argc,argv);
    
    //chapter15
    //t_stat(argc,argv);
    //t_chown(argc,argv);
    //t_umask(argc,argv);

    //chapter16
    //xattr_view(argc,argv);

    //chapter17

    //chapter18
    //t_unlink(argc,argv);
    //list_files(argc,argv);
    //nftw_dir_tree(argc,argv);
    //view_symlink(argc,argv);
    //t_dirbasename(argc,argv);

    //chapter19
    //demo_inotify(argc,argv);

    //chapter20
    //ouch(argc,argv);
    //intquit(argc,argv);
    //t_kill(argc,argv);
    
    //chapter21
    //t_sigaltstack(argc,argv);

    //chapter22
    //t_sigqueue(argc,argv);
    //catch_rtsigs(argc,argv);
    //t_sigsuspend(argc,argv);
    //t_sigwaitinfo(argc,argv);
    //signalfd_sigval(argc,argv);

   //chapter23
   //real_timer(argc,argv);
   //timed_read(argc,argv);
   //t_nanosleep(argc,argv);
   //ptmr_sigev_signal(argc,argv);
   //demo_timerfd(argc,argv);

   //chapter24
   //t_fork(argc,argv);
   //fork_file_sharing(argc,argv);
   //footprint(argc,argv);
   fork_sig_sync(argc,argv);








    printf("end!\n");
    return 0;
}
