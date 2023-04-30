# Remote Tasker

The remote tasker app does remote operations on different computers in the same house / at work.

# Updates

- 0.01- search and receive files.
- 0.02- search and receive files from another computer.
- *current* 0.03 basic UI.
- 0.04- windows support.
- 0.05- Log.
- 0.06- Exceptions and exceptions handler.
- 0.07- adding a setting file.
- 0.08- multiple search options.
- 0.09- multiple connections.

# Operations

- Search and copy:
The remote tasker can search for a file in another computer linked to the same WIFI, and copy the file to a directory in your computer.

# Dependencies
## Build Dependencies
- only for GUI version - gtkmm4
- G++ compiler
- Makefile

## Usage
# CLI version
- 1. Download the repo.
- 2. Build it with Make main
- 3. Run "sudo ./remote_tasker"
- 4. 1. For same computer - enter the directory for the copying files.
     -    Every time that you need a certain file, you can enter its name.
          The remote tasker will look it up and copy it to the directory.

     2. For another computer, enter if the computer is server or client (you can search & copy in both of them). Then write the port, if the computer is the client send also the IP of the server. then just write the name of the file that you want to copy.

# GUI version

- 1. Download the repo.
- 2. Build it with Make graphic_tasker
- 3. run "./graphic_tasker"
- 4. follow the application instructions.

# known issues
- Search is only in /home directories for now.
- Search stops after the first occurrence.
- Some PDF and docs files gets corrapted in the copy process.