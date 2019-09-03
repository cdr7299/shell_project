#include <stdio.h> 
#include <dirent.h>
#define BOLDCYAN "\033[1m\033[36m"  /* Bold Cyan */
#define RESET "\033[0m"
#include<string.h>
#include<stdlib.h>


int main(int argc, char **argv)
{
    // printf("I run");
    char *filenames[100];
    char *search_key = argv[1];
    if (argv[1] == NULL)
    {
        printf("Please provide arguments. example --> find_c hello.c");
        return 0;
    }
    struct dirent *de; 
    DIR *dr = opendir(".");
    if (dr == NULL) 
    {
        printf("Could not open current directory");
        return 0;
    }
    int z = 0;
    while ((de = readdir(dr)) != NULL)
    {
        // printf("%s\n", de->d_name);
        filenames[z] = malloc(100);
        filenames[z] = strdup(de->d_name);
        z++;
    }
    closedir(dr);

    int found = 0;
    for (int i = 0; i < z; i++)
    {
        // printf("%s\n",filenames[i]);
        if (!strcmp(filenames[i], search_key))
        {
            found = 1;
        }
    }
    if (found)
    {
        printf("FILE FOUND. Printing all files..\n");
        for (int i = 0; i < z; i++)
        {
            if (!strcmp(filenames[i], search_key))
            {
                printf(BOLDCYAN "%s\n" RESET, filenames[i]);
            }
            else{
            printf("%s\n", filenames[i]);
            }
        }
    }

    else
    {
        printf("File %s doesn't exist in current directory.", argv[1]);
    }
    return 0;
}