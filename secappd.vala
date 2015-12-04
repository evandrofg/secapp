/* secappd from the Secapp project.
 */

//using Posix;

extern int secapp_ovl(char *path);
extern int secapp_ovl_by_pid(int pid);
extern int get_path_from_pid (int pid, char *path);

int ask_user(string command){
	int answer = Posix.system(command);
	return answer;
}

[DBus (name = "org.efg.Secapp")]
public class SecappServer : Object {

    HashTable<string, string> table = new HashTable<string, string> (str_hash, str_equal);

    public int startedProcess (int pid) {
    	string path = "";
        stdout.printf ("Client started a process: %d\n", pid);

	    Posix.sleep(2);
        get_path_from_pid (pid, path);
        stdout.printf("DEBUG: %s\n", (string) path);
        table.insert(pid.to_string(), (string) path);
        updatedProcessTable(0);
        return 0;
    }

    public int finishedProcess (int pid) {
    	string spid;
    	spid = pid.to_string();
    	table.remove(spid);
    	updatedProcessTable(0);
    	return 0;
    }

    public signal void updatedProcessTable (int count);

    public HashTable<string, string> requestTable (){
        return table;
    }

    public int requestPermissionFromPath (string path) {
        int answer;
        // todo: include path with zenity_q
        string zenity_q1 = """zenity --question --text="Você gostaria de permitir que o aplicativo """;
        string zenity_q2 = """ leia sua pasta pessoal?" --ok-label="Permitir" --cancel-label="Negar" """;
        string zenity_q = zenity_q1 + path + zenity_q2;
        answer = ask_user(zenity_q);
        if (answer == 0){
    	    secapp_ovl(path);
        }

        return answer;
    }

    public int requestPermissionFromPid (int pid) {
        int answer;
        string zenity_q1 = """zenity --question --text="Você gostaria de permitir que o aplicativo de pid """;
        string zenity_q2 = """ leia sua pasta pessoal?" --ok-label="Permitir" --cancel-label="Negar" """;
        string zenity_q = zenity_q1 + pid.to_string() + zenity_q2;
        answer = ask_user(zenity_q);
        if (answer == 0){
    	    stdout.printf("ok");
    	    secapp_ovl_by_pid (pid);
        }
        return answer;
    }
}

[DBus (name = "org.efg.SecappError")]
public errordomain DemoError
{
    SOME_ERROR
}

void on_bus_aquired (DBusConnection conn) {
    try {
        conn.register_object ("/org/efg/secapp", new SecappServer ());
    } catch (IOError e) {
        stderr.printf ("Could not register service\n");
    }
}

void main (string[] args) {
    Bus.own_name (BusType.SESSION, "org.efg.Secapp", BusNameOwnerFlags.NONE,
                  on_bus_aquired,
                  () => {},
                  () => stderr.printf ("Could not aquire name\n"));

    new MainLoop ().run ();
}
