#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

/* send a startedProcess message via dbus */
int snd_startedProcess_msg(int pid){
	int val;
  	char *command;
  	char *str_pid;

  	command = malloc(1024*sizeof(char));
  	str_pid = malloc(1024*sizeof(char));

	strcpy(command, "dbus-send --type=method_call --dest=org.efg.Secapp /org/efg/secapp org.efg.Secapp.startedProcess int32:");
	sprintf(str_pid, "%d", pid);
	strcat(command, str_pid);

	val = system(command);

	//free(command);
	//free(str_pid);
	return val;
}

/* send a finishedProcess message via dbus */
int snd_finishedProcess_msg(int pid){
	int val;
  	char *command;
  	char *str_pid;

  	command = malloc(1024*sizeof(char));
  	str_pid = malloc(1024*sizeof(char));

	strcpy(command, "dbus-send --type=method_call --dest=org.efg.Secapp /org/efg/secapp org.efg.Secapp.finishedProcess int32:");
	sprintf(str_pid, "%d", pid);
	strcat(command, str_pid);

	val = system(command);

	//free(command);
	//free(str_pid);
	return val;
}

/* given a binary as the second argument, write
 * the path in the sandbox in the first argument.
 * Example: /usr/bin/firefox input writes _usr_bin_firefox
 */
int get_path(char *sandboxpath, char* binarypath){
        int size = strlen(binarypath);
        int i;
        char str[2] = "\0";
        for (i = 0; i < size; i++){
                if (binarypath[i] == '/')
                        sandboxpath[i] = '_';
                else
                        sandboxpath[i] = binarypath[i];
        }
        sandboxpath[size] = '\0';
}

/* given a command as the second argument, write
 * the path in the secapp dir in the first argument
 * Example: /usr/bin/firefox input writes
 * $HOME/.local/share/secapp/_usr_bin_firefox
 */
int get_full_path(char *path, char *command){
        char *tmp_path;
        char *tmp_command;
        char *homedir;

        homedir = malloc(2048*sizeof(char));
        tmp_path = malloc (2048*sizeof(char));
        tmp_command = malloc (2048*sizeof(char));

        get_path(tmp_path, path);
        sprintf(homedir, "%s", getenv("HOME"));

        strcat(homedir, "/.local/share/secapp/");
        strcpy(tmp_command, command);
        get_path(tmp_command, command);
        strcat(homedir, tmp_command);

        //printf("%s\n",homedir);
        strcpy(path, homedir);
        strtok(path, "\n");
}

/* recebe como argumento string como:
 * 	/home/evandro/.local/share/secapp/_usr_bin_editor/usr/bin/editor
 * e a altera para:
 * 	/usr/bin/editor
 */
int fix_path(char *path){
        int len;
        strcpy(path, path + strlen(getenv("HOME")));
        strcpy(path, path + strlen("/.local/share/secapp"));
        len = strlen(path);
        len = (len / 2) + 1;
        strcpy(path, path + len);
}

/* Dado um pid, obtém o caminho do executável
 * A função retorna o valor em /proc/pid/exe
 */
int get_path_from_pid (int pid, char *path){
  	char *pathname;
	char *buf;
  	char *cpid;

	pathname = malloc(1024*sizeof(char));
    	buf = malloc(1024*sizeof(char));
  	cpid = malloc(1024*sizeof(char));

  	sprintf(cpid, "%d", pid);

  	strcpy(pathname, "/proc/");
  	strcat(pathname, cpid);
  	strcat(pathname, "/exe");

  	readlink(pathname, buf, 1024);

  	fix_path(buf);
  	strcpy(path, buf);
  	printf("LOG: get_path_from_pid com %d, %s\n", pid, path);
  	return 0;

}
