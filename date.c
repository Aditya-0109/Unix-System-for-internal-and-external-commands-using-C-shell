#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>

int adj=0;

void printDateString(const char *file_path, int rfcFormat) {
    struct stat st;
    
    if (stat(file_path, &st) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    char date_print[256];

    if (rfcFormat) {
        struct tm *time = localtime(&st.st_mtime);
        time_t adjusted_time = mktime(time);
        struct tm *adjusted_tm_info = localtime(&adjusted_time);
        
        strftime(date_print, sizeof(date_print), "%a, %d.%m.%Y %H:%M:%S +05:30", adjusted_tm_info);
    } else {
        struct tm *time = localtime(&st.st_mtime);
        time->tm_mday+=adj;
        strftime(date_print, sizeof(date_print), "%A, %d %B %Y %I:%M:%S %p", time);
    }

    printf("%s\n", date_print);
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 4) {
        fprintf(stderr, "Usage: date [-d] [-R] file_name\n");
        return 1;
    }


    int rf_date = 0;
    char *file_name = NULL;

    // if(argc==4){
    //     // if(argv[1]!="-d"){
    //     //     perror("Wrong command");
    //     //     return 1;
    //     // }
    //     if (argv[2]!="yesterday" && argv[2]!="today" && argv[2]!="tomorrow"){
    //         perror("Invalid command");
    //         return 1;
    //     }
    //     else{
    //         argv[3]=file_name;
    //         if (argv[2]=="yesterday") adj=-1;
    //         if (argv[2]=="tomorrow") adj=1;
    //     }
    // }

    if (strcmp(argv[1], "-d") == 0) {
        if(argc!=4){
            if (argv[2]) {
                    file_name = argv[2];
                } else {
                    perror("Missing directory name");
                    return 1;
                }
            }
        else{
            if(strcmp(argv[2], "yesterday") == 0) adj=-1;
            else if(strcmp(argv[2], "tomorrow") == 0) adj=1;
            else if(strcmp(argv[2], "today") == 0) adj=0;
            else{
                perror("Invalid command");
                    return 1;
            }
            file_name=argv[3];
        }

    } else if (strcmp(argv[1], "-R") == 0) {
        rf_date = 1;
        if (argv[2]) {
            file_name = argv[2];
        } else {
            perror("Missing directory name");
            return 1;
        }
    } else {
        file_name = argv[1];
        if (argv[2]) {
            perror("Invalid command");
            return 1;
        }
    }
// 
    // Fork a new process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        
        printDateString(file_name,rf_date);
    } else {
        // Parent process
        
        // Wait for the child process to finish
        wait(NULL);
    }

    return 0;
}