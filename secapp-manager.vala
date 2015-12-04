using GLib;
using Gtk;

[DBus (name = "org.efg.Secapp")]
interface Secapp : Object {
    public abstract HashTable<string, string> requestTable () throws IOError;
    public abstract int requestPermissionFromPath(string path) throws IOError;
    public signal void updatedProcessTable (int count);
}

public class Main : Object
{
	private Window window;
	private ListBox listbox;
	private ListBoxRow row;
	//private Box box;
	private Label label;
	private Button button;
	private Secapp sapp;
	private HashTable<string, string> table;
	private int counter = 0;
	string path;
	string pid;
	Label selected_label;

	public Main () {
        /* Vala connection */
		try {
            sapp = Bus.get_proxy_sync (BusType.SESSION, "org.efg.Secapp",
                                                    "/org/efg/secapp");
            updated_table();

            sapp.updatedProcessTable.connect((c) => {
            stdout.printf ("Got pong %d for msg\n", c);
            updated_table();
            populate_list();
            counter++;
        });

        } catch (IOError e) {
            stderr.printf ("%s\n", e.message);
        }

        /* Create and set up window */
		window = new Window ();
		window.set_title ("Image Viewer in Vala");
		window.window_position = Gtk.WindowPosition.CENTER;
        window.destroy.connect (Gtk.main_quit);
        window.set_default_size(600, 400);

		Gtk.HeaderBar header = new Gtk.HeaderBar();
        header.set_show_close_button (true);
        header.set_title ("Secapp Manager");
        header.set_subtitle ("Lista de Processos");
        window.set_titlebar(header);

        button = new Button.with_label("Autorizar");
        header.pack_start(button);
		// Set up the UI
		//var box = new Box (Orientation.VERTICAL, 5);
		//var button = new Button.with_label ("Open image");
		//image = new Image ();

        listbox = new ListBox();
		populate_list();
		window.add(listbox);

		//box.pack_start (image, false, false, 0);
		//box.pack_end (button, false, false, 0);

		//window.add (box);

		// Show open dialog when opening a file
		//button.clicked.connect (on_open_image);
		button.clicked.connect (() => {
                // Emitted when the button has been activated:
            stdout.printf ("Valor clicado: %s, %s\n", this.pid, path);
            try {
                //sapp.requestPermissionFromPid(int.parse(this.pid));
                sapp.requestPermissionFromPath (selected_label.label);
            } catch (IOError e) {
                stderr.printf ("%s\n", e.message);
            }
        });

		window.show_all ();
		window.destroy.connect (main_quit);
	}

	public void populate_list (){
	    /*string path;
        string pid;*/
        HashTableIter<string, string> iter = HashTableIter<string, string> (table);
        stdout.printf("Populando lista...\n");
        listbox.remove(row);

        while (iter.next (out pid, out path)) {
            this.counter++;
            stdout.printf ("%s => %s\n", pid, path);

            //box = new Gtk.Box(Gtk.Orientation.HORIZONTAL, 0);
            label = new Gtk.Label(path);
            //button = new Gtk.Button.with_label("Autorizar");
            //box.pack_start(label, false, false, 0);
            //box.pack_end (button, false, false, 0);
            row = new ListBoxRow();
            //row.add(box);
            row.add(label);

/*            listbox.row_selected.connect (() => {
                stdout.printf("DBG: pid %s\n", pid);
                pid = "10";
                current_pid = pid;
                stdout.printf ("Valor clicado: %s %s\n", current_pid, pid);
            });*/
            listbox.row_selected.connect (() => {
                selected_label = new Label(label.label);
                stdout.printf("DBG: label %s\n", selected_label.label);
            });

            listbox.add(row);
            listbox.show_all();
        }
	}

	public void updated_table (){
	    try{
            table = sapp.requestTable();
        } catch (IOError e) {
            stderr.printf ("%s\n", e.message);
        }
	}

/*	public void dialog_response (Dialog dialog, int response_id) {
	    int reply = demo.ping ("ola");
		switch (response_id) {
			case ResponseType.ACCEPT:
				var filename = (dialog as FileChooserDialog).get_filename ();
				image.set_from_file (filename);
				break;
			default:
				break;
		}
		dialog.destroy ();
	}*/

/*	[CCode (instance_pos = -1)]
	public void on_open_image (Button self) {
		var filter = new FileFilter ();
		var dialog = new FileChooserDialog ("Open image",
		                                    window,
		                                    FileChooserAction.OPEN,
		                                    Stock.CANCEL, ResponseType.CANCEL,
		                                    Stock.OK,     ResponseType.ACCEPT);
		filter.add_pixbuf_formats ();
		dialog.add_filter (filter);
		dialog.response.connect (dialog_response);
		dialog.show ();
	}*/

	static int main (string[] args) {
		Gtk.init (ref args);
		var app = new Main ();

		Gtk.main ();

		return 0;
	}
}

