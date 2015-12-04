[DBus (name = "org.efg.Secapp")]
interface Secapp : Object {
    public abstract int requestPermissionFromPath (string path) throws IOError;
    public abstract int requestPermissionFromPid (int pid) throws IOError;
}

void main (string [] args) {
    Secapp sapp = null;
    int arg;

    if (args.length == 1)
        Process.exit(0);

    try {
        sapp = Bus.get_proxy_sync (BusType.SESSION, "org.efg.Secapp",
                                                    "/org/efg/secapp");
        arg = int.parse(args[1]);
        if (arg == 0)
            sapp.requestPermissionFromPath (args[1]);
        else
            sapp.requestPermissionFromPid (arg);

    } catch (IOError e) {
        stderr.printf ("%s\n", e.message);
    }
}


