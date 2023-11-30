/*  IFMT - CAMPUS CUIABÁ - CEL. OCTAYDE JORGE DA SILVA
    CUIABÁ, 22 DE NOVEMBRO DE 2023
    PROFº JOÃO PAULO PRETI
    DISCIPLINA: ESTRUTURA DE DADOS II
    CURSO E PERIODO: ENGENHARIA DA COMPUTAÇÃO - 4º SEMESTRE
    ALUNOS: ARTHUR OCTÁVIO OLIVEIRA CONFESSOR E NICOLAS FALCÃO HEEMANN
*/

//OBS: Este código funciona melhor quando o arquivo lido .txt não contém carácteres com acentos e o 'ç'
#include "huffman.c"

int main(int argc, char *argv[]) {
    int resp;
    arquivo = argv[1];
    printf("Olá usuário, seja bem vindo ao software COMPACTHANOS :D\n\n");
    printf("Você deseja compactar o seu arquivo txt?\n\n1-> Sim\n2-> Nao\n\nDigite: ");
    scanf(" %d",&resp);
    if(resp == 1){
        system("clear");
        unsigned char *texto;
        unsigned int tabela_frequencia[TAM];
        Lista lista;
        No *arvore;
        int colunas, tam;
        char **dicionario;
        char *codificado, *decodificado;

        FILE *arq = fopen(argv[1], "r");

        tam = descobrir_tamanho(); 
        printf("QUANTIDADE DE CARACTERES: %d\n", tam); //QUANTIDADE DE CARACTER 
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        texto = calloc(tam + 2, sizeof(unsigned char));
        ler_texto(texto);
        inicializaTabela(tabela_frequencia);
        preencherTabelaFrequencia(texto, tabela_frequencia);
    //Lista Encadeada Ordenada
        criar_lista(&lista);
        preencher_lista(tabela_frequencia, &lista);
        
        imprimir_lista(&lista);

    //Árvore de Huffman 
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        arvore = montar_arvore(&lista);
        printf("ARVORE DE HUFFMAN\n");
        imprimir_arvore(arvore, 0);

        colunas = altura_arvore(arvore) + 1;
        dicionario = aloca_dicionario(colunas);
        gerar_dicionario(dicionario, arvore, "", colunas);

    //CODIFICAÇÃO E IMPRESSÃO DE ARQUIVO
        codificado = codificar(dicionario, texto);
        imprimir_em_arquivo("compactado.txt", codificado); //IMPRIME UM ARQUIVO COMPACTADO DO ARQUIVO 
    //COMPACTAÇÃO
        compactar(codificado);

    //TABELA COMPARATIVA ENTRE ASCII E HUFFMAN
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        imprimirTabelaComparativa(dicionario);
    //Para fazer comparação de tamanho, transformei o arquivo teste.txt em binário, seguindo a tabela ASCII
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

    // Convertendo teste.txt para um arquivo binário teste.bin
    if (ler_converter_escrever_binario(argv[1], "teste.bin") == 0) {
        printf("O arquivo %s foi transformado em binário com sucesso!\n",argv[1]);
    }
    //COMPARAÇÃO DE TAMANHOS ENTRE OS ARQUIVOS BINÁRIO ORIGINAL E COMPACTADO PÓS HUFFMAN
    comparar_tamanhos(arquivo, "compactado.bin");
    //DECODIFICANDO O ARQUIVO COMPACTADO.BIN E IMPRIMINDO O QUE ESTA ESCRITO EM BINÁRIO
    decodificar_arquivo("compactado.bin", arvore);
    //LIBERAR MEMÓRIA
        free(texto);
        free(codificado);
        liberar_lista(arvore);
        liberar_dicionario(dicionario, colunas);
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        
        printf("\nObrigado por usar COMPACTHANOS!! :D\n\n");
        return 0;
    } else {
        system("clear");
        printf("Obrigado por acessar o COMPACTHANOS, o melhor software de compactação de Cuiaba\n");
    }
}