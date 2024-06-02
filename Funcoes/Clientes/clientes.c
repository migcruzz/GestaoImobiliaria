#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../VariaveisGlobais/variaveis_globais.h"
#include "../../TiposDados/TiposDados.h"




int criar_cliente(CLIENTE clientes[]) {
    CLIENTE novoCliente;

    printf("Nome: ");
    fflush(stdin);
    fgets(novoCliente.nome, sizeof(novoCliente.nome), stdin);
    novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0'; // Remove newline character

    printf("Palavra-Passe: ");
    fflush(stdin);
    fgets(novoCliente.palavra_passe, sizeof(novoCliente.palavra_passe), stdin);
    novoCliente.palavra_passe[strcspn(novoCliente.palavra_passe, "\n")] = '\0'; // Remove newline character

    printf("NIF: ");
    fflush(stdin);
    fgets(novoCliente.NIF, sizeof(novoCliente.NIF), stdin);
    novoCliente.NIF[strcspn(novoCliente.NIF, "\n")] = '\0'; // Remove newline character

    printf("Telefone: ");
    fflush(stdin);
    fgets(novoCliente.telefone, sizeof(novoCliente.telefone), stdin);
    novoCliente.telefone[strcspn(novoCliente.telefone, "\n")] = '\0'; // Remove newline character

    novoCliente.role = 1; // Definindo o papel do cliente

    int posicaoInserir = -1;

    for (int i = 0; i < MAX_CLIENTES; i++) {
        if (clientes[i].id_cliente == 0) {
            posicaoInserir = i;
            break;
        }
    }

    if (posicaoInserir != -1) {
        strcpy(clientes[posicaoInserir].nome, novoCliente.nome);
        strcpy(clientes[posicaoInserir].NIF, novoCliente.NIF);
        strcpy(clientes[posicaoInserir].telefone, novoCliente.telefone);
        strcpy(clientes[posicaoInserir].palavra_passe, novoCliente.palavra_passe);
        clientes[posicaoInserir].role = novoCliente.role;
        clientes[posicaoInserir].id_cliente = posicaoInserir + 1;

        return 0;
    } else {
        printf("\nNão há lugares disponíveis!\n");
        return -1;
    }
}

void inserir_clientes_em_arquivo(CLIENTE clientes[]) {
    FILE *arquivo = fopen("../Armazenamento/Texto/Clientes.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < MAX_CLIENTES; i++) {
        if (clientes[i].id_cliente != 0) {
            fprintf(arquivo, "%d\n", clientes[i].id_cliente);
            fprintf(arquivo, "%s\n", clientes[i].nome);
            fprintf(arquivo, "%s\n", clientes[i].palavra_passe);
            fprintf(arquivo, "%s\n", clientes[i].NIF);
            fprintf(arquivo, "%s\n", clientes[i].telefone);
            fprintf(arquivo, "%d\n", clientes[i].role);
        }
    }

    fclose(arquivo);
}


void carregar_clientes_do_arquivo(CLIENTE clientes[]) {
    FILE *arquivo = fopen("../Armazenamento/Texto/Clientes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int index = 0;

    while (fscanf(arquivo, "%d %[^\n] %[^\n] %[^\n] %[^\n] %d\n", &clientes[index].id_cliente, clientes[index].nome, clientes[index].palavra_passe, clientes[index].NIF, clientes[index].telefone, &clientes[index].role) != EOF) {
        index++;
    }

    fclose(arquivo);

    // Verificação dos dados carregados
    printf("Clientes carregados do arquivo:\n");
    for (int i = 0; i < index; i++) {
        printf("ID: %d, Nome: %s, Palavra-passe: %s, NIF: %s, Telefone: %s, Role: %d\n", clientes[i].id_cliente, clientes[i].nome, clientes[i].palavra_passe, clientes[i].NIF, clientes[i].telefone, clientes[i].role);
    }
}


void editar_cliente(CLIENTE clientes[]) {
    int id_cliente;

    printf("Digite o ID do cliente que deseja editar: ");
    scanf("%d", &id_cliente);

    // Procurar o cliente com o ID especificado
    int encontrado = 0;
    int indice_cliente = -1; // Índice do cliente a ser editado
    for (int i = 0; i < MAX_CLIENTES; i++) {
        if (clientes[i].id_cliente == id_cliente) {
            encontrado = 1;
            indice_cliente = i; // Armazenar o índice do cliente
            break;
        }
    }

    if (!encontrado) {
        printf("Não existe cliente com o ID especificado.\n");
        return;
    }

    // Limpar o buffer do teclado
    fflush(stdin);

    // Resto do código de edição...

    printf("Nome: ");
    fflush(stdin);
    fgets(clientes[indice_cliente].nome, sizeof(clientes[indice_cliente].nome), stdin);
    clientes[indice_cliente].nome[strcspn(clientes[indice_cliente].nome, "\n")] = '\0';

    printf("Palavra-passe: ");
    fflush(stdin);
    fgets(clientes[indice_cliente].palavra_passe, sizeof(clientes[indice_cliente].palavra_passe), stdin);
    clientes[indice_cliente].palavra_passe[strcspn(clientes[indice_cliente].palavra_passe, "\n")] = '\0';

    printf("NIF: ");
    fflush(stdin);
    fgets(clientes[indice_cliente].NIF, sizeof(clientes[indice_cliente].NIF), stdin);
    clientes[indice_cliente].NIF[strcspn(clientes[indice_cliente].NIF, "\n")] = '\0';

    printf("Telefone: ");
    fflush(stdin);
    fgets(clientes[indice_cliente].telefone, sizeof(clientes[indice_cliente].telefone), stdin);
    clientes[indice_cliente].telefone[strcspn(clientes[indice_cliente].telefone, "\n")] = '\0';

    printf("Cliente editado com sucesso.\n");
}

void editar_cliente_logado(CLIENTE clientes[], int id_cliente_logado) {
    // Encontrar o cliente com o ID correspondente ao cliente logado
    int indice_cliente = -1;
    for (int i = 0; i < MAX_CLIENTES; i++) {
        if (clientes[i].id_cliente == id_cliente_logado) {
            indice_cliente = i;
            break;
        }
    }

    if (indice_cliente == -1) {
        printf("Erro: Cliente não encontrado.\n");
        return;
    }

    // Limpar o buffer do teclado
    fflush(stdin);

    // Resto do código de edição...

    printf("Nome: ");
    fflush(stdin);
    fgets(clientes[indice_cliente].nome, sizeof(clientes[indice_cliente].nome), stdin);
    clientes[indice_cliente].nome[strcspn(clientes[indice_cliente].nome, "\n")] = '\0';

    printf("Palavra-passe: ");
    fflush(stdin);
    fgets(clientes[indice_cliente].palavra_passe, sizeof(clientes[indice_cliente].palavra_passe), stdin);
    clientes[indice_cliente].palavra_passe[strcspn(clientes[indice_cliente].palavra_passe, "\n")] = '\0';

    printf("NIF: ");
    fflush(stdin);
    fgets(clientes[indice_cliente].NIF, sizeof(clientes[indice_cliente].NIF), stdin);
    clientes[indice_cliente].NIF[strcspn(clientes[indice_cliente].NIF, "\n")] = '\0';

    printf("Telefone: ");
    fflush(stdin);
    fgets(clientes[indice_cliente].telefone, sizeof(clientes[indice_cliente].telefone), stdin);
    clientes[indice_cliente].telefone[strcspn(clientes[indice_cliente].telefone, "\n")] = '\0';

    printf("Cliente editado com sucesso.\n");
}


int listar_cliente_alfabeto(CLIENTE clientes[]) {
    int num_clientes = 0;

    // Contagem do número de clientes válidos
    for (int i = 0; i < MAX_CLIENTES; i++) {
        if (clientes[i].id_cliente != 0) {
            num_clientes++;
        }
    }

    if (num_clientes != 0) {
        // Alocação de memória para um novo array de clientes (ordenados)
        CLIENTE *clientes_ordenados = (CLIENTE *)calloc(num_clientes, sizeof(CLIENTE));

        int indice_ordenados = 0;
        for (int i = 0; i < MAX_CLIENTES; i++) {
            if (clientes[i].id_cliente != 0) {
                clientes_ordenados[indice_ordenados++] = clientes[i];
            }
        }

        // Ordenação dos clientes por nome usando o algoritmo Bubble Sort
        for (int i = 0; i < num_clientes - 1; i++) {
            for (int j = 0; j < num_clientes - i - 1; j++) {
                if (strcmp(clientes_ordenados[j].nome, clientes_ordenados[j + 1].nome) > 0) {
                    CLIENTE temp = clientes_ordenados[j];
                    clientes_ordenados[j] = clientes_ordenados[j + 1];
                    clientes_ordenados[j + 1] = temp;
                }
            }
        }

        // Impressão dos detalhes de cada cliente em uma tabela
        printf("┌───────────────┬───────────────────┬───────────────────────┬──────────────┬──────────────┬───────────┐\n");
        printf("│   ID          │        Nome        │          NIF          │    Telefone   │    Role      │\n");
        printf("├───────────────┼───────────────────┼───────────────────────┼──────────────┼──────────────┼───────────┤\n");
        for (int i = 0; i < num_clientes; i++) {
            printf("│   %-11d │ %-17s │ %-21s │ %-12s │ %-12d │\n",
                   clientes_ordenados[i].id_cliente,
                   clientes_ordenados[i].nome,
                   clientes_ordenados[i].NIF,
                   clientes_ordenados[i].telefone,
                   clientes_ordenados[i].role);
            printf("├───────────────┼───────────────────┼───────────────────────┼──────────────┼──────────────┼───────────┤\n");
        }

        free(clientes_ordenados);

        return 0;
    } else {
        printf("\nNão existem clientes!\n");
        return -1;
    }
}


int listar_cliente_nif(CLIENTE clientes[]) {
    int num_clientes = 0;

    // Contagem do número de clientes válidos
    for (int i = 0; i < MAX_CLIENTES; i++) {
        if (clientes[i].id_cliente != 0) {
            num_clientes++;
        }
    }

    if (num_clientes != 0) {
        // Alocação de memória para um novo array de clientes (ordenados)
        CLIENTE *clientes_ordenados = (CLIENTE *)calloc(num_clientes, sizeof(CLIENTE));

        int indice_ordenados = 0;
        for (int i = 0; i < MAX_CLIENTES; i++) {
            if (clientes[i].id_cliente != 0) {
                clientes_ordenados[indice_ordenados++] = clientes[i];
            }
        }

        // Ordenação dos clientes por NIF usando o algoritmo Bubble Sort
        for (int i = 0; i < num_clientes - 1; i++) {
            for (int j = 0; j < num_clientes - i - 1; j++) {
                if (strcmp(clientes_ordenados[j].NIF, clientes_ordenados[j + 1].NIF) > 0) {
                    CLIENTE temp = clientes_ordenados[j];
                    clientes_ordenados[j] = clientes_ordenados[j + 1];
                    clientes_ordenados[j + 1] = temp;
                }
            }
        }

        // Impressão dos detalhes de cada cliente em uma tabela
        printf("┌───────────────┬───────────────────┬───────────────────────┬──────────────┬──────────────┬───────────┐\n");
        printf("│   ID          │        Nome        │          NIF          │    Telefone   │    Role      │\n");
        printf("├───────────────┼───────────────────┼───────────────────────┼──────────────┼──────────────┼───────────┤\n");
        for (int i = 0; i < num_clientes; i++) {
            printf("│   %-11d │ %-17s │ %-21s │ %-12s │ %-12d │\n",
                   clientes_ordenados[i].id_cliente,
                   clientes_ordenados[i].nome,
                   clientes_ordenados[i].NIF,
                   clientes_ordenados[i].telefone,
                   clientes_ordenados[i].role);
            printf("├───────────────┼───────────────────┼───────────────────────┼──────────────┼──────────────┼───────────┤\n");
        }

        free(clientes_ordenados);

        return 0;
    } else {
        printf("\nNão existem clientes!\n");
        return -1;
    }
}


int remover_cliente(CLIENTE clientes[], int id_procura) {
    for (int i = 0; i < MAX_CLIENTES; i++) {
        if (clientes[i].id_cliente == id_procura) {
            // Limpar os dados do cliente
            memset(&clientes[i], 0, sizeof(CLIENTE));
            printf("Cliente removido com sucesso.\n");
            return 0;
        }
    }

    printf("Não existe cliente com o ID especificado.\n");
    return -1;
}

