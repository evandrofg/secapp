#include "secapp-helper.h"

//extern int secapp_open(int argc, char **argv, char **envp, int *pid);

void main (int argc, char **argv, char **envp) {
	int pid = 0;
    int status = system("install -d $HOME/.local/share/secapp/wdir");
	secapp_open (argc, argv, envp, &pid);
}


