#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc < 2 || argc>4) {
        fprintf(stderr, "Usage: dir [-r] [-v] dir_name\n");
        return 1;
    }

    int remove_existing = 0;
    int verbose = 0;
    int create_new = 1;  // Default behavior
    char *dir_name = NULL;

    if (strcmp(argv[1], "-r") == 0) {
        remove_existing = 1;
        if (argv[2])
        {if(strcmp(argv[2], "-v")!=0){
                    if(argv[2]){
                    dir_name=argv[2];
                    }
                    else{
                        perror("Missing directory name");
                        return 1;
                    }
                }
                else{
                    verbose=1;
                    if(argv[3]){
                    dir_name=argv[3];
                    }
                    else{
                        perror("Missing directory name");
                        return 1;
                    }
                }}
        else {
            perror("Missing directory name");
            return 1;
        }
    } else if (strcmp(argv[1], "-v") == 0) {
        verbose=1;
        if (argv[2])
        {if(strcmp(argv[2], "-r")!=0){
                    if(argv[2]){
                    dir_name=argv[2];
                    }
                    else{
                        perror("Missing directory name");
                        return 1;
                    }
                }
                else{
                    remove_existing=1;
                    if(argv[3]){
                    dir_name=argv[3];
                    }
                    else{
                        perror("Missing directory name");
                        return 1;
                    }
                }}
        else {
            perror("Missing directory name");
            return 1;
        }
    } else {
        dir_name=argv[1];
        if(argv[2]) {
            perror("Invalid command");
            return 1;
        }
    }

    // Check if the directory already exists
    struct stat st;
    if (stat(dir_name, &st) == 0 && S_ISDIR(st.st_mode)) {
        if (remove_existing) {
            if (verbose) {
                printf("Removing existing directory: %s\n", dir_name);
            }

            pid_t pid_del=fork();

            if (pid_del < 0) {
                perror("Fork failed");
                return 1;
            } else if (pid_del == 0) {
            
                char *args[] = {"rm", "-r", dir_name, NULL};
                if (execvp("rm", args) == -1) {
                    perror("Error deleting directory");
                    return 1;
                }
            }
            else{
                wait(NULL);
                if(verbose) printf("Directory deleted successfully.\n");
                
                }
            
        } else {
            if (remove_existing) {
                
            printf("Removing existing directory: %s\n", dir_name);
                
            pid_t pid_del=fork();

            if (pid_del < 0) {
                perror("Fork failed");
                return 1;
            } else if (pid_del == 0) {
            
                char *args[] = {"rm", "-r", dir_name, NULL};
                if (execvp("rm", args) == -1) {
                    perror("Error deleting directory");
                    return 1;
                }
            }
            else{
                wait(NULL);
                if(verbose) printf("Directory deleted successfully.\n");
                
                }
            
        } 
            fprintf(stderr, "Directory already exists: %s\n", dir_name); 
            create_new = 0; // Don't create new directory
        }
    }

    if (create_new) {
        // Fork a new process
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            return 1;
        } else if (pid == 0) {
            // Child process
            // Construct the command and arguments array for mkdir
            // wait(NULL);
            char *args[3];
            args[0] = "mkdir";
            args[1] = dir_name;
            // args[1]="hello2";
            args[2] = NULL;

            // Execute the mkdir command using execvp
            
            if (execvp("mkdir", args)==-1){
                perror("Error in making directory");
                return 1;
            }


            
        } else {
            // Parent process

            // Wait for the child process to finish
            // int status;
            wait(NULL);

            pid_t enter_pid = fork();
        
            if (enter_pid < 0) {
                perror("Fork failed");
                return 1;
            } else if (enter_pid == 0) {
                // Child process to change directory
                if (chdir(dir_name) == 0) {
                    if(verbose) {
                        printf("New Directory created: %s\n", dir_name);
                        printf("Changed to directory: %s\n", dir_name);
                        }
                    char cwd[1024];
                    if (getcwd(cwd, sizeof(cwd)) != NULL) {
                        printf("Current working directory: %s\n", cwd);
                    } else {
                        perror("getcwd");
                    }
                } else {
                    perror("Error changing directory");
                    return 1;
                }
            } else {
                // Parent process
                wait(NULL); // Wait for the child process to finish
            }        
        }
    }

// 
    return 0;
}