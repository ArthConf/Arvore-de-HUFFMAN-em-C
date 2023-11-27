huffman: clean
	@echo
	@echo ==========================
	@echo      TRABALHO huffman 
	@echo ==========================
	@echo Compilando o programa arvore
	@gcc huffmanTeste.c -o huffman
	@echo Tornando o arquivo executável 
	@chmod +x huffman
	@echo Executando o programa huffman 
	@echo ======================================================
	@echo
	@./huffman
arvore: clean
	@echo
	@echo ==========================
	@echo      TRABALHO ARVORE 
	@echo ==========================
	@echo Compilando o programa arvore
	@gcc arvoreCompleto.c arvoreCompleto.h arvoreCompletoteste.c -o arvore
	@echo Tornando o arquivo executável 
	@chmod +x arvore
	@echo Executando o programa arvore 
	@echo ======================================================
	@echo
	@./arvore

clean:
	@echo "===================================================================="
	@echo " Removendo os programas compilados                               "
	@echo "===================================================================="
	@rm -f arvore
	@echo "===================================================================="

help:
	@echo "===================================================================="
	@echo "                                AJUDA                                   "
	@echo "===================================================================="
	@echo "help            | ajuda"
	@echo "ola             | executa mensagem de teste"
	@echo "clean           | apaga códigos compilados"
