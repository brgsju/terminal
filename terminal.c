#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
    char input[100];
    char *args[100];
    
    while(1){
        printf("Bem vindo ao meu Terminal:\nmeu_terminal>");
        fflush(stdout);
        
        if (!fgets(input, sizeof(input), stdin)){
            break;
        }
        
        input[strcspn(input, "\n")] = '\0';
        
        if (strcmp(input, "exit") == 0) {
            printf("Encerrando terminal\n");
            break;
        }
        
        // tokenização
        
        int i = 0;
        char *token = strtok(input, " ");  
        while (token != NULL && i < sizeof(input) - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;  

        // Criação dosprocessos pai e filho
        
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork falhou");
            continue;
        }

        if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                perror("Erro ao executar comando");
            }
            exit(EXIT_FAILURE); 
        } else {
            int status;
            waitpid(pid, &status, 0);
        }
      
        return 0;
        
    }
}

