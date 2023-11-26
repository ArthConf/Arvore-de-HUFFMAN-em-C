arvore: clean
	@echo
	@echo ==========================
	@echo      TRABALHO ARVORE 
	@echo ==========================
	@echo Compilando o programa arvore
	@gcc  arvoreCompleto.c arvoreCompleto.h arvoreCompletoteste.h -o arvore
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
    @rm -f ola
    @echo "===================================================================="
help:
    @echo "===================================================================="
    @echo "                                AJUDA                                   "
    @echo "===================================================================="
    @echo "help            | ajuda"
    @echo "ola            | executa mensagem de teste"
    @echo "clean        | apaga códigos compilados"
