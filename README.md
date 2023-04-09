# Remote Tasker

The remote tasker app does remote operations on different computers in the same house / at work.

# Updates

- *current* 0.01- search and receive files.
- 0.02- search and receive files from another computer.
- 0.03 basic UI.
- 0.04- windows support.
- 0.05- adding a setting file.
- 0.06- multiple search options.
- 0.07- multiple connections.

# Operations

- Search and copy:
for now, the remote tasker can search for a file and copy it to a directory.

# Dependencies
## Build Dependencies
- G++ compiler
- Makefile

# Usage
- 1. Download the repo.
- 2. Build it with Make main
- 3. Run "sudo ./remote_tasker"
- 4. For 0.01 - enter the directory for the copying files.
- 5. Every time that you need a certain file, you can enter its name.
     The remote tasker will look it up and copy it to the directory.

# known issues
- Search is only in /home directories for now.
- Search stops after the first occurrence.