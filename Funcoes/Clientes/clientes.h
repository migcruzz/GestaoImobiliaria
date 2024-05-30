#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../TiposDados/TiposDados.h"

#ifndef PROGRAMA_CLIENTES_H
#define PROGRAMA_CLIENTES_H


int criar_cliente(LISTA_CLIENTE **iniLista, LISTA_CLIENTE **fimLista, CLIENTE cliente_novo);

int imprime_todos_clientes (LISTA_CLIENTE *iniLista);

int editar_cliente(LISTA_CLIENTE **iniLista, CLIENTE editado);
// Troca os elementos da lista a para a frente do b

void aux_troca_elementos_lista(LISTA_CLIENTE *a, LISTA_CLIENTE *b, LISTA_CLIENTE **iniLista);

void ordena_cliente_alfabeto_bubble_sort(LISTA_CLIENTE **iniLista);

int remover_cliente(LISTA_CLIENTE **iniLista,int cliente_id);

void limpar_memoria_lista_clientes(LISTA_CLIENTE **iniLista, LISTA_CLIENTE **fimLista);

void ordena_cliente_NIF_bubble_sort(LISTA_CLIENTE **iniLista, LISTA_CLIENTE **fimLista);

//// Primeiro executar a função acima na main para facilitar procura.
int apresenta_informacao_dado_NIF(LISTA_CLIENTE **iniLista, char NIF[]);

int carregar_do_ficheiro_cliente(CLIENTE **iniLista, CLIENTE **fimLista);

#endif //PROGRAMA_CLIENTES_H
