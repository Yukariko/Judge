#ifndef _OKCALLS32_H
#define _OKCALLS32_H

static int LANG_CV[256]={85,8,SYS_time,SYS_read, SYS_uname, SYS_write, SYS_open, SYS_close, SYS_execve, SYS_access, SYS_brk, SYS_munmap, SYS_mprotect, SYS_mmap2, SYS_fstat64, SYS_set_thread_area, 252,0};

//static int LANG_PV[256]={140,91,175,195,13,SYS_open, SYS_set_thread_area, SYS_brk, SYS_read, SYS_uname, SYS_write, SYS_execve, SYS_ioctl, SYS_readlink, SYS_mmap, SYS_rt_sigaction, SYS_getrlimit, 252,191,0};


static int LANG_JV[256]={295,SYS_fcntl64,SYS_getdents64 , SYS_ugetrlimit, SYS_rt_sigprocmask, SYS_futex, SYS_read, SYS_mmap2, SYS_stat64, SYS_open, SYS_close, SYS_execve, SYS_access, SYS_brk, SYS_readlink, SYS_munmap, SYS_close, SYS_uname, SYS_clone, SYS_uname, SYS_mprotect, SYS_rt_sigaction, SYS_sigprocmask, SYS_getrlimit, SYS_fstat64, SYS_getuid32, SYS_getgid32, SYS_geteuid32, SYS_getegid32, SYS_set_thread_area, SYS_set_tid_address, SYS_set_robust_list, SYS_exit_group, 0};

//static int LANG_RV[256]={340,126,SYS_access,SYS_brk,SYS_close,SYS_execve,SYS_exit_group,SYS_fstat64,SYS_futex,SYS_getegid32,SYS_geteuid32,SYS_getgid32,SYS_getrlimit,SYS_gettimeofday,SYS_getuid32,SYS_mmap2,SYS_mprotect,SYS_munmap,SYS_open,SYS_read,SYS_rt_sigaction,SYS_rt_sigprocmask,SYS_set_robust_list,SYS_set_thread_area,SYS_set_tid_address,SYS_uname,SYS_write,191,195,120,7,0};

//static int LANG_BV[256]={7,120,42,158,117,60,39,102,191,183,SYS_access,SYS_brk,SYS_close,SYS_dup2,SYS_execve,SYS_exit_group,SYS_fcntl64,SYS_fstat64,SYS_getegid32,SYS_geteuid32,SYS_getgid32,SYS_getpgrp,SYS_getpid,SYS_getppid,SYS_getrlimit,SYS_gettimeofday,SYS_getuid32,SYS_ioctl,SYS__llseek,SYS_mmap2,SYS_mprotect,SYS_munmap,SYS_open,SYS_read,SYS_rt_sigaction,SYS_rt_sigprocmask,SYS_set_thread_area,SYS_stat64,SYS_time,SYS_uname,SYS_write};

//static int LANG_YV[256]={146,SYS_mremap,158,117,60,39,102,191,SYS_access,SYS_brk,SYS_close,SYS_execve,SYS_exit_group,SYS_fcntl64,SYS_fstat64,SYS_futex,SYS_getcwd,SYS_getdents64,SYS_getegid32,SYS_geteuid32,SYS_getgid32,SYS_getrlimit,SYS_getuid32,SYS_ioctl,SYS__llseek,SYS_lstat64,SYS_mmap2,SYS_mprotect,SYS_munmap,SYS_open,SYS_read,SYS_readlink,SYS_rt_sigaction,SYS_rt_sigprocmask,SYS_set_robust_list,SYS_set_thread_area,SYS_set_tid_address,SYS_stat64,SYS_uname,SYS_write};


//static int LANG_PHV[256]={146,78,158,117,60,39,102,191,SYS_access,SYS_brk,SYS_clone,SYS_close,SYS_execve,SYS_exit_group,SYS_fcntl64,SYS_fstat64,SYS_futex,SYS_getcwd,SYS_getdents64,SYS_getrlimit,SYS_gettimeofday,SYS_ioctl,SYS__llseek,SYS_lstat64,SYS_mmap2,SYS_mprotect,SYS_munmap,SYS_open,SYS_read,SYS_readlink,SYS_rt_sigaction,SYS_rt_sigprocmask,SYS_set_robust_list,SYS_set_thread_area,SYS_set_tid_address,SYS_stat64,SYS_time,SYS_uname,SYS_write,0};

//static int LANG_PLV[256]={78,158,117,60,39,102,191,SYS_access,SYS_brk,SYS_close,SYS_execve,SYS_exit_group,SYS_fcntl64,SYS_fstat64,SYS_futex,SYS_getegid32,SYS_geteuid32,SYS_getgid32,SYS_getrlimit,SYS_getuid32,SYS_ioctl,SYS__llseek,SYS_mmap2,SYS_mprotect,SYS_munmap,SYS_open,SYS_read,SYS_readlink,SYS_rt_sigaction,SYS_rt_sigprocmask,SYS_set_robust_list,SYS_set_thread_area,SYS_set_tid_address,SYS_stat64,SYS_time,SYS_uname,SYS_write,0};

//static int LANG_CSV[256]={141,158,117,60,39,102,191,SYS_access,SYS_brk,SYS_chmod,SYS_clock_getres,SYS_clock_gettime,SYS_clone,SYS_close,SYS_execve,SYS_exit_group,SYS_fcntl64,SYS_fstat64,SYS_ftruncate64,SYS_futex,SYS_getcwd,SYS_getdents64,SYS_geteuid32,SYS_getpid,SYS_getppid,SYS_getrlimit,SYS_gettimeofday,SYS_getuid32,SYS_ioctl,SYS__llseek,SYS_lstat64,SYS_mmap2,SYS_mprotect,SYS_mremap,SYS_munmap,SYS_open,SYS_read,SYS_readlink,SYS_rt_sigaction,SYS_rt_sigprocmask,SYS_sched_getaffinity,SYS_sched_getparam,SYS_sched_get_priority_max,SYS_sched_get_priority_min,SYS_sched_getscheduler,SYS_set_robust_list,SYS_set_thread_area,SYS_set_tid_address,SYS_sigaltstack,SYS_stat64,SYS_statfs,SYS_tgkill,SYS_time,SYS_uname,SYS_unlink,SYS_write,0};

//static int LANG_OV[256]={102,191,SYS_access,SYS_brk,SYS_close,SYS_execve,SYS_exit_group,SYS_fstat64,SYS_futex,SYS_getcwd,SYS_geteuid32,SYS_getrlimit,SYS_gettimeofday,SYS_getuid32,SYS__llseek,SYS_lstat64,SYS_mmap2,SYS_mprotect,SYS_munmap,SYS_open,SYS_read,SYS_readlink,SYS_rt_sigaction,SYS_rt_sigprocmask,SYS_set_robust_list,SYS_set_thread_area,SYS_set_tid_address,SYS_stat64,SYS_uname,SYS_write,0};


/*static int LANG_BASICV[256]={125,191,SYS_access
,SYS_brk
,SYS_close
,SYS_execve
,SYS_exit_group
,SYS_fstat64
,SYS_futex
,SYS_getrlimit
,SYS_ioctl
,SYS_ioperm
,SYS_mmap2
,SYS_open
,SYS_read
,SYS_rt_sigaction
,SYS_rt_sigprocmask
,SYS_set_robust_list
,SYS_set_thread_area
,SYS_set_tid_address
,SYS_stat64
,SYS_uname
,SYS_write
,0};*/

//static int LANG_SV[256]={100,295,SYS_fcntl64,SYS_getdents64 , SYS_ugetrlimit, SYS_rt_sigprocmask, SYS_futex, SYS_read, SYS_mmap2, SYS_stat64, SYS_open, SYS_close, SYS_execve, SYS_access, SYS_brk, SYS_readlink, SYS_munmap, SYS_close, SYS_uname, SYS_clone, SYS_uname, SYS_mprotect, SYS_rt_sigaction, SYS_sigprocmask, SYS_getrlimit, SYS_fstat64, SYS_getuid32, SYS_getgid32, SYS_geteuid32, SYS_getegid32, SYS_set_thread_area, SYS_set_tid_address, SYS_set_robust_list, SYS_exit_group, 0};
#endif