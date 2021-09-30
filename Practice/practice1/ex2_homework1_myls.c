#include <stdio.h>
#include <dirent.h>
#include <errno.h>

int main (int argc, const char* argv[])
{
    if (argc != 2)
  {
    fprintf(stderr, "Usage: ./FileAttributes 'file-path'\n");
    return 1;
  }

    DIR * dir=opendir(argv[1]);
    if (dir==NULL){
        printf("cannot open directory '%s' \n",argv[1]);
        return 1;
    }

    struct dirent *dir_to_print;

    while((dir_to_print= readdir(dir))!=NULL){
        printf("'%s' \n",dir_to_print->d_name);
    }

    if (0 != errno)
            perror("readdir() failed");
        
        else
            printf("No more files.\n");
    

    closedir(dir);

  return 0;
}