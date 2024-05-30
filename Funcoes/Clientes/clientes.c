#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../VariaveisGlobais/variaveis_globais.h"
#include "../../TiposDados/TiposDados.h"


int criar_cliente(LISTA_CLIENTE **iniLista, LISTA_CLIENTE **fimLista, CLIENTE cliente_novo){

    LISTA_CLIENTE *novo = NULL;

    novo = (LISTA_CLIENTE *) calloc(1,sizeof(LISTA_CLIENTE));

    if(novo == NULL){ // se a lista estiver vazia
        printf("Out of memory ! \n");
        return -1;
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

int imprime_todos_clientes (LISTA_CLIENTE *iniLista) {

    int contador =0;

    LISTA_CLIENTE *aux = NULL;

    if (iniLista == NULL) {
        printf("Lista Vazia\n");
        return -1;
    }

    for (aux = iniLista; aux != NULL; aux = aux->seguinte) {
        contador ++;

        printf("------------------------------------------------------------------\n");
        printf("Nome do Cliente: %s\n",aux->cliente.nome);
        printf("NIF do cliente: %s\n",aux -> cliente.NIF);
        printf("Telefone do Cliente: %s\n", aux -> cliente.telefone);
        printf("ID do Cliente: %d\n", aux -> cliente.id_cliente);
        printf("Palavra passe: %s", aux -> cliente.palavra_passe);
        printf("------------------------------------------------------------------\n");
    }
    return 0;
}

int editar_cliente(LISTA_CLIENTE **iniLista, CLIENTE editado) {

    int contador = 0;

    LISTA_CLIENTE *aux = NULL;

    if (iniLista == NULL) {
        printf("Lista Vazia\n");
        return -1;
    }

    for (aux = *iniLista; aux != NULL; aux = aux ->seguinte) {

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
    return 0;
}

// Troca os elementos da lista a para a frente do b

void aux_troca_elementos_lista(LISTA_CLIENTE *a, LISTA_CLIENTE *b, LISTA_CLIENTE **iniLista){

    LISTA_CLIENTE *b_aux = NULL;
    LISTA_CLIENTE *a_aux= NULL;
    LISTA_CLIENTE *bb_aux = NULL;
    LISTA_CLIENTE *aa_aux = NULL;

    LISTA_CLIENTE *bb = NULL;
    LISTA_CLIENTE *aa = NULL;

    // Auxiliares apenas para guardar dados para serem mais trde acedidos, de forma a garantir que não se perde segurança no procedimento de troca de elementos.
    //Podia ser mais rápido de outra forma usando apenas os apontadores importantes mas a segurança é mais importante.

    a_aux = a;
    b_aux = b;
    aa_aux = a -> anterior;
    bb_aux = b -> seguinte;

    // Dados a serem alterados assim como os argumentos a e b da função.
    aa = a -> anterior;
    bb = b -> seguinte;

    if(a -> anterior == NULL){
        a ->seguinte = bb_aux;
        bb -> anterior = a_aux;
        *iniLista = b_aux;
        b -> seguinte = a_aux;
        a-> anterior = b_aux;
    }
    else if(b -> seguinte == NULL){
        aa -> seguinte = b_aux;
        b -> seguinte = a_aux;
        a -> seguinte = NULL;
        a ->anterior  = b_aux;
        b -> anterior = aa_aux;
    }
    else{
        aa -> seguinte = b_aux;
        b -> seguinte = b_aux -> anterior;
        a -> seguinte = bb_aux;
        bb -> anterior = a_aux;
        a -> anterior = b_aux;
        b -> anterior = aa_aux;
    }
}

void ordena_cliente_alfabeto_bubble_sort(LISTA_CLIENTE **iniLista){

    int contador =0;
    int i;
    LISTA_CLIENTE *aux = NULL;

    for (aux = *iniLista; aux != NULL; aux = aux->seguinte) {
        contador ++;
    }


    for(i =0; i < contador; i++){

        for(aux = *iniLista; aux != NULL; aux = aux->seguinte){

            if(strcmp(aux -> cliente.nome, aux -> seguinte ->cliente.nome) > 0){
                aux_troca_elementos_lista(aux, aux ->seguinte, iniLista);
            }
        }
    }
}

int remover_cliente(LISTA_CLIENTE **iniLista,int cliente_id) {

    LISTA_CLIENTE *aux = *iniLista;
    LISTA_CLIENTE *NoSeguinte = NULL;
    LISTA_CLIENTE  *NoAnterior = NULL;
    int contador =0;


    if (aux == NULL) {
        printf("Lista vazia.\n");
        return -1;
    }

    while (aux != NULL) {
        if (aux->cliente.id_cliente == cliente_id) {

            NoSeguinte = aux->seguinte;
            NoAnterior = aux->anterior;

            if (NoAnterior != NULL) {
                NoAnterior->seguinte = NoSeguinte;
            } else {
                *iniLista = NoSeguinte;
            }

            if (NoSeguinte != NULL) {
                NoSeguinte->anterior = NoAnterior;
            }

            free(aux);
            printf("Cliente removido.\n");
            return 0;
        }
        aux = aux->seguinte;
    }

    printf("Cliente com ID %d não encontrado.\n", cliente_id);
    return -1;

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

void ordena_cliente_NIF_bubble_sort(LISTA_CLIENTE **iniLista, LISTA_CLIENTE **fimLista){

    int contador =0;
    int i;
    LISTA_CLIENTE *aux = NULL;

    for (aux = *iniLista; aux != NULL; aux = aux->seguinte) {
        contador ++;
    }

    for(i =0; i < contador; i++){

        for(aux = *iniLista; aux != NULL; aux = aux->seguinte){

            if(strcmp(aux -> cliente.NIF, aux -> seguinte ->cliente.NIF) > 0){
                aux_troca_elementos_lista(aux, aux ->seguinte, iniLista);
            }
        }
    }
}

//// Primeiro executar a função acima na main para facilitar procura.
int apresenta_informacao_dado_NIF(LISTA_CLIENTE **iniLista, char NIF[]){

    CLIENTE cliente_encontrado;

    int contador = 0;

    LISTA_CLIENTE *aux = NULL;

    if (iniLista == NULL) {
        printf("Lista Vazia\n");
        return -1;
    }

    for (aux = *iniLista; aux != NULL; aux = aux ->seguinte) {

        if (strcmp(aux->cliente.NIF , NIF) == 0) {

            strcpy(cliente_encontrado.nome,aux->cliente.nome );
            strcpy(cliente_encontrado.NIF, aux->cliente.NIF);
            strcpy(cliente_encontrado.telefone, aux->cliente.telefone );
            strcpy( cliente_encontrado.palavra_passe, aux->cliente.palavra_passe);
            cliente_encontrado.id_cliente = aux ->cliente.id_cliente;

        }
        return 0;
    }
    return 0;


}

int carregar_do_ficheiro_cliente(CLIENTE **iniLista, CLIENTE **fimLista){

    CLIENTE cliente_lido;
    FILE *ficheiro_cliente = fopen("../Armazenamento/Texto/Agentes_Imobiliarios.txt", "r");
    if (ficheiro_cliente == NULL) {
        printf("\nErro a abrir o ficheiro de clientes !!!!\n");
        return -1;
    }

    while (fscanf(ficheiro_cliente, "%29[^;];%9[^;];%9[^;];%d;%d;%20[^;];",
                  cliente_lido.nome,
                  cliente_lido.NIF,
                  cliente_lido.telefone,
                  &cliente_lido.id_cliente,
                  &cliente_lido.role,
                  cliente_lido.palavra_passe) == 6)
    {
        criar_cliente((LISTA_CLIENTE **) iniLista, (LISTA_CLIENTE **) fimLista, cliente_lido);
    }

    fclose(ficheiro_cliente);

    return 0;
}

