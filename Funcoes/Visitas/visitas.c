#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../VariaveisGlobais/variaveis_globais.h"
#include "../../TiposDados/TiposDados.h"
#include <time.h>

// Trabalhar com formato 24H
// Dentro do programa todos os algoritmos vão ser no formato de minutos e só para o cliente vai ser mostrado


// Função para remover o caractere de nova linha de fgets
void remove_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int conversor_horas_para_minutos(int hora, int minutos_antes){
    int minutos =0;
    if((hora >= 0 && hora <= 24) && (minutos_antes >=0 && minutos_antes < 60 )){
        minutos = 60 * hora;
    }else{
        printf("\nErro na conversão de horas !!!\n");
        return -1;
    }
    return minutos + minutos_antes;
}

TEMPO conversor_minutos_para_horas(int minutos){
TEMPO conversao;
    if(minutos <= 1440 && minutos >=0){
        conversao.horas = minutos % 60;
        conversao.minutos =minutos - (conversao.horas);
    }else{
        printf("\nErro na conversão de dados !!!\n");
        conversao.horas = -1;
        conversao.minutos =-1;
    }
    return conversao;
}


int contador_visitas(LISTA_VISITA **iniLista){

    LISTA_VISITA *primeira = *iniLista;

    int contador =0;

    while(primeira ->seguinte != NULL){
        contador ++;
        primeira = primeira->seguinte;
    }

    return contador;
}


// Cada visita tem de duração máxima de 240 minutos ou 2 Horas.
// Função com funcionamnto normal:
// Função para o cliente usar:


int agendar_visita(LISTA_VISITA **iniLista, LISTA_VISITA **fimLista, CLIENTE cliente_login){

    VISITA nova_visita;
    LISTA_VISITA *nova = NULL;

    nova = (LISTA_VISITA *) calloc(1,sizeof(LISTA_VISITA));

    if(nova == NULL){ // se a lista estiver vazia
        printf("Out of memory ! \n");
        return -1;
    }

    //// Interação com utilizador:

    /// Caso seja uma visita não casa aberta:

    // Entrada para casa aberta

    nova_visita.id_cliente = cliente_login.id_cliente;

    while (1) {
        printf("Casa Aberta (1 para sim, 0 para não): ");
        scanf("%d", &nova_visita.casa_aberta);
        if (nova_visita.casa_aberta == 0 || nova_visita.casa_aberta == 1) break;
        printf("Entrada inválida. Por favor, insira 1 para sim ou 0 para não.\n");
    }

    switch (nova_visita.casa_aberta) {

        case 1:
            break;

        case 0:

            // Entrada para o dia
            while (1) {
                printf("Dia (1-31): ");
                scanf("%d", &nova_visita.dia);
                if (nova_visita.dia >= 1 && nova_visita.dia <= 31) break;
                printf("Dia inválido. Por favor, insira um valor entre 1 e 31.\n");
            }

            // Entrada para o mês
            while (1) {
                printf("Mês (1-12): ");
                scanf("%d", &nova_visita.mes);
                if (nova_visita.mes >= 1 && nova_visita.mes <= 12) break;
                printf("Mês inválido. Por favor, insira um valor entre 1 e 12.\n");
            }

            // Entrada para o ano
            while (1) {
                printf("Ano: ");
                scanf("%d", &nova_visita.ano);
                if (nova_visita.ano > 0) break;
                printf("Ano inválido. Por favor, insira um ano válido.\n");
            }

            // Entrada para ID do agente
            printf("ID do Agente: ");
            scanf("%d", &nova_visita.id_agente);

            // Entrada para ID da propriedade
            printf("ID da Propriedade: ");
            scanf("%d", &nova_visita.id_propriedade);

            // Entrada para duração
            while (1) {
                printf("Duração (em minutos, até 1440): ");
                scanf("%d", &nova_visita.duracao);
                if (nova_visita.duracao > 0 && nova_visita.duracao <= 240) break;
                printf("Duração inválida. Por favor, insira um valor entre 1 e 240 minutos.\n");
            }

            // Entrada para hora de marcação
            while (1) {
                printf("Hora da Marcação (em minutos desde meia-noite, até 1440): ");
                scanf("%d", &nova_visita.hora_marcacao);
                if (nova_visita.hora_marcacao >= 0 && nova_visita.hora_marcacao < 1440) break;
                printf("Hora da marcação inválida. Por favor, insira um valor entre 0 e 1439 minutos.\n");
            }

            // Limpar o buffer do stdin antes de usar fgets para strings
            fflush(stdin);

            // Entrada para relatório
            printf("Relatório (até 3000 caracteres): ");
            fgets(nova_visita.relatorio, sizeof(nova_visita.relatorio), stdin);
            remove_newline(nova_visita.relatorio);

            // Entrada para detalhes de interesse do cliente
            printf("Detalhes de Interesse do Cliente (até 3000 caracteres): ");
            fgets(nova_visita.detalhes_intresse_cliente, sizeof(nova_visita.detalhes_intresse_cliente), stdin);
            remove_newline(nova_visita.detalhes_intresse_cliente);


            break;

        default:
            printf("\nErro casa aberta \n");
            return -1;
    }







    //// Fim interação utilizador


    nova -> visita = nova_visita;

    nova -> seguinte = NULL;
    nova -> anterior = NULL;

    if(*iniLista == NULL){

        *iniLista = nova;
        *fimLista = nova;

    }else{
        nova -> seguinte = *iniLista;
        (*iniLista) -> anterior = nova;
        (*iniLista) = nova;
    }

    return 0;
}


int listar_visita_dia(){



    return 0;
}


//// Funcionalidades de texto entre outras para replicar




// O ID do agente imobiliario começa a 1 !!!! e sempre que se apaga um do meio os restantes vão manter a posição

int inserir_agente_imobiliario_editado(AGENTE *agente_imobiliario, AGENTE novo_agente) {
    // Verificar se o array está cheio
    int posicaoVazia = -1;
    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (agente_imobiliario[i].id_agente == 0) {
            posicaoVazia = i;
            break;
        }
    }

    // Verificar se encontrou uma posição vazia
    if (posicaoVazia == -1) {
        printf("O array de agentes está cheio. Não é possível adicionar mais agentes.\n");
        return -1;
    }

    // Inserir o novo agente na posição encontrada
    agente_imobiliario[posicaoVazia] = novo_agente;


    return 0;
}




// Para esta função apenas e editado a disponibilidade os restantes dados não serao inseridos por causa da outra função ter verificações que não o permitem (no caso de )

int criar_agente_imobiliario(AGENTE agente_imobiliario[]) {
    AGENTE novoAgente;
    int tipo_disponibilidade = -1;

    printf("Nome: ");
    fflush(stdin);
    fgets(novoAgente.nome, 30, stdin);
    novoAgente.nome[strcspn(novoAgente.nome, "\n")] = '\0';  // Remove newline character

    printf("Palavra-Passe: ");
    fflush(stdin);
    fgets(novoAgente.palavra_passe, 30, stdin);
    novoAgente.palavra_passe[strcspn(novoAgente.palavra_passe, "\n")] = '\0';  // Remove newline character

    printf("NIF: ");
    fflush(stdin);
    fgets(novoAgente.NIF, 9, stdin);
    novoAgente.NIF[strcspn(novoAgente.NIF, "\n")] = '\0';  // Remove newline character

    printf("Morada: ");
    fflush(stdin);
    fgets(novoAgente.morada, 50, stdin);
    novoAgente.morada[strcspn(novoAgente.morada, "\n")] = '\0';  // Remove newline character

    printf("Telefone: ");
    fflush(stdin);
    fgets(novoAgente.telefone, 9, stdin);
    novoAgente.telefone[strcspn(novoAgente.telefone, "\n")] = '\0';  // Remove newline character

    printf("Dia de Nascimento: ");
    scanf("%d", &novoAgente.dia_nascimento);
    printf("Mes de Nascimento: ");
    scanf("%d", &novoAgente.mes_nascimento);
    printf("Ano de Nascimento: ");
    scanf("%d", &novoAgente.ano_nascimento);

    do {
        printf("Disponibilidade:\n");
        printf("1. Disponivel\n");
        printf("2. Indisponivel\n");
        scanf("%d", &tipo_disponibilidade);

        if (tipo_disponibilidade == 1) {
            novoAgente.disponibilidade = 1;
        } else if (tipo_disponibilidade == 2) {
            novoAgente.disponibilidade = 0;
        } else {
            printf("Opção inválida. Por favor, escolha 1 para 'Disponivel' ou 2 para 'Nao Disponivel'.\n");
        }
    } while (tipo_disponibilidade != 1 && tipo_disponibilidade != 2);

    novoAgente.role = 2;

    int posicaoInserir = -1;

    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (agente_imobiliario[i].id_agente == 0) {
            posicaoInserir = i;
            break;
        }
    }

    if (posicaoInserir != -1) {
        strcpy(agente_imobiliario[posicaoInserir].nome, novoAgente.nome);
        strcpy(agente_imobiliario[posicaoInserir].NIF, novoAgente.NIF);
        strcpy(agente_imobiliario[posicaoInserir].morada, novoAgente.morada);
        strcpy(agente_imobiliario[posicaoInserir].telefone, novoAgente.telefone);
        strcpy(agente_imobiliario[posicaoInserir].palavra_passe, novoAgente.palavra_passe);
        agente_imobiliario[posicaoInserir].dia_nascimento = novoAgente.dia_nascimento;
        agente_imobiliario[posicaoInserir].mes_nascimento = novoAgente.mes_nascimento;
        agente_imobiliario[posicaoInserir].ano_nascimento = novoAgente.ano_nascimento;
        agente_imobiliario[posicaoInserir].role = novoAgente.role;
        agente_imobiliario[posicaoInserir].disponibilidade = novoAgente.disponibilidade;
        agente_imobiliario[posicaoInserir].id_agente = posicaoInserir + 1;

        return 0;
    } else {
        printf("\nNão há lugares disponíveis!\n");
        return -1;
    }
}

void inserir_agentes_em_arquivo(AGENTE agente_imobiliario[]) {
    FILE *arquivo = fopen("../Armazenamento/Texto/Agentes_Imobiliarios.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (agente_imobiliario[i].id_agente != 0) {
            fprintf(arquivo, "%d\n", agente_imobiliario[i].id_agente);
            fprintf(arquivo, "%s\n", agente_imobiliario[i].nome);
            fprintf(arquivo, "%s\n", agente_imobiliario[i].palavra_passe);
            fprintf(arquivo, "%s\n", agente_imobiliario[i].NIF);
            fprintf(arquivo, "%s\n", agente_imobiliario[i].morada);
            fprintf(arquivo, "%s\n", agente_imobiliario[i].telefone);
            fprintf(arquivo, "%d\n", agente_imobiliario[i].dia_nascimento);
            fprintf(arquivo, "%d\n", agente_imobiliario[i].mes_nascimento);
            fprintf(arquivo, "%d\n", agente_imobiliario[i].ano_nascimento);
            fprintf(arquivo, "%d\n", agente_imobiliario[i].disponibilidade);
            fprintf(arquivo, "%d\n", agente_imobiliario[i].role);
        }
    }

    fclose(arquivo);
}

void carregar_agentes_do_arquivo(AGENTE agente_imobiliario[]) {
    FILE *arquivo = fopen("../Armazenamento/Texto/Agentes_Imobiliarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int index = 0;

    while (fscanf(arquivo, "%d\n", &agente_imobiliario[index].id_agente) != EOF) {
        fscanf(arquivo, "%[^\n]\n", agente_imobiliario[index].nome);
        fscanf(arquivo, "%[^\n]\n", agente_imobiliario[index].palavra_passe);
        fscanf(arquivo, "%[^\n]\n", agente_imobiliario[index].NIF);
        fscanf(arquivo, "%[^\n]\n", agente_imobiliario[index].morada);
        fscanf(arquivo, "%[^\n]\n", agente_imobiliario[index].telefone);
        fscanf(arquivo, "%d\n", &agente_imobiliario[index].dia_nascimento);
        fscanf(arquivo, "%d\n", &agente_imobiliario[index].mes_nascimento);
        fscanf(arquivo, "%d\n", &agente_imobiliario[index].ano_nascimento);
        fscanf(arquivo, "%d\n", &agente_imobiliario[index].disponibilidade);
        fscanf(arquivo, "%d\n", &agente_imobiliario[index].role);
        index++;
    }

    fclose(arquivo);
}

int editar_agente_imobiliario(AGENTE agente_imobiliario[]) {
    int id_agente;
    AGENTE novoAgente;

    printf("Digite o ID do agente que deseja editar: ");
    scanf("%d", &id_agente);

    // Procurar o agente com o ID especificado
    int encontrado = 0;
    int indice_agente = -1; // Índice do agente a ser editado
    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (agente_imobiliario[i].id_agente == id_agente) {
            encontrado = 1;
            indice_agente = i; // Armazenar o índice do agente
            break;
        }
    }

    if (!encontrado) {
        printf("Não existe agente com o ID especificado.\n");
        return -1;
    }

    // Limpar o buffer do teclado
    fflush(stdin);

    // Resto do código de edição...

    printf("Nome: ");
    fflush(stdin);
    fgets(novoAgente.nome, sizeof(novoAgente.nome), stdin);
    novoAgente.nome[strcspn(novoAgente.nome, "\n")] = '\0';

    printf("Palavre-passe: ");
    fflush(stdin);
    fgets(novoAgente.palavra_passe, sizeof(novoAgente.palavra_passe), stdin);
    novoAgente.palavra_passe[strcspn(novoAgente.palavra_passe, "\n")] = '\0';

    printf("NIF: ");
    fflush(stdin);
    fgets(novoAgente.NIF, sizeof(novoAgente.NIF), stdin);
    novoAgente.NIF[strcspn(novoAgente.NIF, "\n")] = '\0';

    printf("Morada: ");
    fflush(stdin);
    fgets(novoAgente.morada, sizeof(novoAgente.morada), stdin);
    novoAgente.morada[strcspn(novoAgente.morada, "\n")] = '\0';


    printf("Telefone: ");
    fflush(stdin);
    fgets(novoAgente.telefone, sizeof(novoAgente.telefone), stdin);
    novoAgente.telefone[strcspn(novoAgente.telefone, "\n")] = '\0';

    printf("Dia de Nascimento: ");

    scanf("%d", &novoAgente.dia_nascimento);


    printf("Mês de Nascimento: ");

    scanf("%d", &novoAgente.mes_nascimento);

    printf("Ano de Nascimento: ");

    scanf("%d", &novoAgente.ano_nascimento);

    printf("Disponibilidade:\n");
    printf("1. Disponível\n");
    printf("2. Indisponível\n");
    int tipo_disponibilidade;
    scanf("%d", &tipo_disponibilidade);

    if (tipo_disponibilidade == 1) {
        novoAgente.disponibilidade = 1;
    } else if (tipo_disponibilidade == 2) {
        novoAgente.disponibilidade = 0;
    } else {
        printf("Opção inválida. Por favor, escolha 1 para 'Disponível' ou 2 para 'Indisponível'.\n");
        return -1;
    }

    // Armazenar temporariamente o ID original
    int id_original = agente_imobiliario[indice_agente].id_agente;

    // Atualizar o agente no array
    agente_imobiliario[indice_agente] = novoAgente;

    // Restaurar o ID original
    agente_imobiliario[indice_agente].id_agente = id_original;

    printf("Agente editado com sucesso.\n");
    return 0;
}

int listar_agente_imobiliario_alfabeto(AGENTE agente_imobiliario[]){
    int num_agentes = 0;

    for(int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++){
        if(agente_imobiliario[i].id_agente != 0){
            num_agentes++;
        }
    }

    if(num_agentes != 0){
        AGENTE *agente_imobiliario_ordenar = (AGENTE *) calloc(num_agentes, sizeof(AGENTE));

        for(int i = 0; i < num_agentes; i++){
            if(agente_imobiliario[i].id_agente != 0){
                agente_imobiliario_ordenar[i] = agente_imobiliario[i];
            }
        }

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

        printf("Lista de Agentes Imobiliários (Ordem Alfabética):\n");
        printf("--------------------------------\n");
        for(int a = 0; a < num_agentes; a++){
            printf("ID do Agente: %d\n", agente_imobiliario_ordenar[a].id_agente);
            printf("Nome: %s\n", agente_imobiliario_ordenar[a].nome);
            printf("NIF: %s\n", agente_imobiliario_ordenar[a].NIF);
            printf("Morada: %s\n", agente_imobiliario_ordenar[a].morada);
            printf("Telefone: %s\n", agente_imobiliario_ordenar[a].telefone);
            printf("Data de Nascimento: %d/%d/%d\n", agente_imobiliario_ordenar[a].dia_nascimento,
                   agente_imobiliario_ordenar[a].mes_nascimento, agente_imobiliario_ordenar[a].ano_nascimento);
            printf("Disponibilidade: %s\n", (agente_imobiliario_ordenar[a].disponibilidade == 1) ? "Disponível" : "Indisponível");
            printf("--------------------------------\n");
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

    // Contagem do número de agentes imobiliários válidos
    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (agente_imobiliario[i].id_agente != 0) {
            num_agentes++;
        }
    }

    if (num_agentes != 0) {
        // Alocação de memória para um novo array de agentes imobiliários (ordenados)
        AGENTE *agente_imobiliario_ordenar = (AGENTE *)calloc(num_agentes, sizeof(AGENTE));

        int indice_ordenar = 0;
        for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
            if (agente_imobiliario[i].id_agente != 0) {
                agente_imobiliario_ordenar[indice_ordenar++] = agente_imobiliario[i];
            }
        }

        // Ordenação dos agentes por idade usando o algoritmo Bubble Sort
        for (int i = 0; i < num_agentes - 1; i++) {
            for (int j = 0; j < num_agentes - i - 1; j++) {
                int idade_agente_j = 2024 - agente_imobiliario_ordenar[j].ano_nascimento;
                int idade_agente_j_1 = 2024 - agente_imobiliario_ordenar[j + 1].ano_nascimento;

                if (idade_agente_j > idade_agente_j_1) {
                    AGENTE temp = agente_imobiliario_ordenar[j];
                    agente_imobiliario_ordenar[j] = agente_imobiliario_ordenar[j + 1];
                    agente_imobiliario_ordenar[j + 1] = temp;
                }
            }
        }

        // Impressão dos detalhes de cada agente
        printf("Lista de Agentes Imobiliários (Ordem de Idade):\n");
        printf("--------------------------------\n");
        for (int i = 0; i < num_agentes; i++) {
            printf("ID do Agente: %d\n", agente_imobiliario_ordenar[i].id_agente);
            printf("Nome: %s\n", agente_imobiliario_ordenar[i].nome);
            printf("NIF: %s\n", agente_imobiliario_ordenar[i].NIF);
            printf("Morada: %s\n", agente_imobiliario_ordenar[i].morada);
            printf("Telefone: %s\n", agente_imobiliario_ordenar[i].telefone);
            printf("Data de Nascimento: %d/%d/%d\n", agente_imobiliario_ordenar[i].dia_nascimento,
                   agente_imobiliario_ordenar[i].mes_nascimento, agente_imobiliario_ordenar[i].ano_nascimento);
            printf("Disponibilidade: %s\n", (agente_imobiliario_ordenar[i].disponibilidade == 1) ? "Disponível" : "Indisponível");
            printf("--------------------------------\n");
        }

        free(agente_imobiliario_ordenar);

        return 0;
    } else {
        printf("\nNao existem agentes!\n");
        return -1;
    }
}

void tornar_agente_indisponivel(AGENTE agente_imobiliario[], int id_agente) {
    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (agente_imobiliario[i].id_agente == id_agente) {
            agente_imobiliario[i].disponibilidade = 0; // Definindo disponibilidade como indisponível
            printf("Agente com ID %d tornou-se indisponível.\n", id_agente);
            return; // Agente encontrado e disponibilidade alterada, portanto, saia da função
        }
    }
    // Se o loop terminar sem retornar, o agente com o ID fornecido não foi encontrado
    printf("Agente com ID %d não encontrado.\n", id_agente);
}

int remover_agente_imobiliario(AGENTE agente_imobiliario[], int id_procura) {
    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (agente_imobiliario[i].id_agente == id_procura) {
            // Limpar os dados do agente
            memset(&agente_imobiliario[i], 0, sizeof(AGENTE));
            printf("Agente removido com sucesso.\n");
            return 0;
        }
    }

    printf("Não existe agente com o ID especificado.\n");
    return -1;
}


int listar_agente_imobiliario(AGENTE agente_imobiliario[]) {
    int num_agentes = 0;

    // Count the number of valid real estate agents
    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (agente_imobiliario[i].id_agente != 0) {
            num_agentes++;
        }
    }

    if (num_agentes != 0) {
        printf("Lista de Agentes Imobiliários:\n");
        printf("--------------------------------\n");

        // Iterate over the array and print the details of each agent
        for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
            if (agente_imobiliario[i].id_agente != 0) {
                printf("ID do Agente: %d\n", agente_imobiliario[i].id_agente);
                printf("Nome: %s\n", agente_imobiliario[i].nome);
                printf("NIF: %s\n", agente_imobiliario[i].NIF);
                printf("Morada: %s\n", agente_imobiliario[i].morada);
                printf("Telefone: %s\n", agente_imobiliario[i].telefone);
                printf("Data de Nascimento: %d/%d/%d\n", agente_imobiliario[i].dia_nascimento,
                       agente_imobiliario[i].mes_nascimento, agente_imobiliario[i].ano_nascimento);
                printf("Disponibilidade: %s\n", (agente_imobiliario[i].disponibilidade == 1) ? "Disponível" : "Indisponível");
                printf("--------------------------------\n");
            }
        }

        printf("Total de Agentes Imobiliários: %d\n", num_agentes);
    } else {
        printf("Não existem agentes imobiliários cadastrados.\n");
        return -1;
    }

    return 0;
}





