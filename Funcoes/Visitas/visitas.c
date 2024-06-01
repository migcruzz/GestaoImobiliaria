#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../VariaveisGlobais/variaveis_globais.h"
#include "../../TiposDados/TiposDados.h"
#include "../AgentesImobiliarios/agentes_imobiliarios.h"
#include "../Propriedades/propriedades.h"


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

// Aqui tem de procurar em todos os agentes que têm essa propriedade e averiguar aqual é que somando os valores passados
// tem a disponibilidade de oferecer visita:



// Aqui tem de verificar em todas as propriedades (em visita) se o agente tem horários sobrepostos
/*int verifica_disponibilidade_agente_visita(LISTA_VISITA *iniLista_visita, int agente_verificar, int hora_em_minutos_verificar, int duracao_visita_verificar) {
    // Verifica se a lista de visitas está vazia
    if (iniLista_visita == NULL) {
        printf("Lista Vazia\n");
        return -1;
    }

    // Variável para armazenar o tempo total de visitas já marcadas pelo agente
    int tempo_total = HORA_INICIO_AGENTE_IMOBILIARIO; // Inicializa com o horário de início do agente imobiliário

    // Ponteiro auxiliar para percorrer a lista de visitas
    LISTA_VISITA *aux = iniLista_visita;

    // Percorre a lista de visitas
    while (aux != NULL) {
        // Verifica se a visita é do agente que estamos verificando
        if (aux->visita.id_agente == agente_verificar) {
            // Calcula o tempo total de visitas já marcadas pelo agente
            tempo_total += aux->visita.duracao;
        }

        // Move para a próxima visita na lista
        aux = aux->seguinte;
    }

    // Verifica se há disponibilidade para a nova visita
    if (tempo_total + duracao_visita_verificar <= HORA_FIM_AGENTE_IMOBILIARIO) {
        // Verifica se o horário da nova visita não ultrapassa o horário de término do agente imobiliário
        if (hora_em_minutos_verificar + duracao_visita_verificar <= HORA_FIM_AGENTE_IMOBILIARIO) {
            // Retorna o horário da nova visita
            return hora_em_minutos_verificar;
        } else {
            printf("Não há horário disponível para a nova visita. Horário de término ultrapassado.\n");
            return -1;
        }
    } else {
        printf("Não há horário disponível para a nova visita. Horário de término ultrapassado.\n");
        return -1;
    }
}*/

/*int verifica_disponibilidade_agente_visita(LISTA_VISITA *iniLista_visita, int agente_verificar, int hora_visita, int duracao_visita) {


    int tempo_total = HORA_INICIO_AGENTE_IMOBILIARIO;
    LISTA_VISITA *aux = iniLista_visita;

    while (aux != NULL) {
        if (aux->visita.id_agente == agente_verificar) {
            tempo_total += aux->visita.duracao;
        }
        aux = aux->seguinte;
    }

    if (tempo_total + duracao_visita <= HORA_FIM_AGENTE_IMOBILIARIO && hora_visita + duracao_visita <= HORA_FIM_AGENTE_IMOBILIARIO) {
        return hora_visita;
    } else {
        printf("Não há horário disponível para a nova visita. Horário de término ultrapassado.\n");
        return -1;
    }
} */

int verifica_disponibilidade_agente_visita(LISTA_VISITA *iniLista_visita, int agente_verificar, int hora_visita, int duracao_visita) {
    /*  if (iniLista_visita == NULL) {
            printf("Lista de visitas vazia\n");
            return -1;
        }
    */
    int tempo_total = HORA_INICIO_AGENTE_IMOBILIARIO;
    LISTA_VISITA *aux = iniLista_visita;

    while (aux != NULL) {
        if (aux->visita.id_agente == agente_verificar) {
            // Verificar sobreposição de horários
            if (hora_visita >= aux->visita.hora_marcacao && hora_visita < aux->visita.hora_marcacao + aux->visita.duracao) {
                printf("Horário de visita sobreposto. Agente ocupado.\n");
                return -1;
            }
            tempo_total += aux->visita.duracao;
        }
        aux = aux->seguinte;
    }

    if (tempo_total + duracao_visita <= HORA_FIM_AGENTE_IMOBILIARIO && hora_visita + duracao_visita <= HORA_FIM_AGENTE_IMOBILIARIO) {
        return hora_visita;
    } else {
        printf("Não há horário disponível para a nova visita. Horário de término ultrapassado.\n");
        return -1;
    }
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
/*
int contador_visitas(LISTA_VISITA **iniLista){

    LISTA_VISITA *primeira = *iniLista;

    int contador =0;

    while(primeira ->seguinte != NULL){
        contador ++;
        primeira = primeira->seguinte;
    }

    return contador;
}
*/

// Cada visita tem de duração máxima de 240 minutos ou 2 Horas.
// Função com funcionamnto normal:
// Função para o cliente usar:


int agendar_visita_cliente(LISTA_VISITA **iniLista_visita, LISTA_VISITA **fimLista, int id_cliente_logado,AGENTE agente_imobiliario[],LISTA_PROPRIEDADE *iniLista_propriedade){

    VISITA nova_visita;
    LISTA_VISITA *nova = NULL;

    nova = (LISTA_VISITA *) calloc(1, sizeof(LISTA_VISITA));
    if (nova == NULL) {
        printf("Erro ao alocar memoria para nova visita \n");
        return -1;
    }

    // STRUCT com valores que são passados para a função de converter horas para minutos:
    TEMPO horario;

    // Valores para verificação de horários:
    int horario_valido = -1;

    // Valores para averiguar o agente disponivel (associado à propriedade);
    int id_agente_imobiliario_responsavel = -1;



    nova = (LISTA_VISITA *) calloc(1,sizeof(LISTA_VISITA));

    if(nova == NULL){ // se a lista estiver vazia
        printf("Out of memory ! \n");
        return -1;
    }

    //// Interação com utilizador:

    /// Caso seja uma visita não casa aberta:

    // Entrada para casa aberta

    nova_visita.id_cliente = id_cliente_logado;

    while (1) {
        printf("Casa Aberta (1 para sim, 0 para não): ");
        scanf("%d", &nova_visita.casa_aberta);
        if (nova_visita.casa_aberta == 0 || nova_visita.casa_aberta == 1) break;
        printf("Entrada inválida. Por favor, insira 1 para sim ou 0 para não.\n");
    }

    switch (nova_visita.casa_aberta) {

        case 1:


            imprime_todas_propriedades_populares(iniLista_propriedade);
            // Fazer verificação se o id introduzido pertence mesmo a propriedade listadas
            // Entrada para ID da propriedade
            printf("ID da Propriedade: ");
            scanf("%d", &nova_visita.id_propriedade);


            //listar agentes disponiveis
            // Fazer verificação se o id introduzido pertence mesmo aos agentes imobiliarios disponiveis
            listar_agente_imobiliario_disponiveis(agente_imobiliario);

            // Entrada para ID do agente
            printf("ID do Agente: ");
            scanf("%d", &nova_visita.id_agente);



            // Entrada para duração
            while (1) {
                printf("Duração (em minutos, até 1440): ");
                scanf("%d", &nova_visita.duracao);
                if (nova_visita.duracao > 0 && nova_visita.duracao <= 240) break;
                printf("Duração inválida. Por favor, insira um valor entre 1 e 240 minutos.\n");
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

                while (1){
                    printf("Ano: ");
                    fflush(stdin);
                    scanf("%d", &nova_visita.ano);
                    if (nova_visita.ano > 0) break;
                    printf("Ano inválido. Por favor, insira um ano válido.\n");
                    fflush(stdout);
                }


                while (1){
                    // Entrada para o mês
                    fflush(stdout);
                    printf("Mês (1-12): ");
                    fflush(stdin);
                    scanf("%d", &nova_visita.mes);
                    if (nova_visita.mes >= 1 && nova_visita.mes <= 12) break;
                    printf("Mês inválido. Por favor, insira um valor entre 1 e 12.\n");
                    fflush(stdout);
                }


                while(1){
                    // Entrada para o dia
                    fflush(stdout);
                    printf("Dia (1-31): ");
                    fflush(stdin);
                    scanf("%d", &nova_visita.dia);
                    if (nova_visita.dia >= 1 && nova_visita.dia <= 31) break;
                    printf("Dia inválido. Por favor, insira um valor entre 1 e 31.\n");
                    fflush(stdout);
                }


                if(verifica_dia_mes_ano(nova_visita.dia, nova_visita.mes, nova_visita.ano) == 0){
                    break;
                }else{
                    printf("\nData inválida insira uma data valida.\n");
                }

            }

            while(1){

                imprime_todas_propriedades_nao_populares(iniLista_propriedade);

                // verificaçãp de dado introduzido se é casa não popular
                // Entrada para ID da propriedade
                printf("\nIntroduza o identificador da propriedade pela qual demosntra interesse: \n");
                scanf("%d", &nova_visita.id_propriedade);
                id_agente_imobiliario_responsavel = verifica_agente_casa_responsavel(agente_imobiliario, iniLista_propriedade, nova_visita.id_propriedade );

                if(id_agente_imobiliario_responsavel != -1){
                    nova_visita.id_agente = id_agente_imobiliario_responsavel;
                    break;
                }else{
                    printf("\nErro ao escolher prorpiedade válida !!!!\n");
                }

            }

            // Verificador se o agente tem disponibilidade, calculando assim a partir de que horas pode marcar

        while(1){

            while (1) {
                // Entrada para hora de marcação
                printf("\nIntroduza o horário da visita:\n");
                printf("\nHora da Marcação : ");
                fflush(stdin);
                scanf("%d", &horario.horas);
                printf("\nIntroduza o número de minutos:\n");
                scanf("%d", &horario.minutos);
                nova_visita.hora_marcacao = conversor_horas_para_minutos(horario.horas,horario.minutos);



                if (nova_visita.hora_marcacao >= 0 && nova_visita.hora_marcacao <= 1440){
                    break;
                }else{
                    printf("Hora da marcação inválida. Por favor, insira um valor entre 0 e 1439 minutos.\n");
                }
            }

            while (1) {
                // Entrada para duração
                printf("\nIntroduza a duracao da visita, tendo um tempo maximo de 2 horas e mínimo de 20 minutos\n");
                printf("\nIntroduza o número de horas:\n");
                scanf("%d", &horario.horas);
                printf("\nIntroduza o número de minutos:\n");
                scanf("%d", &horario.minutos);
                nova_visita.duracao = conversor_horas_para_minutos(horario.horas, horario.minutos);

                // Função para verificar se a duracao e valida:

                if (nova_visita.duracao > 20 && nova_visita.duracao <= 120){
                    break;
                }else{
                    printf("\nDuração inválida. Por favor, insira uma duração máxima de 2 horas \n");
                }


            }

            horario_valido = verifica_disponibilidade_agente_visita(*iniLista_visita, nova_visita.id_agente ,nova_visita.hora_marcacao, nova_visita.duracao);

            if(horario_valido != -1){
                break;
            }else{ printf("\nIntroduza  valores válidos !!!\n");}

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

    if(*iniLista_visita == NULL){

        *iniLista_visita = nova;
        *fimLista = nova;

    }else{
        nova -> seguinte = *iniLista_visita;
        (*iniLista_visita) -> anterior = nova;
        (*iniLista_visita) = nova;
    }

    return 0;
}

void listar_todas_visitas(LISTA_VISITA *iniLista_visita) {
    // Verifica se a lista de visitas está vazia
    if (iniLista_visita == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    // Ponteiro auxiliar para percorrer a lista de visitas
    LISTA_VISITA *aux = iniLista_visita;

    // Percorre a lista de visitas
    while (aux != NULL) {
        printf("-------------------------------------------------------------\n");
        printf("Dia: %d\tMês: %d\tAno: %d\n", aux->visita.dia, aux->visita.mes, aux->visita.ano);
        printf("ID Cliente: %d\tID Agente: %d\tID Propriedade: %d\n", aux->visita.id_cliente, aux->visita.id_agente, aux->visita.id_propriedade);
        printf("Duração: %d minutos\tHora Marcação: %d minutos\n", aux->visita.duracao, aux->visita.hora_marcacao);
        printf("Relatório: %s\n", aux->visita.relatorio);
        printf("Detalhes Interesse Cliente: %s\n", aux->visita.detalhes_intresse_cliente);
        printf("Cliente Compareceu: %s\n", aux->visita.cliente_compareceu ? "Sim" : "Não");
        printf("Visita Terminou: %s\n", aux->visita.visita_terminou ? "Sim" : "Não");
        printf("Casa Aberta: %s\n", aux->visita.casa_aberta ? "Sim" : "Não");
        printf("-------------------------------------------------------------\n");

        // Move para a próxima visita na lista
        aux = aux->seguinte;
    }
}


int listar_visita_dia(){



    return 0;
}


//// Funcionalidades de texto entre outras para replicar



