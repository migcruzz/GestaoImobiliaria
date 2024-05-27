#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../TiposDados/TiposDados.h"


int criar_cliente(LISTA_CLIENTE **iniLista, LISTA_CLIENTE **fimLista, CLIENTE cliente_novo){

    LISTA_CLIENTE *novo = NULL;

    novo = (LISTA_CLIENTE *) calloc(1,sizeof(LISTA_CLIENTE));

    if(novo == NULL){ // se a lista estiver vazia
        printf("Out of memory ! \n");
    }

    novo -> cliente = cliente_novo;

    novo -> seguinte = NULL;
    novo -> anterior = NULL;

    if(*iniLista == NULL){

        *iniLista = novo;
        *fimLista = novo;

    }else{
        novo -> seguinte = *iniLista;
        (*iniLista) -> anterior = novo;
        (*iniLista) = novo;
    }

    return 0;
}

void imprime_todos_clientes (LISTA_CLIENTE *iniLista) {

    int contador =0;
    char verdade [] = "verdade";
    char falso [] = "falso";

    LISTA_CLIENTE *aux = NULL;

    if (iniLista == NULL) {
        printf("Lista Vazia\n");
    }

    for (aux = iniLista; aux != NULL; aux = aux->seguinte) {
        contador ++;

        printf("------------------------------------------------------------------");
        printf("Nome do Cliente: %s\n",aux->cliente.nome);
        printf("NIF do cliente: %s\n",aux -> cliente.NIF);
        printf("Telefone do Cliente: %s\n", aux -> cliente.telefone);
        printf("ID do Cliente: %d\n", aux -> cliente.id_cliente);
        printf("Palavra passe: %s", aux -> cliente.palavra_passe);
        printf("------------------------------------------------------------------");
    }
}


int editar_cliente(LISTA_CLIENTE **iniLista, CLIENTE editado) {

    int contador = 0;
    char verdade[] = "verdade";
    char falso[] = "falso";

    LISTA_CLIENTE *aux = NULL;

    if (iniLista == NULL) {
        printf("Lista Vazia\n");
        return -1;
    }

    for (aux = *iniLista; aux != NULL; aux = aux->seguinte) {

        if (aux->cliente.id_cliente == editado.id_cliente) {

            strcpy(aux->cliente.nome, editado.nome);
            strcpy(aux->cliente.NIF, editado.NIF);
            strcpy(aux->cliente.telefone, editado.telefone);
            strcpy(aux->cliente.palavra_passe, editado.palavra_passe);

            printf("Utilizador alterado ficou com o seguintes dados:\n");

            printf("------------------------------------------------------------------\n");
            printf("Nome do Cliente: %s\n", aux->cliente.nome);
            printf("NIF do cliente: %s\n", aux->cliente.NIF);
            printf("Telefone do Cliente: %s\n", aux->cliente.telefone);
            printf("ID do Cliente: %d\n", aux->cliente.id_cliente);
            printf("Palavra passe: %s", aux->cliente.palavra_passe);
            printf("------------------------------------------------------------------\n");

        }
        return 0;
    }
}


int remover_cliente(LISTA_CLIENTE *iniLista,int cliente_id) {

    LISTA_CLIENTE *aux = NULL;
    LISTA_CLIENTE *NoSeguinte = NULL;
    LISTA_CLIENTE  *NoAnterior = NULL;
    int contador =0;


    if(iniLista == NULL){
        printf("Lista vazia\n");
        return 0;
    }

    for(aux = iniLista; aux != NULL; aux = aux->seguinte){

        if(aux ->cliente.id_propriedade == propriedade_id){
            contador ++;

            NoSeguinte = aux -> seguinte;
            NoAnterior = aux -> anterior;

            NoAnterior ->seguinte = aux -> seguinte;
            NoSeguinte ->anterior = aux -> anterior;

            free(aux);

            printf("\nPropriedade apagada !\n");
            break;
        }

        if(contador == 0){
            printf("\nPropriedade nao encontrada !\n");
            return -1;
        }
    }

    return 0;
}

void limpar_memoria_lista_clientes(LISTA_CLIENTE **iniLista, LISTA_CLIENTE **fimLista) {

    LISTA_CLIENTE *aux = NULL;
    LISTA_CLIENTE *proximo = NULL;

    aux = *iniLista;

    *iniLista = NULL;
    *fimLista = NULL;

    while(aux != NULL){
        proximo = aux -> seguinte;

        free(aux);

        aux = proximo;
    }
}
