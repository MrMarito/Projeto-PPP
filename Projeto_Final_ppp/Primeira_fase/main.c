#include "Header.h"


int main(int argc, char *argv[]) {
    if(argc==2){
        while(verifica_nome(argv[1])==1){
            fflush(stdin);
            argv[1] = getnome();
        }
        primeira_fase(argv[1]);
    }
    else{
        char *nome;
        nome = getnome();
        while(verifica_nome(nome)==1){
            fflush(stdin);
            nome = getnome();
        }
        primeira_fase(nome);
    }
}