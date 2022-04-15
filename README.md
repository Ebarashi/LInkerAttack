# LinkerAttack
Inject our own scanf function in c

Files included : the changed binary file which is using our injected library,server which we send the password to, , the injection code itself.

How to run:

Istall all files into a folder, when in the folder directory , in the terminal first type: export export LD_LIBRARY_PATH="." so it can find our injected library.

The server must be running , so type : gcc server.c -o server

To compile the injected library type: gcc scanFake.c --shared -fPIC -ldl -o .so.6

*The secret binary file is already included with the changed dynamic section params.

After completing these steps , type ./sec and you have the program running! and each type you type the password into the console it will be sent to the server.

Screenshots of changed dynamic sections , and examples of sent password to server:

