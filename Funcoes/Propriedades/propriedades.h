#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../TiposDados/TiposDados.h"

#ifndef PROGRAMA_PROPRIEDADES_H
#define PROGRAMA_PROPRIEDADES_H

int criar_propriedade(LISTA_PROPRIEDADE **iniLista, LISTA_PROPRIEDADE **fimLista, PROPRIEDADE propriedade_nova);
int editar_propriedade(LISTA_PROPRIEDADE **iniLista, PROPRIEDADE editada);
int remover_propriedade(LISTA_PROPRIEDADE **iniLista,int propriedade_id);
void imprime_todas_propriedades (LISTA_PROPRIEDADE *iniLista);
#endif //PROGRAMA_PROPRIEDADES_H
