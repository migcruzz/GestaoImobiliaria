#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <regex.h>
#include "../../VariaveisGlobais/variaveis_globais.h"
#include "../../TiposDados/TiposDados.h"
#include "../AgentesImobiliarios/agentes_imobiliarios.h"
#include "../Propriedades/propriedades.h"


// Trabalhar com formato 24H
// Dentro do programa todos os algoritmos vão ser no formato de minutos e só para o cliente vai ser mostrado


// Função para remover o caractere de nova linha de fgets
void remove_newlineVisitas(char *string) {
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
        conversao.horas = minutos / 60;
        conversao.minutos =minutos % 60;
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


int verifica_disponibilidade_agente_visita(LISTA_VISITA *iniLista_visita, int agente_verificar, int hora_visita, int duracao_visita, int dia_verificar, int mes_verificar, int ano_verificar) {

    if (iniLista_visita == NULL) {
        if (hora_visita >= HORA_INICIO_AGENTE_IMOBILIARIO && hora_visita + duracao_visita <= HORA_FIM_AGENTE_IMOBILIARIO) {
            return hora_visita;
        } else {
            printf("Não há horário disponível para a nova visita. Horário de término ultrapassado.\n");
            return -1;
        }
    }
    LISTA_VISITA *aux = iniLista_visita;

    while (aux != NULL) {
        if (aux->visita.id_agente == agente_verificar) {
            // Verificar sobreposição de horários
            if (((hora_visita >= aux->visita.horario_marcacao && hora_visita < aux->visita.horario_marcacao + aux->visita.duracao) ||
                 (aux->visita.horario_marcacao >= hora_visita && aux->visita.horario_marcacao < hora_visita + duracao_visita)) &&
                ((aux ->visita.dia == dia_verificar) && (aux ->visita.mes == mes_verificar) && (aux ->visita.ano == ano_verificar ))) {
                printf("Horário de visita sobreposto. Agente ocupado.\n");
                return -1;
            }
        }
        aux = aux->seguinte;
    }

    if (hora_visita >= HORA_INICIO_AGENTE_IMOBILIARIO && hora_visita + duracao_visita <= HORA_FIM_AGENTE_IMOBILIARIO) {
        return hora_visita;
    } else {
        printf("Não há horário disponível para a nova visita. Horário de término ultrapassado.\n");
        return -1;
    }
}


int hora_atual(){
    int hora_atual =0;


    time_t seconds=time(NULL);
    struct tm* data_atual=localtime(&seconds);

    hora_atual =data_atual->tm_hour;
    return hora_atual;
}

int minuto_atual(){
    int minuto_atual =0;


    time_t seconds=time(NULL);
    struct tm* data_atual=localtime(&seconds);

    minuto_atual =data_atual ->tm_min;
    return minuto_atual;
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

    // Valores para poder serem alterados no momento de atendimento.
    nova_visita.id_cliente = id_cliente_logado;
    nova_visita.visita_terminada = 0;
    nova_visita.propriedade_vendida = -1;
    nova_visita.cliente_compareceu = -1;

    while (1) {
        printf("Casa Aberta (1 para sim, 0 para não): ");
        scanf("%d", &nova_visita.casa_aberta);
        if (nova_visita.casa_aberta == 0 || nova_visita.casa_aberta == 1){
            break;
        }
        printf("Entrada inválida. Por favor, insira 1 para sim ou 0 para não.\n");
    }

    switch (nova_visita.casa_aberta) {

        case 1:

            nova_visita.propriedade_vendida = 0;
            nova_visita.cliente_compareceu = 1;

            imprime_todas_propriedades_populares_negocio_por_concluir(iniLista_propriedade);
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

            nova_visita.dia = dia_atual();
            nova_visita.mes = mes_atual();
            nova_visita.ano = ano_atual();

            while(1){

                while(1){
                    horario.horas = hora_atual();
                    horario.minutos = minuto_atual();

                    nova_visita.horario_marcacao = conversor_horas_para_minutos(horario.horas,horario.minutos);

                    if (nova_visita.horario_marcacao >= 0 && nova_visita.horario_marcacao <= 1440){
                        break;
                    }else{
                        printf("Hora da marcação inválida. Por favor, venha a uma hora entre 9 e as 19 horas\n");
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

                horario_valido = verifica_disponibilidade_agente_visita(*iniLista_visita, nova_visita.id_agente ,nova_visita.horario_marcacao, nova_visita.duracao, nova_visita.dia,nova_visita.mes,nova_visita.ano);

                if(horario_valido != -1){
                    break;
                }else if(nova_visita.horario_marcacao > HORA_FIM_AGENTE_IMOBILIARIO){

                }else{ printf("\nIntroduza  valores válidos !!!\n");}

            }



            // Limpar o buffer do stdin antes de usar fgets para strings
            fflush(stdin);

            // Entrada para detalhes de interesse do cliente
            printf("Detalhes de Interesse do Cliente (até 3000 caracteres): ");
            fgets(nova_visita.detalhes_intresse_cliente, sizeof(nova_visita.detalhes_intresse_cliente), stdin);
            remove_newlineVisitas(nova_visita.detalhes_intresse_cliente);



            break;

        case 0:

            nova_visita.cliente_compareceu = -1;
            // Entrada para o ano mês e dia
            while (1) {

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

                while (1){
                    printf("Ano: ");
                    fflush(stdin);
                    scanf("%d", &nova_visita.ano);
                    if (nova_visita.ano > 0) break;
                    printf("Ano inválido. Por favor, insira um ano válido.\n");
                    fflush(stdout);
                }

                if(verifica_dia_mes_ano(nova_visita.dia, nova_visita.mes, nova_visita.ano) == 0){
                    break;
                }else{
                    printf("\nData inválida insira uma data valida.\n");
                }

            }

            while(1){

                imprime_todas_propriedades_nao_populares_negocio_por_concluir(iniLista_propriedade);

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
                    nova_visita.horario_marcacao = conversor_horas_para_minutos(horario.horas,horario.minutos);

                    if (nova_visita.horario_marcacao >= 0 && nova_visita.horario_marcacao <= 1440){
                        break;
                    }else{
                        printf("Hora da marcação inválida. Por favor, insira um valor entre as 9 horas e as 19 horas.\n");
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

                horario_valido = verifica_disponibilidade_agente_visita(*iniLista_visita, nova_visita.id_agente ,nova_visita.horario_marcacao, nova_visita.duracao, nova_visita.dia,nova_visita.mes,nova_visita.ano);


                if(horario_valido != -1){
                    break;
                }else{ printf("\nIntroduza  valores válidos !!!\n");}

            }


            // Limpar o buffer do stdin antes de usar fgets para strings
            fflush(stdin);

            // Entrada para relatório

            /*
            printf("Relatório (até 3000 caracteres): ");
            fgets(nova_visita.relatorio, sizeof(nova_visita.relatorio), stdin);
            remove_newline1(nova_visita.relatorio);
             */

            // Entrada para detalhes de interesse do cliente
            printf("Detalhes de Interesse do Cliente (até 3000 caracteres): ");
            fgets(nova_visita.detalhes_intresse_cliente, sizeof(nova_visita.detalhes_intresse_cliente), stdin);
            remove_newlineVisitas(nova_visita.detalhes_intresse_cliente);

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

    TEMPO visita, duracao_visita;



    // Ponteiro auxiliar para percorrer a lista de visitas
    LISTA_VISITA *aux = iniLista_visita;

    // Percorre a lista de visitas
    while (aux != NULL) {

        visita = conversor_minutos_para_horas(aux ->visita.horario_marcacao);
        duracao_visita = conversor_minutos_para_horas(aux ->visita.duracao);

        printf("-------------------------------------------------------------\n");
        printf("Dia: %d\tMês: %d\tAno: %d\n", aux->visita.dia, aux->visita.mes, aux->visita.ano);
        printf("ID Cliente: %d\tID Agente: %d\tID Propriedade: %d\n", aux->visita.id_cliente, aux->visita.id_agente, aux->visita.id_propriedade);
        printf("Duração:  %d:%d \tHora Marcação: %d:%d\n", duracao_visita.horas,duracao_visita.minutos,visita.horas,visita.minutos );
        printf("Relatório: %s\n", aux->visita.relatorio);
        printf("Detalhes Interesse Cliente: %s\n", aux->visita.detalhes_intresse_cliente);
        printf("Cliente Compareceu: %s\n", aux->visita.cliente_compareceu ? "Sim" : "Não");
        printf("Visita Terminou: %s\n", aux->visita.propriedade_vendida ? "Sim" : "Não");
        printf("Casa Aberta: %s\n", aux->visita.casa_aberta ? "Sim" : "Não");
        printf("-------------------------------------------------------------\n");

        // Move para a próxima visita na lista
        aux = aux->seguinte;
    }
}


//// Funcionalidades de texto entre outras para replicar

void listar_visitas_por_dia_agente(LISTA_VISITA *iniLista_visita, int dia, int mes, int ano, int id_agente) {
    if (iniLista_visita == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    LISTA_VISITA *aux = iniLista_visita;
    while (aux != NULL) {
        if (aux->visita.dia == dia && aux->visita.mes == mes && aux->visita.ano == ano && aux->visita.id_agente == id_agente) {
            TEMPO visita = conversor_minutos_para_horas(aux->visita.horario_marcacao);
            TEMPO duracao_visita = conversor_minutos_para_horas(aux->visita.duracao);

            printf("-------------------------------------------------------------\n");
            printf("Dia: %d\tMês: %d\tAno: %d\n", aux->visita.dia, aux->visita.mes, aux->visita.ano);
            printf("ID Cliente: %d\tID Agente: %d\tID Propriedade: %d\n", aux->visita.id_cliente, aux->visita.id_agente, aux->visita.id_propriedade);
            printf("Duração:  %d:%d \tHora Marcação: %d:%d\n", duracao_visita.horas, duracao_visita.minutos, visita.horas, visita.minutos);
            printf("Relatório: %s\n", aux->visita.relatorio);
            printf("Detalhes Interesse Cliente: %s\n", aux->visita.detalhes_intresse_cliente);
            printf("Cliente Compareceu: %s\n", aux->visita.cliente_compareceu ? "Sim" : "Não");
            printf("Visita Terminou: %s\n", aux->visita.propriedade_vendida ? "Sim" : "Não");
            printf("Casa Aberta: %s\n", aux->visita.casa_aberta ? "Sim" : "Não");
            printf("-------------------------------------------------------------\n");
        }
        aux = aux->seguinte;
    }
}

void listar_visitas_de_hoje_por_hora_ascendente(LISTA_VISITA *iniLista_visita) {
    if (iniLista_visita == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    int dia = dia_atual();
    int mes = mes_atual();
    int ano = ano_atual();

    // Variáveis auxiliares
    LISTA_VISITA *atual = iniLista_visita;
    LISTA_VISITA *proximo = NULL;
    LISTA_VISITA *temp = NULL;
    int trocado;

    // Ordena as visitas por hora de marcação (ascendente)
    do {
        trocado = 0;
        atual = iniLista_visita;
        proximo = atual->seguinte;

        // Loop para percorrer a lista e fazer as trocas necessárias
        while (proximo != NULL) {
            // Converte as horas de marcação das visitas
            TEMPO hora_atual = conversor_minutos_para_horas(atual->visita.horario_marcacao);
            TEMPO hora_proximo = conversor_minutos_para_horas(proximo->visita.horario_marcacao);

            // Compara as horas de marcação das visitas e realiza a troca, se necessário
            if (hora_atual.horas > hora_proximo.horas || (hora_atual.horas == hora_proximo.horas && hora_atual.minutos > hora_proximo.minutos)) {
                // Troca os nós sem modificar as estruturas da lista
                if (atual == iniLista_visita) {
                    iniLista_visita = proximo;
                } else {
                    temp->seguinte = proximo;
                }
                atual->seguinte = proximo->seguinte;
                proximo->seguinte = atual;

                // Atualiza os ponteiros
                temp = proximo;
                proximo = atual->seguinte;

                trocado = 1; // Indica que houve uma troca
            } else {
                // Atualiza os ponteiros
                temp = atual;
                atual = proximo;
                proximo = proximo->seguinte;
            }
        }
    } while (trocado);

    // Lista as visitas ordenadas por hora de marcação
    printf("Lista de visitas de hoje ordenadas por hora de marcação (ascendente):\n");
    atual = iniLista_visita;
    while (atual != NULL) {
        if (atual->visita.dia == dia && atual->visita.mes == mes && atual->visita.ano == ano) {
            TEMPO visita = conversor_minutos_para_horas(atual->visita.horario_marcacao);
            TEMPO duracao_visita = conversor_minutos_para_horas(atual->visita.duracao);

            printf("-------------------------------------------------------------\n");
            printf("Dia: %d\tMês: %d\tAno: %d\n", atual->visita.dia, atual->visita.mes, atual->visita.ano);
            printf("ID Cliente: %d\tID Agente: %d\tID Propriedade: %d\n", atual->visita.id_cliente, atual->visita.id_agente, atual->visita.id_propriedade);
            printf("Duração: %d:%d \tHora Marcação: %d:%d\n", duracao_visita.horas, duracao_visita.minutos, visita.horas, visita.minutos);
            printf("Relatório: %s\n", atual->visita.relatorio);
            printf("Detalhes Interesse Cliente: %s\n", atual->visita.detalhes_intresse_cliente);
            printf("Cliente Compareceu: %s\n", atual->visita.cliente_compareceu ? "Sim" : "Não");
            printf("Visita Terminou: %s\n", atual->visita.propriedade_vendida ? "Sim" : "Não");
            printf("Casa Aberta: %s\n", atual->visita.casa_aberta ? "Sim" : "Não");
            printf("-------------------------------------------------------------\n");
        }
        atual = atual->seguinte;
    }
}


void ordenar_visitas_por_hora_ascendente(LISTA_VISITA **iniLista_visita) {
    // Verifica se a lista está vazia
    if (*iniLista_visita == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    // Variáveis auxiliares
    LISTA_VISITA *atual = *iniLista_visita;
    LISTA_VISITA *proximo = NULL;
    LISTA_VISITA *temp = NULL;
    int trocado;

    // Solicita a data desejada ao usuário
    int dia_desejado, mes_desejado, ano_desejado;
    printf("Digite o dia desejado: ");
    scanf("%d", &dia_desejado);
    printf("Digite o mês desejado: ");
    scanf("%d", &mes_desejado);
    printf("Digite o ano desejado: ");
    scanf("%d", &ano_desejado);

    // Loop para ordenação
    do {
        trocado = 0;
        atual = *iniLista_visita;
        proximo = atual->seguinte;

        // Loop para percorrer a lista e fazer as trocas necessárias
        while (proximo != NULL) {
            // Converte as horas de marcação das visitas
            TEMPO hora_atual = conversor_minutos_para_horas(atual->visita.horario_marcacao);
            TEMPO hora_proximo = conversor_minutos_para_horas(proximo->visita.horario_marcacao);

            // Compara as horas de marcação das visitas e realiza a troca, se necessário
            if ((atual->visita.dia == dia_desejado) && (atual->visita.mes == mes_desejado) && (atual->visita.ano == ano_desejado) &&
                (hora_atual.horas > hora_proximo.horas || (hora_atual.horas == hora_proximo.horas && hora_atual.minutos > hora_proximo.minutos))) {
                // Troca os nós sem modificar as estruturas da lista
                if (atual == *iniLista_visita) {
                    *iniLista_visita = proximo;
                } else {
                    temp->seguinte = proximo;
                }
                atual->seguinte = proximo->seguinte;
                proximo->seguinte = atual;

                // Atualiza os ponteiros
                temp = proximo;
                proximo = atual->seguinte;

                trocado = 1; // Indica que houve uma troca
            } else {
                // Atualiza os ponteiros
                temp = atual;
                atual = proximo;
                proximo = proximo->seguinte;
            }
        }
    } while (trocado);

    // Lista as visitas ordenadas por hora de marcação
    printf("Lista de visitas do dia %d/%d/%d ordenadas por hora de marcação:\n", dia_desejado, mes_desejado, ano_desejado);
    atual = *iniLista_visita;
    while (atual != NULL) {
        if (atual->visita.dia == dia_desejado && atual->visita.mes == mes_desejado && atual->visita.ano == ano_desejado) {
            TEMPO visita = conversor_minutos_para_horas(atual->visita.horario_marcacao);
            TEMPO duracao_visita = conversor_minutos_para_horas(atual->visita.duracao);

            printf("-------------------------------------------------------------\n");
            printf("Dia: %d\tMês: %d\tAno: %d\n", atual->visita.dia, atual->visita.mes, atual->visita.ano);
            printf("ID Cliente: %d\tID Agente: %d\tID Propriedade: %d\n", atual->visita.id_cliente, atual->visita.id_agente, atual->visita.id_propriedade);
            printf("Duração: %d:%d \tHora Marcação: %d:%d\n", duracao_visita.horas, duracao_visita.minutos, visita.horas, visita.minutos);
            printf("Relatório: %s\n", atual->visita.relatorio);
            printf("Detalhes Interesse Cliente: %s\n", atual->visita.detalhes_intresse_cliente);
            printf("Cliente Compareceu: %s\n", atual->visita.cliente_compareceu ? "Sim" : "Não");
            printf("Visita Terminou: %s\n", atual->visita.propriedade_vendida ? "Sim" : "Não");
            printf("Casa Aberta: %s\n", atual->visita.casa_aberta ? "Sim" : "Não");
            printf("-------------------------------------------------------------\n");
        }
        atual = atual->seguinte;
    }
}

void listar_visitas_de_hoje_por_hora_ascendente_agente_logado(LISTA_VISITA *iniLista_visita, int id_agente_logado) {
    if (id_agente_logado == -1) {
        printf("Apenas agentes autenticados podem acessar esta função.\n");
        return;
    }

    if (iniLista_visita == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    int dia = dia_atual();
    int mes = mes_atual();
    int ano = ano_atual();

    LISTA_VISITA *atual = iniLista_visita;
    LISTA_VISITA *proximo = NULL;
    LISTA_VISITA *temp = NULL;
    int trocado;

    do {
        trocado = 0;
        atual = iniLista_visita;
        proximo = atual->seguinte;

        while (proximo != NULL) {
            TEMPO hora_atual = conversor_minutos_para_horas(atual->visita.horario_marcacao);
            TEMPO hora_proximo = conversor_minutos_para_horas(proximo->visita.horario_marcacao);

            if (hora_atual.horas > hora_proximo.horas || (hora_atual.horas == hora_proximo.horas && hora_atual.minutos > hora_proximo.minutos)) {
                if (atual == iniLista_visita) {
                    iniLista_visita = proximo;
                } else {
                    temp->seguinte = proximo;
                }
                atual->seguinte = proximo->seguinte;
                proximo->seguinte = atual;

                temp = proximo;
                proximo = atual->seguinte;

                trocado = 1;
            } else {
                temp = atual;
                atual = proximo;
                proximo = proximo->seguinte;
            }
        }
    } while (trocado);

    printf("Lista de visitas de hoje ordenadas por hora de marcação (ascendente):\n");
    atual = iniLista_visita;
    while (atual != NULL) {
        if (atual->visita.dia == dia && atual->visita.mes == mes && atual->visita.ano == ano && atual->visita.id_agente == id_agente_logado) {
            TEMPO visita = conversor_minutos_para_horas(atual->visita.horario_marcacao);
            TEMPO duracao_visita = conversor_minutos_para_horas(atual->visita.duracao);

            printf("-------------------------------------------------------------\n");
            printf("Dia: %d\tMês: %d\tAno: %d\n", atual->visita.dia, atual->visita.mes, atual->visita.ano);
            printf("ID Cliente: %d\tID Agente: %d\tID Propriedade: %d\n", atual->visita.id_cliente, atual->visita.id_agente, atual->visita.id_propriedade);
            printf("Duração: %d:%d \tHora Marcação: %d:%d\n", duracao_visita.horas, duracao_visita.minutos, visita.horas, visita.minutos);
            printf("Relatório: %s\n", atual->visita.relatorio);
            printf("Detalhes Interesse Cliente: %s\n", atual->visita.detalhes_intresse_cliente);
            printf("Cliente Compareceu: %s\n", atual->visita.cliente_compareceu ? "Sim" : "Não");
            printf("Visita Terminou: %s\n", atual->visita.propriedade_vendida ? "Sim" : "Não");
            printf("Casa Aberta: %s\n", atual->visita.casa_aberta ? "Sim" : "Não");
            printf("-------------------------------------------------------------\n");
        }
        atual = atual->seguinte;
    }
}

void listar_visitas_de_dia_ascendente_agente_logado(LISTA_VISITA *iniLista_visita, int id_agente_logado) {
    if (id_agente_logado == -1) {
        printf("Apenas agentes autenticados podem acessar esta função.\n");
        return;
    }

    // Variáveis para armazenar o dia, mês e ano fornecidos pelo usuário
    int dia, mes, ano;

    // Solicita o dia desejado ao usuário
    printf("Digite o dia desejado: ");
    scanf("%d", &dia);

    // Solicita o mês desejado ao usuário
    printf("Digite o mês desejado: ");
    scanf("%d", &mes);

    // Solicita o ano desejado ao usuário
    printf("Digite o ano desejado: ");
    scanf("%d", &ano);

    if (iniLista_visita == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    LISTA_VISITA *atual = iniLista_visita;
    LISTA_VISITA *proximo = NULL;
    LISTA_VISITA *temp = NULL;
    int trocado;

    do {
        trocado = 0;
        atual = iniLista_visita;
        proximo = atual->seguinte;

        while (proximo != NULL) {
            TEMPO hora_atual = conversor_minutos_para_horas(atual->visita.horario_marcacao);
            TEMPO hora_proximo = conversor_minutos_para_horas(proximo->visita.horario_marcacao);

            if (hora_atual.horas > hora_proximo.horas || (hora_atual.horas == hora_proximo.horas && hora_atual.minutos > hora_proximo.minutos)) {
                if (atual == iniLista_visita) {
                    iniLista_visita = proximo;
                } else {
                    temp->seguinte = proximo;
                }
                atual->seguinte = proximo->seguinte;
                proximo->seguinte = atual;

                temp = proximo;
                proximo = atual->seguinte;

                trocado = 1;
            } else {
                temp = atual;
                atual = proximo;
                proximo = proximo->seguinte;
            }
        }
    } while (trocado);

    printf("Lista de visitas do dia %d/%d/%d ordenadas por hora de marcação (ascendente):\n", dia, mes, ano);
    atual = iniLista_visita;
    while (atual != NULL) {
        if (atual->visita.dia == dia && atual->visita.mes == mes && atual->visita.ano == ano && atual->visita.id_agente == id_agente_logado) {
            TEMPO visita = conversor_minutos_para_horas(atual->visita.horario_marcacao);
            TEMPO duracao_visita = conversor_minutos_para_horas(atual->visita.duracao);

            printf("-------------------------------------------------------------\n");
            printf("Dia: %d\tMês: %d\tAno: %d\n", atual->visita.dia, atual->visita.mes, atual->visita.ano);
            printf("ID Cliente: %d\tID Agente: %d\tID Propriedade: %d\n", atual->visita.id_cliente, atual->visita.id_agente, atual->visita.id_propriedade);
            printf("Duração: %d:%d \tHora Marcação: %d:%d\n", duracao_visita.horas, duracao_visita.minutos, visita.horas, visita.minutos);
            printf("Relatório: %s\n", atual->visita.relatorio);
            printf("Detalhes Interesse Cliente: %s\n", atual->visita.detalhes_intresse_cliente);
            printf("Cliente Compareceu: %s\n", atual->visita.cliente_compareceu ? "Sim" : "Não");
            printf("Visita Terminou: %s\n", atual->visita.propriedade_vendida ? "Sim" : "Não");
            printf("Casa Aberta: %s\n", atual->visita.casa_aberta ? "Sim" : "Não");
            printf("-------------------------------------------------------------\n");
        }
        atual = atual->seguinte;
    }
}

void listar_visitas_cliente_nao_compareceu_agente_logado(LISTA_VISITA *iniLista_visita, int id_agente_logado) {
    if (id_agente_logado == -1) {
        printf("Apenas agentes autenticados podem acessar esta função.\n");
        return;
    }

    // Variáveis para armazenar o dia, mês e ano fornecidos pelo usuário
    int dia, mes, ano;

    // Solicita o dia desejado ao usuário
    printf("Digite o dia desejado: ");
    scanf("%d", &dia);

    // Solicita o mês desejado ao usuário
    printf("Digite o mês desejado: ");
    scanf("%d", &mes);

    // Solicita o ano desejado ao usuário
    printf("Digite o ano desejado: ");
    scanf("%d", &ano);

    if (iniLista_visita == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    LISTA_VISITA *atual = iniLista_visita;
    TEMPO visita;
    TEMPO duracao_visita;

    printf("Lista de visitas em que o cliente não compareceu para o agente logado no dia %d/%d/%d:\n", dia, mes, ano);
    while (atual != NULL) {
        if (atual->visita.dia == dia && atual->visita.mes == mes && atual->visita.ano == ano && atual->visita.id_agente == id_agente_logado && !atual->visita.cliente_compareceu) {
            visita = conversor_minutos_para_horas(atual->visita.horario_marcacao);
            duracao_visita = conversor_minutos_para_horas(atual->visita.duracao);

            printf("-------------------------------------------------------------\n");
            printf("Dia: %d\tMês: %d\tAno: %d\n", atual->visita.dia, atual->visita.mes, atual->visita.ano);
            printf("ID Cliente: %d\tID Agente: %d\tID Propriedade: %d\n", atual->visita.id_cliente, atual->visita.id_agente, atual->visita.id_propriedade);
            printf("Duração: %d:%d \tHora Marcação: %d:%d\n", duracao_visita.horas, duracao_visita.minutos, visita.horas, visita.minutos);
            printf("Relatório: %s\n", atual->visita.relatorio);
            printf("Detalhes Interesse Cliente: %s\n", atual->visita.detalhes_intresse_cliente);
            printf("Cliente Compareceu: %s\n", atual->visita.cliente_compareceu ? "Sim" : "Não");
            printf("Visita Terminou: %s\n", atual->visita.propriedade_vendida ? "Sim" : "Não");
            printf("Casa Aberta: %s\n", atual->visita.casa_aberta ? "Sim" : "Não");
            printf("-------------------------------------------------------------\n");
        }
        atual = atual->seguinte;
    }
}

void ordenar_visitas_por_hora(LISTA_VISITA **iniLista_visita) {
    if (*iniLista_visita == NULL) {
        return;
    }

    LISTA_VISITA *atual, *proximo, *temp;
    int trocado;

    do {
        trocado = 0;
        atual = *iniLista_visita;
        proximo = atual->seguinte;
        temp = NULL;

        while (proximo != NULL) {
            TEMPO hora_atual = conversor_minutos_para_horas(atual->visita.horario_marcacao);
            TEMPO hora_proximo = conversor_minutos_para_horas(proximo->visita.horario_marcacao);

            if ((hora_atual.horas > hora_proximo.horas) ||
                (hora_atual.horas == hora_proximo.horas && hora_atual.minutos > hora_proximo.minutos)) {
                if (atual == *iniLista_visita) {
                    *iniLista_visita = proximo;
                } else {
                    temp->seguinte = proximo;
                }
                atual->seguinte = proximo->seguinte;
                proximo->seguinte = atual;

                temp = proximo;
                proximo = atual->seguinte;

                trocado = 1;
            } else {
                temp = atual;
                atual = proximo;
                proximo = proximo->seguinte;
            }
        }
    } while (trocado);
}

void listar_visitas_de_hoje_por_hora_ascendente_casa_aberta_agente_logado_vistita_nao_concluida(LISTA_VISITA **iniLista_visita, int id_agente_logado) {
    if (*iniLista_visita == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    TEMPO total_tempo_espera = {0, 0};
    int dia = dia_atual();
    int mes = mes_atual();
    int ano = ano_atual();

    ordenar_visitas_por_hora(iniLista_visita);

    LISTA_VISITA *atual = *iniLista_visita;
    while (atual != NULL) {
        if ((atual->visita.dia == dia && atual->visita.mes == mes && atual->visita.ano == ano) &&
            (atual->visita.casa_aberta == 1) &&
            (atual->visita.propriedade_vendida == 0) &&
            (id_agente_logado == atual->visita.id_agente) &&
            (atual->visita.visita_terminada == 0)) {

            TEMPO visita = conversor_minutos_para_horas(atual->visita.horario_marcacao);
            TEMPO duracao_visita = conversor_minutos_para_horas(atual->visita.duracao);

            total_tempo_espera.horas += duracao_visita.horas;
            total_tempo_espera.minutos += duracao_visita.minutos;

            printf("-------------------------------------------------------------\n");
            printf("Dia: %d\tMês: %d\tAno: %d\n", atual->visita.dia, atual->visita.mes, atual->visita.ano);
            printf("ID Cliente: %d\tID Agente: %d\tID Propriedade: %d\n", atual->visita.id_cliente, atual->visita.id_agente, atual->visita.id_propriedade);
            printf("Duração: %d:%d \tHora Marcação: %d:%d\n", duracao_visita.horas, duracao_visita.minutos, visita.horas, visita.minutos);
            printf("Relatório: %s\n", atual->visita.relatorio);
            printf("Detalhes Interesse Cliente: %s\n", atual->visita.detalhes_intresse_cliente);
            printf("Cliente Compareceu: %s\n", atual->visita.cliente_compareceu ? "Sim" : "Não");
            printf("Visita Terminou: %s\n", atual->visita.propriedade_vendida ? "Sim" : "Não");
            printf("Casa Aberta: %s\n", atual->visita.casa_aberta ? "Sim" : "Não");
            printf("O Cliente %d tem de esperar %d horas e %d minutos\n", atual->visita.id_cliente, total_tempo_espera.horas, total_tempo_espera.minutos);
            printf("-------------------------------------------------------------\n");
        }
        atual = atual->seguinte;
    }
}

int atender_visitas(LISTA_VISITA **iniLista_visita, int id_agente_logado){

    int opcao = 0;
    int vendida = 0;
    int cliente_compareceu = 0;


    // Ordenar as visitas por hora
    ordenar_visitas_por_hora(iniLista_visita);

    printf("ordenado");

    // Listar as visitas de hoje por hora ascendente, casa aberta e não concluída
    listar_visitas_de_hoje_por_hora_ascendente_casa_aberta_agente_logado_vistita_nao_concluida(iniLista_visita, id_agente_logado);


    printf("listar");
    // Verificar se a lista de visitas está vazia
    if (*iniLista_visita == NULL) {
        printf("Não há visitas agendadas para hoje.\n");
        return -1;
    }

    TEMPO total_tempo_espera = {0, 0}; // Tempo total de espera acumulado
    int dia = dia_atual();
    int mes = mes_atual();
    int ano = ano_atual();

    // Percorrer a lista de visitas
    LISTA_VISITA *atual = *iniLista_visita;
    while (atual != NULL) {
        if ((atual->visita.dia == dia && atual->visita.mes == mes && atual->visita.ano == ano) &&
            (atual->visita.casa_aberta == 1) &&
            (atual->visita.propriedade_vendida == 0) &&
            (id_agente_logado == atual->visita.id_agente) &&
            (atual->visita.visita_terminada == 0)) {

            // Solicitar ao agente que decida se quer atender a visita ou sair
            printf("\nIntroduza 1 se quiser atender o cliente, caso contrário, introduza 2 para sair: ");
            scanf("%d", &opcao);

            if (opcao != 1) {
                printf("Saindo...\n");
                return 0;
            }

            // Solicitar ao agente que informe se a propriedade foi vendida
            printf("\nIntroduza 1 se a propriedade foi vendida, caso contrário, introduza qualquer número: ");
            scanf("%d", &vendida);
            atual->visita.propriedade_vendida = (vendida == 1) ? 1 : 0;

            // Marcar a visita como terminada
            atual->visita.visita_terminada = 1;

            // Solicitar ao agente que informe se o cliente compareceu
            printf("\nIntroduza 1 se o cliente compareceu, caso contrário, introduza qualquer número: ");
            scanf("%d", &cliente_compareceu);
            atual->visita.cliente_compareceu = (cliente_compareceu == 1) ? 1 : 0;

            // Limpar o buffer do stdin antes de usar fgets para strings
            fflush(stdin);

            // Entrada para o relatório
            printf("Relatório (até 3000 caracteres): ");
            fgets(atual->visita.relatorio, sizeof(atual->visita.relatorio), stdin);
            remove_newlineVisitas(atual->visita.relatorio);

            // Atualizar o tempo total de espera acumulado
            total_tempo_espera.horas += atual->visita.duracao / 60;
            total_tempo_espera.minutos += atual->visita.duracao % 60;

            // Imprimir informações sobre a próxima visita
            if (atual->seguinte != NULL) {
                printf("\nO próximo cliente tem os seguintes dados:\n");
                printf("-------------------------------------------------------------\n");
                printf("Dia: %d\tMês: %d\tAno: %d\n", atual->seguinte->visita.dia, atual->seguinte->visita.mes, atual->seguinte->visita.ano);
                printf("ID Cliente: %d\tID Agente: %d\tID Propriedade: %d\n", atual->seguinte->visita.id_cliente, atual->seguinte->visita.id_agente, atual->seguinte->visita.id_propriedade);
                printf("Duração da Visita: %d horas e %d minutos\n", atual->seguinte->visita.duracao / 60, atual->seguinte->visita.duracao % 60);
                printf("Horário de Marcação: %d:%d\n", atual->seguinte->visita.horario_marcacao / 60, atual->seguinte->visita.horario_marcacao % 60);
                printf("-------------------------------------------------------------\n");
            } else {
                printf("\nNão há mais clientes agendados para hoje.\n");
                printf("O seu turno terminou.\n");
                printf("Tempo total de espera acumulado: %d horas e %d minutos.\n", total_tempo_espera.horas, total_tempo_espera.minutos);
                printf("-------------------------------------------------------------\n");
                return 0;
            }
        }
        atual = atual->seguinte;
    }

    return 0;
}


int relatorio_contas_mes(LISTA_VISITA **iniLista_visita, LISTA_PROPRIEDADE **iniLista_propriedade){

    FILE *file = fopen("../Armazenamento/Texto/RelatorioContas.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro de texto !\n");
        return -1;
    }

    LISTA_VISITA *atual = *iniLista_visita;
    LISTA_PROPRIEDADE *propriedade_procura_preco = *iniLista_propriedade;
    double total_vendas = 0;

    for(int i =0; i<12; i++){
        total_vendas = 0;

        for(int j =0; j<31; j++) {
            atual = *iniLista_visita;

            while (atual != NULL) {

                if (atual->visita.mes == i && atual ->visita.dia == j) {

                    TEMPO visita = conversor_minutos_para_horas(atual->visita.horario_marcacao);
                    TEMPO duracao_visita = conversor_minutos_para_horas(atual->visita.duracao);

                    printf("-------------------------------------------------------------\n");
                    printf("-------------------------------------------------------------\n");
                    printf("-------------------------------------------------------------\n");
                    printf("-------------------------------------------------------------\n");
                    printf("Dia: %d\tMês: %d\tAno: %d\n", atual->visita.dia, atual->visita.mes, atual->visita.ano);
                    printf("ID Cliente: %d\tID Agente: %d\tID Propriedade: %d\n", atual->visita.id_cliente,
                           atual->visita.id_agente, atual->visita.id_propriedade);
                    printf("Duração: %d:%d \tHora Marcação: %d:%d\n", duracao_visita.horas, duracao_visita.minutos,
                           visita.horas, visita.minutos);
                    printf("Relatório: %s\n", atual->visita.relatorio);
                    printf("Detalhes Interesse Cliente: %s\n", atual->visita.detalhes_intresse_cliente);
                    printf("Cliente Compareceu: %s\n", atual->visita.cliente_compareceu ? "Sim" : "Não");
                    printf("Visita Terminou: %s\n", atual->visita.propriedade_vendida ? "Sim" : "Não");
                    printf("Casa Aberta: %s\n", atual->visita.casa_aberta ? "Sim" : "Não");
                    printf("Foi feita a visita no dia %d , no mês %d, do ano %d\n", atual->visita.dia, atual ->visita.mes, atual -> visita.ano);
                    printf("-------------------------------------------------------------\n");
                    printf("-------------------------------------------------------------\n");


                    if (atual->visita.propriedade_vendida == 1) {

                        while (propriedade_procura_preco != NULL) {
                            if (propriedade_procura_preco->propriedade.id_propriedade == atual->visita.id_propriedade) {

                                total_vendas += propriedade_procura_preco->propriedade.preco;

                            }

                            printf("A propriedade foi vendida por %.2f €",
                                   propriedade_procura_preco->propriedade.preco);
                        }

                    }

                    printf("-------------------------------------------------------------\n");
                    printf("-------------------------------------------------------------\n");
                    printf("-------------------------------------------------------------\n");
                    printf("-------------------------------------------------------------\n");

                }


                atual = atual->seguinte;

            }

            printf("-------------------------------------------------------------\n");
            printf("-------------------------------------------------------------\n");
            printf("-------------------------------------------------------------\n");
            printf("-------------------------------------------------------------\n");

            printf(" O total de vendas do mês %d foi de %.2f\n", i, total_vendas);

        }

    }

// saber quanto foi faturado por mes por tipo de propriedade;


    return 0;
}

void listar_visitas_de_hoje_por_agente(LISTA_VISITA *iniLista_visita) {
    if (iniLista_visita == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    int dia = dia_atual();
    int mes = mes_atual();
    int ano = ano_atual();

    // Solicita o ID do agente desejado ao usuário
    int id_agente_desejado;
    printf("Digite o ID do agente desejado: ");
    scanf("%d", &id_agente_desejado);

    // Variáveis auxiliares
    LISTA_VISITA *atual = iniLista_visita;
    LISTA_VISITA *proximo = NULL;
    LISTA_VISITA *temp = NULL;
    int trocado;
    int encontrou_visitas = 0;

    // Ordena as visitas por hora de marcação (ascendente)
    do {
        trocado = 0;
        atual = iniLista_visita;
        proximo = atual->seguinte;

        // Loop para percorrer a lista e fazer as trocas necessárias
        while (proximo != NULL) {
            // Converte as horas de marcação das visitas
            TEMPO hora_atual = conversor_minutos_para_horas(atual->visita.horario_marcacao);
            TEMPO hora_proximo = conversor_minutos_para_horas(proximo->visita.horario_marcacao);

            // Compara as horas de marcação das visitas e realiza a troca, se necessário
            if ((atual->visita.dia == dia) && (atual->visita.mes == mes) && (atual->visita.ano == ano) && (atual->visita.id_agente == id_agente_desejado) &&
                ((hora_atual.horas > hora_proximo.horas) || (hora_atual.horas == hora_proximo.horas && hora_atual.minutos > hora_proximo.minutos))) {
                // Troca os nós sem modificar as estruturas da lista
                if (atual == iniLista_visita) {
                    iniLista_visita = proximo;
                } else {
                    temp->seguinte = proximo;
                }
                atual->seguinte = proximo->seguinte;
                proximo->seguinte = atual;

                // Atualiza os ponteiros
                temp = proximo;
                proximo = atual->seguinte;

                trocado = 1; // Indica que houve uma troca
            } else {
                // Atualiza os ponteiros
                temp = atual;
                atual = proximo;
                proximo = proximo->seguinte;
            }
        }
    } while (trocado);

    // Lista as visitas ordenadas por hora de marcação
    printf("Lista de visitas do agente %d de hoje:\n", id_agente_desejado);
    atual = iniLista_visita;
    while (atual != NULL) {
        if ((atual->visita.dia == dia) && (atual->visita.mes == mes) && (atual->visita.ano == ano) && (atual->visita.id_agente == id_agente_desejado)) {
            encontrou_visitas = 1;
            TEMPO visita = conversor_minutos_para_horas(atual->visita.horario_marcacao);
            TEMPO duracao_visita = conversor_minutos_para_horas(atual->visita.duracao);

            printf("-------------------------------------------------------------\n");
            printf("Dia: %d\tMês: %d\tAno: %d\n", atual->visita.dia, atual->visita.mes, atual->visita.ano);
            printf("ID Cliente: %d\tID Agente: %d\tID Propriedade: %d\n", atual->visita.id_cliente, atual->visita.id_agente, atual->visita.id_propriedade);
            printf("Duração: %d:%d \tHora Marcação: %d:%d\n", duracao_visita.horas, duracao_visita.minutos, visita.horas, visita.minutos);
            printf("Relatório: %s\n", atual->visita.relatorio);
            printf("Detalhes Interesse Cliente: %s\n", atual->visita.detalhes_intresse_cliente);
            printf("Cliente Compareceu: %s\n", atual->visita.cliente_compareceu ? "Sim" : "Não");
            printf("Visita Terminou: %s\n", atual->visita.propriedade_vendida ? "Sim" : "Não");
            printf("Casa Aberta: %s\n", atual->visita.casa_aberta ? "Sim" : "Não");
            printf("-------------------------------------------------------------\n");
        }
        atual = atual->seguinte;
    }

    if (!encontrou_visitas) {
        printf("Nenhuma visita encontrada para o agente %d hoje.\n", id_agente_desejado);
    }
}

void ordenar_visitas_por_dia_agente(LISTA_VISITA **iniLista_visita) {
    // Verifica se a lista está vazia
    if (*iniLista_visita == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    // Solicita o ID do agente desejado ao usuário
    int id_agente_desejado;
    printf("Digite o ID do agente desejado: ");
    scanf("%d", &id_agente_desejado);

    // Solicita a data desejada ao usuário
    int dia_desejado, mes_desejado, ano_desejado;
    printf("Digite o dia desejado: ");
    scanf("%d", &dia_desejado);
    printf("Digite o mês desejado: ");
    scanf("%d", &mes_desejado);
    printf("Digite o ano desejado: ");
    scanf("%d", &ano_desejado);

    // Variáveis auxiliares
    LISTA_VISITA *atual = *iniLista_visita;
    LISTA_VISITA *proximo = NULL;
    LISTA_VISITA *temp = NULL;
    int trocado;

    // Ordena as visitas por hora de marcação (ascendente)
    do {
        trocado = 0;
        atual = *iniLista_visita;
        proximo = atual->seguinte;

        // Loop para percorrer a lista e fazer as trocas necessárias
        while (proximo != NULL) {
            // Converte as horas de marcação das visitas
            TEMPO hora_atual = conversor_minutos_para_horas(atual->visita.horario_marcacao);
            TEMPO hora_proximo = conversor_minutos_para_horas(proximo->visita.horario_marcacao);

            // Compara as horas de marcação das visitas e realiza a troca, se necessário
            if ((atual->visita.dia == dia_desejado) && (atual->visita.mes == mes_desejado) && (atual->visita.ano == ano_desejado) &&
                (atual->visita.id_agente == id_agente_desejado) &&
                ((hora_atual.horas > hora_proximo.horas) || (hora_atual.horas == hora_proximo.horas && hora_atual.minutos > hora_proximo.minutos))) {
                // Troca os nós sem modificar as estruturas da lista
                if (atual == *iniLista_visita) {
                    *iniLista_visita = proximo;
                } else {
                    temp->seguinte = proximo;
                }
                atual->seguinte = proximo->seguinte;
                proximo->seguinte = atual;

                // Atualiza os ponteiros
                temp = proximo;
                proximo = atual->seguinte;

                trocado = 1; // Indica que houve uma troca
            } else {
                // Atualiza os ponteiros
                temp = atual;
                atual = proximo;
                proximo = proximo->seguinte;
            }
        }
    } while (trocado);

    // Lista as visitas ordenadas por hora de marcação e data
    printf("Lista de visitas do agente %d do dia %d/%d/%d ordenadas por hora de marcação:\n", id_agente_desejado, dia_desejado, mes_desejado, ano_desejado);
    atual = *iniLista_visita;
    while (atual != NULL) {
        if ((atual->visita.dia == dia_desejado) && (atual->visita.mes == mes_desejado) && (atual->visita.ano == ano_desejado) && (atual->visita.id_agente == id_agente_desejado)) {
            TEMPO visita = conversor_minutos_para_horas(atual->visita.horario_marcacao);
            TEMPO duracao_visita = conversor_minutos_para_horas(atual->visita.duracao);

            printf("-------------------------------------------------------------\n");
            printf("Dia: %d\tMês: %d\tAno: %d\n", atual->visita.dia, atual->visita.mes, atual->visita.ano);
            printf("ID Cliente: %d\tID Agente: %d\tID Propriedade: %d\n", atual->visita.id_cliente, atual->visita.id_agente, atual->visita.id_propriedade);
            printf("Duração: %d:%d \tHora Marcação: %d:%d\n", duracao_visita.horas, duracao_visita.minutos, visita.horas, visita.minutos);
            printf("Relatório: %s\n", atual->visita.relatorio);
            printf("Detalhes Interesse Cliente: %s\n", atual->visita.detalhes_intresse_cliente);
            printf("Cliente Compareceu: %s\n", atual->visita.cliente_compareceu ? "Sim" : "Não");
            printf("Visita Terminou: %s\n", atual->visita.propriedade_vendida ? "Sim" : "Não");
            printf("Casa Aberta: %s\n", atual->visita.casa_aberta ? "Sim" : "Não");
            printf("-------------------------------------------------------------\n");
        }
        atual = atual->seguinte;
    }
}

void listar_visitas_por_dia_tipo_propriedade(LISTA_VISITA *iniLista_visita) {
    if (iniLista_visita == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    // Solicita a data desejada ao usuário
    int dia_desejado, mes_desejado, ano_desejado;
    printf("Digite o dia desejado: ");
    scanf("%d", &dia_desejado);
    printf("Digite o mês desejado: ");
    scanf("%d", &mes_desejado);
    printf("Digite o ano desejado: ");
    scanf("%d", &ano_desejado);

    // Solicita o tipo de propriedade desejado ao usuário
    int tipo_propriedade_desejado;
    printf("Digite o tipo de propriedade desejado: ");
    scanf("%d", &tipo_propriedade_desejado);

    // Variáveis auxiliares
    LISTA_VISITA *atual = iniLista_visita;
    TEMPO visita;
    TEMPO duracao_visita;

    // Lista as visitas do tipo de propriedade especificado e da data especificada
    printf("Lista de visitas do tipo %d de hoje:\n", tipo_propriedade_desejado);
    while (atual != NULL) {
        if ((atual->visita.dia == dia_desejado) && (atual->visita.mes == mes_desejado) && (atual->visita.ano == ano_desejado) &&
            (atual->visita.id_propriedade == tipo_propriedade_desejado)) {
            visita = conversor_minutos_para_horas(atual->visita.horario_marcacao);
            duracao_visita = conversor_minutos_para_horas(atual->visita.duracao);

            printf("-------------------------------------------------------------\n");
            printf("Dia: %d\tMês: %d\tAno: %d\n", atual->visita.dia, atual->visita.mes, atual->visita.ano);
            printf("ID Cliente: %d\tID Agente: %d\tID Propriedade: %d\n", atual->visita.id_cliente, atual->visita.id_agente, atual->visita.id_propriedade);
            printf("Duração: %d:%d \tHora Marcação: %d:%d\n", duracao_visita.horas, duracao_visita.minutos, visita.horas, visita.minutos);
            printf("Relatório: %s\n", atual->visita.relatorio);
            printf("Detalhes Interesse Cliente: %s\n", atual->visita.detalhes_intresse_cliente);
            printf("Cliente Compareceu: %s\n", atual->visita.cliente_compareceu ? "Sim" : "Não");
            printf("Visita Terminou: %s\n", atual->visita.propriedade_vendida ? "Sim" : "Não");
            printf("Casa Aberta: %s\n", atual->visita.casa_aberta ? "Sim" : "Não");
            printf("-------------------------------------------------------------\n");
        }
        atual = atual->seguinte;
    }
}

void listar_visitas_de_hoje_por_tipo_propriedade(LISTA_VISITA *iniLista_visita) {
    if (iniLista_visita == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    // Obtém a data atual
    int dia = dia_atual();
    int mes = mes_atual();
    int ano = ano_atual();

    // Solicita o tipo de propriedade desejado ao usuário
    int tipo_propriedade_desejado;
    printf("Digite o tipo de propriedade desejado: ");
    scanf("%d", &tipo_propriedade_desejado);

    // Variáveis auxiliares
    LISTA_VISITA *atual = iniLista_visita;
    TEMPO visita;
    TEMPO duracao_visita;

    // Lista as visitas do tipo de propriedade especificado e de hoje
    printf("Lista de visitas do tipo %d de hoje:\n", tipo_propriedade_desejado);
    while (atual != NULL) {
        if ((atual->visita.dia == dia) && (atual->visita.mes == mes) && (atual->visita.ano == ano) &&
            (atual->visita.id_propriedade == tipo_propriedade_desejado)) {
            visita = conversor_minutos_para_horas(atual->visita.horario_marcacao);
            duracao_visita = conversor_minutos_para_horas(atual->visita.duracao);

            printf("-------------------------------------------------------------\n");
            printf("Dia: %d\tMês: %d\tAno: %d\n", atual->visita.dia, atual->visita.mes, atual->visita.ano);
            printf("ID Cliente: %d\tID Agente: %d\tID Propriedade: %d\n", atual->visita.id_cliente, atual->visita.id_agente, atual->visita.id_propriedade);
            printf("Duração: %d:%d \tHora Marcação: %d:%d\n", duracao_visita.horas, duracao_visita.minutos, visita.horas, visita.minutos);
            printf("Relatório: %s\n", atual->visita.relatorio);
            printf("Detalhes Interesse Cliente: %s\n", atual->visita.detalhes_intresse_cliente);
            printf("Cliente Compareceu: %s\n", atual->visita.cliente_compareceu ? "Sim" : "Não");
            printf("Visita Terminou: %s\n", atual->visita.propriedade_vendida ? "Sim" : "Não");
            printf("Casa Aberta: %s\n", atual->visita.casa_aberta ? "Sim" : "Não");
            printf("-------------------------------------------------------------\n");
        }
        atual = atual->seguinte;
    }
}


void inserir_visitas_em_arquivo(LISTA_VISITA *iniLista_visita) {
    FILE *arquivo = fopen("../Armazenamento/Texto/Visitas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    LISTA_VISITA *aux = iniLista_visita;
    while (aux != NULL) {
        fprintf(arquivo, "%d %d %d %d %d %d %d %d %s %s %d %d %d\n",
                aux->visita.dia, aux->visita.mes, aux->visita.ano,
                aux->visita.id_cliente, aux->visita.id_agente, aux->visita.id_propriedade,
                aux->visita.horario_marcacao, aux->visita.duracao, aux->visita.relatorio,
                aux->visita.detalhes_intresse_cliente, aux->visita.cliente_compareceu,
                aux->visita.propriedade_vendida, aux->visita.casa_aberta);
        aux = aux->seguinte;
    }

    fclose(arquivo);
}

int carregar_visitas(LISTA_VISITA **iniLista_visita) {
    FILE *arquivo = fopen("../Armazenamento/Texto/Visitas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    char linha[256];
    int contador_visitas = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        LISTA_VISITA *nova_visita = (LISTA_VISITA *)malloc(sizeof(LISTA_VISITA));
        if (nova_visita == NULL) {
            printf("Erro de alocação de memória.\n");
            break;
        }

        // Dividir a linha em campos individuais
        sscanf(linha, "%d %d %d %d %d %d %d %d %s %s %d %d %d",
               &nova_visita->visita.dia, &nova_visita->visita.mes, &nova_visita->visita.ano,
               &nova_visita->visita.id_cliente, &nova_visita->visita.id_agente, &nova_visita->visita.id_propriedade,
               &nova_visita->visita.horario_marcacao, &nova_visita->visita.duracao, nova_visita->visita.relatorio,
               nova_visita->visita.detalhes_intresse_cliente, &nova_visita->visita.cliente_compareceu,
               &nova_visita->visita.propriedade_vendida, &nova_visita->visita.casa_aberta);

        nova_visita->seguinte = NULL;
        if (*iniLista_visita == NULL) {
            *iniLista_visita = nova_visita;
        } else {
            LISTA_VISITA *aux = *iniLista_visita;
            while (aux->seguinte != NULL) {
                aux = aux->seguinte;
            }
            aux->seguinte = nova_visita;
        }

        contador_visitas++;
    }

    printf("Total de visitas carregadas: %d\n", contador_visitas);
    fclose(arquivo);
    return contador_visitas;
}


void historico_visitas(LISTA_VISITA *iniLista_visita) {
    if (iniLista_visita == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    // Solicita o ID da propriedade ao usuário
    int id_propriedade_desejada;
    printf("Digite o ID da propriedade para verificar o histórico de visitas: ");
    scanf("%d", &id_propriedade_desejada);

    // Obtém a data atual
    int dia_atual_visita = dia_atual();
    int mes_atual_visita = mes_atual();
    int ano_atual_visita = ano_atual();

    // Percorre a lista de visitas e imprime as visitas passadas para a propriedade especificada
    LISTA_VISITA *atual = iniLista_visita;
    printf("Histórico de visitas para a propriedade %d:\n", id_propriedade_desejada);
    while (atual != NULL) {
        if (atual->visita.id_propriedade == id_propriedade_desejada &&
            (atual->visita.ano < ano_atual_visita ||
             (atual->visita.ano == ano_atual_visita && atual->visita.mes < mes_atual_visita) ||
             (atual->visita.ano == ano_atual_visita && atual->visita.mes == mes_atual_visita && atual->visita.dia < dia_atual_visita))) {
            printf("-------------------------------------------------------------\n");
            printf("Dia: %d\tMês: %d\tAno: %d\n", atual->visita.dia, atual->visita.mes, atual->visita.ano);
            printf("ID Cliente: %d\tID Agente: %d\n", atual->visita.id_cliente, atual->visita.id_agente);
            printf("Hora Marcação: %d:%d\n", atual->visita.horario_marcacao / 60, atual->visita.horario_marcacao % 60);
            printf("Duração: %d minutos\n", atual->visita.duracao);
            printf("Relatório: %s\n", atual->visita.relatorio);
            printf("Detalhes Interesse Cliente: %s\n", atual->visita.detalhes_intresse_cliente);
            printf("Cliente Compareceu: %s\n", atual->visita.cliente_compareceu ? "Sim" : "Não");
            printf("Visita Terminou: %s\n", atual->visita.propriedade_vendida ? "Sim" : "Não");
            printf("Casa Aberta: %s\n", atual->visita.casa_aberta ? "Sim" : "Não");
        }
        atual = atual->seguinte;
    }
}

void historico_visitas_logado(LISTA_VISITA *iniLista_visita, int id_agente_logado) {
    if (iniLista_visita == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    // Verifica se o agente está logado
    if (id_agente_logado == -1) {
        printf("Apenas agentes autenticados podem acessar esta função.\n");
        return;
    }

    // Solicita o ID da propriedade ao usuário
    int id_propriedade_desejada;
    printf("Digite o ID da propriedade para verificar o histórico de visitas: ");
    scanf("%d", &id_propriedade_desejada);

    // Obtém a data atual
    int dia_atual_visita = dia_atual();
    int mes_atual_visita = mes_atual();
    int ano_atual_visita = ano_atual();

    // Percorre a lista de visitas e imprime as visitas passadas para a propriedade especificada
    LISTA_VISITA *atual = iniLista_visita;
    printf("Histórico de visitas para a propriedade %d:\n", id_propriedade_desejada);
    while (atual != NULL) {
        if (atual->visita.id_propriedade == id_propriedade_desejada &&
            atual->visita.id_agente == id_agente_logado &&
            (atual->visita.ano < ano_atual_visita ||
             (atual->visita.ano == ano_atual_visita && atual->visita.mes < mes_atual_visita) ||
             (atual->visita.ano == ano_atual_visita && atual->visita.mes == mes_atual_visita && atual->visita.dia < dia_atual_visita))) {
            printf("-------------------------------------------------------------\n");
            printf("Dia: %d\tMês: %d\tAno: %d\n", atual->visita.dia, atual->visita.mes, atual->visita.ano);
            printf("ID Cliente: %d\tID Agente: %d\n", atual->visita.id_cliente, atual->visita.id_agente);
            printf("Hora Marcação: %d:%d\n", atual->visita.horario_marcacao / 60, atual->visita.horario_marcacao % 60);
            printf("Duração: %d minutos\n", atual->visita.duracao);
            printf("Relatório: %s\n", atual->visita.relatorio);
            printf("Detalhes Interesse Cliente: %s\n", atual->visita.detalhes_intresse_cliente);
            printf("Cliente Compareceu: %s\n", atual->visita.cliente_compareceu ? "Sim" : "Não");
            printf("Visita Terminou: %s\n", atual->visita.propriedade_vendida ? "Sim" : "Não");
            printf("Casa Aberta: %s\n", atual->visita.casa_aberta ? "Sim" : "Não");
        }
        atual = atual->seguinte;
    }
}


void listar_visitas_por_agente(LISTA_VISITA *iniLista_visita, AGENTE agentes[], int num_agentes) {
    // Verifica se a lista de visitas está vazia
    if (iniLista_visita == NULL) {
        printf("Lista de visitas vazia\n");
        return;
    }

    // Verifica se a lista de agentes está vazia
    if (num_agentes == 0) {
        printf("Lista de agentes vazia\n");
        return;
    }

    // Obtém a data atual
    int dia_atual_visita = dia_atual();
    int mes_atual_visita = mes_atual();
    int ano_atual_visita = ano_atual();

    // Cabeçalho da tabela
    printf("┌─────────────────────────────┬────────┬──────────────┐\n");
    printf("│ Nome do Agente              │   ID   │ Visitas Mês  │\n");
    printf("├─────────────────────────────┼────────┼──────────────┤\n");

    // Percorre a lista de agentes
    for (int i = 0; i < num_agentes; i++) {
        // Verifica se o agente tem nome
        if (strlen(agentes[i].nome) > 0) {
            // Contador de visitas para o agente atual
            int contador_visitas = 0;

            // Percorre a lista de visitas e conta as visitas realizadas pelo agente no mês atual
            LISTA_VISITA *aux_visita = iniLista_visita;
            while (aux_visita != NULL) {
                if (aux_visita->visita.id_agente == agentes[i].id_agente &&
                    aux_visita->visita.ano == ano_atual_visita &&
                    aux_visita->visita.mes == mes_atual_visita) {
                    contador_visitas++;
                }
                aux_visita = aux_visita->seguinte;
            }

            // Imprime o resultado para o agente atual em formato de tabela
            printf("│ %-27s │ %6d │ %12d │\n", agentes[i].nome, agentes[i].id_agente, contador_visitas);
        }
    }

    // Rodapé da tabela
    printf("└─────────────────────────────┴────────┴──────────────┘\n");
}


int simular_agendar_visita_cliente(LISTA_VISITA **iniLista_visita, LISTA_VISITA **fimLista, int id_cliente_logado,AGENTE agente_imobiliario[],LISTA_PROPRIEDADE *iniLista_propriedade){

    VISITA nova_visita;
    LISTA_VISITA *nova = NULL;

    nova = (LISTA_VISITA *) calloc(1, sizeof(LISTA_VISITA));
    if (nova == NULL) {
        printf("Erro ao alocar memoria para nova visita \n");
        return -1;
    }

    // STRUCT com valores que são para a função de converter horas para minutos:
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

    // Valores para poder serem alterados no momento de atendimento.
    nova_visita.id_cliente = id_cliente_logado;
    nova_visita.visita_terminada = 0;
    nova_visita.propriedade_vendida = -1;
    nova_visita.cliente_compareceu = -1;

    while (1) {
        printf("Casa Aberta (1 para sim, 0 para não): ");
        scanf("%d", &nova_visita.casa_aberta);
        if (nova_visita.casa_aberta == 0 || nova_visita.casa_aberta == 1){
            break;
        }
        printf("Entrada inválida. Por favor, insira 1 para sim ou 0 para não.\n");
    }

    switch (nova_visita.casa_aberta) {

        case 1:

            nova_visita.propriedade_vendida = 0;
            nova_visita.cliente_compareceu = 1;

            printf("Por favor, insira o ID do cliente: ");
            scanf("%d", &id_cliente_logado);

            imprime_todas_propriedades_populares_negocio_por_concluir(iniLista_propriedade);
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

            nova_visita.dia = dia_atual();
            nova_visita.mes = mes_atual();
            nova_visita.ano = ano_atual();

            while(1){

                while(1){
                    horario.horas = hora_atual();
                    horario.minutos = minuto_atual();

                    nova_visita.horario_marcacao = conversor_horas_para_minutos(horario.horas,horario.minutos);

                    if (nova_visita.horario_marcacao >= 0 && nova_visita.horario_marcacao <= 1440){
                        break;
                    }else{
                        printf("Hora da marcação inválida. Por favor, venha a uma hora entre 9 e as 19 horas\n");
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

                horario_valido = verifica_disponibilidade_agente_visita(*iniLista_visita, nova_visita.id_agente ,nova_visita.horario_marcacao, nova_visita.duracao,nova_visita.dia,nova_visita.mes,nova_visita.ano);

                if(horario_valido != -1){
                    break;
                }else if(nova_visita.horario_marcacao > HORA_FIM_AGENTE_IMOBILIARIO){

                }else{ printf("\nIntroduza  valores válidos !!!\n");}

            }



            // Limpar o buffer do stdin antes de usar fgets para strings
            fflush(stdin);

            // Entrada para relatório
            printf("Relatório (até 3000 caracteres): ");
            fgets(nova_visita.relatorio, sizeof(nova_visita.relatorio), stdin);
            remove_newlineVisitas(nova_visita.relatorio);

            // Entrada para detalhes de interesse do cliente
            printf("Detalhes de Interesse do Cliente (até 3000 caracteres): ");
            fgets(nova_visita.detalhes_intresse_cliente, sizeof(nova_visita.detalhes_intresse_cliente), stdin);
            remove_newlineVisitas(nova_visita.detalhes_intresse_cliente);



            break;

        case 0:

            nova_visita.cliente_compareceu = -1;
            // Entrada para o ano mês e dia
            while (1) {

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

                while (1){
                    printf("Ano: ");
                    fflush(stdin);
                    scanf("%d", &nova_visita.ano);
                    if (nova_visita.ano > 0) break;
                    printf("Ano inválido. Por favor, insira um ano válido.\n");
                    fflush(stdout);
                }

                if(verifica_dia_mes_ano(nova_visita.dia, nova_visita.mes, nova_visita.ano) == 0){
                    break;
                }else{
                    printf("\nData inválida insira uma data valida.\n");
                }

            }

            while(1){

                imprime_todas_propriedades_nao_populares_negocio_por_concluir(iniLista_propriedade);

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
                    nova_visita.horario_marcacao = conversor_horas_para_minutos(horario.horas,horario.minutos);

                    if (nova_visita.horario_marcacao >= 0 && nova_visita.horario_marcacao <= 1440){
                        break;
                    }else{
                        printf("Hora da marcação inválida. Por favor, insira um valor entre as 9 horas e as 19 horas.\n");
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

                horario_valido = verifica_disponibilidade_agente_visita(*iniLista_visita, nova_visita.id_agente ,nova_visita.horario_marcacao, nova_visita.duracao, nova_visita.dia,nova_visita.mes,nova_visita.ano);


                if(horario_valido != -1){
                    break;
                }else{ printf("\nIntroduza  valores válidos !!!\n");}

            }


            // Limpar o buffer do stdin antes de usar fgets para strings
            fflush(stdin);

            // Entrada para relatório

            /*
            printf("Relatório (até 3000 caracteres): ");
            fgets(nova_visita.relatorio, sizeof(nova_visita.relatorio), stdin);
            remove_newline1(nova_visita.relatorio);
             */

            // Entrada para detalhes de interesse do cliente
            printf("Detalhes de Interesse do Cliente (até 3000 caracteres): ");
            fgets(nova_visita.detalhes_intresse_cliente, sizeof(nova_visita.detalhes_intresse_cliente), stdin);
            remove_newlineVisitas(nova_visita.detalhes_intresse_cliente);

            break;

        default:
            printf("\nErro casa aberta \n");
            return -1;
    }


    //// Fim interação utilizador

        printf("A simulaçao de visita pode ser agendada");

    return 0;
}
