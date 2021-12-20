#include "Header.h"

int main(int argc, char *argv[]) {
    struct arvore_binaria arvore;
    inicializar_arvore(&arvore);
    char *nome = NULL, nome_ficheiro[50];
    if(argc==2){
        while(verifica_nome(argv[1])==1){
            fflush(stdin);
            argv[1] = getnome();
        }
        strcpy(nome_ficheiro, argv[1]);
        segunda_fase(&arvore, argv[1]);
    }
    else{
        nome = getnome();
        while(verifica_nome(nome)==1){
            fflush(stdin);
            nome = getnome();
        }
        strcpy(nome_ficheiro, nome);
        segunda_fase(&arvore, nome);
    }
    int opcao;
    char string[50];
    menu();
    scanf("%s", string);
    opcao = (int)strtol(string, NULL, 10);
    while(opcao!=3){
        if(opcao==1)
            opcao1(&arvore, nome_ficheiro);
        else if(opcao==2)
            opcao2(&arvore);
        else
            printf("Comando errado, tente novamente\n");
        fflush(stdin);
        menu();
        scanf("%s", string);
        opcao = (int)strtol(string, NULL, 10);
    }
}