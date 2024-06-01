#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../TiposDados/TiposDados.h"
#include "../Menu/menu.h"

#ifndef PROGRAMA_AGENTESIMOBILIARIOS_H
#define PROGRAMA_AGENTESIMOBILIARIOS_H

int inserir_agente_imobiliario_editado(AGENTE *agente_imobiliario, AGENTE novo_agente);
int inserir_agente_imobiliario(AGENTE *agente_imobiliario, AGENTE novo_agente, int *posicaoInserir);


// Para esta função apenas e editado a disponibilidade os restantes dados não serao inseridos por causa da outra função ter verificações que não o permitem (no caso de )

int criar_agente_imobiliario(AGENTE agente_imobiliario[]);

void inserir_agentes_em_arquivo(AGENTE agente_imobiliario[]);

void carregar_agentes_do_arquivo(AGENTE agente_imobiliario[]);

int editar_agente_imobiliario(AGENTE agente_imobiliario[]) ;


int remover_agente_imobiliario(AGENTE agente_imobiliario[], int id_procura) ;

void tornar_agente_indisponivel(AGENTE agente_imobiliario[]);

int listar_agente_imobiliario(AGENTE agente_imobiliario[]);

int listar_agente_imobiliario_alfabeto(AGENTE agente_imobiliario[]);

int listar_agente_imobiliario_idade(AGENTE agente_imobiliario[]);

int listar_agente_imobiliario_disponiveis(AGENTE agente_imobiliario[]);

int verificar_agente_imobiliario_disponiveis(AGENTE agente_imobiliario[], int id_agente_verificar)
#endif //PROGRAMA_AGENTESIMOBILIARIOS_H
