#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../TiposDados/TiposDados.h"

#ifndef PROGRAMA_CLIENTES_H
#define PROGRAMA_CLIENTES_H


int criar_cliente(CLIENTE clientes[]);
void inserir_clientes_em_arquivo(CLIENTE clientes[]);
void carregar_clientes_do_arquivo(CLIENTE clientes[]);
void editar_cliente(CLIENTE clientes[]);
int listar_cliente_alfabeto(CLIENTE clientes[]);
int listar_cliente_nif(CLIENTE clientes[]);
int remover_cliente(CLIENTE clientes[], int id_procura);
void editar_cliente_logado(CLIENTE clientes[], int id_cliente_logado);

#endif //PROGRAMA_CLIENTES_H