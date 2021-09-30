#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#define MAX_LINE_SIZE 2048
#define NUM_STRINGS_IN_ARRAY 100

void illegal_action_error();
int ls_action(char *filename, FILE *fp);
FILE *open_file(char *filename, char *mode);
void ls(char **array);
int cat_action(char *filename_from, FILE *fp_to);
char **split_to_arr(char *line);
void cat(char **array);

// get filname and mode and open it in this mode , return pointer to the file 
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

// print error 
void illegal_action_error()
{
    fprintf(stderr, "This is an illegal action\n");
    
}

// get array and split the array to char* sections
char **split_to_arr(char *line)
{
    int array_length = NUM_STRINGS_IN_ARRAY;

    char **splited_arr = malloc(array_length * sizeof(char *));
    if (splited_arr == NULL)
    {
        fprintf(stderr, "Cannot allocate array");
        exit(1);
    }

    char space[3] = " \n";
    splited_arr[0] = strtok(line, space);
    char **temparr;
    for (int i = 0; splited_arr[i] != NULL; i++)
    {
        if (i == array_length)
        {
            array_length += NUM_STRINGS_IN_ARRAY;
            temparr = realloc(splited_arr, array_length * sizeof(char *));
            if (temparr == NULL)
            {
                free(splited_arr);
                fprintf(stderr, "Cannot allocate array");
                exit(1);
            }
            else
            {
                splited_arr = temparr;
            }
        }
        splited_arr[i + 1] = strtok(NULL, space);
    }

    return splited_arr;
}

// action  ls
int ls_action(char *filename, FILE *fp)
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

    if(fp!=stdout) fclose(fp);
    closedir(dir);

    return 1;
}

//  ls 
void ls(char **array)
{

    // ls
    if (array[1] == NULL)
    {
        ls_action("./", stdout);
    }

    // ls > filename
    else if (!strcmp(array[1], ">"))
    {
        if (array[2] == NULL)
            exit(-1);

        ls_action("./", open_file(array[2], "w"));
    }

    else
    {
        // ls filename
        if (array[2] == NULL)
        {
            ls_action(array[1], stdout);
        }

        // ls from > to
        else if (!strcmp(array[2], ">"))
        {

            if (array[3] == NULL)
                exit(-1);

            ls_action(array[1], open_file(array[3], "w"));
        }

        else
        {
            illegal_action_error();
            exit(-1);
        }
    }
}

// cat action
int cat_action(char *filename_from, FILE *fp_to)
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

// cat
void cat(char **array)
{
    if (array[1] == NULL)
    {
        illegal_action_error();
        exit(-1);
    }

    else if (array[2] != NULL && !strcmp(array[2], ">"))
    {
        if (array[3] == NULL)
        {

            illegal_action_error();
            exit(-1);
        }

        cat_action(array[1], open_file(array[3], "w"));
    }

    else if (array[2] != NULL)
    {
        illegal_action_error();
        exit(-1);
    }

    else
    {
        cat_action(array[1], stdout);
    }
}

int main(int argc, const char *argv[])
{
    char *line;
    size_t length = MAX_LINE_SIZE;
    pid_t pid;

    printf("> ");
    while (getline(&line, &length, stdin) != -1)
    {

        char **splited_array = split_to_arr(line);

        if ((pid = fork()) < 0)
            perror("fork error");

        else if (pid == 0) //child
        {
            fprintf(stdout, "--------- Process Id child: %d \n", getpid());
            if (splited_array[0] == NULL)
            {
                exit(1);
            }

            else if (!strcmp(splited_array[0], "ls"))
            {
                ls(splited_array);
                exit(1);
            }

            else if (!strcmp(splited_array[0], "cat"))
            {
                cat(splited_array);
                exit(1);
            }

            else
            {
                illegal_action_error();
                exit(1);
            }
        }

        else //parent
        {
            int status;
            if ((pid = waitpid(pid, &status, 0) < 0))
                perror("waitpid");
        }

        printf("> ");
        free(line);
        free(splited_array);
        line=NULL;
    }
    exit(0);
}