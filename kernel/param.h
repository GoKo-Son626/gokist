// 头文件定义了 xv6 内核的系统级配置参数和限制
// 例如，它规定了系统中最大进程数、最大文件描述符数
// 块设备数量等常量。通过修改这些参数
// 可以在不更改核心逻辑的情况下调整 xv6 系统的规模和能力

#ifndef __PARAM_H__
#define __PARAM_H__

#define NPROC        64  // maximum number of processes
#define NCPU          8  // maximum number of CPUs
#define NOFILE       16  // open files per process
#define NFILE       100  // open files per system
#define NINODE       50  // maximum number of active i-nodes
#define NDEV         10  // maximum major device number
#define ROOTDEV       1  // device number of file system root disk
#define MAXARG       32  // max exec arguments
#define MAXOPBLOCKS  10  // max # of blocks any FS op writes
#define LOGSIZE      (MAXOPBLOCKS*3)  // max data blocks in on-disk log
#define NBUF         (MAXOPBLOCKS*3)  // size of disk block cache
#define FSSIZE       2000  // size of file system in blocks
#define MAXPATH      128   // maximum file path name

#endif // !__PARAM_H__
