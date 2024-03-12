#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


#define BUFF_SIZE 400

char** split_str(char* str, char c)
{
    char* p1 = str; 
    char* p2 = str;
    int token_count = 0;
    while(p1 != NULL)
    {
        p1 = strchr(p1 + 1, c);
        token_count++;
    }
    
    char** tokens = (char**)malloc((token_count + 1) * sizeof(char*));
    int i = 0;
    while(1)
    {
        p1 = strchr(p2, c);
        if(p1 == NULL) break;
        *p1 = '\0'; 
        
        tokens[i] = (char*)malloc(strlen(p2) + 1);
        strcpy(tokens[i], p2);
        
        *p1 = c;
        p2 = p1 + 1;
        i++;
    }

    tokens[i] = (char*)malloc(strlen(p2) + 1);
    strcpy(tokens[i], p2);

    tokens[token_count] = NULL;
    return tokens;
}

void free_tokens(char** tokens)
{
    for(int i = 0; tokens[i] != NULL; i++)
    {
        free(&tokens[i]);
        free(tokens);
    }
}

int main(int argc, char* argv[])
{
    // int fd[2];
    // pipe(fd);
    // int id = fork();
    // if(id == 0)
    // {
    //     close(fd[0]);
    //     dup2(fd[1], STDOUT_FILENO);
    //     char* cmd[] = {"/bin/mkdir", "testFolder", NULL};
    //     execv(cmd[0], cmd);
    //     exit(0);
    // }
    // else
    // {
    //     close(fd[1]);
    //     char buff[BUFF_SIZE];
    //     int c = read(fd[0], buff, BUFF_SIZE);
    //     buff[c] = '\0';
    //     printf("OTHER PROCESS OUTPUT:\n%s\n=============");
    //     exit(0);
    // }
    char str[] = "lssda";
    char** tokens = split_str(str, ' ');
    for(int i = 0; tokens[i] != NULL; i++)
    {
        printf("token %d: %s\n", i, tokens[i]);
    }
    printf("%s\n", str);
}