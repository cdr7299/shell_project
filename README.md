										-------- Custom Shell Interpreter Implementation -> ZShell  --------

Required software -> 
# any linux distro
# make
# gcc

Instructions to run -> 

# cd to directory contatining source code
# run make (if make is not installed, do "sudo apt install make"
# if make is successfull, you'll see a message.
# run ./zshell
# profit
# Note if you're bored of animations, just run ./zshell test. (I got bored too)

Things Implemented ->

# Menu driven list
# Manual pages
# Entry and Exit commands
# History of commands entered + Up arrow traverses through list of all the commands entered
# All commands which interact with system run as processes (Through execvp and fork)
# PWD -->>> Implemented as pwd_c. Note that i have generally used getcwd() if i need dir. information in my program. When pwd_c is called, the pwd_c executable is run.
# FIND -->>> Implemented as find_c. Implemented as module.
# CD -->>> Implemented as cd_c. it can't be run in execvp due to system design limitation, so chdir() wrapper is used for this
# piping works fine.
# added makefile for easier compilation

Credits ->

# The very basic flow of this code is inspired by Suprotik Dey's code on GeeksForGeeks. The way the arguments are parsed is similar to his code.
# If a module has been inspired by someone's code, credit has been given inside --version flag.


Information -->


SUMMARISED -->
# Okay so the basic flow of the program is that we take commands from user
# Check if it's an inbuilt command, then the arguments are modified. If not then it is    	
# directly passed as an argument to execvp() function

Detailed -->
# Take input from user. libreadline is used to handle history and stuff. Also a custom history function is implemented to give history of last 10 commands.

# We handle spaces and pipes using inbuilt string functions in C. We seperate at spaces
# or pipes and save arguments in an array of strings.

# We then send the arguments to match with our inbuilt functions

# If it's an inbuilt, we modify the parsed command to run our executables in our folder. If not we just run whatever UNIX shell
# supports. If the command doesn't exist in the UNIX shell, execvp will return error.

# We run the executables by forking a new process and replacing it with the command given using execvp

# Now we loop again. 

# If the input is piped, we call a different exec function and pass our arguents. Arg1 run as child 1 and it's output is piped to STDIN of second child which is the
# second command itself. Also dup2 system call is used to the pipe the output of first cmd to input of second.   

