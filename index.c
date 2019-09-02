#include <stdio.h>
// #include<conio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
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

// #define PATH_MAX 100
// char *concatenate_parsed(char * dest, char *strings[], size_t number)
// {
//      dest[0] = '\0';
//      for (size_t i = 0; i < number; i++) {
//          strcat(dest, strings[i]);
//      }
//      return dest;
// }

void pwd_custom(char* flags)
{
    DIR *directory;
    int root_inode;
    int inode;
    int status = 0;
    struct stat statbuf;
    struct dirent *fileEntry;
    char *parsed[10];
    char test[100];
    // printf("Mem all succ");
    int total_length_dir = 0;
    char buffer[100];
    char* orig_path = getcwd(buffer,100);
    // printf("%s\n\n\n",orig_path);

    if(flags!=NULL){
        printf("Version 1.0--> Implementation inspired from Github source of Tirth Shah.\n");
        printf("Modified by Vineet Sawhney");
        return;
    }
    // else{
    //     if(parsed[1]!=NULL){
    //         printf("Unsupported arguments");
    //         return;
    //     }
    // }
    
    if (lstat(".", &statbuf))
    {
        perror("opendir(.)");
        status = 1;
    }
    else
    {
        //get the inode of the current directory
        inode = statbuf.st_ino;
        //print mssg and exit if current directory is the root directory
        if (inode == 2)
        {
            printf("and then we're at the root directory\n");
            exit(1);
        }

        root_inode = inode;
        //traverse through the parent directories until inode is equal to 2
        int z = 0;
        while (inode != 2)
        {
            if (!(chdir("..")))
            {
                if ((directory = opendir(".")) == NULL)
                {
                    perror("opendir(..)");
                    exit(1);
                }
                //traverse through the contents of the current directory
                while ((fileEntry = readdir(directory)))
                {
                    inode = fileEntry->d_ino;
                    //print out directory name if inodes match
                    if (inode == root_inode)
                    {
                        
                        parsed[z] = malloc(100);
                        parsed[z] = strdup(fileEntry->d_name);
                        //found parent directory}
                        z++;

                    }
                    else if (inode == 2)
                    {
                        parsed[z] = "-->home";
                        break;
                        z++;
                    }
                }
                if (lstat(".", &statbuf))
                {
                    perror("");
                    exit(1);
                }
                else
                    //next time you want to compare it with the inode of the current directory
                    root_inode = statbuf.st_ino;
                closedir(directory);
            }
            else
            {
                perror("chdir(..)");
                exit(1);
            }
        }
        total_length_dir = z;
    }
    for(int i = total_length_dir  ; i>=0; i--){
        printf("%s->",parsed[i]);
    }
    char * par = malloc(100);
    chdir(orig_path);
    printf("\n");
    fflush(stdout);

}

void loader()
{
    printf("Dropping to shell. Please wait...\n");

    int i;
    char str[] = "                                        ";
    // green();
    for (i = 0; i <= 40; i++)
    {
        printf(BOLDGREEN "\r[%s]" RESET, str);
        str[i] = '-';
        usleep(40000);
        fflush(stdout);
    }
    // reset();
}

void init_s()
{
    unsigned ms_delay = 13;
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
    char *anim4 = "# Exit\n\n\n\n";
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
         "\n>Change Directory --> cd_c"
         "\n>Present Working Directory--> pwd_c"
         "\n>exit"
         "\n>all other general commands available in UNIX shell");
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

int commands(char **parsed)
{
    printf("Command given : %s\n", parsed[0]);
    printf("Arguments passed %s\n", parsed[1]);

    int NoOfOwnCmds = 4, i, switchOwnArg = 0;
    char *ListOfOwnCmds[NoOfOwnCmds];
    char *username;

    ListOfOwnCmds[0] = "exit";
    ListOfOwnCmds[1] = "cd_c";
    ListOfOwnCmds[2] = "list";
    ListOfOwnCmds[3] = "pwd_c";

    for (i = 0; i < NoOfOwnCmds; i++)
    {
        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0)
        {
            switchOwnArg = i + 1;
            break;
        }
    }

    switch (switchOwnArg)
    {
    case 1:
        printf("\nGoodbye\n");
        exit(0);
    case 2:
        chdir(parsed[1]);
        return 1;
    case 3:
        // openHelp();
        list_commands();
        return 1;
    case 4:
        pwd_custom(parsed[1]);
        return 1;
    default:
        break;
    }

    return 0;
}

int processString(char *str, char **parsed)
{
    //HERE we parse the string, see stuff like if it has any arguments, pipes etc
    // char* strpiped[2];
    int piped = 0;

    // piped = parsePipe(str, strpiped);
    // piped = parsePipe(str);

    // printf("%d",piped);

    if (piped)
    {
        // parseSpace(strpiped[0], parsed);
        // parseSpace(strpiped[1], parsedpipe);
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

int main()
{
    char user_input[MAX_CHAR];
    char *parsedArgs[MAXLIST];
    // char* parsedArgsPiped[1024];

    init_s();
    // test();
    int parsedCommBranch = 0;
    printf("\nTo see list of supported commands, enter \"list\" anytime\n ");

    while (1)
    {
        if (take_user_input(user_input))
        {
            printf(BOLDRED "Error --> Blank Input" RESET);
            continue;
        }

        printf("\nInput is %s\n", user_input);
        parsedCommBranch = processString(user_input, parsedArgs);
    }
}
