# LinkerAttack

Name: David Ehevich

Name: Ilon Barashi

Inject our own scanf function in c

Files included : the changed binary file which is using our injected library,server which we send the password to, , the injection code itself.

How to run:

Istall all files into a folder, when in the folder directory , in the terminal first type: export export LD_LIBRARY_PATH="." so it can find our injected library.

The server must be running , so type : gcc server.c -o server

To compile the injected library type: gcc scanFake.c --shared -fPIC -ldl -o .so.6

*The secret binary file is already included with the changed dynamic section params, it's named sec.

After completing these steps , type ./sec and you have the program running! and each time you type the password into the console it will be sent to the server.

Screenshots of changed dynamic sections , and examples of sent password to server:

ELF SCREENSHOT:

![elf](https://user-images.githubusercontent.com/54214707/163558756-2a4c63bb-209b-4adb-8c3c-d3e03a4622cf.PNG)

HEXEDIT SCREENSHOT:

![hexedit](https://user-images.githubusercontent.com/54214707/163558777-0b1f58e6-80cc-4478-9434-0e6427d60ef1.PNG)

PASSWORD SENT TO SERVER SCREENSHOT:

![password](https://user-images.githubusercontent.com/54214707/163558804-df5797cc-c7db-414a-8a09-344eedefcc80.PNG)

