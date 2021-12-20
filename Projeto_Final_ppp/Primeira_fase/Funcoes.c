#include "Header.h"


//Lê nome do ficheiro txt da consola
char* getnome(){
    printf("Indique o nome do ficheiro: \n");
    char *nome = malloc(50);
    scanf("%s", nome);
    return nome;
}


//Esta funcao vai efetuar a verificacao do nome fornecido pela consola
//Se a partir do nome dado for possivel abrir um ficheiro txt, ele e considerado valido
//Caso nao seja possivel e pedido para ser inserido novamente o nome
int verifica_nome(char *nome){
    FILE *fo = fopen(nome, "r");
    if(fo==NULL){
        fprintf(stderr, "Nome do ficheiro errado, tente novamente\n");
        return 1;
    }
    fclose(fo);
    return 0;
}

//Os valores presentes no array correspondem a todos os simbolos que possam separar as palavras
//E possivel desta forma, entao, verificar a validade de todos os caracters a medida que sao lidos do ficheiro
//Separando assim, devidamente, as palavras
int valueinarray(int val){
    int i;
    int arr[] = {10, 13, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 58, 59, 60, 61, 62, 63, 64, 91, 92, 93, 95, 123, 124, 125};
    for(i = 0; i < 30; i++){
        if(arr[i] == val) return 1;
    }
    return 0;
}

//E nesta funcao que, a partir do nome fornecido, o ficheiro txt e lido, e e criado o novo ficheiro txt
//com as palavras e as respetivas posicoes
void primeira_fase(char *nome){
    char nome2[]="idx_";
    strcat(nome2, nome);
    FILE *fo = fopen(nome, "r");
    if(fo==NULL){
        fprintf(stderr, "Erro ao abrir o ficheiro de origem\n");
        return;
    }
    FILE *fd = fopen(nome2, "w");
    if(fd==NULL){
        fprintf(stderr, "Erro ao abrir o ficheiro de destino\n");
        return;
    }
    int c, count = 0, count2 = 1;
    char palavra[50];
    int j = 0;
    while (j != 49) {
        palavra[j] = '\0';
        j++;
    }
    while((c=fgetc(fo))!=EOF){
        if(valueinarray(c)==0){
            palavra[count] = (char) c;
            count++;
        }
        else{
            if(strlen(palavra)>3) {
                fprintf(fd, "%s %d\n", palavra, (count2 - count));
            }
            count = 0;
            j = 0;
            while (palavra[j] != '\0') {
                palavra[j] = '\0';
                j++;
            }
        }
        count2++;
    }
    fclose(fo);
    fclose(fd);
}