#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

// ls - get source DIR and output file
int ls_func(char *filename, FILE *fp)
{
    DIR *dir = opendir(filename);
    if (dir == NULL){
        printf("cannot open directory '%s' \n", filename);
        return -1;
    }

    struct dirent *dir_to_print;

    while ((dir_to_print = readdir(dir)) != NULL){

        fprintf(fp, "'%s' \n", dir_to_print->d_name);
    }

    if (0 != errno)
        perror("readdir() failed");

    else
        printf("No more files.\n");

    return 1;
}

int main(int argc, const char *argv[])
{

    while (1)
    {
        printf("%s", "Enter_ls >");
        char sentence[50];
        char *first_arg = NULL;
        char *second_arg = NULL;
        char *third_arg = NULL;
        char *fourarg = NULL;

        char space[3] = " \n";

        // input pkuda
        fgets(sentence, 50, stdin);

        first_arg = strtok(sentence, space);
        second_arg = strtok(NULL, space);
        third_arg = strtok(NULL, space);
        fourarg = strtok(NULL, space);

        // ls
        if (first_arg != NULL)
        {
            if (strcmp(first_arg, "ls") != 0)
            {
                fprintf(stderr, "%s", "The action is not ls\n");
                return -1;
            }
        }
        // 2 arguments : ls filename
        if (third_arg == NULL)
        {
            if (ls_func(second_arg, stdout) == -1)
                return -1;
        }

        // 3 arguments or more
        else
        {

            if (strcmp(third_arg, ">") == 1 && strcmp(second_arg, ">") == 1)
            {
                fprintf(stderr, "illegal action!\n");
                return -1;
            }

            else if (strcmp(second_arg, ">") == 0)
            {
                FILE *fp = fopen(third_arg, "w");
                if (fp == NULL)
                {
                    fprintf(stderr, "%s", "cannot open this file");
                    return -1;
                }

                if (ls_func("./", fp) == -1)
                    return -1;
                fclose(fp);
            }

            else if (strcmp(third_arg, ">") == 0)
            {
                FILE *fp = fopen(fourarg, "w");
                if (fp == NULL)
                {
                    fprintf(stderr, "%s", "cannot open this file");
                    return -1;
                }

                if (ls_func(second_arg, fp) == -1)
                    return -1;
                fclose(fp);
            }
        }
    }


    return 0;
}