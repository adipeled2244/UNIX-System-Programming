#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#define MAX_LINE_SIZE 2048

int ls_func(char *filename, FILE *fp)
{
    DIR *dir = opendir(filename);
    if (dir == NULL)
    {
        printf("cannot open directory '%s' \n", filename);
        return -1;
    }

    struct dirent *dir_to_print;

    while ((dir_to_print = readdir(dir)) != NULL)
    {
        fprintf(fp, "'%s' \n", dir_to_print->d_name);
    }

    if (0 != errno)
        perror("readdir() failed");

    // errno==0
    else
        printf("No more files.\n");

    return 1;
}

int cat_func(char *filename_from, FILE *fp_to)
{

    FILE *fp_from = fopen(filename_from, "r");
    if (fp_from == NULL)
    {
        printf("cannot open file: %s\n", filename_from);
        return -1;
    }

    char c;
    while ((c = fgetc(fp_from)) != EOF)
    {
        fputc(c, fp_to);
    }

    fclose(fp_from);

    return 1;
}

FILE *open_file(char *filename, char *mode)
{
    FILE *fp_output = fopen(filename, mode);
    if (fp_output == NULL)
    {
        fprintf(stderr, "%s", "cannot open this file");
        exit(-1);
    }

    return fp_output;
}

void illegal_action_error()
{
    fprintf(stderr, "%s", "This is an illegal action\n");
    printf("> ");
}

int main(int argc, const char *argv[])
{
    char line[MAX_LINE_SIZE];
    pid_t pid;
    char *first_arg = NULL;
    char *second_arg = NULL;
    char *third_arg = NULL;
    char *fourth_arg = NULL;
    char space[3] = " \n";

    printf("> ");
    while (fgets(line, MAX_LINE_SIZE, stdin) != NULL)
    {
        first_arg = strtok(line, space);
        second_arg = strtok(NULL, space);
        third_arg = strtok(NULL, space);
        fourth_arg = strtok(NULL, space);

        if ((pid = fork()) < 0)
            perror("fork error");

        else if (pid == 0) //child
        {
            fprintf(stdout, "--------- Process Id : %d ---------\n", getpid());
            FILE *fp_output;

            // 4 arguments -ls,cat
            if (fourth_arg != NULL)
            {
                // ls : ls dirname > outputfile
                if ((strcmp(first_arg, "ls") == 0) && (strcmp(third_arg, ">") == 0))
                {
                    fp_output=open_file(fourth_arg,"w");

                    if (ls_func(second_arg, fp_output) == -1)
                        return -1;

                    fclose(fp_output);
                }

                // cat : cat filename > outputfile
                else if ((strcmp(first_arg, "cat") == 0) && (strcmp(third_arg, ">") == 0))
                {
                    fp_output=open_file(fourth_arg,"w");


                    if (cat_func(second_arg, fp_output) == -1)
                        return -1;
                    fclose(fp_output);
                }
                // 4 and more arguments- error
                else
                {
                    illegal_action_error();
                    continue;
                }
            }

            // 1,2,3 arguments - ls
            else if (strcmp(first_arg, "ls") == 0)
            {
                if (second_arg != NULL)
                {
                    //3 arguments: ls > outputfile (ls from current dir)
                    if (strcmp(second_arg, ">") == 0 && third_arg != NULL)
                    {

                        fp_output=open_file(third_arg,"w");

                        if (ls_func("./", fp_output) == -1)
                            return -1;

                        fclose(fp_output);
                    }
                    // 2 arguments: ls filename
                    else if (third_arg == NULL)
                    {
                        if (ls_func(second_arg, stdout) == -1)
                            return -1;
                    }
                    else
                    {
                        illegal_action_error();
                        continue;
                    }
                }
                //one argument: ls (curren dir)
                else
                {
                    if (ls_func("./", stdout) == -1)
                        return -1;
                }
            }
            //2 arguments- cat
            else if (strcmp(first_arg, "cat") == 0 && second_arg != NULL && third_arg == NULL)
            {
                if (cat_func(second_arg, stdout) == -1)
                    return -1;

                printf("\n");
            }

            // illegal_action_error
            else
            {
                illegal_action_error();
                continue;
            }
        }

        else //parent
        {
            int status;
            if ((pid = waitpid(pid, &status, 0) < 0))
                perror("waitpid");
        }

        printf("> ");
    }
    exit(0);
}