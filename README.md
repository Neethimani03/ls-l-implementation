 -l Command Implementation in C

This project implements a simplified version of the Linux `ls -l` command using C and POSIX system calls.

## Features
- Lists files in a directory
- Displays file permissions
- Shows number of hard links
- Displays owner and group names
- Shows file size and last modified time

## System Calls and APIs Used
- opendir()
- readdir()
- stat()
- getpwuid()
- getgrgid()
- ctime()

## Build and Run
```bash
gcc ls-l.c -o myls
./myls

