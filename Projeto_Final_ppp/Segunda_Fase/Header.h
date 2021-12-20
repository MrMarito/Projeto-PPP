#ifndef PROJETO_FINAL_2F_HEADER_H
#define PROJETO_FINAL_2F_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//structs
struct no_fila {
    int num;
    struct no_fila * pseg;
};
struct lista {
    struct no_fila *raiz;
};
struct no {
    char palavra[50];
    struct lista pf;
    struct no *left;
    struct no *right;
};
struct arvore_binaria {
    struct no * raiz;
};

//funcoes de apio a tratamento de strings
void strtobase_u8(char *dest, const char *orig);
int comp_mchar(const char *um, const char *outro);
char* getnome();
void limpastring(char *token);
int verifica_nome(char *nome);

//funcoes para tratamento das listas
void inicializar_lista(struct lista *pf);
bool colocar_lista(struct lista *pf, int num);
void print_lista(struct lista *pf);
void print_opcao1(struct lista *pf, char *nome);

//funcoes para tratamento da arvore
void inicializar_arvore(struct arvore_binaria * pa);
struct no *addtree(struct no *pr, struct no *p);
bool colocar_arvore(struct arvore_binaria * pa, char *palavra, int num);
struct no *find(struct no *pr, char *pn);
bool consultar(struct arvore_binaria * pa, char *nome, int num);
bool consultar_opcao1(struct arvore_binaria * pa, char *nome, char *nome_ficheiro);
void consultar_opcao2(struct no *raiz, char *nome, bool *flag_opcao2);
void print_arvore(struct no *raiz);

//funcoes auxiliares
void contexto_palavra(char* nome, int num);
void segunda_fase(struct arvore_binaria *arvore, char *nome);
void menu();
void opcao1(struct arvore_binaria * pa, char *nome_ficheiro);
void opcao2(struct arvore_binaria *pa);


#endif //PROJETO_FINAL_2F_HEADER_H