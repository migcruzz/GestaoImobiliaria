#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../TiposDados/TiposDados.h"

#ifndef PROGRAMA_PROPRIEDADES_H
#define PROGRAMA_PROPRIEDADES_H

int procuraMaiorID_ou_ID_Disponivel(LISTA_PROPRIEDADE **iniLista);

int criar_propriedade(LISTA_PROPRIEDADE **iniLista, LISTA_PROPRIEDADE **fimLista, AGENTE agente_imobiliario[]);

void imprime_todas_propriedades (LISTA_PROPRIEDADE *iniLista);

void imprime_todas_propriedades_nao_populares(LISTA_PROPRIEDADE *iniLista);

void imprime_todas_propriedades_populares(LISTA_PROPRIEDADE *iniLista);

int editar_propriedade(LISTA_PROPRIEDADE **iniLista, AGENTE agente_imobiliario[]);

int remover_propriedade(LISTA_PROPRIEDADE **iniLista);

void limpar_memoria_lista_propriedades(LISTA_PROPRIEDADE **iniLista, LISTA_PROPRIEDADE **fimLista);

void salvar_lista_propriedades_ficheiro_binario(LISTA_PROPRIEDADE *iniLista);

void carregar_lista_do_arquivo_binario(LISTA_PROPRIEDADE **iniLista, LISTA_PROPRIEDADE **fimLista);

void imprime_todas_propriedades_populares_negocio_por_concluir(LISTA_PROPRIEDADE *iniLista);

void imprime_todas_propriedades_nao_populares_negocio_por_concluir(LISTA_PROPRIEDADE *iniLista);

/*
void salvar_lista_propriedades_ficheiro_texto(LISTA_PROPRIEDADE *iniLista);

void carregar_lista_do_arquivo_texto(LISTA_PROPRIEDADE **iniLista, LISTA_PROPRIEDADE **fimLista);

 */
#endif //PROGRAMA_PROPRIEDADES_H
