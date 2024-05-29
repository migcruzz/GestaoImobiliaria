#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../VariaveisGlobais/variaveis_globais.h"
#include "../../TiposDados/TiposDados.h"

//// fazer função para todos para procurar o maior ID !!!!
int criar_propriedade(LISTA_PROPRIEDADE **iniLista, LISTA_PROPRIEDADE **fimLista, PROPRIEDADE propriedade_nova){

    LISTA_PROPRIEDADE *novo = NULL;

    novo = (LISTA_PROPRIEDADE *) calloc(1,sizeof(LISTA_PROPRIEDADE));

    if(novo == NULL){ // se a lista estiver vazia
        printf("Out of memory ! \n");
    }

    novo -> propriedade = propriedade_nova;

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

void imprime_todas_propriedades (LISTA_PROPRIEDADE *iniLista) {

    int contador =0;
    char verdade [] = "verdade";
    char falso [] = "falso";

    LISTA_PROPRIEDADE *aux = NULL;

    if (iniLista == NULL) {
        printf("Lista Vazia\n");
    }

    for (aux = iniLista; aux != NULL; aux = aux->seguinte) {
        contador ++;

        printf("-------------------------------");

        if(aux->propriedade.popular == 0){
            printf("Propriedade popular ?: %s\n",falso );
        }else{
            printf("Propriedade popular ?: %s\n",verdade );
        }

        printf("Preço da propriedade: %.2f\n",aux->propriedade.preco);
        printf("Tipo da propriedade: %s\n",aux -> propriedade.tipo_comercial);
        printf("Tipo da propriedade: %s\n",aux -> propriedade.tipo_imovel);
        printf("ID da propriedade: %d\n", aux -> propriedade.id_propriedade);

        printf("-------------------------------");
    }
}

int editar_propriedade(LISTA_PROPRIEDADE **iniLista, PROPRIEDADE editada){

    int contador =0;
    char verdade [] = "verdade";
    char falso [] = "falso";

    LISTA_PROPRIEDADE *aux = NULL;

    if (iniLista == NULL) {
        printf("Lista Vazia\n");
        return -1;
    }

    for (aux = *iniLista; aux != NULL; aux = aux->seguinte) {

        if(aux -> propriedade.id_propriedade == editada.id_propriedade){

            strcpy(aux -> propriedade.tipo_imovel, editada.tipo_imovel);
            strcpy(aux -> propriedade.tipo_comercial, editada.tipo_comercial);
            aux -> propriedade.preco = editada.preco;
            aux -> propriedade.popular = editada.popular;

        }
        contador ++;

        printf("------------------------------------------------------------------");

        if(aux->propriedade.popular == 0){
            printf("Propriedade popular ?: %s\n",falso );
        }else{
            printf("Propriedade popular ?: %s\n",verdade );
        }

        printf("Preço da propriedade: %.2f\n",aux->propriedade.preco);
        printf("Tipo da propriedade: %s\n",aux -> propriedade.tipo_comercial);
        printf("Tipo da propriedade: %s\n",aux -> propriedade.tipo_imovel);
        printf("ID da propriedade: %d\n", aux -> propriedade.id_propriedade);

        printf("------------------------------------------------------------------");
    }
    return 0;
}

int remover_propriedade(LISTA_PROPRIEDADE *iniLista,int propriedade_id){

    LISTA_PROPRIEDADE *aux = NULL;
    LISTA_PROPRIEDADE *NoSeguinte = NULL;
    LISTA_PROPRIEDADE  *NoAnterior = NULL;
    int contador =0;


    if(iniLista == NULL){
        printf("Lista vazia\n");
        return 0;
    }

    for(aux = iniLista; aux != NULL; aux = aux->seguinte){

        if(aux ->propriedade.id_propriedade == propriedade_id){
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

void limpar_memoria_lista_propriedades(LISTA_PROPRIEDADE **iniLista, LISTA_PROPRIEDADE **fimLista){

    LISTA_PROPRIEDADE *aux = NULL;
    LISTA_PROPRIEDADE *proximo = NULL;

    aux = *iniLista;

    *iniLista = NULL;
    *fimLista = NULL;

    while(aux != NULL){
        proximo = aux -> seguinte;

        free(aux);

        aux = proximo;
    }
}