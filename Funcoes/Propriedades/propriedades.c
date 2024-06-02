#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../VariaveisGlobais/variaveis_globais.h"
#include "../../TiposDados/TiposDados.h"
#include "../AgentesImobiliarios/agentes_imobiliarios.h"

int procuraMaiorID_ou_ID_Disponivel(LISTA_PROPRIEDADE **iniLista){

    int maiorID=0;
    int menorID =0;
    LISTA_PROPRIEDADE *aux;



    for(aux = *iniLista; aux != NULL; aux = aux->seguinte){
        if(aux->propriedade.id_propriedade > maiorID){
            maiorID = aux -> propriedade.id_propriedade;
        }
    }

    menorID = maiorID;

    for(aux = *iniLista; aux != NULL; aux = aux->seguinte){
        if(aux->propriedade.id_propriedade < menorID){
            menorID = aux -> propriedade.id_propriedade;
        }
    }

    if(menorID-1 > 0 ){
        menorID = menorID -1;
        return menorID;
    }else{
        if (maiorID != 0){
            return maiorID+1;
        }else{
            return 1;
        }
    }



}

int criar_propriedade(LISTA_PROPRIEDADE **iniLista, LISTA_PROPRIEDADE **fimLista, AGENTE agente_imobiliario[]) {
    LISTA_PROPRIEDADE *novo = NULL;
    PROPRIEDADE propriedade_nova;
    int tipo_comercial = -1;
    int tipo_imovel = -1;
    int popularidade = -1;
    int agente_selecionado = -1;



    propriedade_nova.id_propriedade = procuraMaiorID_ou_ID_Disponivel(iniLista);
    propriedade_nova.negocio_concluido = 0;

    novo = (LISTA_PROPRIEDADE *) calloc(1, sizeof(LISTA_PROPRIEDADE));
    if (novo == NULL) {
        printf("Erro ao inserir nova propriedade \n");
        return -1;
    }
    printf("\nDados da nova propriedade:\n");

    printf("\nAssociar agente a nova casa:\n");



    while(1){
    listar_agente_imobiliario_disponiveis(agente_imobiliario);

        int verificador =-1;
        printf("\nSelecione um agente:\n");
        scanf("%d",&agente_selecionado);
       verificador = verificar_agente_imobiliario_disponiveis(agente_imobiliario,agente_selecionado);
       if(verificador == 0){
           propriedade_nova.id_agente_responsavel = agente_selecionado;
           break;
       }else{
           printf("\nAgente inválido, tente novamente !\n");
       }
    }

    // Recolher dados do utilizador:

    printf("Nome da propriedade: ");
    fflush(stdin);
    fgets(propriedade_nova.nome, sizeof(propriedade_nova.nome), stdin);
    propriedade_nova.nome[strcspn(propriedade_nova.nome, "\n")] = '\0'; // Remove newline character

    // Recolher morada
    printf("Morada: ");
    fgets(propriedade_nova.morada, sizeof(propriedade_nova.morada), stdin);
    propriedade_nova.morada[strcspn(propriedade_nova.morada, "\n")] = '\0'; // Remove newline character

    do {
        printf("Tipo de comércio:\n");
        printf("1. Vender\n");
        printf("2. Arrendar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &tipo_comercial);
        getchar(); // Limpar o buffer de entrada

        if (tipo_comercial == 1) {
            strcpy(propriedade_nova.tipo_comercial, "Vender");
            break;
        } else if (tipo_comercial == 2) {
            strcpy(propriedade_nova.tipo_comercial, "Arrendar");
            break;
        } else {
            printf("Opção inválida. Tipo de comércio não definido.\n");
        }
    } while (tipo_comercial != 1 && tipo_comercial != 2);

    printf("Preço: ");
    scanf("%f", &propriedade_nova.preco);
    getchar(); // Limpar o buffer de entrada

    do {
        printf("Tipo de imóvel:\n");
        printf("1. Casa\n");
        printf("2. Escritório\n");
        printf("3. Apartamento\n");
        printf("4. Garagem\n");
        printf("5. Armazém\n");
        printf("Escolha uma opção: ");
        scanf("%d", &tipo_imovel);
        getchar(); // Limpar o buffer de entrada

        if (tipo_imovel == 1) {
            strcpy(propriedade_nova.tipo_imovel, "Casa");
            break;
        } else if (tipo_imovel == 2) {
            strcpy(propriedade_nova.tipo_imovel, "Escritório");
            break;
        } else if (tipo_imovel == 3) {
            strcpy(propriedade_nova.tipo_imovel, "Apartamento");
            break;
        } else if (tipo_imovel == 4) {
            strcpy(propriedade_nova.tipo_imovel, "Garagem");
            break;
        } else if (tipo_imovel == 5) {
            strcpy(propriedade_nova.tipo_imovel, "Armazém");
            break;
        } else {
            printf("Opção inválida. Tipo de imóvel não definido.\n");
        }
    } while (tipo_imovel != 1 && tipo_imovel != 2 && tipo_imovel != 3 && tipo_imovel != 4 && tipo_imovel != 5);

    do {
        printf("Popularidade:\n");
        printf("1. Popular\n");
        printf("2. Não Popular\n");
        scanf("%d", &popularidade);
        getchar(); // Limpar o buffer de entrada

        if (popularidade == 1) {
            propriedade_nova.popular = 1;
        } else if (popularidade == 2) {
            propriedade_nova.popular = 0;
        } else {
            printf("Opção inválida. Por favor, escolha 1 para 'Popular' ou 2 para 'Não Popular'.\n");
        }
    } while (popularidade != 1 && popularidade != 2);

    novo->propriedade = propriedade_nova;
    novo->seguinte = NULL;
    novo->anterior = NULL;

    if (*iniLista == NULL) {
        *iniLista = novo;
        *fimLista = novo;
    } else {
        (*fimLista)->seguinte = novo;
        novo->anterior = *fimLista;
        *fimLista = novo;
    }

    printf("Propriedade criada com sucesso!\n");
    return 0;
}

void imprime_todas_propriedades(LISTA_PROPRIEDADE *iniLista) {
    if (iniLista == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    // Contagem do número total de propriedades
    int contador = 0;
    LISTA_PROPRIEDADE *aux;
    for (aux = iniLista; aux != NULL; aux = aux->seguinte) {
        contador++;
    }

    // Ordenação da lista por IDs de forma crescente
    LISTA_PROPRIEDADE *propriedades[contador];
    int i = 0;
    for (aux = iniLista; aux != NULL; aux = aux->seguinte) {
        propriedades[i++] = aux;
    }

    // Bubble sort para ordenar a lista de propriedades por IDs
    for (int i = 0; i < contador - 1; i++) {
        for (int j = 0; j < contador - i - 1; j++) {
            if (propriedades[j]->propriedade.id_propriedade > propriedades[j + 1]->propriedade.id_propriedade) {
                LISTA_PROPRIEDADE *temp = propriedades[j];
                propriedades[j] = propriedades[j + 1];
                propriedades[j + 1] = temp;
            }
        }
    }

    // Impressão formatada das propriedades ordenadas
    printf("┌────┬──────────────────┬──────────────────────┬────────┬─────────┬───────────────────────────────┬───────────────┐\n");
    printf("│ ID │      Nome        │        Morada        │ Preço  │ Popular │   Agente Imobiliário Resp.    │ Negócio Concl. │\n");
    printf("├────┼──────────────────┼──────────────────────┼────────┼─────────┼───────────────────────────────┼───────────────┤\n");
    for (int i = 0; i < contador; i++) {
        LISTA_PROPRIEDADE *prop = propriedades[i];
        printf("│ %2d │ %-16s │ %-20s │ %6.2f │   %s   │ %-29d │ %-13s │\n",
               prop->propriedade.id_propriedade,
               prop->propriedade.nome,
               prop->propriedade.morada,
               prop->propriedade.preco,
               prop->propriedade.popular == 1 ? "Sim" : "Não",
               prop->propriedade.id_agente_responsavel,
               prop->propriedade.negocio_concluido == 1 ? "Sim" : "Não");
    }
    printf("└────┴──────────────────┴──────────────────────┴────────┴─────────┴───────────────────────────────┴───────────────┘\n");

}

void imprime_todas_propriedades_populares_negocio_por_concluir(LISTA_PROPRIEDADE *iniLista) {
    if (iniLista == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    // Contagem do número total de propriedades
    int contador = 0;
    LISTA_PROPRIEDADE *aux;
    for (aux = iniLista; aux != NULL; aux = aux->seguinte) {
        contador++;
    }

    // Ordenação da lista por IDs de forma crescente
    LISTA_PROPRIEDADE *propriedades[contador];
    int i = 0;
    for (aux = iniLista; aux != NULL; aux = aux->seguinte) {
        propriedades[i++] = aux;
    }

    // Bubble sort para ordenar a lista de propriedades por IDs
    for (int i = 0; i < contador - 1; i++) {
        for (int j = 0; j < contador - i - 1; j++) {
            if (propriedades[j]->propriedade.id_propriedade > propriedades[j + 1]->propriedade.id_propriedade) {
                LISTA_PROPRIEDADE *temp = propriedades[j];
                propriedades[j] = propriedades[j + 1];
                propriedades[j + 1] = temp;
            }
        }
    }

    // Impressão formatada das propriedades ordenadas
    printf("┌────┬──────────────────┬──────────────────────┬────────┬─────────┬───────────────────────────────┬───────────────┐\n");
    printf("│ ID │      Nome        │        Morada        │ Preço  │ Popular │   Agente Imobiliário Resp.    │ Negócio Concl. │\n");
    printf("├────┼──────────────────┼──────────────────────┼────────┼─────────┼───────────────────────────────┼───────────────┤\n");
    for (int i = 0; i < contador; i++) {
        LISTA_PROPRIEDADE *prop = propriedades[i];
        if (prop->propriedade.popular == 1 && prop ->propriedade.negocio_concluido == 0) {
            printf("│ %2d │ %-16s │ %-20s │ %6.2f │   %s   │ %-29d │ %-13s │\n",
                   prop->propriedade.id_propriedade,
                   prop->propriedade.nome,
                   prop->propriedade.morada,
                   prop->propriedade.preco,
                   prop->propriedade.popular == 1 ? "Sim" : "Não",
                   prop->propriedade.id_agente_responsavel,
                   prop->propriedade.negocio_concluido == 1 ? "Sim" : "Não");
        }
    }
    printf("└────┴──────────────────┴──────────────────────┴────────┴─────────┴───────────────────────────────┴───────────────┘\n");
}

void imprime_todas_propriedades_nao_populares_negocio_por_concluir(LISTA_PROPRIEDADE *iniLista) {
    if (iniLista == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    // Contagem do número total de propriedades
    int contador = 0;
    LISTA_PROPRIEDADE *aux;
    for (aux = iniLista; aux != NULL; aux = aux->seguinte) {
        contador++;
    }

    // Ordenação da lista por IDs de forma crescente
    LISTA_PROPRIEDADE *propriedades[contador];
    int i = 0;
    for (aux = iniLista; aux != NULL; aux = aux->seguinte) {
        propriedades[i++] = aux;
    }

    // Bubble sort para ordenar a lista de propriedades por IDs
    for (int i = 0; i < contador - 1; i++) {
        for (int j = 0; j < contador - i - 1; j++) {
            if (propriedades[j]->propriedade.id_propriedade > propriedades[j + 1]->propriedade.id_propriedade) {
                LISTA_PROPRIEDADE *temp = propriedades[j];
                propriedades[j] = propriedades[j + 1];
                propriedades[j + 1] = temp;
            }
        }
    }

    // Impressão formatada das propriedades ordenadas
    printf("┌────┬──────────────────┬──────────────────────┬────────┬─────────┬───────────────────────────────┬───────────────┐\n");
    printf("│ ID │      Nome        │        Morada        │ Preço  │ Popular │   Agente Imobiliário Resp.    │ Negócio Concl. │\n");
    printf("├────┼──────────────────┼──────────────────────┼────────┼─────────┼───────────────────────────────┼───────────────┤\n");
    for (int i = 0; i < contador; i++) {
        LISTA_PROPRIEDADE *prop = propriedades[i];
        if (prop->propriedade.popular == 0 && prop ->propriedade.negocio_concluido == 0) {
            printf("│ %2d │ %-16s │ %-20s │ %6.2f │   %s   │ %-29d │ %-13s │\n",
                   prop->propriedade.id_propriedade,
                   prop->propriedade.nome,
                   prop->propriedade.morada,
                   prop->propriedade.preco,
                   prop->propriedade.popular == 1 ? "Sim" : "Não",
                   prop->propriedade.id_agente_responsavel,
                   prop->propriedade.negocio_concluido == 1 ? "Sim" : "Não");
        }
    }
    printf("└────┴──────────────────┴──────────────────────┴────────┴─────────┴───────────────────────────────┴───────────────┘\n");
}

void imprime_todas_propriedades_nao_populares(LISTA_PROPRIEDADE *iniLista) {
    if (iniLista == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    // Contagem do número total de propriedades
    int contador = 0;
    LISTA_PROPRIEDADE *aux;
    for (aux = iniLista; aux != NULL; aux = aux->seguinte) {
        contador++;
    }

    // Ordenação da lista por IDs de forma crescente
    LISTA_PROPRIEDADE *propriedades[contador];
    int i = 0;
    for (aux = iniLista; aux != NULL; aux = aux->seguinte) {
        propriedades[i++] = aux;
    }

    // Bubble sort para ordenar a lista de propriedades por IDs
    for (int i = 0; i < contador - 1; i++) {
        for (int j = 0; j < contador - i - 1; j++) {
            if (propriedades[j]->propriedade.id_propriedade > propriedades[j + 1]->propriedade.id_propriedade) {
                LISTA_PROPRIEDADE *temp = propriedades[j];
                propriedades[j] = propriedades[j + 1];
                propriedades[j + 1] = temp;
            }
        }
    }

    // Impressão formatada das propriedades ordenadas
    printf("┌────┬──────────────────┬──────────────────────┬────────┬─────────┬───────────────────────────────┬───────────────┐\n");
    printf("│ ID │      Nome        │        Morada        │ Preço  │ Popular │   Agente Imobiliário Resp.    │ Negócio Concl. │\n");
    printf("├────┼──────────────────┼──────────────────────┼────────┼─────────┼───────────────────────────────┼───────────────┤\n");
    for (int i = 0; i < contador; i++) {
        LISTA_PROPRIEDADE *prop = propriedades[i];
        if (prop->propriedade.popular == 0) {
            printf("│ %2d │ %-16s │ %-20s │ %6.2f │   %s   │ %-29d │ %-13s │\n",
                   prop->propriedade.id_propriedade,
                   prop->propriedade.nome,
                   prop->propriedade.morada,
                   prop->propriedade.preco,
                   prop->propriedade.popular == 1 ? "Sim" : "Não",
                   prop->propriedade.id_agente_responsavel,
                   prop->propriedade.negocio_concluido == 1 ? "Sim" : "Não");
        }
    }
    printf("└────┴──────────────────┴──────────────────────┴────────┴─────────┴───────────────────────────────┴───────────────┘\n");
}

void imprime_todas_propriedades_populares(LISTA_PROPRIEDADE *iniLista) {
    if (iniLista == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    // Contagem do número total de propriedades
    int contador = 0;
    LISTA_PROPRIEDADE *aux;
    for (aux = iniLista; aux != NULL; aux = aux->seguinte) {
        contador++;
    }

    // Ordenação da lista por IDs de forma crescente
    LISTA_PROPRIEDADE *propriedades[contador];
    int i = 0;
    for (aux = iniLista; aux != NULL; aux = aux->seguinte) {
        propriedades[i++] = aux;
    }

    // Bubble sort para ordenar a lista de propriedades por IDs
    for (int i = 0; i < contador - 1; i++) {
        for (int j = 0; j < contador - i - 1; j++) {
            if (propriedades[j]->propriedade.id_propriedade > propriedades[j + 1]->propriedade.id_propriedade) {
                LISTA_PROPRIEDADE *temp = propriedades[j];
                propriedades[j] = propriedades[j + 1];
                propriedades[j + 1] = temp;
            }
        }
    }

    // Impressão formatada das propriedades ordenadas
    printf("┌────┬──────────────────┬──────────────────────┬────────┬─────────┬───────────────────────────────┬───────────────┐\n");
    printf("│ ID │      Nome        │        Morada        │ Preço  │ Popular │   Agente Imobiliário Resp.    │ Negócio Concl. │\n");
    printf("├────┼──────────────────┼──────────────────────┼────────┼─────────┼───────────────────────────────┼───────────────┤\n");
    for (int i = 0; i < contador; i++) {
        LISTA_PROPRIEDADE *prop = propriedades[i];
        if (prop->propriedade.popular == 1) {
            printf("│ %2d │ %-16s │ %-20s │ %6.2f │   %s   │ %-29d │ %-13s │\n",
                   prop->propriedade.id_propriedade,
                   prop->propriedade.nome,
                   prop->propriedade.morada,
                   prop->propriedade.preco,
                   prop->propriedade.popular == 1 ? "Sim" : "Não",
                   prop->propriedade.id_agente_responsavel,
                   prop->propriedade.negocio_concluido == 1 ? "Sim" : "Não");
        }
    }
    printf("└────┴──────────────────┴──────────────────────┴────────┴─────────┴───────────────────────────────┴───────────────┘\n");
}

int editar_propriedade(LISTA_PROPRIEDADE **iniLista, AGENTE agente_imobiliario[]) {
    int agente_responsavel = -1;

    if (iniLista == NULL || *iniLista == NULL) {
        printf("Lista Vazia\n");
        return -1;
    }

    int id_propriedade;
    LISTA_PROPRIEDADE *aux = NULL;

    do {
        printf("ID da propriedade a editar: ");
        scanf("%d", &id_propriedade);

        aux = *iniLista;
        while (aux != NULL) {
            if (aux->propriedade.id_propriedade == id_propriedade) {
                break;
            }
            aux = aux->seguinte; // vai averiguar se o nó seguinte contém o id até que seja nulo o apontador final
        }

        if (aux == NULL) {
            printf("ID não encontrado. Por favor, insira um ID válido.\n");
        }
    } while (aux == NULL);

    // Interação com o utilizador
    PROPRIEDADE propriedade_editada;

    // Recolher dados do utilizador:
    printf("Nome da propriedade: ");
    fflush(stdin);
    fgets(propriedade_editada.nome, sizeof(propriedade_editada.nome), stdin);
    propriedade_editada.nome[strcspn(propriedade_editada.nome, "\n")] = '\0'; // Remove newline character

    printf("\nMorada: "); // Adicionando um enter extra aqui
    fflush(stdin);
    fgets(propriedade_editada.morada, sizeof(propriedade_editada.morada), stdin);
    propriedade_editada.morada[strcspn(propriedade_editada.morada, "\n")] = '\0'; // Remove newline character

    while (1) {
        listar_agente_imobiliario_disponiveis(agente_imobiliario);

        int verificador = -1;
        printf("\nSelecione um agente:\n");
        scanf("%d", &agente_responsavel);
        verificador = verificar_agente_imobiliario_disponiveis(agente_imobiliario, agente_responsavel);
        if (verificador == 0) {
            propriedade_editada.id_agente_responsavel = agente_responsavel;
            break;
        } else {
            printf("\nAgente inválido, tente novamente !\n");
        }
    }

    int tipo_comercial = -1;
    do {
        printf("Tipo de comércio:\n");
        printf("1. Vender\n");
        printf("2. Arrendar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &tipo_comercial);

        if (tipo_comercial == 1) {
            strcpy(propriedade_editada.tipo_comercial, "Vender");
        } else if (tipo_comercial == 2) {
            strcpy(propriedade_editada.tipo_comercial, "Arrendar");
        } else {
            printf("Opção inválida. Tipo de comércio não definido.\n");
        }
    } while (tipo_comercial != 1 && tipo_comercial != 2);

    printf("Preço: ");
    scanf("%f", &propriedade_editada.preco);

    int tipo_imovel = -1;
    do {
        printf("Tipo de imóvel:\n");
        printf("1. Casa\n");
        printf("2. Escritório\n");
        printf("3. Apartamento\n");
        printf("4. Garagem\n");
        printf("5. Armazém\n");
        printf("Escolha uma opção: ");
        scanf("%d", &tipo_imovel);

        switch (tipo_imovel) {
            case 1:
                strcpy(propriedade_editada.tipo_imovel, "Casa");
                break;
            case 2:
                strcpy(propriedade_editada.tipo_imovel, "Escritório");
                break;
            case 3:
                strcpy(propriedade_editada.tipo_imovel, "Apartamento");
                break;
            case 4:
                strcpy(propriedade_editada.tipo_imovel, "Garagem");
                break;
            case 5:
                strcpy(propriedade_editada.tipo_imovel, "Armazém");
                break;
            default:
                printf("Opção inválida. Tipo de imóvel não definido.\n");
                break;
        }
    } while (tipo_imovel < 1 || tipo_imovel > 5);

    int popularidade = -1;
    do {
        printf("Popularidade:\n");
        printf("1. Popular\n");
        printf("2. Não Popular\n");
        scanf("%d", &popularidade);

        if (popularidade == 1) {
            propriedade_editada.popular = 1;
        } else if (popularidade == 2) {
            propriedade_editada.popular = 0;
        } else {
            printf("Opção inválida. Por favor, escolha 1 para 'Popular' ou 2 para 'Não Popular'.\n");
        }
    } while (popularidade != 1 && popularidade != 2);

    int negocio_concluido = -1;
    do {
        printf("Negócio Concluído:\n");
        printf("1. Sim\n");
        printf("2. Não\n");
        scanf("%d", &negocio_concluido);

        if (negocio_concluido == 1) {
            propriedade_editada.negocio_concluido = 1;
        } else if (negocio_concluido == 2) {
            propriedade_editada.negocio_concluido = 0;
        } else {
            printf("Opção inválida. Por favor, escolha 1 para 'Sim' ou 2 para 'Não'.\n");
        }
    } while (negocio_concluido != 1 && negocio_concluido != 2);

    // Atualiza a propriedade
    strcpy(aux->propriedade.nome, propriedade_editada.nome);
    strcpy(aux->propriedade.morada, propriedade_editada.morada);
    strcpy(aux->propriedade.tipo_imovel, propriedade_editada.tipo_imovel);
    strcpy(aux->propriedade.tipo_comercial, propriedade_editada.tipo_comercial);
    aux->propriedade.preco = propriedade_editada.preco;
    aux->propriedade.popular = propriedade_editada.popular;
    aux->propriedade.negocio_concluido = propriedade_editada.negocio_concluido;

    printf("Propriedade editada com sucesso!\n");

    return 0;
}

int remover_propriedade(LISTA_PROPRIEDADE **iniLista) {
    if (iniLista == NULL || *iniLista == NULL) {
        printf("Lista Vazia\n");
        return -1;
    }

    LISTA_PROPRIEDADE *aux = NULL;
    int id_propriedade;

    // Solicitar e verificar se o ID existe
    do {
        printf("ID da propriedade a remover: ");
        fflush(stdin);
        scanf("%d", &id_propriedade);

        aux = *iniLista;
        while (aux != NULL) {
            if (aux->propriedade.id_propriedade == id_propriedade) {
                break;
            }
            aux = aux->seguinte;
        }

        if (aux == NULL) {
            printf("ID não encontrado. Por favor, insira um ID válido.\n");
        }
    } while (aux == NULL);

    // Remover a propriedade
    LISTA_PROPRIEDADE *NoSeguinte = aux->seguinte;
    LISTA_PROPRIEDADE *NoAnterior = aux->anterior;

    if (NoAnterior != NULL) {
        NoAnterior->seguinte = NoSeguinte;
    } else {
        *iniLista = NoSeguinte;
    }

    if (NoSeguinte != NULL) {
        NoSeguinte->anterior = NoAnterior;
    }

    free(aux);
    printf("Propriedade removida.\n");
    return 0;
}

void limpar_memoria_lista_propriedades(LISTA_PROPRIEDADE **iniLista, LISTA_PROPRIEDADE **fimLista){

    LISTA_PROPRIEDADE *aux = NULL;
    LISTA_PROPRIEDADE *proximo = NULL;

    aux = *iniLista;

    *iniLista = NULL;
    *fimLista = NULL;

    while(aux != NULL){
        proximo = aux -> seguinte;

        free(aux);

        aux = proximo;
    }
}

void salvar_lista_propriedades_ficheiro_binario(LISTA_PROPRIEDADE *iniLista) {
    FILE *arquivo = fopen("../Armazenamento/Binario/Propriedades.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    LISTA_PROPRIEDADE *aux = iniLista;
    while (aux != NULL) {
        fwrite(&(aux->propriedade), sizeof(PROPRIEDADE), 1, arquivo);
        aux = aux->seguinte;
    }

    fclose(arquivo);
    printf("Lista salva com sucesso no arquivo binário.\n");
}

void carregar_lista_do_arquivo_binario(LISTA_PROPRIEDADE **iniLista, LISTA_PROPRIEDADE **fimLista) {
    FILE *arquivo = fopen("../Armazenamento/Binario/Propriedades.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    PROPRIEDADE propriedade_lida;

    while (fread(&propriedade_lida, sizeof(PROPRIEDADE), 1, arquivo) == 1) {
        LISTA_PROPRIEDADE *novo = (LISTA_PROPRIEDADE *)calloc(1, sizeof(LISTA_PROPRIEDADE));
        if (novo == NULL) {
            printf("Erro ao alocar memória para a nova propriedade.\n");
            fclose(arquivo);
            return;
        }

        novo->propriedade = propriedade_lida;
        novo->seguinte = NULL;

        if (*iniLista == NULL) {
            *iniLista = novo;
            *fimLista = novo;
        } else {
            (*fimLista)->seguinte = novo;
            novo->anterior = *fimLista;
            *fimLista = novo;
        }
    }

    if (!feof(arquivo)) {
        printf("Erro: leitura do arquivo incompleta.\n");
    }

    fclose(arquivo);
    printf("Lista carregada com sucesso do arquivo binário.\n");
}

