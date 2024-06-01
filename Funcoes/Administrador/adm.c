#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../VariaveisGlobais/variaveis_globais.h"
#include "../../TiposDados/TiposDados.h"


void remove_newline(char *string) {
    int tamanho = strlen(string);
    if (tamanho > 0 && string[tamanho - 1] == '\n') {
        string[tamanho - 1] = '\0';
    }
}

int inserir_administrador(ADMIN administrador[], ADMIN novo_administrador, int posicaoInserir) {

    if(administrador[posicaoInserir].id_admin != posicaoInserir + 1){administrador[posicaoInserir].id_admin = posicaoInserir + 1;}
    if (strcmp(administrador[posicaoInserir].nome, novo_administrador.nome) != 0){strcpy(administrador[posicaoInserir].nome, novo_administrador.nome);}
    if (strcmp(administrador[posicaoInserir].NIF, novo_administrador.NIF) != 0){strcpy(administrador[posicaoInserir].NIF, novo_administrador.NIF);}
    if (strcmp(administrador[posicaoInserir].palavra_passe, novo_administrador.palavra_passe) != 0){strcpy(administrador[posicaoInserir].palavra_passe, novo_administrador.palavra_passe);}
    if (administrador[posicaoInserir].role != novo_administrador.role){administrador[posicaoInserir].role = novo_administrador.role;}
    return 0;
}

int imprimir_administrador(ADMIN administrador[], int posicaoImprimir) {

    if(posicaoImprimir != 0){
        printf("-------------------------------------------------------------------------");
        printf("-------------------------------------------------------------------------");
        printf("\n O administrador com o nome %s tem os seguintes dados:\n",administrador[posicaoImprimir].nome);
        printf("-------------------------------------------------------------------------");
        printf("\nO NIF do administrador e %s\n",administrador[posicaoImprimir].NIF);
        printf("\nA palavra passe do administrador e %s\n",administrador[posicaoImprimir].palavra_passe);
        printf("\nA role do agente e %d\n",administrador[posicaoImprimir].role);
        printf("-------------------------------------------------------------------------");
    }

    return 0;
}

int criar_administrador(ADMIN administrador[], ADMIN novo_administrador) {

    int novaPosicao = -1;

    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (administrador[i].id_admin == 0) {
            novaPosicao = i;
            break;
        }
    }

    if (novaPosicao != -1) {
        inserir_administrador(administrador, novo_administrador, novaPosicao);
        return 0;
    }else{
        printf("\nNão tem lugares disponiveis !\n");
        return -1;
    }

}

// Para esta função apenas e editado a disponibilidade os restantes dados não serao inseridos por causa da outra função ter verificações que não o permitem (no caso de )

void editar_administrador(ADMIN administrador[], int id_admin_logado) {
    // Encontre o administrador com o ID correspondente ao administrador logado
    int posicao_array = -1;
    for (int i = 0; i < MAX_ADMINISTRADORES; i++) {
        if (administrador[i].id_admin == id_admin_logado) {
            posicao_array = i;
            break;
        }
    }

    if (posicao_array != -1) {
        // O administrador foi encontrado, permita que ele edite suas informações
        printf("Editar perfil do administrador:\n");
        printf("Bem-vindo, Admin!\n");

        // Imprimir informações em forma de tabela
        printf("+----------------------+\n");
        printf("|   Perfil do Admin    |\n");
        printf("+----------------------+\n");
        printf(" Nome: %-15s \n", administrador[posicao_array].nome);
        printf(" Palavra-passe: %-15s \n", administrador[posicao_array].palavra_passe);
        printf(" NIF: %-15s \n", administrador[posicao_array].NIF);
        printf("+----------------------+\n");

        // Solicitar novos dados
        printf("Novo nome: ");
        fflush(stdin);
        fgets(administrador[posicao_array].nome,29,stdin);
        remove_newline(administrador[posicao_array].nome);

        printf("Nova Palavra-passe: ");
        fflush(stdin);
        fgets(administrador[posicao_array].palavra_passe,20,stdin);
        remove_newline(administrador[posicao_array].palavra_passe);

        printf("Novo NIF: ");
        fflush(stdin);
        fgets(administrador[posicao_array].NIF,9,stdin);
        remove_newline(administrador[posicao_array].NIF);

        printf("Perfil do administrador atualizado com sucesso.\n");
    } else {
        // O administrador não foi encontrado
        printf("Erro: Administrador não encontrado.\n");
    }
}


// Aqui apenas vai inserir valores vazios (Zero no ID) ou NULL:
int remover_administrador(ADMIN administrador[],int id_procura){

    int id_encontrado =0;

    ADMIN admin_eliminar;

    strcpy(admin_eliminar.nome,"");
    strcpy(admin_eliminar.NIF, "");
    strcpy(admin_eliminar.palavra_passe, "");
    admin_eliminar.role = 0;


    for(int i =0; i < MAX_AGENTES_IMOBILIARIOS; i++){

        if(administrador[i].id_admin == id_procura){
            id_encontrado = administrador[i].id_admin;
        }
    }

    if(id_encontrado == 0){
        printf("\nNao existe o agente que pretende editar !!!\n");
        return -1;
    } else{
        inserir_administrador(administrador, admin_eliminar, id_encontrado);
        return 0;
    }
}

int carregar_do_ficheiro_administrador(ADMIN administrador[]) {
    ADMIN administrador_lido;
    FILE *ficheiro_administrador = fopen("../Armazenamento/Texto/Admins.txt", "r");
    if (ficheiro_administrador == NULL) {
        printf("\nErro a abrir o ficheiro de administradores !!!!\n");
        return -1;
    }

    printf("\nConteúdo do arquivo de administradores antes do carregamento:\n");
    char linha[100]; // Suponha que uma linha tenha no máximo 100 caracteres
    while (fgets(linha, sizeof(linha), ficheiro_administrador) != NULL) {
        // Remova o caractere de nova linha do final da linha
        linha[strcspn(linha, "\n")] = '\0';

        printf("%s\n", linha); // Imprimir linha do arquivo

        // Use sscanf para analisar a linha e extrair os campos
        if (sscanf(linha, "%29[^;];%9[^;];%d;%d;%20[^;]",
                   administrador_lido.nome,
                   administrador_lido.NIF,
                   &administrador_lido.role,
                   &administrador_lido.id_admin,
                   administrador_lido.palavra_passe) == 5) {
            inserir_administrador(administrador, administrador_lido, administrador_lido.id_admin - 1);
        } else {
            printf("Erro ao ler a linha: %s\n", linha);
        }
    }

    fclose(ficheiro_administrador);

    return 0;
}



int inserir_no_ficheiro_administrador(ADMIN administrador[]) {
    FILE *ficheiro_administrador = fopen("../Armazenamento/Texto/Admins.txt", "w");
    if (ficheiro_administrador == NULL) {
        printf("\nErro a abrir o ficheiro de administradores !!!!\n");
        return -1;
    }

    for (int i = 0; i < MAX_ADMINISTRADORES; i++) {
        if (administrador[i].id_admin != 0) {
            // Escrevendo os dados do novo administrador no arquivo
            fprintf(ficheiro_administrador, "%s;%s;%d;%d;%s\n",
                    administrador[i].nome,
                    administrador[i].NIF,
                    administrador[i].role,
                    administrador[i].id_admin,
                    administrador[i].palavra_passe);
        }
    }
    fclose(ficheiro_administrador);
    return 0;
}


int gerar_relatorio_agentes(AGENTE agentes[]) {
    int num_agentes = 0;

    // Contagem do número de agentes imobiliários válidos
    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (agentes[i].id_agente != 0) {
            num_agentes++;
        }
    }

    if (num_agentes != 0) {
        // Alocação de memória para um novo array de agentes (ordenados)
        AGENTE *agentes_ordenados = (AGENTE *)calloc(num_agentes, sizeof(AGENTE));

        int indice_ordenados = 0;
        for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
            if (agentes[i].id_agente != 0) {
                agentes_ordenados[indice_ordenados++] = agentes[i];
            }
        }

        // Ordenação dos agentes por NIF usando o algoritmo Bubble Sort
        for (int i = 0; i < num_agentes - 1; i++) {
            for (int j = 0; j < num_agentes - i - 1; j++) {
                if (strcmp(agentes_ordenados[j].NIF, agentes_ordenados[j + 1].NIF) > 0) {
                    AGENTE temp = agentes_ordenados[j];
                    agentes_ordenados[j] = agentes_ordenados[j + 1];
                    agentes_ordenados[j + 1] = temp;
                }
            }
        }

        // Abrir o arquivo para escrita
        FILE *arquivo = fopen("../Armazenamento/Texto/Relatorios_Agentes.txt", "w");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo para escrita.\n");
            free(agentes_ordenados);
            return -1;
        }

        // Escrever os detalhes de cada agente no arquivo
        fprintf(arquivo, "┌───────────────┬───────────────────┬───────────────────────┬──────────────┬───────────────────┬─────────────────────┬───────────────────────┐\n");
        fprintf(arquivo, "│   ID          │        Nome        │          NIF          │    Morada    │     Telefone      │ Data de Nascimento │   Disponibilidade   │\n");
        fprintf(arquivo, "├───────────────┼───────────────────┼───────────────────────┼──────────────┼───────────────────┼─────────────────────┼───────────────────────┤\n");
        for (int i = 0; i < num_agentes; i++) {
            fprintf(arquivo, "│   %-11d │ %-17s │ %-21s │ %-12s │ %-17s │ %2d/%2d/%-12d │ %-19s │\n",
                    agentes_ordenados[i].id_agente,
                    agentes_ordenados[i].nome,
                    agentes_ordenados[i].NIF,
                    agentes_ordenados[i].morada,
                    agentes_ordenados[i].telefone,
                    agentes_ordenados[i].dia_nascimento,
                    agentes_ordenados[i].mes_nascimento,
                    agentes_ordenados[i].ano_nascimento,
                    (agentes_ordenados[i].disponibilidade == 1) ? "Disponível" : "Indisponível");
            fprintf(arquivo, "├───────────────┼───────────────────┼───────────────────────┼──────────────┼───────────────────┼─────────────────────┼───────────────────────┤\n");
        }

        // Fechar o arquivo
        fclose(arquivo);

        free(agentes_ordenados);
        printf("Relatório gerado com sucesso em 'Relatorios_Agentes.txt'.\n");

        return 0;
    } else {
        printf("\nNão existem agentes!\n");
        return -1;
    }
}