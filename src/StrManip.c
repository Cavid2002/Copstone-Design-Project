#include <stdlib.h>
#include <string.h>

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