
extern int secapp_open(int argc, char **argv, char **envp, int *pid);

void main (string [] args) {
    int pid = 0;
	secapp_open (2, args, GLib.Environ.get(), &pid);
}


