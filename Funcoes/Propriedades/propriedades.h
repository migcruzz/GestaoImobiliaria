#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../TiposDados/TiposDados.h"

#ifndef PROGRAMA_PROPRIEDADES_H
#define PROGRAMA_PROPRIEDADES_H

int procuraMaiorID(LISTA_PROPRIEDADE **iniLista);

int criar_propriedade(LISTA_PROPRIEDADE **iniLista, LISTA_PROPRIEDADE **fimLista);

void imprime_todas_propriedades (LISTA_PROPRIEDADE *iniLista);

int editar_propriedade(LISTA_PROPRIEDADE **iniLista);

int remover_propriedade(LISTA_PROPRIEDADE **iniLista);

void limpar_memoria_lista_propriedades(LISTA_PROPRIEDADE **iniLista, LISTA_PROPRIEDADE **fimLista);

void salvar_lista_propriedades_ficheiro_binario(LISTA_PROPRIEDADE *iniLista);

void carregar_lista_do_arquivo(LISTA_PROPRIEDADE **iniLista, LISTA_PROPRIEDADE **fimLista);

#endif //PROGRAMA_PROPRIEDADES_H
