#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define TAM 256

typedef struct no{
    unsigned char caracter;
    int frequencia;
    struct no *esq, *dir, *proximo;
}No;

typedef struct{
    No *inicio;
    int tam;
}Lista;

void inicializa_tabela_com_zero(unsigned int tab[]);

void preenche_tab_frequencia(unsigned char texto[], unsigned int tab[]);

void imprime_tab_frequencia(unsigned int tab[]);

//----------- parte 2: Lista Encadeada Ordenada ----------------------

void criar_lista(Lista *lista);

void inserir_ordenado(Lista *lista, No *no);

void preencher_lista(unsigned int tab[], Lista *lista);

void imprimir_lista(Lista *lista);
    
No* remove_no_inicio(Lista *lista);

No* montar_arvore(Lista *lista);

void imprimir_arvore(No *raiz, int tam);

//-------------- parte 4: Montar o dicionario ---------------------

int altura_arvore(No *raiz);

char** aloca_dicionario(int colunas);

void gerar_dicionario(char **dicionario, No *raiz, char *caminho, int colunas);

void imprime_dicionario(char **dicionario);

//-------------- parte 5: Codificar ----------------------------

int calcula_tamanho_string(char **dicionoario, unsigned char *texto);

char* codificar(char **dicionario, unsigned char *texto);

//-------------- parte 6: Decodificar --------------------------
char* decodificar(unsigned char texto[], No *raiz);

//-------------- parte 7: Compactar --------------------------
void compactar(unsigned char str[]);
//-------------- parte 8: Descompactar ------------------------
unsigned int eh_bit_um(unsigned char byte, int i);

void descompactar(No *raiz);
// função para descobrir o tamanho de um texto em arquivo texto (quantidade de caracteres)
int descobrir_tamanho();

// função para ler um texto de um arquivo texto
void ler_texto(unsigned char *texto);