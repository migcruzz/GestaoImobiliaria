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
    agente_imobiliario[posicaoInserir].role = novo_agente.role;
    agente_imobiliario[posicaoInserir].disponibilidade = novo_agente.disponibilidade;
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



    return 0;
}

int listar_agente_imobiliario_idade(){

    return 0;
}

int mudar_estado_agente_imobiliario(){

    return 0;
}

int gerador_relatorios_agentes(){

    return 0;
}