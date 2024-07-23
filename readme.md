# operating_system

OPERATING SYSTEM

In this assignment, we implement the functions required for a simple operating system to manage programs and files kept in memory.
Each file stored in memory has the following properties:

 ID: uniquely identifies the file. Program uses the ID of the file it wants to access. The operating system assigns this
value to the file when the file is created.
 NAME: is the name of the file. Ex: Notes.docx. This name is determined by the user.
 FILE PATH: the path to the folder where the file is located. This FILE PATH is determined by the user.
 NUMBER OF READ: counter that keeps track of how many programs read it. The initial value is 0. A file can be
read by a maximum of 2 different programs.
 NUMBER OF WRITE: This is the counter that keeps track of how many programs write data to this file. The initial
value is 0. A maximum of 1 program can write to a file.
 IS READ: is a boolean value indicating whether there is any reading operation on the file. The initial value is False.
 IS WRITTEN: is a boolean value that indicates whether there is any writing operation on the file. The initial value is
False.

Each program that runs has the following features:

 ID: uniquely identifies a program. This value is assigned by the operating system when the program is first created.
The operating system uses ID information when a program requests access to a file.
 NAME: is the name of the program. Ex: Codeblocks. It is determined by the user.
 READ FILE ID: holds the ID of the file from which data is read by the program. The initial value is -1 and this
indicates that no files have been read.
 WRITE FILE ID: holds the ID of the file to which the program writes data. The initial value is -1 and this indicates
that there is no writing to any file.


The Operating System has 10 basic functions. Each function is performed respectively as follows:

Create new file (1): The ID, NAME and FILE PATH of the new file to be created are entered by the user and a new file is created
according to these values. Finally, the created file is added to memory to read/write.
Points to consider when creating a new file:
 There cannot be two files with the same ID.
 The operating system initially allocates enough space to hold a maximum of 4 files.
 If the user wants to create more than 4 files, this capacity is doubled.
Create new program (2): The ID and NAME of the new program to be run are entered by the user and a new program is created
according to these values. Finally, the created program is added to memory to run.
Points to consider when creating a new program:
 There cannot be two programs with the same ID.
 The operating system initially allocates enough space to run a maximum of 4 programs.
 If the user wants to run more than 4 programs, this capacity is doubled.
Read file (3): This function is run when a program wants to read a file. The ID of the file to be read and the program ID of the program
that wants to read this file are received from the user.
Here are the steps to check before a program can read the file:
 The file to be read must not be being written by another program.
 The file to be read must not have reached the maximum number of reads.
Once all conditions are met, the program can read the file. At this point, the READ FILE ID information of the program and both the
NUMBER OF READ and IS READ information of the file are updated.
Write to file (4): This function is run when a program wants to write a file. The ID of the file to be written and the program ID of the
program that wants to write this file are received from the user.
Here are the steps to check before a program can write the file:
 The file to be written must not be being read by another program.
 The file to be written must not have reached the maximum number of writes.
Once all conditions are met, the program can write the file. At this point, the WRITE FILE ID information of the program and both the
NUMBER OF WRITE and IS WRITTEN information of the file are updated.
Release reading file (5): When a program wants to finish reading operation on the file it has read, this function is run and the file
becomes available for other programs to read/write. At this stage, the ID of the program that will release the file is obtained from the
user.
The following updates must be made during the releasing phase:
 Make sure that the program is reading a file.
 The file that the program reads is determined by the READ FILE ID.
 The NUMBER OF READ information of the file is decreased.
 If NUMBER OF READ is equal to 0, IS READ information is set to false.
 Finally, the READ FILE ID information of the program is updated.
Release writing file (6): When a program wants to finish writing operation on the file it has written, this function is run and the file
becomes available for other programs to read/write. At this stage, the ID of the program that will release the file is obtained from the
user.
The following updates must be made during the releasing phase:
 Make sure that the program is writing a file.
 The file that the program writes is determined by the WRITE FILE ID.
 The NUMBER OF WRITE information of the file is decreased.
 If NUMBER OF WRITE is equal to 0, IS WRITE information is set to false.

 Finally, the READ FILE ID information of the program is updated.

Close all files for the program (7): This function is run when a program wants to release all the files it has. For this, the program ID
is obtained from the user. Then, the Release reading file and Release writing file functions are run respectively for this program.
Display all files (8): Information about each file is printed on the screen.
Display all programs (9): Information about each program is printed on the screen.
Shut down the computer (10): The computer is turned off.
