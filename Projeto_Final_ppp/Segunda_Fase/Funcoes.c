#include "Header.h"

/***********************************************************************/
//Funcoes de verificacao e tratamento de strings

static char acentuadas[][8] = {"á", "Á", "à", "À", "ã", "Ã", "â", "Â", "ä", "Ä", "ç", "Ç",
                        "é", "É", "è", "È", "ê", "Ê", "í", "Í", "ì", "Ì", "î", "Î",
                        "ó", "Ó", "ò", "Ò", "õ", "Õ", "ô", "Ô", "ö", "Ö", "ú", "Ú",
                        "ù", "Ù", "û", "Û", "\0"};
static char base[] = {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'c', 'c',
               'e', 'e', 'e', 'e', 'e', 'e', 'i', 'i', 'i', 'i', 'i', 'i',
               'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'u', 'u',
               'u', 'u', 'u', 'u', '\0'};


//funcoes da livraria fornecida pelo professor para tratamento de strings
int comp_mchar(const char *um, const char *outro) {
    int i = 0;
    while (um[i] != 0) {
        if (um[i] != outro[i])
            return 0;
        i++;
    }
    return i;
}
void strtobase_u8(char *dest, const char *orig) {
    int i = 0, j = 0, c;
    // percorrer a string origem
    c = (unsigned char) orig[0];
    while (c != 0) {
        if ((c & 0x80) == 0) {
            // é um carater ASCII, basta converter as letras para minusculas
            if (c <= 'Z' && c >= 'A')
                c = c + 'a' - 'A';
            i++;
            dest[j] = (char) c;
            j++;
        } else {
            // é um carater UTF-8 com mais de um byte
            int k = 0, tc = 0;
            while (acentuadas[k][0] != 0) {
                // se for uma das letras acentuadas, retira-se o acento
                if ((tc = comp_mchar(&acentuadas[k][0], &orig[i])) != 0) {
                    // encontramos uma minúscula acentuada
                    dest[j] = base[k];
                    j++;
                    i = i + tc;
                    break;
                }
                k++;
            }
            if (tc == 0) {
                // não é uma letra acentuada, logo é de copiar para
                //   o destino, sem alterações, todos os carateres UTF-8
                do {
                    dest[j] = orig[i];
                    i++;
                    j++;
                } while ((orig[i] & 0xC0) == 0x80);
            }
        }
        c = (unsigned char) orig[i];
    }
    dest[j] = 0;
}


//Lê nome do ficheiro txt da consola
char* getnome(){
    printf("Indique o nome do ficheiro: \n");
    char *nome = malloc(50);
    scanf("%s", nome);
    return nome;
}


//Limpa o conteudo de uma string
void limpastring(char *token){
    int j = 0;
    while(token[j] != '\0'){
        token[j] = '\0';
        j++;
    }
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


/***********************************************************************/
//Funcoes para o tratamento das listas


//Inicializacao de uma lista
void inicializar_lista(struct lista *pf) {
    pf->raiz = NULL;
}


//Realiza a insercao na lista
bool colocar_lista(struct lista *pf, int num) {
    struct no_fila *aux, *prox, *anterior;
    //Obter espaço para um novo nó
    aux = (struct no_fila *) malloc(sizeof(struct no_fila));
    if (aux == NULL)
        return false;
    aux->num = num;
    aux->pseg = NULL;
    if (pf->raiz == NULL) {
        // fila vazia, é a primeira mensagem
        pf->raiz = aux;
    } else {
        // procurar posição de inserção
        anterior = pf->raiz;
        prox = pf->raiz->pseg;
        while (prox != NULL) {
            anterior = prox;
            prox = prox->pseg;
        }
        anterior->pseg = aux;
    }
    return true;
}


//Funcao da print de todos os elementos de uma lista fornecida
void print_lista(struct lista *pf){
    struct no_fila *anterior;
    if(pf->raiz == NULL)
        return;
    anterior = pf->raiz;
    while(anterior!=NULL){
        printf("%d ", anterior->num);
        anterior = anterior->pseg;
    }
    printf("\n");
}


//Funcao recebe uma lista e uma palavra
//Percorre a lista fornecida chamando a funcao contexto_palavra para cada numero presente
//na lista, de forma a obter o contexto de todas as posicoes da palavra fornecida
void print_opcao1(struct lista *pf, char *nome){
    struct no_fila *anterior;
    if(pf->raiz == NULL)
        return;
    anterior = pf->raiz;
    int count = 0;
    while(anterior!=NULL){
        anterior = anterior->pseg;
        count++;
    }
    int array[count];
    count = 0;
    anterior = pf->raiz;
    while(anterior!=NULL){
        array[count] = anterior->num;
        anterior = anterior->pseg;
        count++;
    }
    for(int i = 0; i<count; i++){
        printf("%dº ocorrencia:\n", count-i);
        contexto_palavra(nome, array[count-i-1]);
    }
}


/***********************************************************************/
//Funcoes para o tratamento da arvore


//Inicializacao da arvore
void inicializar_arvore(struct arvore_binaria * pa) {
    pa->raiz = NULL;
}


//Funcao percorre a arvore de forma a encontrar a posicao correta para colocar
//a nova palavra
struct no *addtree(struct no *pr, struct no *p) {
    int cond;
    char nome1[50],nome2[50];
    if (pr == NULL) {
        pr = p;
    } else {
        strtobase_u8(nome1,p->palavra);
        strtobase_u8(nome2,pr->palavra);
        if ((cond = strcmp(nome1,nome2)) > 0) {
            pr->right = addtree(pr->right, p);
        } else if (cond < 0)
            pr->left = addtree(pr->left, p);
    }
    return pr;
}


//Cria espaco para um novo no, coloca nele os dados fornecidos (palavra, num)
//e chama a funcao addtree para o colocar na arvore
bool colocar_arvore(struct arvore_binaria * pa, char *palavra, int num) {
    struct no *p;
    struct lista list;
    inicializar_lista(&list);
    p = (struct no *) malloc(sizeof(struct no)); // make a new node
    if (p == NULL)
        return false;
    colocar_lista(&list, num);
    p->pf = list;
    strcpy(p->palavra, palavra);
    p->left = p->right = NULL;
    pa->raiz = addtree(pa->raiz, p);
    return true;
}


//Recebe a raiz de uma arvore binaria assim como uma palavra
//Percorre a arvore binaria, verificando se a palavra e igual a presente em algum no da arvore
//Devolve o no caso encontre uma igual e devolve NULL caso nao encontre
struct no *find(struct no *pr, char *pn) {
    int cond;
    if (pr == NULL)
        return NULL;
    char nome1[50],nome2[50];
    strtobase_u8(nome1,pr->palavra);
    strtobase_u8(nome2,pn);
    if ((cond = strcmp(nome1, nome2)) == 0)
        return pr;
    else if (cond > 0)
        return find(pr->left, pn);
    return find(pr->right, pn);
}


//A funcao vai chamar a funcao find para verificar se a palavra que recebe existe na arvore.
//Se a palavra existir e porque so necessitamos de colocar a sua nova ocorrencia na sua lista; e dado return true.
//E entao chamada a funcao colocar_lista que o vai fazer.
//Caso a palavra nao exista e simplesmente dado return false.
bool consultar(struct arvore_binaria * pa, char *nome, int num) {
    struct no *p;
    p = find(pa->raiz, nome);
    if (p == NULL)
        return false;
    colocar_lista(&p->pf, num);
    return true;
}


//A funcao vai ser utilizada quando o utilizador pretende ver todas as ocorrencias da palavra que forneceu no seu contexto
//Vai ser entao verificado a partir da funcao find se a palavra existe na arvore
//Caso exista vai ser chamada a funcao print_opcao1 para obter a informacao pedida
bool consultar_opcao1(struct arvore_binaria * pa, char *nome, char *nome_ficheiro) {
    struct no *p;
    p = find(pa->raiz, nome);
    if (p == NULL){
        printf("Palavra nao existe na arvore\n");
        return false;
    }
    print_opcao1(&p->pf, nome_ficheiro);
    return true;
}


//A funcao vai ser utilizada quando o utilizador pretende ver todas as palavras que contenham a sequencia de letras que forneceu
//Vai percorrer a arvore binaria e verificar se a palavra de cada no contem a sequencia de letras fornecida.
//Caso contenha vai ser chamada a funcao print_lista para obter as ocorrencias dessa mesma palavra.
//Da return 0 se nenhuma palavra corresponder a condicao pedida, e 1 caso exista pelo menos uma
void consultar_opcao2(struct no *raiz, char *nome, bool *flag_opcao2){
    char token[50];
    if (raiz != NULL){
        limpastring(token);
        if(strlen(raiz->palavra)>=strlen(nome)){
            for(int i = 0; i<(int)strlen(nome); i++){
                token[i] = raiz->palavra[i];
            }
            if(strcmp(nome, token)==0){
                printf("%s ", raiz->palavra);
                print_lista(&raiz->pf);
                *flag_opcao2 = true;
            }
        }
        consultar_opcao2(raiz->left, nome, flag_opcao2);
        consultar_opcao2(raiz->right, nome, flag_opcao2);
    }
}


//Funcao auxiliar que mostra da print a toda arvore para realizar verificacoes
void print_arvore(struct no *raiz){
    if (raiz != NULL){
        printf("%s\n", raiz->palavra);
        print_lista(&raiz->pf);
        print_arvore(raiz->left);
        print_arvore(raiz->right);
    }
}


/***********************************************************************/


//Recebe o nome do ficheiro txt assim como a posicao de uma palavra num ficheiro
//A partir da posicao da palavra no ficheiro vai obter o contexto ao qual ela pertence
void contexto_palavra(char* nome, int num){
    FILE *fo = fopen(nome, "r");
    if(fo==NULL){
        fprintf(stderr, "Erro ao abrir o ficheiro de origem\n");
        return;
    }
    fseek(fo, 0, SEEK_END);
    long int length = ftell(fo);
    fseek(fo, 0, SEEK_SET);
    int c, count = 1, count2 = 0;
    char contexto[500];
    for(int j = 0; j<500; j++){
        contexto[j]='\0';
    }
    //coloca o ponteiro do ficheiro na posicao fornecida
    fseek(fo, num, SEEK_SET);
    //anda para tras no ficheiro a partir da posicao dada ate encontrar um "."
    while(fgetc(fo)!=46 && ftell(fo)!=1){
        fseek(fo, num-count, SEEK_SET);
        count++;
    }
    count = 0;
    //verifica se estamos no inicio do ficheiro
    if(ftell(fo)==1){
        fseek(fo, 0, SEEK_SET);
    }
    else{
        fgetc(fo);
    }
    //percorrer o ficheiro ate encontrar dois "." para obter o contexto
    while(count!=2 && ftell(fo)!=length){
        c = fgetc(fo);
        //retirar os "\r\n" do contexto
        if(c==13){
            c = fgetc(fo);
            contexto[count2] = 32;
        }
        else
            contexto[count2] = (char) c;
        count2++;
        if(c==46){
            count++;
        }
    }
    printf("%s\n", contexto);
}


//A funcao vai ser utilizada quando o utilizador pretende ver todas as ocorrencias da palavra que forneceu, no seu contexto
//Vai pedir a palavra ao utilizador e chamar a funcao consultar_opcao1 para obter o seu contexto
void opcao1(struct arvore_binaria * pa, char *nome_ficheiro){
    printf("       Indique a palavra: \n");
    char palavra[50];
    scanf("%s", palavra);
    consultar_opcao1(pa, palavra, nome_ficheiro);
}


//A funcao vai ser utilizada quando o utilizador pretende ver todas as palavras que contenham a sequencia de letras que forneceu
//Vai pedir a letra ou gama de letras ao utilizador e chamar a funcao consultar_opcao2 para obter as suas ocorrencias
void opcao2(struct arvore_binaria *pa){
    printf("       Indique a letra ou gama de letras: \n");
    char palavra[50];
    scanf("%s", palavra);
    bool flag_opcao2=false;
    consultar_opcao2(pa->raiz, palavra, &flag_opcao2);
    if(flag_opcao2==false)
        printf("A sequencia de letras nao corresponde a uma sequencia em nenhuma das palavras\n");
    fflush(stdin);
}


//Esta funcao e responsavel pela por colocar todas as palavras na arvore binaria.
//Vai percorrer o ficheiro que contem uma palavra e a sua posicao no ficheiro original por linha
//e chamar a funcao consultar e colocar_arvore dependendo se e uma palavra nova ou nao
void segunda_fase(struct arvore_binaria *arvore, char *nome){
    char nomeficheiro[50];
    strcpy(nomeficheiro, "idx_");
    strcat(nomeficheiro, nome);
    FILE *fo = fopen(nomeficheiro, "r");
    if(fo==NULL){
        fprintf(stderr, "Erro ao abrir o ficheiro de origem\n");
        return;
    }
    char str[100];
    char palavra[50];
    char *ptr;
    int num;
    while(fgets(str,100,fo)!=NULL){
        strcpy(palavra, strtok(str, ", "));
        num = (int)strtol(strtok(NULL, ", "), &ptr, 10);
        //a funcao colocar_arvore so e chamada se a palavra nao existir na arvore por
        //isso e necessario chamar a funcao consultar para fazer a verificacao
        //caso ja exista na arvore a propria funcao consultar faz a insercao da nova
        //ocorrencia na lista correspondente a palavra
        if(!consultar(arvore, palavra, num)){
            colocar_arvore(arvore, palavra, num);
        }
    }
    fclose(fo);
}

//Apresenta no ecra as opcoes que o utilizador pode tomar
void menu(){
    printf("------------------------------------------------------\n");
    printf("       Indique a operacao que pretende realizar       \n");
    printf("1-Apresentar todas as ocorrencias de uma palavra\n");
    printf("2-Listar todas as palavras\n");
    printf("3-Sair\n");
    printf("------------------------------------------------------\n");
}