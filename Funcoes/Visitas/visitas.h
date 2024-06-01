#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../TiposDados/TiposDados.h"
#include "time.h"

#ifndef PROGRAMA_VISITAS_H
#define PROGRAMA_VISITAS_H

void remove_newline1(char *string);

int conversor_horas_para_minutos(int hora, int minutos_antes);

TEMPO conversor_minutos_para_horas(int minutos);

int verifica_dia_mes_ano(int dia, int mes, int ano);

int verifica_disponibilidade_agente_visita(LISTA_VISITA *iniLista_visita, int agente_verificar, int hora_em_minutos_verificar, int duraco_visita_verifiar);

int agendar_visita_cliente(LISTA_VISITA **iniLista_visita, LISTA_VISITA **fimLista, int id_cliente_logado,AGENTE agente_imobiliario[],LISTA_PROPRIEDADE *iniLista_propriedade);

void listar_todas_visitas(LISTA_VISITA *iniLista_visita);

int dia_atual();

int mes_atual();

int ano_atual();

int contador_visitas(LISTA_VISITA **iniLista);

int listar_visita_dia();


#endif //PROGRAMA_VISITAS_H