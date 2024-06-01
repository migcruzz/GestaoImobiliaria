#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../VariaveisGlobais/variaveis_globais.h"
#include "../../TiposDados/TiposDados.h"

// O ID do agente imobiliario começa a 1 !!!! e sempre que se apaga um do meio os restantes vão manter a posição
// Para esta função apenas e editado a disponibilidade os restantes dados não serao inseridos por causa da outra função ter verificações que não o permitem (no caso de )

void remove_newlineAgente(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

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
    fflush(stdin);
    scanf("%d", &novoAgente.dia_nascimento);


    printf("Mês de Nascimento: ");
    fflush(stdin);
    scanf("%d", &novoAgente.mes_nascimento);

    printf("Ano de Nascimento: ");
    fflush(stdin);
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

int editar_agente_imobiliario_logado(AGENTE agente_imobiliario[], int id_agente_logado) {
    AGENTE *agente_logado = NULL;

    // Procurar o agente com o ID correspondente ao agente logado
    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (agente_imobiliario[i].id_agente == id_agente_logado) {
            agente_logado = &agente_imobiliario[i];
            break;
        }
    }

    if (agente_logado == NULL) {
        printf("Erro: Agente não encontrado.\n");
        return -1;
    }

    // Solicitar novos dados
    printf("Editar perfil do agente:\n");
    printf("Bem-vindo, %s!\n", agente_logado->nome);

    printf("Novo nome: ");
    fflush(stdin);
    fgets(agente_logado->nome, sizeof(agente_logado->nome), stdin);
    remove_newlineAgente(agente_logado->nome);

    printf("Nova palavra-passe: ");
    fflush(stdin);
    fgets(agente_logado->palavra_passe, sizeof(agente_logado->palavra_passe), stdin);
    remove_newlineAgente(agente_logado->palavra_passe);

    printf("Novo NIF: ");
    fflush(stdin);
    fgets(agente_logado->NIF, sizeof(agente_logado->NIF), stdin);
    remove_newlineAgente(agente_logado->NIF);

    printf("Nova morada: ");
    fflush(stdin);
    fgets(agente_logado->morada, sizeof(agente_logado->morada), stdin);
    remove_newlineAgente(agente_logado->morada);

    printf("Novo telefone: ");
    fflush(stdin);
    fgets(agente_logado->telefone, sizeof(agente_logado->telefone), stdin);
    remove_newlineAgente(agente_logado->telefone);

    printf("Novo dia de nascimento: ");
    fflush(stdin);
    scanf("%d", &agente_logado->dia_nascimento);

    printf("Novo mês de nascimento: ");
    fflush(stdin);
    scanf("%d", &agente_logado->mes_nascimento);

    printf("Novo ano de nascimento: ");
    fflush(stdin);
    scanf("%d", &agente_logado->ano_nascimento);

    printf("Nova disponibilidade (1 para Disponível, 0 para Indisponível): ");
    fflush(stdin);
    scanf("%d", &agente_logado->disponibilidade);

    printf("Perfil do agente atualizado com sucesso.\n");

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

        printf("┌───────────────┬───────────────────┬───────────────────────┬──────────────┬───────────────────┬─────────────────────┬───────────────────────┐\n");
        printf("│   ID          │        Nome        │          NIF          │    Morada    │     Telefone      │ Data de Nascimento │   Disponibilidade   │\n");
        printf("├───────────────┼───────────────────┼───────────────────────┼──────────────┼───────────────────┼─────────────────────┼───────────────────────┤\n");
        for(int a = 0; a < num_agentes; a++){
            printf("│   %-11d │ %-17s │ %-21s │ %-12s │ %-17s │ %2d/%2d/%-12d │ %-19s │\n",
                   agente_imobiliario_ordenar[a].id_agente,
                   agente_imobiliario_ordenar[a].nome,
                   agente_imobiliario_ordenar[a].NIF,
                   agente_imobiliario_ordenar[a].morada,
                   agente_imobiliario_ordenar[a].telefone,
                   agente_imobiliario_ordenar[a].dia_nascimento,
                   agente_imobiliario_ordenar[a].mes_nascimento,
                   agente_imobiliario_ordenar[a].ano_nascimento,
                   (agente_imobiliario_ordenar[a].disponibilidade == 1) ? "Disponível" : "Indisponível");
            printf("├───────────────┼───────────────────┼───────────────────────┼──────────────┼───────────────────┼─────────────────────┼───────────────────────┤\n");
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

        // Impressão dos detalhes de cada agente em uma tabela
        printf("┌───────────────┬───────────────────┬───────────────────────┬──────────────┬───────────────────┬─────────────────────┬───────────────────────┐\n");
        printf("│   ID          │        Nome        │          NIF          │    Morada    │     Telefone      │ Data de Nascimento │   Disponibilidade   │\n");
        printf("├───────────────┼───────────────────┼───────────────────────┼──────────────┼───────────────────┼─────────────────────┼───────────────────────┤\n");
        for (int i = 0; i < num_agentes; i++) {
            printf("│   %-11d │ %-17s │ %-21s │ %-12s │ %-17s │ %2d/%2d/%-12d │ %-19s │\n",
                   agente_imobiliario_ordenar[i].id_agente,
                   agente_imobiliario_ordenar[i].nome,
                   agente_imobiliario_ordenar[i].NIF,
                   agente_imobiliario_ordenar[i].morada,
                   agente_imobiliario_ordenar[i].telefone,
                   agente_imobiliario_ordenar[i].dia_nascimento,
                   agente_imobiliario_ordenar[i].mes_nascimento,
                   agente_imobiliario_ordenar[i].ano_nascimento,
                   (agente_imobiliario_ordenar[i].disponibilidade == 1) ? "Disponível" : "Indisponível");
            printf("├───────────────┼───────────────────┼───────────────────────┼──────────────┼───────────────────┼─────────────────────┼───────────────────────┤\n");
        }

        free(agente_imobiliario_ordenar);

        return 0;
    } else {
        printf("\nNao existem agentes!\n");
        return -1;
    }
}

void tornar_agente_indisponivel(AGENTE agente_imobiliario[]) {
    int num_agentes = 0;
    int id_agente=0;

    // Contagem do número de agentes imobiliários válidos
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

        printf("Insira o ID do agente que deseja tornar indisponível: ");
        scanf("%d", &id_agente);

        for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
            if (agente_imobiliario[i].id_agente == id_agente) {
                agente_imobiliario[i].disponibilidade = 0; // Definindo disponibilidade como indisponível
                printf("Agente com ID %d tornou-se indisponível.\n", id_agente);
                return; // Agente encontrado e disponibilidade alterada, portanto, saia da função
            }
        }
        // Se o loop terminar sem retornar, o agente com o ID fornecido não foi encontrado
        printf("Agente com ID %d não encontrado.\n", id_agente);
    } else {
        printf("Não existem agentes imobiliários cadastrados.\n");
    }
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

    // Contagem do número de agentes imobiliários válidos
    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (agente_imobiliario[i].id_agente != 0) {
            num_agentes++;
        }
    }

    if (num_agentes != 0) {
        printf("┌───────────────┬───────────────────┬───────────────────────┬──────────────┬───────────────────┬─────────────────────┬───────────────────────┐\n");
        printf("│   ID          │        Nome        │          NIF          │    Morada    │     Telefone      │ Data de Nascimento │   Disponibilidade   │\n");
        printf("├───────────────┼───────────────────┼───────────────────────┼──────────────┼───────────────────┼─────────────────────┼───────────────────────┤\n");

        // Iteração sobre o array e impressão dos detalhes de cada agente
        for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
            if (agente_imobiliario[i].id_agente != 0) {
                printf("│   %-11d │ %-17s │ %-21s │ %-12s │ %-17s │ %2d/%2d/%-12d │ %-19s │\n",
                       agente_imobiliario[i].id_agente,
                       agente_imobiliario[i].nome,
                       agente_imobiliario[i].NIF,
                       agente_imobiliario[i].morada,
                       agente_imobiliario[i].telefone,
                       agente_imobiliario[i].dia_nascimento,
                       agente_imobiliario[i].mes_nascimento,
                       agente_imobiliario[i].ano_nascimento,
                       (agente_imobiliario[i].disponibilidade == 1) ? "Disponível" : "Indisponível");
                printf("├───────────────┼───────────────────┼───────────────────────┼──────────────┼───────────────────┼─────────────────────┼───────────────────────┤\n");
            }
        }

        printf("Total de Agentes Imobiliários: %d\n", num_agentes);
    } else {
        printf("Não existem agentes imobiliários cadastrados.\n");
        return -1;
    }

    return 0;
}

int listar_agente_imobiliario_disponiveis(AGENTE agente_imobiliario[]) {
    int num_agentes = 0;

    // Contagem do número de agentes imobiliários válidos
    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (agente_imobiliario[i].id_agente != 0) {
            num_agentes++;
        }
    }

    if (num_agentes != 0) {
        printf("┌───────────────┬───────────────────┬───────────────────────┬──────────────┬───────────────────┬─────────────────────┬───────────────────────┐\n");
        printf("│   ID          │        Nome        │          NIF          │    Morada    │     Telefone      │ Data de Nascimento │   Disponibilidade   │\n");
        printf("├───────────────┼───────────────────┼───────────────────────┼──────────────┼───────────────────┼─────────────────────┼───────────────────────┤\n");

        // Iteração sobre o array e impressão dos detalhes de cada agente
        for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
            if (agente_imobiliario[i].id_agente != 0 && agente_imobiliario[i].disponibilidade == 1) {
                printf("│   %-11d │ %-17s │ %-21s │ %-12s │ %-17s │ %2d/%2d/%-12d │ %-19s │\n",
                       agente_imobiliario[i].id_agente,
                       agente_imobiliario[i].nome,
                       agente_imobiliario[i].NIF,
                       agente_imobiliario[i].morada,
                       agente_imobiliario[i].telefone,
                       agente_imobiliario[i].dia_nascimento,
                       agente_imobiliario[i].mes_nascimento,
                       agente_imobiliario[i].ano_nascimento,
                       (agente_imobiliario[i].disponibilidade == 1) ? "Disponível" : "Indisponível");
                printf("├───────────────┼───────────────────┼───────────────────────┼──────────────┼───────────────────┼─────────────────────┼───────────────────────┤\n");
            }
        }

        printf("Total de Agentes Imobiliários: %d\n", num_agentes);
    } else {
        printf("Não existem agentes imobiliários cadastrados.\n");
        return -1;
    }

    return 0;
}

int listar_agente_imobiliario_disponiveis_propriedade(AGENTE agente_imobiliario[]) {
    int num_agentes = 0;

    // Contagem do número de agentes imobiliários válidos
    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (agente_imobiliario[i].id_agente != 0) {
            num_agentes++;
        }
    }

    if (num_agentes != 0) {
        printf("┌───────────────┬───────────────────┬───────────────────────┬──────────────┬───────────────────┬─────────────────────┬───────────────────────┐\n");
        printf("│   ID          │        Nome        │          NIF          │    Morada    │     Telefone      │ Data de Nascimento │   Disponibilidade   │\n");
        printf("├───────────────┼───────────────────┼───────────────────────┼──────────────┼───────────────────┼─────────────────────┼───────────────────────┤\n");

        // Iteração sobre o array e impressão dos detalhes de cada agente
        for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
            if (agente_imobiliario[i].id_agente != 0 && agente_imobiliario[i].disponibilidade == 1) {
                printf("│   %-11d │ %-17s │ %-21s │ %-12s │ %-17s │ %2d/%2d/%-12d │ %-19s │\n",
                       agente_imobiliario[i].id_agente,
                       agente_imobiliario[i].nome,
                       agente_imobiliario[i].NIF,
                       agente_imobiliario[i].morada,
                       agente_imobiliario[i].telefone,
                       agente_imobiliario[i].dia_nascimento,
                       agente_imobiliario[i].mes_nascimento,
                       agente_imobiliario[i].ano_nascimento,
                       (agente_imobiliario[i].disponibilidade == 1) ? "Disponível" : "Indisponível");
                printf("├───────────────┼───────────────────┼───────────────────────┼──────────────┼───────────────────┼─────────────────────┼───────────────────────┤\n");
            }
        }

        printf("Total de Agentes Imobiliários: %d\n", num_agentes);
    } else {
        printf("Não existem agentes imobiliários cadastrados.\n");
        return -1;
    }

    return 0;
}

int verificar_agente_imobiliario_disponiveis(AGENTE agente_imobiliario[], int id_agente_verificar) {

    // Contagem do número de agentes imobiliários válidos
    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (agente_imobiliario[i].id_agente != 0 &&
        agente_imobiliario[i].id_agente == id_agente_verificar &&
        agente_imobiliario[i].disponibilidade == 1)
        {
            return 0;
        }
    }

    printf("\nErro ao encontrar agente. Introduziu um identificador inválido !!!!\n");

    return -1;

}

int verifica_agente_casa_responsavel(AGENTE agente_imobiliario[], LISTA_PROPRIEDADE *iniLista, int id_propriedade_verificar){

    int agente_imobiliario_correto=-1;

// Verifica se a lista de propriedades está vazia
    if (iniLista == NULL) {
        printf("Lista de propriedades vazia\n");
        return agente_imobiliario_correto;
    }

    // Ponteiro auxiliar para percorrer a lista de propriedades
    LISTA_PROPRIEDADE *aux = iniLista;

    // Percorre a lista de propriedades
    while (aux != NULL) {
        // Verifica se encontrou a propriedade com o ID especificado
        if (aux->propriedade.id_propriedade == id_propriedade_verificar) {
            // Obtém o ID do agente imobiliário responsável por esta propriedade
            agente_imobiliario_correto = aux->propriedade.id_agente_responsavel;
            break;  // Sai do loop, pois encontrou a propriedade
        }
        // Move para a próxima propriedade na lista
        aux = aux->seguinte;
    }

    // Verifica se a propriedade foi encontrada
    if (agente_imobiliario_correto == -1) {
        printf("Propriedade não encontrada\n");
    }

    return agente_imobiliario_correto;
}




