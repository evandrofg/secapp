#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mount.h>
#include "secapp-helper-utils.h"

/* given a command, mount the real homedir using overlayfs */
int overlay(char *command){
  	char *dirname, *homedir, *ovl_arg, *ovl_path, *lowerdir, *upperdir, *workdir;
  	dirname = malloc(1024*sizeof(char));
	homedir = malloc(1024*sizeof(char));
	ovl_arg = malloc(1024*sizeof(char));
	ovl_path = malloc(1024*sizeof(char));
	lowerdir = malloc(1024*sizeof(char));
	upperdir = malloc(1024*sizeof(char));
	workdir = malloc(1024*sizeof(char));
  	get_path(dirname, command);

  	strcpy (homedir, getenv("HOME"));

	strcpy (lowerdir, "lowerdir=/home,upperdir=");

	strcpy (upperdir, homedir);
  	strcat (upperdir, "/.local/share/secapp/");
  	strcpy (ovl_path, upperdir);
	strcat (upperdir, dirname);
	strcat (upperdir, "/home,workdir=");

	strcpy (workdir, homedir);
  	strcat (workdir, "/.local/share/secapp/wdir");

	strcat (ovl_arg, lowerdir);
	strcat (ovl_arg, upperdir);
	strcat (ovl_arg, workdir);

	strcat (ovl_path, dirname);
	strcat (ovl_path, "/home");

	return mount("overlay", ovl_path, "overlay", MS_MGC_VAL, ovl_arg);
}

/* given a command, umount the real homedir via overlayfs */
int overlay_umount(char *command){
	char *dirname, *homedir;
  	dirname = malloc(1024*sizeof(char));
	homedir = malloc(1024*sizeof(char));

  	get_path(dirname, command);

  	strcpy (homedir, getenv("HOME"));
	strcat (homedir, "/.local/share/secapp/");
	strcat (homedir, dirname);
	strcat (homedir, "/home");

    return umount(homedir);
}

