#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include<string.h>

int main(int argc, char **argv)
{
    DIR *directory;
    int root_inode;
    int inode;
    int status = 0;
    struct stat statbuf;
    struct dirent *fileEntry;
    char *parsed[10];
    char test[100];
    int total_length_dir = 0;
    char buffer[100];
    char *orig_path = getcwd(buffer, 100);
    char *ver = "--version";
    char* flags = argv[1];

    if (flags != NULL)
    {
        if (!strcmp(flags, ver))
        {
            printf("Version 0.1--> Implementation inspired from Github source of Tirth Shah.\n");
            printf("Modified by Vineet Sawhney");
        }
        else
        {
            printf("Invalid flags. Please do man_c pwd_c to see available options");
        }
        return 0;
    }

    if (lstat(".", &statbuf))
    {
        perror("opendir(.)");
        status = 1;
    }
    else
    {
        // Find inode of current dir
        inode = statbuf.st_ino;
        // printf("%d\n\n\n",inode);
        if (inode == 2)
        {
            printf("/home");
            exit(1);
        }

        root_inode = inode;
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
                //read current directory
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
    for (int i = total_length_dir; i >= 0; i--)
    {
        printf("%s->", parsed[i]);
    }
    char *par = malloc(100);
    chdir(orig_path);
    printf("\n");
    fflush(stdout);
    return 0;
}