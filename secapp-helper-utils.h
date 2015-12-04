
int snd_startedProcess_msg(int pid);
int snd_finishedProcess_msg(int pid);
int get_full_path(char *path, char *command);
int get_path(char *sandboxpath, char* binarypath);
int fix_path(char *path);
int get_path_from_pid (int pid, char *path);
