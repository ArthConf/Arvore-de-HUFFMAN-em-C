#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

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

void inicializaTabela(unsigned int tab[]);
void preencherTabelaFrequencia(unsigned char texto[], unsigned int tab[]);
void criar_lista(Lista *lista);
void inserir_ordenado(Lista *lista, No *no);
void preencher_lista(unsigned int tab[], Lista *lista);
void imprimir_lista(Lista *lista);
No* remove_no_inicio(Lista *lista);
No* montar_arvore(Lista *lista);
void imprimir_arvore(No *raiz, int tam);
int altura_arvore(No *raiz);
char** aloca_dicionario(int colunas);
void gerar_dicionario(char **dicionario, No *raiz, char *caminho, int colunas);
int calcula_tamanho_string(char **dicionoario, unsigned char *texto);
char* codificar(char **dicionario, unsigned char *texto);
void compactar(unsigned char str[]);
unsigned int eh_bit_um(unsigned char byte, int i);
int descobrir_tamanho();
void ler_texto(unsigned char *texto);
void liberar_lista(No *raiz);
void liberar_dicionario(char **dicionario, int colunas);
void intToBinaryString(int num, char *binaryString) ;
void imprimirTabelaComparativa(char **dicionario);
void imprimir_em_arquivo(const char *nome_arquivo, const char *conteudo);
