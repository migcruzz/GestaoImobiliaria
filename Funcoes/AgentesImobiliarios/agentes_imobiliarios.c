#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../VariaveisGlobais/variaveis_globais.h"
#include "../../TiposDados/TiposDados.h"

// O ID do agente imobiliario começa a 1 !!!! e sempre que se apaga um do meio os restantes vão ser copiados para o mesmo apontador

int inserir_agente_imobiliario(AGENTE agente_imobiliario[], AGENTE novo_agente, int posicaoInserir) {

    agente_imobiliario[posicaoInserir].id_agente = posicaoInserir + 1;
    strcpy(agente_imobiliario[posicaoInserir].nome, novo_agente.nome);
    strcpy(agente_imobiliario[posicaoInserir].NIF, novo_agente.NIF);
    strcpy(agente_imobiliario[posicaoInserir].morada, novo_agente.morada);
    strcpy(agente_imobiliario[posicaoInserir].telefone, novo_agente.telefone);
    strcpy(agente_imobiliario[posicaoInserir].palavra_passe, novo_agente.palavra_passe);
    agente_imobiliario[posicaoInserir].dia_nascimento = novo_agente.dia_nascimento;
    agente_imobiliario[posicaoInserir].mes_nascimento = novo_agente.mes_nascimento;
    agente_imobiliario[posicaoInserir].ano_nascimento = novo_agente.ano_nascimento;
    agente_imobiliario[posicaoInserir].role = novo_agente.role;
    agente_imobiliario[posicaoInserir].disponibilidade = novo_agente.disponibilidade;
    return 0;
}


int imprimir_agente_imobiliario(AGENTE agente_imobiliario[], int posicaoImprimir) {

    printf("-------------------------------------------------------------------------");
    printf("-------------------------------------------------------------------------");

    printf("\n O agente com o nome %s tem os seguintes dados:\n",agente_imobiliario[posicaoImprimir].nome);
    printf("-------------------------------------------------------------------------");
    printf("\nO ID do agente e %d\n",agente_imobiliario[posicaoImprimir].id_agente);
    printf("\nO NIF do agente e %s\n",agente_imobiliario[posicaoImprimir].NIF);
    printf("\nA morada do agente e %s\n",agente_imobiliario[posicaoImprimir].morada);
    printf("\nO telefone do agente e %s\n",agente_imobiliario[posicaoImprimir].telefone);
    printf("\nA palavra passe do agente e %s\n",agente_imobiliario[posicaoImprimir].palavra_passe);
    printf("\nA role do agente e %d\n",agente_imobiliario[posicaoImprimir].role);
    printf("\nA disponibilidade do agente e %d\n",agente_imobiliario[posicaoImprimir].disponibilidade);
    printf("\nA data de nascimento do agente e %d-%d-%d, (dd-mm-aaaa)\n",agente_imobiliario[posicaoImprimir].dia_nascimento,agente_imobiliario[posicaoImprimir].mes_nascimento,agente_imobiliario[posicaoImprimir].ano_nascimento);
    printf("-------------------------------------------------------------------------");
    return 0;
}


int criar_agente_imobiliario(AGENTE agente_imobiliario[], AGENTE novo_agente) {

    int novaPosicao = -1;

    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (agente_imobiliario[i].id_agente == 0) {
            novaPosicao = i;
            break;
        }
    }

    if (novaPosicao != -1) {
        inserir_agente_imobiliario(agente_imobiliario, novo_agente, novaPosicao);
    return 0;
    }else{
        printf("\nNão tem lugares disponiveis !\n");
        return -1;
    }

}


int editar_agente_imobiliario(AGENTE agente_imobiliario[], AGENTE agente_editado,int id_procura){

    int id_encontrado =0;

    for(int i =0; i < MAX_AGENTES_IMOBILIARIOS; i++){

        if(agente_imobiliario[i].id_agente == id_procura){
            id_encontrado = agente_imobiliario[i].id_agente;
        }
    }

    if(id_encontrado == 0){
        printf("\nNao existe o agente que pretende editar !!!\n");
        return -1;
    } else{
        inserir_agente_imobiliario(agente_imobiliario, agente_editado, id_encontrado);
        return 0;
    }

}

// Aqui apenas vai inserir valores vazios (Zero no ID) ou NULL:
int remover_agente_imobiliario(AGENTE agente_imobiliario[],int id_procura){

    int id_encontrado =0;

    AGENTE agente_eliminar;

    agente_eliminar.id_agente = 0;
    strcpy(agente_eliminar.nome,"");
    strcpy(agente_eliminar.NIF, "");
    strcpy(agente_eliminar.morada, "");
    strcpy(agente_eliminar.telefone, "");
    strcpy(agente_eliminar.palavra_passe, "");
    agente_eliminar.dia_nascimento =0;
    agente_eliminar.mes_nascimento =0;
    agente_eliminar.ano_nascimento =0;
    agente_eliminar.role = 0;
    agente_eliminar.disponibilidade = 0;


    for(int i =0; i < MAX_AGENTES_IMOBILIARIOS; i++){

        if(agente_imobiliario[i].id_agente == id_procura){
            id_encontrado = agente_imobiliario[i].id_agente;
        }
    }

    if(id_encontrado == 0){
        printf("\nNao existe o agente que pretende editar !!!\n");
        return -1;
    } else{
        inserir_agente_imobiliario(agente_imobiliario, agente_eliminar, id_encontrado);
        return 0;
    }
}

int listar_agente_imobiliario_alfabeto(AGENTE agente_imobiliario[]){

    int num_agentes =0;

    for(int i =0; i<15; i++){
        if(agente_imobiliario[i].id_agente != 0){
            num_agentes ++;
        }
    }
    if(num_agentes != 0){

    AGENTE *agente_imobiliario_ordenar = NULL;

    agente_imobiliario_ordenar = (AGENTE *) calloc(num_agentes, sizeof (AGENTE));

    // Uso do algoritmo Selection sort:

        int i = 0, j = 0, min = 0;
        char aux[30];

        for (i = 0; i < num_agentes; i++) {
            min = i;

            for (j = i + 1; j < num_agentes; j++) {
                if (strcmp(agente_imobiliario_ordenar[j].nome, agente_imobiliario_ordenar[min].nome) < 0) {
                    min = j;
                }
            }

            if (min != i) {
                strcpy(aux, agente_imobiliario_ordenar[min].nome);
                strcpy(agente_imobiliario_ordenar[min].nome, agente_imobiliario_ordenar[i].nome);
                strcpy(agente_imobiliario_ordenar[i].nome, aux);
            }
        }

        for(int a =0; a < num_agentes; a++){
            imprimir_agente_imobiliario(agente_imobiliario_ordenar,a);
        }

        free(agente_imobiliario_ordenar);

        return 0;

    }else{
        printf("\nNao existem agentes !\n");
    return -1;
    }
}

int listar_agente_imobiliario_idade(AGENTE agente_imobiliario[]){


    int num_agentes =0;

    for(int i =0; i<15; i++){
        if(agente_imobiliario[i].id_agente != 0){
            num_agentes ++;
        }
    }
    if(num_agentes != 0){

        AGENTE *agente_imobiliario_ordenar = NULL;

        agente_imobiliario_ordenar = (AGENTE *) calloc(num_agentes, sizeof (AGENTE));

        // Uso do algoritmo Selection sort:

        int i=0,j=0,min=0;
        AGENTE aux;

        for(i=0;i<num_agentes-1;i++){
            min = i;
            for(j=i;j<num_agentes;j++){
                if(agente_imobiliario_ordenar[j].ano_nascimento >= agente_imobiliario_ordenar[min].ano_nascimento &&
                   agente_imobiliario_ordenar[j].mes_nascimento >= agente_imobiliario_ordenar[min].mes_nascimento &&
                   agente_imobiliario_ordenar[j].dia_nascimento > agente_imobiliario_ordenar[min].dia_nascimento){
                    min = j;
                }
            }
            if(min != i){
                aux = agente_imobiliario_ordenar[min];
                agente_imobiliario_ordenar[min] = agente_imobiliario_ordenar[i];
                agente_imobiliario_ordenar[i]= aux;
            }
        }

        for(int a =0; a < num_agentes; a++){
            imprimir_agente_imobiliario(agente_imobiliario_ordenar,a);
        }

        free(agente_imobiliario_ordenar);

        return 0;

    }else{
        printf("\nNao existem agentes !\n");
        return -1;
    }
}

// True = 1; False = 0;

int mudar_estado_agente_imobiliario(){

    return 0;
}

int gerador_relatorios_agentes(){

    return 0;
}