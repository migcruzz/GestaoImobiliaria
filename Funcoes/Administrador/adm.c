#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../VariaveisGlobais/variaveis_globais.h"
#include "../../TiposDados/TiposDados.h"


int inserir_agente_imobiliario(ADMIN administrador[], AGENTE novo_agente, int posicaoInserir) {

    if(agente_imobiliario[posicaoInserir].id_agente != posicaoInserir + 1){agente_imobiliario[posicaoInserir].id_agente = posicaoInserir + 1;}
    if (strcmp(agente_imobiliario[posicaoInserir].nome, novo_agente.nome) != 0){strcpy(agente_imobiliario[posicaoInserir].nome, novo_agente.nome);}
    if (strcmp(agente_imobiliario[posicaoInserir].NIF, novo_agente.NIF) != 0){strcpy(agente_imobiliario[posicaoInserir].NIF, novo_agente.NIF);}
    if (strcmp(agente_imobiliario[posicaoInserir].morada, novo_agente.morada) != 0){strcpy(agente_imobiliario[posicaoInserir].morada, novo_agente.morada);}
    if (strcmp(agente_imobiliario[posicaoInserir].telefone, novo_agente.telefone) != 0){strcpy(agente_imobiliario[posicaoInserir].telefone, novo_agente.telefone);}
    if (strcmp(agente_imobiliario[posicaoInserir].palavra_passe, novo_agente.palavra_passe) != 0){strcpy(agente_imobiliario[posicaoInserir].palavra_passe, novo_agente.palavra_passe);}
    if (agente_imobiliario[posicaoInserir].dia_nascimento != novo_agente.dia_nascimento){agente_imobiliario[posicaoInserir].dia_nascimento = novo_agente.dia_nascimento;}
    if (agente_imobiliario[posicaoInserir].mes_nascimento != novo_agente.mes_nascimento){agente_imobiliario[posicaoInserir].mes_nascimento = novo_agente.mes_nascimento;}
    if (agente_imobiliario[posicaoInserir].ano_nascimento != novo_agente.ano_nascimento){agente_imobiliario[posicaoInserir].ano_nascimento = novo_agente.ano_nascimento;}
    if (agente_imobiliario[posicaoInserir].role != novo_agente.role){agente_imobiliario[posicaoInserir].role = novo_agente.role;}
    if (agente_imobiliario[posicaoInserir].disponibilidade != novo_agente.disponibilidade){agente_imobiliario[posicaoInserir].disponibilidade = novo_agente.disponibilidade;}
    return 0;
}

int imprimir_agente_imobiliario(AGENTE agente_imobiliario[], int posicaoImprimir) {

    if(posicaoImprimir != 0){
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
    }

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

// Para esta função apenas e editado a disponibilidade os restantes dados não serao inseridos por causa da outra função ter verificações que não o permitem (no caso de )

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



