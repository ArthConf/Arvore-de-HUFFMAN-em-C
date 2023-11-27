#include "arvoreCompleto.h"

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
    printf("\nQuantidade: %d\n", tam);

    texto = calloc(tam + 2, sizeof(unsigned char));
    ler_texto(texto);
    //printf("\nTEXTO:\n%s\n", texto);


    //----------- parte 1: tabela de frequência ---------------
    inicializa_tabela_com_zero(tabela_frequencia);
    preenche_tab_frequencia(texto, tabela_frequencia);
    //imprime_tab_frequencia(tabela_frequencia);

    //----------- parte 2: Lista Encadeada Ordenada -----------
    criar_lista(&lista);
    preencher_lista(tabela_frequencia, &lista);
    //imprimir_lista(&lista);

    //----------- parte 3: Montar a Árvore de Huffman ---------
    arvore = montar_arvore(&lista);
    printf("\n\tArvore de Huffam\n");
    //imprimir_arvore(arvore, 0);

    //----------- parte 4: Montar o dicionário ----------------
    colunas = altura_arvore(arvore) + 1;
    dicionario = aloca_dicionario(colunas);
    gerar_dicionario(dicionario, arvore, "", colunas);
    //imprime_dicionario(dicionario);

    //----------- parte 5: Codificar ---------------------------
    codificado = codificar(dicionario, texto);
    //printf("\n\tTexto codificado: %s\n", codificado);

    //----------- parte 6: Decodificar -------------------------
    decodificado = decodificar(codificado, arvore);
    //printf("\n\tTexto decodificado: %s\n", decodificado);

    //----------- parte 7: Compactar ----------------------------
    compactar(codificado);

    //----------- parte 8: Descompactar ----------------------------
    printf("\nARQUIVO DESCOMPACTADO!\n");
    descompactar(arvore);
    printf("\n\n");

    free(texto);
    free(codificado);
    free(decodificado);

    return 0;
}