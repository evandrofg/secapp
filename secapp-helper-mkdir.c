/* Creates the directories used in Secapp */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "secapp-helper-utils.h"

/* create one directory in the given path */
int mkdir_one (char *path, char *dir){
  	char *tmp_path;
  	char *homedir;

  	homedir = malloc(512*sizeof(char));
  	tmp_path = malloc (512*sizeof(char));

	strcpy(tmp_path, path);
  	sprintf(homedir, "%s", getenv("HOME"));

  	strcat(homedir, "/.local/share/secapp/");

    strcpy(tmp_path, strcat(homedir, tmp_path));
  	mkdir (tmp_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

  	strcat(tmp_path, dir);
  	mkdir (tmp_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

  	return 0;
}

/* create all directories used in the chroot */
int mkdir_all (char *path){
	char *tmp_dir, *tmp_path;
  	tmp_dir = malloc (8 * sizeof(char));
  	tmp_path = malloc (512 * sizeof(char));

  	get_path(tmp_path, path);

	if (mkdir_one (tmp_path, strcpy(tmp_dir, "/usr")) != 0) return 1;
	if (mkdir_one (tmp_path, strcpy(tmp_dir, "/lib")) != 0) return 1;
	if (mkdir_one (tmp_path, strcpy(tmp_dir, "/lib64")) != 0) return 1;
	if (mkdir_one (tmp_path, strcpy(tmp_dir, "/bin")) != 0) return 1;
	if (mkdir_one (tmp_path, strcpy(tmp_dir, "/dev")) != 0) return 1;
	if (mkdir_one (tmp_path, strcpy(tmp_dir, "/etc")) != 0) return 1;
	if (mkdir_one (tmp_path, strcpy(tmp_dir, "/proc")) != 0) return 1;
	if (mkdir_one (tmp_path, strcpy(tmp_dir, "/var")) != 0) return 1;

  	if (mkdir_one (tmp_path, strcpy(tmp_dir, "/home")) != 0) return 1;
  	if (mkdir_one (tmp_path, strcpy(tmp_dir, getenv("HOME"))) != 0) return 1;
	return 0;
}

