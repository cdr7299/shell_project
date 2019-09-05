#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <time.h>

#define clear() printf("\033[H\033[J")
#define MAX_CHAR 200
#define MAXLIST 100 // max number of commands to be supported

#define RESET "\033[0m"
#define BOLDBLACK "\033[1m\033[30m" /* Bold Black */
#define BOLDRED "\033[1m\033[31m"   /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define BOLDBLUE "\033[1m\033[34m"  /* Bold Blue */
#define BOLDCYAN "\033[1m\033[36m"  /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m" /* Bold White */
#define TEST_ANIM_VAL_LOADER 10000
#define MASTER_ANIM_VAL_LOADER 150000
#define TEST_ANIM_VAL_TEXT 2
#define MASTER_ANIM_VAL_TEXT 12

char *history[30];
int history_index = 0;
int test = 0;

void open_history()
{
    // get_hist
    // To save history of entered commands
    int count = history_index - 1;
    if (count < 10)
    {
        while (count > -1)
        {
            puts(history[count]);
            // printf("\n");
            count--;
        }
    }
    else
    {
        //if number of commands is greater than 10, show the recent 10
        while (count > (history_index - 10))
        {
            puts(history[count]);
            // printf("\n");
            count--;
        }
    }
}

void open_man(char **args)
{
    // Vi is preinstalled in most linux distros.
    char *command_name = args[1];

    if (!strcmp(command_name, "pwd_c"))
    {
        system("cat man_pwd.txt");
    }

    if (!strcmp(command_name, "find_c"))
    {
        system("cat man_find.txt");
    }

    if (!strcmp(command_name, "cd_c"))
    {
        system("cat man_cd.txt");
    }
    
}

void loader()
{
    printf("Dropping to shell. Please wait...\n");
    int i;
    char str[] = "                                        ";
    float usec_val;
    if (test == 1)
    {
        usec_val = TEST_ANIM_VAL_LOADER;
    }
    else
    {
        printf("Loader set a master");
        usec_val = MASTER_ANIM_VAL_LOADER;
    }

    for (i = 0; i <= 40; i++)
    {
        printf(BOLDGREEN "\r[%s]" RESET, str);
        str[i] = '-';
        usleep(usec_val);
        usec_val = usec_val * 0.85;
        fflush(stdout);
    }
    // reset();
}

void init_s()
{
    unsigned ms_delay;
    if (test)
    {
        ms_delay = TEST_ANIM_VAL_TEXT;
    }
    else
    {
        ms_delay = MASTER_ANIM_VAL_TEXT;
    }

    unsigned usecs = ms_delay * 1000;
    clear();
    printf(BOLDWHITE "**********WELCOME TO MY SHELL ************" RESET);
    printf("\n\n");
    char *user = getenv("USER");
    printf("You are @");
    printf(BOLDCYAN "%s\n" RESET, user);
    char *anim1 = "Stuff you can do ----->\n";
    for (int i = 0; i < strlen(anim1); i++)
    {
        // printf("\033[1;31m");
        printf("%c", anim1[i]);
        usleep(usecs);
        fflush(stdout);
    }
    char *anim2 = "# Execute from a list of a commands\n";
    // printf("# Execute from a list of a commands\n");
    for (int i = 0; i < strlen(anim2); i++)
    {
        printf("%c", anim2[i]);
        usleep(usecs);
        fflush(stdout);
    }
    char *anim3 = "# Read manual pages\n";
    // printf("# Read manual pages\n");
    for (int i = 0; i < strlen(anim3); i++)
    {
        printf("%c", anim3[i]);
        usleep(usecs);
        fflush(stdout);
    }
    char *anim4 = "# Exit\n\n";
    // printf("# Exit\n\n\n\n");
    for (int i = 0; i < strlen(anim4); i++)
    {

        printf("%c", anim4[i]);
        usleep(usecs);
        fflush(stdout);
    }

    loader();
    printf("\n");
    // sleep(1);
}

void list_commands()
{
    puts("\nList of Custom Commands supported (To see implementation, read code):"
         "\n> Change Directory -->" BOLDCYAN " cd_c" RESET
         "\n> Present Working Directory -->" BOLDCYAN " pwd_c" RESET
         "\n> Find if file exists in current directory -->" BOLDCYAN " find_c <filename>." RESET
         "\n  example: find_c index.c"
         "\n> To see last 10 commands, enter -->" BOLDCYAN " history" RESET
         "\n> exit"
         "\n> All other general commands available in UNIX shell" BOLDCYAN "\n> To open manual, enter man_c followed by command name" RESET);
}

void get_cur_dir()
{
    //Just to print every time waiting for user as pwd_custom does't return the parsed string,
    //rather prints one string at a time. Concat and processing it as a string would increase time complexity
    //even more
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    // printf( BOLDCYAN "\nCurrent Working Directory: %s" RESET, cwd);
    printf(BOLDCYAN "\n%s" RESET, cwd);
}

int take_user_input(char *arr)
{
    char *buffer;
    get_cur_dir();
    buffer = readline(":~$ ");
    // scanf("%s",arr);
    if (strlen(buffer) != 0)
    {
        add_history(buffer);
        strcpy(arr, buffer);
        if(strcmp(buffer,"history")){
            history[history_index] = malloc(100);
            history[history_index] = strdup(buffer);
            history_index++;
        }
        return 0;
    }
    else
    {
        return 1;
    }
}
void parseSpace(char *str, char **parsed)
{
    //we seperate spaces and take the arguments seperately
    //like cd hello
    //cd -> stored in 0th index, argument hello in parsed[1]
    int i;
    for (i = 0; i < MAXLIST; i++)
    {
        //This function seperates the arguments and commands
        parsed[i] = strsep(&str, " ");
        //Also handle the fact the if parsed character is 0, don't increment i
        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
    // printf("%s",*parsed);
}
int parsePipe(char *str, char **strpiped)
{
    int i;
    for (i = 0; i < 2; i++)
    {
        strpiped[i] = strsep(&str, "|");
        if (strpiped[i] == NULL)
            break;
    }

    if (strpiped[1] == NULL)
        return 0; // returns zero if no pipe is found.
    else
    {
        return 1;
    }
}
int commands(char **parsed)
{
    int n = 8, i, command_given = 0;
    char *custom_commands[n];
    char *username;

    custom_commands[0] = "exit";
    custom_commands[1] = "cd_c";
    custom_commands[2] = "list";
    custom_commands[3] = "pwd_c";
    custom_commands[4] = "cd";
    custom_commands[5] = "find_c";
    custom_commands[6] = "man_c";
    custom_commands[7] = "history";

    for (i = 0; i < n; i++)
    {
        if (strcmp(parsed[0], custom_commands[i]) == 0)
        {
            command_given = i + 1;
            break;
        }
    }

    switch (command_given)
    {
    case 1:
        printf("Bye\n");
        exit(0);
    case 2:
        if (parsed[1] == NULL)
            return 1;
        chdir(parsed[1]);
        return 1;
    case 3:
        list_commands();
        return 1;
    case 4:
        parsed[0] = "./pwd_c";
        return 0;
    case 5:
        if (parsed[1] == NULL)
            return 1;
        chdir(parsed[1]);
        return 1;
    case 6:
        parsed[0] = "./find_c";
        return 0;
    case 7:
        open_man(parsed);
        return 1;
    case 8:
        open_history();
        return 1;
    default:
        break;
    }
    return 0;
}

int processString(char *str, char **parsed, char **parsedpipe)
{
    //HERE we parse the string, see stuff like if it has any arguments, pipes etc
    // char* strpiped[2];
    int piped = 0;
    char *strpiped[2];
    piped = parsePipe(str, strpiped);
    // printf("%d",piped);

    if (piped)
    {

        parseSpace(strpiped[0], parsed);
        parseSpace(strpiped[1], parsedpipe);
        // printf("%s\n", strpiped[0]);
        // printf("%s\n", strpiped[1]);
    }
    else
    {
        //check and seperate the arguments and store the args in parsed array.
        //Note that first index will have command and second will have args if no pipes exist
        parseSpace(str, parsed);
    }

    if (commands(parsed))
        return 0;
    else
        return 1 + piped;
}
void eCommandPiped(char **parsed, char **parsedpipe)
{
    pid_t pid1, pid2;
    int pipefd[2];
    // Create a pipe.
    pipe(pipefd);
    // Create our first process.
    pid1 = fork();
    if (pid1 == 0)
    {
        printf("Hello p1");
        // Hook stdout up to the write end of the pipe and close the read end of
        // the pipe which is no longer needed by this process.
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        //Exec our first command
        execvp(parsed[0], parsed);
        perror("exec");
        return;
    }
    // Create our second process.
    pid2 = fork();
    if (pid2 == 0)
    {
        printf("Hello p2");

        // Hook stdin up to the read end of the pipe and close the write end of
        // the pipe which is no longer needed by this process.
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]);
        // Similarly, exec second command.
        execvp(parsedpipe[0], parsedpipe);
        perror("exec");
        return;
    }
    // Close both ends of the pipe.

    close(pipefd[0]);
    close(pipefd[1]);
    // Wait for everything to finish and exit.
    wait(&pid1);
    wait(&pid2);
    return;
}
void eCommand(char **parsed)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        printf(BOLDRED "\nCoudln't fork child.." RESET);
        return;
    }
    else if (pid == 0)
    {
        if (execvp(parsed[0], parsed) < 0)
        {
            printf(BOLDRED "\nError executing command.." RESET);
        }

        exit(0);
    }
    else
    {
        wait(NULL);
        return;
    }
}

int main(int argc, char **argv)
{
    char user_input[MAX_CHAR];
    char *args[MAXLIST];
    char *argsPiped[MAXLIST];

    if (argv[1])
    {
        printf("  ");
        if (!strcmp(argv[1], "test"))
        {
            test = 1;
            // printf("test set");
        }
    }

    //start loading
    init_s();

    int parsedCommBranch = 0;
    printf("\nTo see list of supported commands, enter \"list\" anytime\n ");

    while (1)
    {
        //wait for user input
        if (take_user_input(user_input))
        {
            // printf(BOLDRED "Error --> Blank Input" RESET);
            continue;
        }
        parsedCommBranch = processString(user_input, args, argsPiped);
        if (parsedCommBranch == 1)
            eCommand(args);

        if (parsedCommBranch == 2)
        {
            eCommandPiped(args, argsPiped);
        }
    }
    return 0;
}
