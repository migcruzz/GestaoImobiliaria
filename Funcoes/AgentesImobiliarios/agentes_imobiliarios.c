#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../VariaveisGlobais/variaveis_globais.h"
#include "../../TiposDados/TiposDados.h"

// O ID do agente imobiliario começa a 1 !!!! e sempre que se apaga um do meio os restantes vão ser copiados para o mesmo apontador


int inserir_agente_imobiliario(AGENTE agente_imobiliario[], AGENTE novo_agente, int *posicaoInserir) {

    if (*posicaoInserir < 0 || *posicaoInserir >= MAX_AGENTES_IMOBILIARIOS) {
        printf("Posicao de insercao invalida.\n");
        return -1;
    }

    if (agente_imobiliario[*posicaoInserir].id_agente == 0) {
        agente_imobiliario[*posicaoInserir].id_agente = *posicaoInserir + 1;
    }else{
        agente_imobiliario[*posicaoInserir].id_agente = *posicaoInserir;
    }

    strcpy(agente_imobiliario[*posicaoInserir].nome, novo_agente.nome);
    strcpy(agente_imobiliario[*posicaoInserir].NIF, novo_agente.NIF);
    strcpy(agente_imobiliario[*posicaoInserir].morada, novo_agente.morada);
    strcpy(agente_imobiliario[*posicaoInserir].telefone, novo_agente.telefone);
    strcpy(agente_imobiliario[*posicaoInserir].palavra_passe, novo_agente.palavra_passe);
    agente_imobiliario[*posicaoInserir].dia_nascimento = novo_agente.dia_nascimento;
    agente_imobiliario[*posicaoInserir].mes_nascimento = novo_agente.mes_nascimento;
    agente_imobiliario[*posicaoInserir].ano_nascimento = novo_agente.ano_nascimento;
    agente_imobiliario[*posicaoInserir].role = novo_agente.role;
    agente_imobiliario[*posicaoInserir].disponibilidade = novo_agente.disponibilidade;

    return 0;
}

int imprimir_agente_imobiliario(AGENTE agente_imobiliario[], int *posicaoImprimir) {
    if(agente_imobiliario->id_agente != 0){
        fflush(stdout);
        printf("-------------------------------------------------------------------------");
        printf("-------------------------------------------------------------------------");
        printf("\n O agente com o nome %s tem os seguintes dados:\n",agente_imobiliario[*posicaoImprimir].nome);
        fflush(stdout);
        printf("-------------------------------------------------------------------------");
        printf("\nO ID do agente e %d\n",agente_imobiliario[*posicaoImprimir].id_agente);
        printf("\nO NIF do agente e %s\n",agente_imobiliario[*posicaoImprimir].NIF);
        printf("\nA morada do agente e %s\n",agente_imobiliario[*posicaoImprimir].morada);
        printf("\nO telefone do agente e %s\n",agente_imobiliario[*posicaoImprimir].telefone);
        printf("\nA palavra passe do agente e %s\n",agente_imobiliario[*posicaoImprimir].palavra_passe);
        printf("\nA role do agente e %d\n",agente_imobiliario[*posicaoImprimir].role);
        printf("\nA disponibilidade do agente e %d\n",agente_imobiliario[*posicaoImprimir].disponibilidade);
        printf("\nA data de nascimento do agente e %d-%d-%d, (dd-mm-aaaa)\n",agente_imobiliario[*posicaoImprimir].dia_nascimento,agente_imobiliario[*posicaoImprimir].mes_nascimento,agente_imobiliario[*posicaoImprimir].ano_nascimento);
        printf("-------------------------------------------------------------------------");
        fflush(stdout);
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
        inserir_agente_imobiliario(agente_imobiliario, novo_agente, &novaPosicao);
        return 0;
    }else{
        printf("\nNão tem lugares disponiveis !\n");
        return -1;
    }

}

// Para esta função apenas e editado a disponibilidade os restantes dados não serao inseridos por causa da outra função ter verificações que não o permitem (no caso de )
int editar_agente_imobiliario(AGENTE agente_imobiliario[], AGENTE agente_editado, int id_procura) {

    int id_encontrado = -1;

    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (agente_imobiliario[i].id_agente == id_procura) {
            id_encontrado = i;
            break;
        }
    }

    if (id_encontrado == -1) {
        // Não existe agente com o id_procura, inserir um novo agente.
        for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
            if (agente_imobiliario[i].id_agente == 0) { // Espaço livre encontrado
                inserir_agente_imobiliario(agente_imobiliario, agente_editado, &i);
                printf("Novo agente inserido na posição %d.\n", i + 1);
                return 0;
            }
        }
        printf("Nao ha espaco para adicionar um novo agente.\n");
        return -1;
    } else {
        // Agente encontrado, editar
        inserir_agente_imobiliario(agente_imobiliario, agente_editado, &id_encontrado);
        printf("Agente com ID %d editado.\n", id_procura);
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
        inserir_agente_imobiliario(agente_imobiliario, agente_eliminar, &id_encontrado);
        return 0;
    }
}

// ALGORITMO FUNCIONA
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

        // Popular com dados o array que vai aparecer ordenado:

        for(int i =0; i< num_agentes; i++){
            if(agente_imobiliario[i].id_agente != 0){
                agente_imobiliario_ordenar[i] = agente_imobiliario[i];
            }
        }

        // Uso do algoritmo Selection sort:

        int i = 0, j = 0, min = 0;
        AGENTE aux;

        for (i = 0; i < num_agentes; i++) {
            min = i;

            for (j = i + 1; j < num_agentes; j++) {
                if (strcmp(agente_imobiliario_ordenar[j].nome, agente_imobiliario_ordenar[min].nome) < 0) {
                    min = j;
                }
            }

            if (min != i) {
                aux = agente_imobiliario_ordenar[min];
                agente_imobiliario_ordenar[min] = agente_imobiliario_ordenar[i];
                agente_imobiliario_ordenar[i] = aux;
            }
        }

        for(int a =0; a < num_agentes; a++){
            imprimir_agente_imobiliario( agente_imobiliario_ordenar, &a);

        }

        free(agente_imobiliario_ordenar);

        return 0;

    }else{
        printf("\nNao existem agentes !\n");
    return -1;
    }
}

// ALGORITMO FUNCIONA
int listar_agente_imobiliario_idade(AGENTE agente_imobiliario[]) {
    int num_agentes = 0;

    // Contar o número de agentes imobiliários válidos
    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (agente_imobiliario[i].id_agente != 0) {
            num_agentes++;
        }
    }

    if (num_agentes != 0) {
        // Alocar memória para um novo array de agentes imobiliários (ordenados)
        AGENTE *agente_imobiliario_ordenar = (AGENTE *)calloc(num_agentes, sizeof(AGENTE));

        // Copiar os agentes imobiliários válidos para o novo array
        int indice_ordenar = 0;
        for (int i = 0; i < num_agentes; i++) {
            if (agente_imobiliario[i].id_agente != 0) {
                indice_ordenar++;
                agente_imobiliario_ordenar[indice_ordenar] = agente_imobiliario[i];
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
            imprimir_agente_imobiliario( agente_imobiliario, &i);
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