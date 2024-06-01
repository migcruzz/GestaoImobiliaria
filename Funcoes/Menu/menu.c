#include <stdio.h>
#include <stdlib.h>
#include <string.h>





void submenupropriedadeAgente() {
    printf("┌───────────────────────────────────────────────────────────────────────┐\n");
    printf("│                   Gerir Tipos de Propriedades (Agente)                │\n");
    printf("├───────┬───────────────────────────────────────────────────────────────┤\n");
    printf("│ Opção │                           Descrição                           │\n");
    printf("├───────┼───────────────────────────────────────────────────────────────┤\n");
    printf("│   1   │ Criar propriedade                                             │\n");
    printf("│   2   │ Editar propriedade                                            │\n");
    printf("│   3   │ Remover propriedade                                           │\n");
    printf("│   4   │ Listar propriedades                                           │\n");
    printf("│   5   │ Sair                                                          │\n");
    printf("└───────┴───────────────────────────────────────────────────────────────┘\n");
    printf("\n");
}



void submenuagentes() {
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                      Gerir Agentes                          │\n");
    printf("├───────┬─────────────────────────────────────────────────────┤\n");
    printf("│ Opção │                   Descrição                         │\n");
    printf("├───────┼─────────────────────────────────────────────────────┤\n");
    printf("│   1   │ Criar agentes                                       │\n");
    printf("│   2   │ Editar agentes                                      │\n");
    printf("│   3   │ Remover agentes                                     │\n");
    printf("│   4   │ Listar todos os agentes                             │\n");
    printf("│   5   │ Listar agentes por ordem alfabética                 │\n");
    printf("│   6   │ Listar agentes por idade ascendente                 │\n");
    printf("│   7   │ Listar agentes disponiveis                          │\n");
    printf("│   8   │ Colocar agente como Indisponível                    │\n");
    printf("│   9   │ Sair                                                │\n");
    printf("└───────┴─────────────────────────────────────────────────────┘\n");
    printf("\n");
}

void sair() {
    printf("Saindo do programa.\n");
    exit(0);
}

//Menu /agente imobiliario

void menuAgente() {
    printf("┌───────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                          Menu Agente Imobiliário                          │\n");
    printf("├──────────────────────┬────────────────────────────────────────────────────┤\n");
    printf("│   Opção              │   Descrição                                        │\n");
    printf("├──────────────────────┼────────────────────────────────────────────────────┤\n");
    printf("│   1                  │   Gerir tipos de propriedades                      │\n");
    printf("├──────────────────────┼────────────────────────────────────────────────────┤\n");
    printf("│   2                  │   Listar as visitas do dia por hora ascendente     │\n");
    printf("├──────────────────────┼────────────────────────────────────────────────────┤\n");
    printf("│   3                  │   Saber o histórico de visitas de uma propriedade  │\n");
    printf("├──────────────────────┼────────────────────────────────────────────────────┤\n");
    printf("│   4                  │   Simular a realização de uma visita               │\n");
    printf("├──────────────────────┼────────────────────────────────────────────────────┤\n");
    printf("│   5                  │   Editar Perfil                                    │\n");
    printf("├──────────────────────┼────────────────────────────────────────────────────┤\n");
    printf("│   6                  │   Sair                                             │\n");
    printf("└──────────────────────┴────────────────────────────────────────────────────┘\n");
}

void menuCliente() {
    printf("┌───────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                             Menu Cliente                                  │\n");
    printf("├──────────────────────┬────────────────────────────────────────────────────┤\n");
    printf("│   Opção              │   Descrição                                        │\n");
    printf("├──────────────────────┼────────────────────────────────────────────────────┤\n");
    printf("│   1                  │   Pesquisar propriedades                           │\n");
    printf("├──────────────────────┼────────────────────────────────────────────────────┤\n");
    printf("│   2                  │   Ver detalhes de uma propriedade                  │\n");
    printf("├──────────────────────┼────────────────────────────────────────────────────┤\n");
    printf("│   3                  │   Marcar visita para uma propriedade               │\n");
    printf("├──────────────────────┼────────────────────────────────────────────────────┤\n");
    printf("│   4                  │   Listar visitas agendadas                         │\n");
    printf("├──────────────────────┼────────────────────────────────────────────────────┤\n");
    printf("│   5                  │   Cancelar visita agendada                         │\n");
    printf("├──────────────────────┼────────────────────────────────────────────────────┤\n");
    printf("│   6                  │   Editar Perfil                                    │\n");
    printf("├──────────────────────┼────────────────────────────────────────────────────┤\n");
    printf("│   7                  │   Sair                                             │\n");
    printf("└──────────────────────┴────────────────────────────────────────────────────┘\n");
}


void menuAdmin(){
    printf("┌───────────────────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                                      Menu Principal Administrador                         │\n");
    printf("├────────────┬──────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│   Opção    │                                 Descrição                                    │\n");
    printf("├────────────┼──────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│     1      │ Gerir tipos de propriedades                                                  │\n");
    printf("│     2      │ Quanto faturou cada propriedade hoje e este mês                              │\n");
    printf("│     3      │ Gerir agentes                                                                │\n");
    printf("│     4      │ Listar visitas                                                               │\n");
    printf("│     5      │ Simular a realização de uma visita                                           │\n");
    printf("│     6      │ Gerir Clientes                                                               │\n");
    printf("│     7      │ Gerar um relatório por dia e por mês de contas                               │\n");
    printf("│     8      │ Gerar um relatório de todos os agentes                                       │\n");
    printf("│     9      │ Editar perfil                                                                │\n");
    printf("│    10      │ Sair                                                                         │\n");
    printf("└────────────┴──────────────────────────────────────────────────────────────────────────────┘\n");



}

void submenuvisitas() {


    printf("┌──────────────────────────────────────────────────────────────────────┐\n");
    printf("│                            Gerir Visitas                             │\n");
    printf("├───────┬──────────────────────────────────────────────────────────────┤\n");
    printf("│ Opção │                         Descrição                            │\n");
    printf("├───────┼──────────────────────────────────────────────────────────────┤\n");
    printf("│   1   │ Visitas de hoje por hora ascendente                          │\n");
    printf("│   2   │ Visitas de um dia (data) de um agente                        │\n");
    printf("│   3   │ Todas as visitas de um determinado tipo de propriedade       │\n");
    printf("│   4   │ Visitas do dia em que o cliente não compareceu               │\n");
    printf("│   5   │ Sair                                                         │\n");
    printf("└───────┴──────────────────────────────────────────────────────────────┘\n");
    printf("\n");
}


void submenucliente() {
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                      Gerir Clientes                         │\n");
    printf("├───────┬─────────────────────────────────────────────────────┤\n");
    printf("│ Opção │                   Descrição                         │\n");
    printf("├───────┼─────────────────────────────────────────────────────┤\n");
    printf("│   1   │ Criar clientes                                      │\n");
    printf("│   2   │ Editar clientes                                     │\n");
    printf("│   3   │ Remover clientes                                    │\n");
    printf("│   4   │ Listar clientes por ordem alfabética                │\n");
    printf("│   5   │ Listar clientes por o NIF                           │\n");
    printf("│   6   │ Sair                                                │\n");
    printf("└───────┴─────────────────────────────────────────────────────┘\n");
    printf("\n");
}