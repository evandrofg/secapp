/* bind mounts all directories in the Secapp environment */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mount.h>

/* bind mount one directory */
int bind_mount (char *path, char *dir){
	char *tmp_path;
  	tmp_path = malloc (512*sizeof(char));
  	strcpy (tmp_path, path);

  	strcpy (tmp_path, strcat(tmp_path, dir) );
  	if ( mount (dir, tmp_path, NULL, MS_MGC_VAL|MS_BIND, NULL) != 0){
		printf("error: mounting\n");
	  	return 1;
	}
  	return 0;
}

/* bind umount one directory */
int bind_umount (char *path, char *dir){
  	char *tmp_path;
  	tmp_path = malloc (512*sizeof(char));
	strcpy (tmp_path, path);

  	strcpy (tmp_path, strcat(tmp_path, dir) );

	if ( umount (tmp_path) != 0) {
	  	return 1;
	}
  	return 0;
}

/* bind mount all directories in the chroot */
int bind_mount_all (char *path){
	char *tmp_dir;
  	tmp_dir = malloc (12 * sizeof(char));

	if (bind_mount (path, strcpy(tmp_dir, "/usr")) != 0) return 1;
	if (bind_mount (path, strcpy(tmp_dir, "/lib")) != 0) return 1;
	if (bind_mount (path, strcpy(tmp_dir, "/lib64")) != 0) return 1;
	if (bind_mount (path, strcpy(tmp_dir, "/bin")) != 0) return 1;
	if (bind_mount (path, strcpy(tmp_dir, "/dev")) != 0) return 1;
	if (bind_mount (path, strcpy(tmp_dir, "/etc")) != 0) return 1;
	if (bind_mount (path, strcpy(tmp_dir, "/proc")) != 0) return 1;
	if (bind_mount (path, strcpy(tmp_dir, "/var")) != 0) return 1;
	return 0;
}

/* bind umount all directories in the chroot */
int bind_umount_all (char *path){
	char *tmp_dir;
  	tmp_dir = malloc (12 * sizeof(char));

	if (bind_umount (path, strcpy(tmp_dir, "/usr")) != 0) return 1;
	if (bind_umount (path, strcpy(tmp_dir, "/lib")) != 0) return 2;
	if (bind_umount (path, strcpy(tmp_dir, "/lib64")) != 0) return 3;
	if (bind_umount (path, strcpy(tmp_dir, "/bin")) != 0) return 4;
	if (bind_umount (path, strcpy(tmp_dir, "/dev")) != 0) return 5;
	if (bind_umount (path, strcpy(tmp_dir, "/etc")) != 0) return 6;
	if (bind_umount (path, strcpy(tmp_dir, "/proc")) != 0) return 7;
	if (bind_umount (path, strcpy(tmp_dir, "/var")) != 0) return 8;
	return 0;
}

