#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define INP_SZE 1024
#define CMD_LNE 4096
#define ARGS_SZE 8
#define BREAKERS " \t\n"

int CngDir(char *args, char *arger);
char *ppwwdd(char *args);
char *PWD();
int worder(char **command);

// file directory
char const *whereami;
// working directory
char *myself;
// fork and execute a new process

int diver(char **args)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        char *where = malloc(INP_SZE * sizeof(char));
        strcat(where, whereami);
        strcat(where, "/");
        strcat(where, args[0]);
        execl(where, where, args[1], args[2], args[3], args[4], args[5], args[6], args[7], NULL);
        perror("shell error");
        exit(-1);
    }
    else
    {
        pid_t kid = wait(NULL);
        if (kid == -1)
        {
            perror("shell error");
            return -1;
        }
        else if (!strcmp(args[0], "dir"))
        {
            if (args[2])
                CngDir(args[2], args[3]);
            else
                CngDir(args[1], args[2]);
        }
        return 0;
    }
    return 0;
}

// returns current folder name
char *whoami(char *dir)
{
    char *sacrifice = dir;
    char *me = NULL;
    int cnt = 1;
    while (sacrifice)
    {
        me = sacrifice;
        sacrifice = strchr(sacrifice, '/');
        if (sacrifice)
        {
            sacrifice++;
            cnt++;
        }
    }
    return me;
}

// breaks shell input about the spaces
char *cattle(char *brod, char *brooker)
{
    char *shruker = malloc(3 * sizeof(char));
    strcpy(shruker, brooker);
    if (strstr(brod, ">>"))
        strcat(shruker, ">");
    char *pieces = strtok(brod, brooker);
    char *vitality = malloc((strlen(brod) + 4) * sizeof(char));
    while (1)
    {
        strcat(vitality, pieces);
        pieces = strtok(NULL, brooker);
        if (!pieces)
            break;
        strcat(vitality, " ");
        strcat(vitality, shruker);
        strcat(vitality, " ");
    }
    return vitality;
}
char **prompt_breaker(char *argu)
{
    argu = cattle(argu, ">");
    int cnt = 2;
    char *mortality = malloc((strlen(argu) + 2) * sizeof(char));
    strcpy(mortality, argu);
    char *pieces = strtok(argu, BREAKERS);
    while (mortality)
    {
        mortality = strpbrk(mortality, BREAKERS);
        if (mortality)
        {
            mortality++;
            cnt++;
        }
    }
    int hen = 0;
    char **coin = malloc(cnt * sizeof(char *));
    while (pieces != NULL)
    {
        coin[hen] = pieces;
        hen++;
        pieces = strtok(NULL, BREAKERS);
    }
    return coin;
}

// checks for command
int prompt_chk(char **cmd)
{
    char *task = cmd[0];
    if (!strcmp(task, "clear"))
        printf("\e[1;1H\e[2J");
    else if (!strcmp(task, "pwd"))
        printf("%s\n", ppwwdd(cmd[1]));
    else if (!strcmp(task, "cd"))
        CngDir(cmd[1], cmd[2]);
    else if (!strcmp(task, "exit"))
    {
        printf("\x1B[33mProcess terminated with exit code\x1B[0m \x1B[32m0\x1B[0m\n");
        exit(0);
    }
    else if(!strcmp(task, "word"))
    {
        int ans = worder(cmd);
    }
    else
        diver(cmd);
    return 0;
}

// shell
int run_terminal()
{
    while (1)
    {
        char *cutted = whoami(myself);
        char *argu = malloc(INP_SZE * sizeof(char));
        char **cmd = calloc(sizeof(char), ARGS_SZE);
        size_t sze = INP_SZE;
        printf("\x1b[31mSHELL\x1b[0m\x1b[36m /%s\x1b[0m\x1b[31m>\x1b[0m ", cutted);
        ssize_t inpsze = getline(&argu, &sze, stdin);
        if (argu[inpsze - 1] == '\n')
            argu[inpsze - 1] = '\0';
        if (strcmp(argu, ""))
            cmd = prompt_breaker(argu);
        if (cmd[0])
            prompt_chk(cmd);
        myself = PWD();
    }
    return 0;
}

// shell error
int main(int argc, char const *argv[])
{
    whereami = PWD();
    myself = PWD();
    printf(" ");
    printf("\x1B[33mwelcome to\x1B[0m ");
    printf("\x1B[32mSHELL\x1B[0m\n");
    run_terminal();
}

// pwd options
char *ppwwdd(char *dir)
{
    if (dir && !strcmp(dir, "-L"))
    {
    }
    else if (dir && !strcmp(dir, "-P"))
    {
        char *where = malloc(INP_SZE * sizeof(char));
        char *notu = getcwd(where, INP_SZE);
        if (!notu)
        {
            perror("shell error");
            return NULL;
        }
        return where;
    }
    else if (dir)
    {
        return "shell error: invalid option";
    }
    return getenv("PWD");
}

// pwd
char *PWD()
{
    char *where = malloc(INP_SZE * sizeof(char));
    char *notu = getcwd(where, INP_SZE);
    if (!notu)
    {
        perror("shell error");
        return NULL;
    }
    return where;
}

// cd
int CngDir(char *dir, char *direr)
{
    if (dir)
    {

        if (!strcmp(dir, "~"))
        {
            int p = chdir(getenv("HOME"));
            if (p == -1)
            {
                perror("shell error");
                return -1;
            }
            setenv("PWD", PWD(), 1);
            return 0;
        }
        int p = chdir(dir);
        if (dir && p == -1)
        {
            perror("shell error");
            return -1;
        }
        setenv("PWD", PWD(), 1);
        return 0;
    }
    return 0;
}

int worder(char **argv) {
    // Parse options
    int ignore_newline = 0;
    int diff_mode = 0;
    char *filename1 = NULL;
    char *filename2 = NULL;
    char c1,c2;
    int argc = 0;
    while(argv[argc] !=NULL) argc++;
    if (argc < 2 || argc > 5) {
        fprintf(stderr, "Usage: word [-n] [-d] file_name1 [file_name2]\n");
        return 1;
    }

    if (strcmp(argv[1], "-n") == 0) {
        ignore_newline = 1;
    } else if (strcmp(argv[1], "-d") == 0) {
        diff_mode = 1;
        ignore_newline = 0;
    } else {
        if(argv[1]) filename1 = argv[1];
        else{
            perror("Misiing file name");
            return 1;
        }
        ignore_newline = 0;
    }

    if (!diff_mode && argc > 3) {
        fprintf(stderr, "Wrong command\n");
        return 1;
    }

    if (diff_mode && argc < 4) {
        fprintf(stderr, "Usage: word -d file_name1 file_name2\n");
        return 1;
    }

    if (!filename1) {
        if(argv[2]) filename1 = argv[2];
        else{
            perror("Misiing file name");
            return 1;

        }
    }
    if (diff_mode) {
        if (strcmp(argv[2], "-n") == 0) {
            ignore_newline=1;
            if(argv[3]) filename1 = argv[3];
            else{
                perror("Misiing file name");
                return 1;

            }
            if(argv[4]) filename2 = argv[4];
            else{
                perror("Misiing file name");
                return 1;

            }
        }
        else{
            filename2 = argv[3];
        }

    }

    // Pipes for capturing output
    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // Fork a new process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process

        close(pipe1[0]); // Close read end of pipe1

        // Redirect standard output to the write end of pipe1
        if (dup2(pipe1[1], STDOUT_FILENO) == -1) {
            perror("Dup2 failed");
            return 1;
        }

        close(pipe1[1]); // Close write end of pipe1

        // Construct the command and arguments array for execvp
        char *args[4];
        args[0] = "wc";
        args[1] = ignore_newline ? "-w" : "-w";
        args[2] = filename1;
        args[3] = NULL;

        // Execute the word count logic using execvp
        execvp("wc", args);

        // If execvp fails, print an error
        perror("Execvp failed");
        return 1;
    } else {
        // Parent process

        close(pipe1[1]); // Close write end of pipe1

        // Wait for the child process to finish
// 
        wait(NULL);

        char buffer[128]; // Buffer for reading from pipe1
        int bytes_read = read(pipe1[0], buffer, sizeof(buffer));
        close(pipe1[0]); // Close read end of pipe1

        if (bytes_read > 0) {
            buffer[bytes_read] = '\0'; // Null-terminate the buffer
            int word_count1;
            sscanf(buffer, "%d", &word_count1); // Extract word count from output

            if (diff_mode) {
                // Fork another process for the second file comparison
                pid_t pid2 = fork();

                if (pid2 < 0) {
                    perror("Fork failed");
                    return 1;
                } else if (pid2 == 0) {
                    // Child process

                    close(pipe2[0]); // Close read end of pipe2

                    // Redirect standard output to the write end of pipe2
                    if (dup2(pipe2[1], STDOUT_FILENO) == -1) {
                        perror("Dup2 failed");
                        return 1;
                    }

                    close(pipe2[1]); // Close write end of pipe2

                    // Construct the command and arguments array for execvp
                    char *args[4];
                    args[0] = "wc";
                    args[1] = ignore_newline ? "-w" : "-w";
                    args[2] = filename2;
                    args[3] = NULL;

                    // Execute the word count logic for the second file using execvp
                    execvp("wc", args);

                    // If execvp fails, print an error
                    perror("Execvp failed");
                    return 1;
                } else {
                    // Parent process

                    close(pipe2[1]); // Close write end of pipe2

                    // Wait for the second child process to finish
                    wait(NULL);

                    char buffer2[128]; // Buffer for reading from pipe2
                    int bytes_read2 = read(pipe2[0], buffer2, sizeof(buffer2));
                    close(pipe2[0]); // Close read end of pipe2

                    if (bytes_read2 > 0) {
                        buffer2[bytes_read2] = '\0'; // Null-terminate the buffer
                        int word_count2;
                        sscanf(buffer2, "%d", &word_count2); // Extract word count from output

                        // Calculate and display the word count difference
                        if(!ignore_newline){
                        FILE *file1=NULL, *file2=NULL;
                        file1=fopen(filename1, "r");
                        file2 = fopen(filename2, "r");
                        while ((c1 = fgetc(file1)) != EOF){
                            if(c1=='\n') word_count1++;
                        }
                        while ((c2 = fgetc(file2)) != EOF){
                            if(c2=='\n') word_count2++;
                        }
                    }
                        int word_difference = abs(word_count1 - word_count2);
                        printf("Word count difference: %d\n", word_difference);
                    } else {
                        perror("Read from pipe2 failed");
                        return 1;
                    }
                }
            } else {
                if(!ignore_newline)
                {
                    FILE *file1=NULL;
                    file1=fopen(filename1, "r");
                    while ((c1 = fgetc(file1)) != EOF){
                        if(c1=='\n') word_count1++;
                    }}
                // Display the word count from the first child process
                printf("Word count: %d\n", word_count1);

            }
        } else {
            perror("Read from pipe1 failed");
            return 1;
        }
    }

    return 0;
}