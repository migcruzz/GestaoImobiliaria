#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../TiposDados/TiposDados.h"
#include "time.h"

#ifndef PROGRAMA_VISITAS_H
#define PROGRAMA_VISITAS_H

void remove_newlineVisitas(char *string);

int conversor_horas_para_minutos(int hora, int minutos_antes);

TEMPO conversor_minutos_para_horas(int minutos);

int verifica_dia_mes_ano(int dia, int mes, int ano);

int agendar_visita_cliente(LISTA_VISITA **iniLista_visita, LISTA_VISITA **fimLista, int id_cliente_logado,AGENTE agente_imobiliario[],LISTA_PROPRIEDADE *iniLista_propriedade);

void listar_todas_visitas(LISTA_VISITA *iniLista_visita);

void ordenar_visitas_por_hora_ascendente(LISTA_VISITA **iniLista_visita);

int verifica_disponibilidade_agente_visita(LISTA_VISITA *iniLista_visita, int agente_verificar, int hora_visita, int duracao_visita, int dia_verificar, int mes_verificar, int ano_verificar);

int dia_atual();

int mes_atual();

int ano_atual();

int contador_visitas(LISTA_VISITA **iniLista);

int listar_visita_dia();

void listar_visitas_de_hoje_por_hora_ascendente(LISTA_VISITA *iniLista_visita);

void inserir_visitas_em_arquivo(LISTA_VISITA *iniLista_visita);

void carregar_visitas(LISTA_VISITA **iniLista_visita);

void listar_visitas_de_hoje_por_agente(LISTA_VISITA *iniLista_visita);
void ordenar_visitas_por_dia_agente(LISTA_VISITA **iniLista_visita);
void listar_visitas_por_dia_tipo_propriedade(LISTA_VISITA *iniLista_visita);
void listar_visitas_de_hoje_por_tipo_propriedade(LISTA_VISITA *iniLista_visita);
void listar_visitas_de_hoje_por_hora_ascendente_agente_logado(LISTA_VISITA *iniLista_visita, int id_agente_logado);
void listar_visitas_de_dia_ascendente_agente_logado(LISTA_VISITA *iniLista_visita, int id_agente_logado);
void listar_visitas_cliente_nao_compareceu_agente_logado(LISTA_VISITA *iniLista_visita, int id_agente_logado);
void historico_visitas(LISTA_VISITA *iniLista_visita);
void historico_visitas_logado(LISTA_VISITA *iniLista_visita, int id_agente_logado);
void listar_visitas_por_agente(LISTA_VISITA *iniLista_visita, AGENTE agentes[]);
int simular_agendar_visita_cliente(LISTA_VISITA **iniLista_visita, LISTA_VISITA **fimLista, int id_cliente_logado,AGENTE agente_imobiliario[],LISTA_PROPRIEDADE *iniLista_propriedade);
void listar_visitas_de_hoje_por_hora_ascendente_casa_aberta_agente_logado_vistita_nao_concluida(LISTA_VISITA **iniLista_visita, int id_agente_logado);
int atender_visitas(LISTA_VISITA **iniLista_visita, int id_agente_logado);
int relatorio_contas_mes(LISTA_VISITA **iniLista_visita, LISTA_PROPRIEDADE **iniLista_propriedade);

#endif //PROGRAMA_VISITAS_H