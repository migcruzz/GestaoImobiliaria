#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../VariaveisGlobais/variaveis_globais.h"
#include "../../TiposDados/TiposDados.h"

// O ID do agente imobiliario começa a 1 !!!! e sempre que se apaga um do meio os restantes vão ser copiados para o mesmo apontador

int inserir_agente_imobiliario(AGENTE agente_imobiliario[], AGENTE novo_agente, int posicaoInserir) {

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
            printf("-------------------------------------------------------------------------");
            printf("-------------------------------------------------------------------------");
            printf("\n O agente com o nome %s tem os seguintes dados:\n",agente_imobiliario[a].nome);
            printf("-------------------------------------------------------------------------");
            printf("\nO ID do agente e %d\n",agente_imobiliario[a].id_agente);
            printf("\nO NIF do agente e %s\n",agente_imobiliario[a].NIF);
            printf("\nA morada do agente e %s\n",agente_imobiliario[a].morada);
            printf("\nO telefone do agente e %s\n",agente_imobiliario[a].telefone);
            printf("\nA palavra passe do agente e %s\n",agente_imobiliario[a].palavra_passe);
            printf("\nA role do agente e %d\n",agente_imobiliario[a].role);
            printf("\nA disponibilidade do agente e %d\n",agente_imobiliario[a].disponibilidade);
            printf("\nA data de nascimento do agente e %d-%d-%d, (dd-mm-aaaa)\n",agente_imobiliario[a].dia_nascimento,agente_imobiliario[a].mes_nascimento,agente_imobiliario[a].ano_nascimento);
            printf("-------------------------------------------------------------------------");
        }

        free(agente_imobiliario_ordenar);

        return 0;

    }else{
        printf("\nNao existem agentes !\n");
    return -1;
    }
}

int listar_agente_imobiliario_idade(AGENTE agente_imobiliario[]) {
    int num_agentes = 0;

    // Contar o número de agentes imobiliários válidos
    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (agente_imobiliario[i].id_agente != 0) {
            num_agentes++;
        }
    }

    if (num_agentes != 0) {
        // Alocar memória para um novo array de agentes imobiliários
        AGENTE *agente_imobiliario_ordenar = (AGENTE *)calloc(num_agentes, sizeof(AGENTE));

        // Copiar os agentes imobiliários válidos para o novo array
        int indice_ordenar = 0;
        for (int i = 0; i < num_agentes; i++) {
            if (agente_imobiliario[i].id_agente != 0) {
                agente_imobiliario_ordenar[indice_ordenar++] = agente_imobiliario[i];
            }
        }

        // Ordenar os agentes imobiliários por idade usando o algoritmo de ordenação Bubble Sort
        for (int i = 0; i < num_agentes - 1; i++) {
            for (int j = 0; j < num_agentes - i - 1; j++) {
                // Calcular a idade de cada agente com base na data de nascimento
                int idade_agente_j = 2024 - agente_imobiliario_ordenar[j].ano_nascimento;
                int idade_agente_j_1 = 2024 - agente_imobiliario_ordenar[j + 1].ano_nascimento;

                // Trocar os agentes de posição se o agente j for mais novo que o agente j+1
                if (idade_agente_j > idade_agente_j_1) {
                    AGENTE temp = agente_imobiliario_ordenar[j];
                    agente_imobiliario_ordenar[j] = agente_imobiliario_ordenar[j + 1];
                    agente_imobiliario_ordenar[j + 1] = temp;
                }
            }
        }

        // Imprimir os agentes imobiliários ordenados por idade
        for (int i = 0; i < num_agentes; i++) {
            printf("-------------------------------------------------------------------------\n");
            printf("O agente com o nome %s tem os seguintes dados:\n", agente_imobiliario_ordenar[i].nome);
            printf("ID do agente: %d\n", agente_imobiliario_ordenar[i].id_agente);
            printf("NIF do agente: %s\n", agente_imobiliario_ordenar[i].NIF);
            printf("Morada do agente: %s\n", agente_imobiliario_ordenar[i].morada);
            printf("Telefone do agente: %s\n", agente_imobiliario_ordenar[i].telefone);
            printf("Palavra passe do agente: %s\n", agente_imobiliario_ordenar[i].palavra_passe);
            printf("Role do agente: %d\n", agente_imobiliario_ordenar[i].role);
            printf("Disponibilidade do agente: %d\n", agente_imobiliario_ordenar[i].disponibilidade);
            printf("Data de nascimento do agente: %d-%d-%d (dd-mm-aaaa)\n", agente_imobiliario_ordenar[i].dia_nascimento, agente_imobiliario_ordenar[i].mes_nascimento, agente_imobiliario_ordenar[i].ano_nascimento);
            printf("-------------------------------------------------------------------------\n");
        }

        // Liberar a memória alocada para o novo array de agentes imobiliários
        free(agente_imobiliario_ordenar);

        return 0;
    } else {
        printf("\nNao existem agentes!\n");
        return -1;
    }
}

// True = 1; False = 0;

int gerador_relatorios_agentes(){

    return 0;
}