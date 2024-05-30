#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../TiposDados/TiposDados.h"

#ifndef PROGRAMA_AGENTESIMOBILIARIOS_H
#define PROGRAMA_AGENTESIMOBILIARIOS_H
int inserir_agente_imobiliario(AGENTE agente_imobiliario[], AGENTE novo_agente, int posicaoInserir);
int editar_agente_imobiliario(AGENTE agente_imobiliario[], AGENTE agente_editado,int id_procura);
int criar_agente_imobiliario(AGENTE agente_imobiliario[], AGENTE novo_agente);
int imprimir_agente_imobiliario(AGENTE agente_imobiliario[], int posicaoImprimir);
int remover_agente_imobiliario(AGENTE agente_imobiliario[],int id_procura);
int listar_agente_imobiliario_alfabeto(AGENTE agente_imobiliario[]);
int listar_agente_imobiliario_idade(AGENTE agente_imobiliario[]);
int inserir_no_ficheiro_agente_imobiliario(AGENTE agente_imobiliario[]);
int carregar_do_ficheiro_agente_imobiliario(AGENTE agente_imobiliario[]);
#endif //PROGRAMA_AGENTESIMOBILIARIOS_H
