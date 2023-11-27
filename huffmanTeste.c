#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>

#define TAM 256
  // Configuração da localização para Português (Portugal) em UTF-8



typedef struct no{
    unsigned char caracter;
    int frequencia;
    struct no *esq, *dir, *proximo;
}No;

typedef struct{
    No *inicio;
    int tam;
}Lista;

//----------- parte 1: tabela de frequencia ----------------------
void inicializa_tabela_com_zero(unsigned int tab[]){
    int i;
    for(i = 0; i < TAM; i++)
        tab[i] = 0;
}

void preenche_tab_frequencia(unsigned char texto[], unsigned int tab[]){
    int i = 0;

    while(texto[i] != '\0'){
        tab[texto[i]]++;
        i++;
    }
}

void imprime_tab_frequencia(unsigned int tab[]){
    int i;


    printf("\nTABELA DE FREQUENCIA\n");
    for(i = 0; i < TAM; i++){
        if(tab[i] > 0)
            printf("\t%d = %u = %c\n", i, tab[i], i);
    }
}

//----------- parte 2: Lista Encadeada Ordenada ----------------------

void criar_lista(Lista *lista){
    lista->inicio = NULL;
    lista->tam = 0;
}

void inserir_ordenado(Lista *lista, No *no){
    No *aux;
    // a lista esta vazia?
    if(lista->inicio == NULL){
        lista->inicio = no;
        //lista->tam++;
    }
    // tem frequencia menor que o inicio da lista
    else if(no->frequencia < lista->inicio->frequencia){
        no->proximo = lista->inicio;
        lista->inicio = no;
        //lista->tam++;
    }
    else{
        aux = lista->inicio;
        while(aux->proximo && aux->proximo->frequencia <= no->frequencia)
            aux = aux->proximo;
        no->proximo = aux->proximo;
        aux->proximo = no;
        //lista->tam++;
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
                printf("\tERRO ao alocar memoria em preencher_lista!\n");
                break;
            }
        }
    }
}

void imprimir_lista(Lista *lista){
    No *aux = lista->inicio;

    printf("\nLISTA ORDENADA: TAMANHO: %d\n", lista->tam);
    while(aux){
        printf("\tCaracter: %c Frequencia: %d\n", aux->caracter, aux->frequencia);
        aux = aux->proximo;
    }
}

//------------- parte 3: Montar a Arvore de Huffman ----------------------

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

//-------------- parte 4: Montar o dicionario ---------------------

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

void imprime_dicionario(char **dicionario){
    int i;

    printf("\nDICIONARIO:\n");
    for(i = 0; i < TAM; i++){
        if(strlen(dicionario[i]) > 0)
            printf("\t%3d: %s\n", i, dicionario[i]);
    }
}

//-------------- parte 5: Codificar ----------------------------

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

//-------------- parte 6: Decodificar --------------------------
char* decodificar(unsigned char texto[], No *raiz){
    int i = 0;
    No *aux = raiz;
    char temp[2];
    char *decodificado = calloc(strlen(texto), sizeof(char));

    while(texto[i] != '\0'){
        if(texto[i] == '0')
            aux = aux->esq;
        else
            aux = aux->dir;

        if(aux->esq == NULL && aux->dir == NULL){
            temp[0] = aux->caracter;
            temp[1] = '\0';
            strcat(decodificado, temp);
            aux = raiz;
        }

        i++;
    }
    return decodificado;
}

//-------------- parte 7: Compactar --------------------------
void compactar(unsigned char str[]){
    FILE *arquivo = fopen("compactado.wg", "wb");
    int i = 0, j = 7;
    unsigned char mascara, byte = 0; // 00000000

    if(arquivo){
        while(str[i] != '\0'){
            mascara = 1;
            if(str[i] == '1'){
                mascara = mascara << j;
                byte = byte | mascara;
            }
            j--;

            if(j < 0){ // tem um byte formado
                fwrite(&byte, sizeof(unsigned char), 1, arquivo);
                byte = 0;
                j = 7;
            }

            i++;
        }
        if(j != 7) //11010000
            fwrite(&byte, sizeof(unsigned char), 1, arquivo);
        fclose(arquivo);
    }
    else
        printf("\nErro ao abrir/criar arquivo em compactar\n");
}

//-------------- parte 8: Descompactar ------------------------
unsigned int eh_bit_um(unsigned char byte, int i){
    unsigned char mascara = (1 << i);
    return byte & mascara;
}

void descompactar(No *raiz){
    FILE *arquivo = fopen("compactado.wg", "rb");
    No *aux = raiz;
    unsigned char byte; // 10111001
    int i;

    if(arquivo){
        while(fread(&byte, sizeof(unsigned char), 1, arquivo)){
            for(i = 7; i >= 0; i--){
                if(eh_bit_um(byte, i))
                    aux = aux->dir;
                else
                    aux = aux->esq;

                if(aux->esq == NULL && aux->dir == NULL){
                    printf("%c", aux->caracter);
                    
                    aux = raiz;
                }
            }
        }
        fclose(arquivo);
    }
    else
        printf("\nErro ao abrir arquivo em descompactar\n");
}

// função para descobrir o tamanho de um texto em arquivo texto (quantidade de caracteres)
int descobrir_tamanho(){
    FILE *arq = fopen("teste.txt", "r");
    int tam = 0;

    if(arq){
        while(fgetc(arq) != -1)
            tam++;
        fclose(arq);
    }
    else
        printf("\nErro ao abri arquivo em descobrir_tamanho\n");
    return tam;
}

// função para ler um texto de um arquivo texto
void ler_texto(unsigned char *texto) {
    FILE *arq = fopen("teste.txt", "r");
    unsigned char letra;
    int i = 0;

    if (arq) {
        while (!feof(arq)) {
            letra = fgetc(arq);
            if (letra != -1) {
                // printf("\t%d: %c\n", letra, letra);
                texto[i] = letra;
                i++;
            }
        }
        fclose(arq);
    } else {
        printf("\nErro ao abrir arquivo em ler_texto\n");
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

// Função para converter um número para uma string binária
void intToBinaryString(int num, char *binaryString) {
    int i, j;

    for (i = 7; i >= 0; --i) {
        j = 1 << i;
        binaryString[7 - i] = (num & j) ? '1' : '0';
    }

    binaryString[8] = '\0'; // Adiciona o terminador nulo
}

// Função para imprimir a tabela comparativa
void imprimirTabelaComparativa(char **dicionario) {
    printf("\n+--------------+-----------------------+--------------------------+");
    printf("\n| Caractere    | Binario ASCII        | Binario Huffman          |");
    printf("\n+--------------+-----------------------+--------------------------+");

    for (int i = 0; i < TAM; i++) {
        if (strlen(dicionario[i]) > 0) {
            printf("\n|    %c         | ", i);
            
            // Binário ASCII
            char binarioASCII[9]; // 8 bits + terminador nulo
            intToBinaryString(i, binarioASCII);
            printf("%s         | ", binarioASCII);

            // Binário Huffman
            printf("    %s                |", dicionario[i]);
        }
    }

    printf("\n+--------------+-----------------------+--------------------------+\n");
}

int main() {
    
    //unsigned char texto[] = "Vamos aprender programação";
    unsigned char *texto;
    unsigned int tabela_frequencia[TAM];
    Lista lista;
    No *arvore;
    int colunas, tam;
    char **dicionario;
    char *codificado, *decodificado;

    tam = descobrir_tamanho();
    printf("\nQUANTIDADE: %d\n", tam);

    texto = calloc(tam + 2, sizeof(unsigned char));
    ler_texto(texto);
    //printf("\nTEXTO:\n%s\n", texto);


    //----------- parte 1: tabela de frequência ---------------
    inicializa_tabela_com_zero(tabela_frequencia);
    preenche_tab_frequencia(texto, tabela_frequencia);
    imprime_tab_frequencia(tabela_frequencia);

    //----------- parte 2: Lista Encadeada Ordenada -----------
    criar_lista(&lista);
    preencher_lista(tabela_frequencia, &lista);
    imprimir_lista(&lista);

    //----------- parte 3: Montar a Árvore de Huffman ---------
    arvore = montar_arvore(&lista);
    printf("\nARVORE DE HUFFMAN\n");
    imprimir_arvore(arvore, 0);

    //----------- parte 4: Montar o dicionário ----------------
    colunas = altura_arvore(arvore) + 1;
    dicionario = aloca_dicionario(colunas);
    gerar_dicionario(dicionario, arvore, "", colunas);
    imprime_dicionario(dicionario);

    //----------- parte 5: Codificar ---------------------------
    codificado = codificar(dicionario, texto);
    printf("\nTEXTO CODIFICADO: %s\n", codificado);

    //----------- parte 6: Decodificar -------------------------
    decodificado = decodificar(codificado, arvore);
    printf("\nTEXTO DECODIFICADO: %s\n", decodificado);

    //----------- parte 7: Compactar ----------------------------
    compactar(codificado);

    //----------- parte 8: Descompactar ----------------------------
    printf("\nARQUIVO DESCOMPACTADO!\n");
    descompactar(arvore);
    printf("\n\n");

    // Imprimir a tabela comparativa
    imprimirTabelaComparativa(dicionario);

    // Liberação de memória
    free(texto);
    free(codificado);
    free(decodificado);
    liberar_lista(arvore);
    liberar_dicionario(dicionario, colunas);

    return 0;
}