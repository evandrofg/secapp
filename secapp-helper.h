/* This program needs special permissions, run
 * sudo setcap cap_sys_chroot+ep /usr/sbin/cchroot
 */

#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/wait.h>

int secapp_ovl(char *path);
int secapp_ovl_by_pid (int pid);
int secapp_open (int argc, char **argv, char **envp, int *teste);
