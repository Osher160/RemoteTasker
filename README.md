# Remote Tasker

The remote tasker app does remote operations on different computers in the same house / at work.

# Updates

- 0.01- search and receive files.
- *current* 0.02- search and receive files from another computer.
- 0.03 basic UI.
- 0.04- windows support.
- 0.05- Exceptions and exceptions handler
- 0.06- adding a setting file.
- 0.07- multiple search options.
- 0.08- multiple connections.

# Operations

- Search and copy:
The remote tasker can search for a file in another computer linked to the same WIFI, and copy the file to a directory in your computer.

# Dependencies
## Build Dependencies
- G++ compiler
- Makefile

# Usage
- 1. Download the repo.
- 2. Build it with Make main
- 3. Run "sudo ./remote_tasker"
- 4. 1. For same computer - enter the directory for the copying files.
     -    Every time that you need a certain file, you can enter its name.
          The remote tasker will look it up and copy it to the directory.
     2. For another computer, enter if the computer is server or client (you can search & copy in both of them). Then write the port, if the computer is the client send also the IP of the server. then just write the name of the file that you want to copy.

# known issues
- Search is only in /home directories for now.
- Search stops after the first occurrence.