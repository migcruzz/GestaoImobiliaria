#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../VariaveisGlobais/variaveis_globais.h"
#include "../../TiposDados/TiposDados.h"

// O ID do agente imobiliario começa a 1 !!!! e sempre que se apaga um do meio os restantes vão manter a posição


int inserir_agente_imobiliario(AGENTE agente_imobiliario[], AGENTE novo_agente, int *posicaoInserir) {

    if (*posicaoInserir < 0 || *posicaoInserir > MAX_AGENTES_IMOBILIARIOS) {
        printf("Posicao de insercao invalida.\n");
        return -1;
    }

    if (agente_imobiliario[*posicaoInserir].id_agente == 0) {
        agente_imobiliario[*posicaoInserir].id_agente = *posicaoInserir + 1;
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
            id_encontrado = id_procura;
            break;
        }
    }

    if (id_encontrado == -1) {
        printf("Não existe agente com o id_procura.\n");
        return -1;
    } else {
        inserir_agente_imobiliario(agente_imobiliario, agente_editado, &id_encontrado-1);
        printf("Agente com ID %d editado.\n", id_procura);
        return 0;
    }
}

// Aqui apenas vai inserir valores vazios (Zero no ID) ou NULL:
int remover_agente_imobiliario(AGENTE agente_imobiliario[], int id_procura) {
    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (agente_imobiliario[i].id_agente == id_procura) {
            // Limpar os dados do agente
            agente_imobiliario[i].id_agente = 0;
            strcpy(agente_imobiliario[i].nome, "");
            strcpy(agente_imobiliario[i].NIF, "");
            strcpy(agente_imobiliario[i].morada, "");
            strcpy(agente_imobiliario[i].telefone, "");
            strcpy(agente_imobiliario[i].palavra_passe, "");
            agente_imobiliario[i].dia_nascimento = 0;
            agente_imobiliario[i].mes_nascimento = 0;
            agente_imobiliario[i].ano_nascimento = 0;
            agente_imobiliario[i].role = 0;
            agente_imobiliario[i].disponibilidade = 0;

            printf("\nAgente removido com sucesso.\n");
            return 0;
        }
    }

    printf("\nNao existe o agente que pretende remover !!!\n");
    return -1;
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

int carregar_do_ficheiro_agente_imobiliario(AGENTE agente_imobiliario[]) {
    AGENTE agente_imobiliario_lido;
    FILE *ficheiro_agente_imobiliario = fopen("../Armazenamento/Texto/Agentes_Imobiliarios.txt", "r");
    if (ficheiro_agente_imobiliario == NULL) {
        printf("\nErro ao abrir o ficheiro de agentes imobiliários !!!!\n");
        return -1;
    }

    int contador = 0;
    printf("Iniciando a leitura do arquivo...\n");

    while (fscanf(ficheiro_agente_imobiliario, "%29[^;];%20[^;];%9[^;];%49[^;];%9[^;];%d;%d;%d;%d;%d;%d\n",
                  agente_imobiliario_lido.nome,
                  agente_imobiliario_lido.palavra_passe,
                  agente_imobiliario_lido.NIF,
                  agente_imobiliario_lido.morada,
                  agente_imobiliario_lido.telefone,
                  &agente_imobiliario_lido.id_agente,
                  &agente_imobiliario_lido.dia_nascimento,
                  &agente_imobiliario_lido.mes_nascimento,
                  &agente_imobiliario_lido.ano_nascimento,
                  &agente_imobiliario_lido.role,
                  &agente_imobiliario_lido.disponibilidade) == 11) {

        printf("Lido do ficheiro: %s, %s, %s, %s, %s, %d, %d/%d/%d, %d, %d\n",
               agente_imobiliario_lido.nome,
               agente_imobiliario_lido.palavra_passe,
               agente_imobiliario_lido.NIF,
               agente_imobiliario_lido.morada,
               agente_imobiliario_lido.telefone,
               agente_imobiliario_lido.id_agente,
               agente_imobiliario_lido.dia_nascimento,
               agente_imobiliario_lido.mes_nascimento,
               agente_imobiliario_lido.ano_nascimento,
               agente_imobiliario_lido.role,
               agente_imobiliario_lido.disponibilidade);

        if (contador < MAX_AGENTES_IMOBILIARIOS) {
            agente_imobiliario[contador] = agente_imobiliario_lido;
            printf("Agente inserido na posição %d\n", contador);
            contador++;
        } else {
            printf("\nO número máximo de agentes imobiliários foi alcançado.\n");
            break;
        }
    }

    if (contador == 0) {
        printf("Nenhum agente foi lido do arquivo.\n");
    } else {
        printf("Total de agentes lidos: %d\n", contador);
    }

    fclose(ficheiro_agente_imobiliario);
    return 0;
}




int inserir_no_ficheiro_agente_imobiliario(AGENTE agente_imobiliario[]) {
    FILE *ficheiro_agente_imobiliario = fopen("../Armazenamento/Texto/Agentes_Imobiliarios.txt", "w");
    int contador = 0;
    int total_adicionado = 0;  // Inicialização correta da variável

    if (ficheiro_agente_imobiliario == NULL) {
        printf("\nErro ao abrir o ficheiro dos Agentes !!!!\n");
        return -1;
    }

    printf("Iniciando a escrita no arquivo...\n");

    while (contador < MAX_AGENTES_IMOBILIARIOS && total_adicionado < MAX_AGENTES_IMOBILIARIOS) {
        if (agente_imobiliario[contador].id_agente > 0 &&
            strlen(agente_imobiliario[contador].nome) > 0 &&
            strlen(agente_imobiliario[contador].palavra_passe) > 0 &&
            strlen(agente_imobiliario[contador].NIF) > 0 &&
            strlen(agente_imobiliario[contador].morada) > 0 &&
            strlen(agente_imobiliario[contador].telefone) > 0) {

            fprintf(ficheiro_agente_imobiliario, "%s;%s;%s;%s;%s;%d;%d;%d;%d;%d;%d\n",
                    agente_imobiliario[contador].nome,
                    agente_imobiliario[contador].palavra_passe,
                    agente_imobiliario[contador].NIF,
                    agente_imobiliario[contador].morada,
                    agente_imobiliario[contador].telefone,
                    agente_imobiliario[contador].id_agente,
                    agente_imobiliario[contador].dia_nascimento,
                    agente_imobiliario[contador].mes_nascimento,
                    agente_imobiliario[contador].ano_nascimento,
                    agente_imobiliario[contador].role,
                    agente_imobiliario[contador].disponibilidade);

            printf("Agente inserido na posição %d: %s\n", contador, agente_imobiliario[contador].nome);

            total_adicionado++;  // Incrementa o total de agentes adicionados
        } else {
            printf("\nErro: Algum dos campos do agente na posição %d está vazio ou contém um valor inválido. Não foi possível adicionar ao arquivo.\n", contador);
        }
        contador++;
    }

    fclose(ficheiro_agente_imobiliario);

    printf("Total de agentes adicionados: %d\n", total_adicionado);

    return 0;
}


int gerador_relatorios_agentes(){

    return 0;
}
