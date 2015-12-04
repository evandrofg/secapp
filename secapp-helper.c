/* This program needs special permissions, run
 * sudo setcap cap_sys_chroot+ep /usr/sbin/cchroot
 *
 * This file provides the secapp_open function
 */

#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "secapp-helper-mount.h"
#include "secapp-helper-mkdir.h"
#include "secapp-helper-overlay.h"
#include "secapp-helper-utils.h"

char *saroot;

int change_root (int argc, char **argv, char **envp){
	int rc;
	const char *m;

    if ( (m="chdir" ,rc=chdir(saroot)) == 0
          && (m="chroot",rc=chroot(saroot)) == 0
          && (m="setuid",rc=setuid(getuid())) == 0 )
        m="execve", execve(argv[1],argv+2,envp);
    else
        return 1;

    return 0;
}

int secapp_ovl(char *path){
	overlay(path);
}

int secapp_ovl_by_pid (int pid){
	char *path;
  	path = malloc(1024*sizeof(char));

  	get_path_from_pid(pid, path);
  	overlay(path);
}

int secapp_open (int argc, char **argv, char **envp, int *pid)
{
	pid_t child_pid, wpid; int a;
  	saroot = malloc (2048*sizeof(char));
	get_full_path(saroot, argv[1]);

	overlay_umount(argv[1]);
  	snd_finishedProcess_msg(*pid);
  	a = bind_umount_all (saroot);

	int status = 0;
	if ((child_pid = fork()) == 0) {
	  	if ( mkdir_all (argv[1]) != 0)
	        	printf("Error: mkdir_all.\n");
		if ( bind_mount_all (saroot) != 0)
	        	printf("Error: bind_mount.\n");
		if ( change_root (argc, argv, envp) != 0)
			printf("Error: change_root\n");
		exit(0);
	}
  	*pid = child_pid;

  	snd_startedProcess_msg(*pid);

	wpid =  wait(&status);
  		overlay_umount(argv[1]);
		snd_finishedProcess_msg(*pid);
  		a = bind_umount_all (saroot);
	  	if ( a != 0)
		        printf ("Error: bind_umount. %d\n", a);
	  	else
	  		printf("Successfully finished!\n");

	return 0;
}

