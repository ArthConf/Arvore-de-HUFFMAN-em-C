#include "huffman.h"

//FREQUÊNCIA
void inicializaTabela(unsigned int tab[]){
    int i;
    for(i = 0; i < TAM; i++)
        tab[i] = 0;
}

void preencherTabelaFrequencia(unsigned char texto[], unsigned int tab[]){
    int i = 0;

    while(texto[i] != '\0'){
        tab[texto[i]]++;
        i++;
    }
}

//LISTA ENCADEADA ORDENADA
void criar_lista(Lista *lista){
    lista->inicio = NULL;
    lista->tam = 0;
}

void inserir_ordenado(Lista *lista, No *no){
    No *aux;
    if(lista->inicio == NULL){
        lista->inicio = no;
    }
    else if(no->frequencia < lista->inicio->frequencia){
        no->proximo = lista->inicio;
        lista->inicio = no;
    }
    else{
        aux = lista->inicio;
        while(aux->proximo && aux->proximo->frequencia <= no->frequencia)
            aux = aux->proximo;
        no->proximo = aux->proximo;
        aux->proximo = no;
    }
    lista->tam++;
}

void preencher_lista(unsigned int tab[], Lista *lista){
    int i;
    No *novo;
    for(i = 0; i < TAM; i++){
        if(tab[i] > 0){
            novo = malloc(sizeof(No));
            if(novo){
                novo->caracter = i;
                novo->frequencia = tab[i];
                novo->dir = NULL;
                novo->esq = NULL;
                novo->proximo = NULL;

                inserir_ordenado(lista, novo);
            }
            else{
                printf("\tERRO AO ALOCAR MEMORIA\n");
                break;
            }
        }
    }
}

//IMPRIME A LISTA ENCADEADA ORDENADA, E O SEU TAMANHO. OU SEJA, O TAMANHO DO CONTEUDO NO ARQUIVO E IMPRIME
//CADA CARACTER E A SUA FREQUÊNCIA AO LONGO DO TEXTO.
void imprimir_lista(Lista *lista){
    No *aux = lista->inicio;

    printf("\nLISTA ORDENADA: TAMANHO: %d\n", lista->tam);
    while(aux){
        printf("\tCaracter: %c Frequencia: %d\n", aux->caracter, aux->frequencia);
        aux = aux->proximo;
    }
}

//ÁRVORE DE HUFFMAN
No* remove_no_inicio(Lista *lista){
    No *aux = NULL;

    if(lista->inicio){
        aux = lista->inicio;
        lista->inicio = aux->proximo;
        aux->proximo = NULL;
        lista->tam--;
    }

    return aux;
}

No* montar_arvore(Lista *lista){
    No *primeiro, *segundo, *novo;
    while(lista->tam > 1){
        primeiro = remove_no_inicio(lista);
        segundo = remove_no_inicio(lista);
        novo = malloc(sizeof(No));

        if(novo){
            novo->caracter = '+';
            novo->frequencia = primeiro->frequencia + segundo->frequencia;
            novo->esq = primeiro;
            novo->dir = segundo;
            novo->proximo = NULL;

            inserir_ordenado(lista, novo);
        }
        else{
            printf("\n\tERRO ao alocar memoria em montar_arvore!\n");
            break;
        }
    }
    return lista->inicio;
}

void imprimir_arvore(No *raiz, int tam){
    if(raiz->esq == NULL && raiz->dir == NULL)
        printf("\tFolha: %c\tAltura: %d\n", raiz->caracter, tam);
    else{
        imprimir_arvore(raiz->esq, tam + 1);
        imprimir_arvore(raiz->dir, tam + 1);
    }
}

//DICIONARIO: COMPARAR O CARACTER E SEU EQUIVALENTE BINARIO OU ATÉ MESMO COMPARAR COM BINÁRIO HUFFMAN
int altura_arvore(No *raiz){
    int esq, dir;

    if(raiz == NULL)
        return -1;
    else{
        esq = altura_arvore(raiz->esq) + 1;
        dir = altura_arvore(raiz->dir) + 1;

        if(esq > dir)
            return esq;
        else
            return dir;
    }
}

char** aloca_dicionario(int colunas){
    char **dicionario;
    int i;

    dicionario = malloc(sizeof(char*) * TAM);

    for(i = 0; i < TAM; i++)
        dicionario[i] = calloc(colunas, sizeof(char));

    return dicionario;
}

void gerar_dicionario(char **dicionario, No *raiz, char *caminho, int colunas){
    char esquerda[colunas], direita[colunas];

    if(raiz->esq == NULL && raiz->dir == NULL)
        strcpy(dicionario[raiz->caracter], caminho);
    else{
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);

        strcat(esquerda, "0");
        strcat(direita, "1");

        gerar_dicionario(dicionario, raiz->esq, esquerda, colunas);
        gerar_dicionario(dicionario, raiz->dir, direita, colunas);
    }
}

//CODIFICAÇÃO
int calcula_tamanho_string(char **dicionoario, unsigned char *texto){
    int i = 0, tam = 0;
    while(texto[i] != '\0'){
        tam = tam + strlen(dicionoario[texto[i]]);
        i++;
    }
    return tam + 1;
}

char* codificar(char **dicionario, unsigned char *texto){

    int i = 0, tam = calcula_tamanho_string(dicionario, texto);
    char *codigo = calloc(tam, sizeof(char));

    while(texto[i] != '\0'){
        strcat(codigo, dicionario[texto[i]]);
        i++;
    }
    return codigo;
}

//COMPACTAÇÃO
void compactar(unsigned char str[]){
    int i = 0, j = 7;
    unsigned char mascara, byte = 0; 
}

//CONTAR O TAMANHO DO TEXTO NO ARQUIVO
int descobrir_tamanho(){
    FILE *arq = fopen("teste.txt", "r");
    int tam = 0;

    if(arq){
        while(fgetc(arq) != -1)
            tam++;
        fclose(arq);
    }
    else
        printf("\nERRO AO ABRIR ARQUIVO!!!\n");
    return tam;
}

//LEITURA DE ARQUIVO
void ler_texto(unsigned char *texto) {
    FILE *arq = fopen("teste.txt", "r"); // Aqui deve colocar o arquivo que deseja compactar
    unsigned char letra;
    int i = 0;

    if (arq) {
        while (!feof(arq)) {
            letra = fgetc(arq);
            if (letra != -1) {
                texto[i] = letra;
                i++;
            }
        }
        
        // Essa função remove o último caracter, já que ele é um bug. Foi feito para evitar contagem de caracteres inexistentes.
        if (i > 0) {
            texto[i - 1] = '\0';
        }

        fclose(arq);
    } else {
        printf("\nERRO AO ABRIR ARQUIVO!!!\n");
    }
}


void liberar_lista(No *raiz) {
    if (raiz) {
        liberar_lista(raiz->esq);
        liberar_lista(raiz->dir);
        free(raiz);
    }
}

void liberar_dicionario(char **dicionario, int colunas) {
    for (int i = 0; i < TAM; i++) {
        free(dicionario[i]);
    }
    free(dicionario);
}

//CONVERTER DECIMAL PARA BINÁRIO
void intToBinaryString(int num, char *binaryString) {
    int i, j;

    for (i = 7; i >= 0; --i) {
        j = 1 << i;
        binaryString[7 - i] = (num & j) ? '1' : '0';
    }

    binaryString[8] = '\0'; // Adiciona o terminador nulo
}

void imprimirTabelaComparativa(char **dicionario) {
    printf("\n-------------------------------------------------------------------");
    printf("\n| Caractere    | Binario ASCII        | Binario Huffman          |");
    printf("\n-------------------------------------------------------------------");

    for (int i = 0; i < TAM; i++) {
        if (strlen(dicionario[i]) > 0 && strchr(dicionario[i], '+') == NULL) {
            printf("\n|    %c         | ", i);
            
            // Binário ASCII
            char binarioASCII[9]; // 8 bits + terminador nulo
            intToBinaryString(i, binarioASCII);
            printf("%s         | ", binarioASCII);

            // Binário Huffman
            printf("    %s                |", dicionario[i]);
        }
    }

    printf("\n-------------------------------------------------------------------\n");
}

// Função para imprimir o conteúdo codificado em um arquivo .txt
void imprimir_em_arquivo(const char *nome_arquivo, const char *conteudo) {
    FILE *arquivo = fopen("compactado.txt", "w");//Nome do Arquivo que será criado, cujo conteúdo sera de valor binário
    
    if (arquivo) {
        fprintf(arquivo, "%s", conteudo);
        fclose(arquivo);
        printf("\nO CONTEÚDO CODIFICADO FOI IMPRESSO NO ARQUIVO %s\n", "compactado.txt");
    } else {
        printf("\nERRO AO ABRIR ARQUIVO!!!\n");
    }
}

