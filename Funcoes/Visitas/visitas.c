#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../VariaveisGlobais/variaveis_globais.h"
#include "../../TiposDados/TiposDados.h"
#include <time.h>

// Trabalhar com formato 24H
// Dentro do programa todos os algoritmos vão ser no formato de minutos e só para o cliente vai ser mostrado


// Função para remover o caractere de nova linha de fgets
void remove_newline1(char *string) {
    int tamanho = strlen(string);
    if (tamanho > 0 && string[tamanho - 1] == '\n') {
        string[tamanho - 1] = '\0';
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

int verifica_dia_mes_ano(int dia, int mes, int ano){

    int ano_atual =0;

    // Forma de obter os anos atuais através da biblioteca time.h
    time_t seconds=time(NULL);
    struct tm* data_atual=localtime(&seconds);

    ano_atual =data_atual->tm_year + 1900;


    if(ano >= ano_atual ){
        switch (mes) {

            case 1: case 3: case 5: case 7: case 8: case 10:  case 12:

                if(dia >0 && dia <= 31){
                    return 0;
                }else{
                    printf("\nDia do mês inválidon\n");
                    return -1;}

                break;

            case 2:

                if((ano % 4 ==0)&&(ano % 100 != 0)&&(ano % 400 ==0)){
                    if(dia >0 && dia <= 29){
                        return 0;
                    }else{
                        return -1;
                    }
                }else{
                    if(dia >0 && dia <= 29){
                        return 0;
                    }
                    else{
                        return -1;
                    }
                }

                break;


            case 4: case 6: case 9: case 11:

                if(dia >0 && dia <= 30){
                    return 0;
                }else{return -1;}


            default:
                printf("\nErro na introdução do mês. Introduza um mês válido\n");
                break;

        }
    }else{
        return -1;
    }
    return 0;
}

int dia_atual(){

    int dia_atual =0;

    time_t seconds=time(NULL);
    struct tm* data_atual=localtime(&seconds);

    dia_atual =data_atual->tm_mday;
    return dia_atual;
}

int mes_atual(){

    int mes_atual =0;

    time_t seconds=time(NULL);
    struct tm* data_atual=localtime(&seconds);

    mes_atual =data_atual->tm_mon +1; // os meses em time.h funcionam iniciando em 0
    return mes_atual;
}

int ano_atual(){

    int ano_atual =0;

    // Forma de obter os anos atuais através da biblioteca time.h
    time_t seconds=time(NULL);
    struct tm* data_atual=localtime(&seconds);

    ano_atual =data_atual->tm_year + 1900;
    return ano_atual;
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


int agendar_visita_cliente(LISTA_VISITA **iniLista, LISTA_VISITA **fimLista, CLIENTE cliente_login){

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


            //// Corrigir horas e minutos e usar função que verifica:
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
            remove_newline1(nova_visita.relatorio);

            // Entrada para detalhes de interesse do cliente
            printf("Detalhes de Interesse do Cliente (até 3000 caracteres): ");
            fgets(nova_visita.detalhes_intresse_cliente, sizeof(nova_visita.detalhes_intresse_cliente), stdin);
            remove_newline1(nova_visita.detalhes_intresse_cliente);

            nova_visita.dia = dia_atual();
            nova_visita.mes = mes_atual();
            nova_visita.ano = ano_atual();

            break;

        case 0:

            // Entrada para o ano mês e dia
            while (1) {
                printf("Ano: ");
                scanf("%d", &nova_visita.ano);
                if (nova_visita.ano > 0) break;
                printf("Ano inválido. Por favor, insira um ano válido.\n");


                // Entrada para o mês

                printf("Mês (1-12): ");
                scanf("%d", &nova_visita.mes);
                if (nova_visita.mes >= 1 && nova_visita.mes <= 12) break;
                printf("Mês inválido. Por favor, insira um valor entre 1 e 12.\n");


                // Entrada para o dia

                printf("Dia (1-31): ");
                scanf("%d", &nova_visita.dia);
                if (nova_visita.dia >= 1 && nova_visita.dia <= 31) break;
                printf("Dia inválido. Por favor, insira um valor entre 1 e 31.\n");

                if(verifica_dia_mes_ano(nova_visita.dia, nova_visita.mes, nova_visita.ano) == 0){
                    break;
                }else{
                    printf("\nData inválida insira uma data valida.\n");
                }

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
            remove_newline1(nova_visita.relatorio);

            // Entrada para detalhes de interesse do cliente
            printf("Detalhes de Interesse do Cliente (até 3000 caracteres): ");
            fgets(nova_visita.detalhes_intresse_cliente, sizeof(nova_visita.detalhes_intresse_cliente), stdin);
            remove_newline1(nova_visita.detalhes_intresse_cliente);

            break;

        default:
            printf("\nErro casa aberta \n");
            return -1;
    }


    //// Fim interação utilizador


    // As visitas ficam todas juntas e depois as funções tratam de separar os dados em novas listas locais para tratarem os dados

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



