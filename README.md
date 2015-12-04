
  Secapp framework for running Linux desktop applications securely.


PROGRAMS
--------

The following programs make up SecApp:

secappd - user session daemon that manages communication between applications

secapp-run - program that starts an application under the SecApp environment

secapp-reqperm - request file access permission for a given program or pid

secapp-manager - GUI utility that lists the running programs and allows the user to authorize file access permission

editor - sample application with a Secapp menu entry


INSTALLATION
------------

Secapp requires valac and the GTK+ development libraries. To install them:

$ dnf install gtk3-devel vala

The command above applies to Fedora based systems, where Secapp was tested and developed.

To install SecApp on your system, run 'make' followed by 'sudo make install'. The installation requires root access, as it copies files to system directories and sets the appropriate capabilities required for SecApp functionality.
'sudo make uninstall' can be used to uninstall it.


CODE ORGANIZATION
-----------------

The source code is explained thoroughly in the monografia.pdf document (in Portuguese). Below is a summary.

secapp-helper-*.c files are written in C and are responsible for low level system calls that create the execution environment, mount the appropriate directories and mount the overlayfs merge when requested.

The Vala programming language is used for higher level components where most of the work is creating and responding to DBus methods or showing the user a GUI in GTK+. Vala is a programming language similar to C# and Java in Syntax, and is made to work with the GOBject system for object orientation. 

secappd.vala is the user session daemon that listens to DBus connections and manages the list of running processes.

secapp-run.vala is a simple program that launches a new application under the SecApp environment. It calls the C helper functions to set up then comminicates to the secappd daemon that an application was started.

secapp-reqperm.vala requests file access permission to the secappd daemon. It simply sends a DBus message with the process pid or executable path to the daemon.

secapp-manager.vala is a GUI application written using the GTK+ toolkit.


CREDITS
--------
Author: Evandro Fernandes Giovanini
	efgiovanini@gmail.com

Under the supervision of Marco Dimas Gubitoso


