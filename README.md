										-------- Custom Shell Interpreter Implementation -> ZShell  --------

Required software -> 
# any linux distro
# make
# gcc

Instructions to run -> 

# cd to directory contatining source code
# run make (if make is not installed, do "sudo apt install make"
# if make is successfull, you'll see a message
# run ./zshell
# profit
# Note if you're bored of animations, just run ./zshell test     <!-- (I got bored too) -->

Things Implemented ->

# Menu driven list
# Modular Structure
# Manual pages
# Entry and Exit commands
# History of commands entered + Up arrow traverses through list of all the commands entered.
# All commands which interact with system run as processes (Through execvp and fork).
# PWD -->>> Implemented as pwd_c. Note that I have generally used getcwd() if i need dir. information in my program. When pwd_c is called, the pwd_c executable is run (the custom module).
# FIND -->>> Implemented as find_c. Implemented as module.
# CD -->>> Implemented as cd_c. it can't be run in execvp due to system design limitation, so chdir() command is used inside a wrapper function for this.
# piping works fine.
# added makefile for easier compilation.

Credits ->

# The very basic flow of this code is inspired by Suprotik Dey's shell implementation code on GeeksForGeeks. The way the arguments are parsed is similar to his code.

# If a module has been inspired by someone's code, credit has been given inside --version flag.


-----------------------------------------------CODE DESCRIPTION---------------------------------------------

SUMMARISED -->
# Okay so the basic flow of the program is that we take commands from user
# Check if it's an inbuilt command, then the arguments are modified. If not then it is    	
# directly passed as an argument to execvp() function

Detailed(Functions described) -->
# take_user_input() and processString() -> Take input from user. libreadline is used to handle history and stuff. Also a custom history function is implemented to give history of last 10 commands.

# parseSpace() and parsePipe() -> We handle spaces and pipes using inbuilt string functions in C. We seperate at spaces
# or pipes and save arguments in an array of strings.

# command() -> We then send the arguments to match with our inbuilt functions. If it's an inbuilt, we modify the parsed command to run custom executables in our folder. If not 
# we just run whatever UNIX shell supports.

# eCommand() -> If the command doesn't exist in the UNIX shell, execvp will return error.
# We run the executables by forking a new process and replacing it with the command given using execvp

# eCommandPiped() -> If the input is piped, we call a different exec function and pass our arguents. Arg1 run as child 1 and it's output is piped to STDIN of second child  
# which is the second command itself. Also dup2 system call is used to the pipe the output of first cmd to input of second.

# getTime() and open_history() -> Also i used a lot of system libraries, helper functions to get time, directory information etc. If you have any questions just email me.   

# init_s() and loader() -> loads the shell's animation and other info.

