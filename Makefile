PROGS = secapp-helper.c secapp-helper-mount.c secapp-helper-mkdir.c secapp-helper-overlay.c secapp-helper-utils.c

all:	secappd secapp-run secapp-reqperm secapp-manager editor

secappd: secappd.vala $(PROGS)
	valac --pkg gio-2.0 --pkg glib-2.0 --pkg posix secappd.vala $(PROGS)

secapp-run: secapp-run.c $(PROGS)
	gcc -o secapp-run secapp-run.c $(PROGS)

secapp-reqperm: secapp-reqperm.vala $(PROGS)
	valac --pkg gio-2.0 secapp-reqperm.vala $(PROGS)

secapp-manager: secapp-manager.vala
	valac --pkg gio-2.0 --pkg gtk+-3.0 secapp-manager.vala

editor: editor.vala data/editor.ui
	valac --pkg gtk+-3.0 --pkg posix editor.vala

install: all
	install -m0755 secappd secapp-run secapp-reqperm secapp-manager editor /usr/bin/
	install -m0644 data/editor.ui /usr/share/
	install -m0644 data/editor.desktop /usr/share/applications/
	install -m0644 data/secappd.desktop /etc/xdg/autostart/
	install -m0644 data/secapp-manager.desktop /usr/share/applications/
	sudo setcap cap_sys_admin,cap_sys_chroot+ep /usr/bin/secappd
	sudo setcap cap_sys_admin,cap_sys_chroot+ep /usr/bin/secapp-run

uninstall:
	rm -f /usr/bin/{secappd,secapp-run,secapp-reqperm,secapp-manager,editor}
	rm -f /usr/share/applications/{editor,secapp-manager}.desktop
	rm -f /usr/share/editor.ui
	rm -f /etc/xdg/autostart/secappd.desktop

clean:
	rm -f secappd secapp-run secapp-reqperm secapp-manager editor
