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
    printf("┌────────────────────────────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                                   Menu Agente Imobiliário                                          │\n");
    printf("├──────────────────────┬─────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│   Opção              │   Descrição                                                                 │\n");
    printf("├──────────────────────┼─────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│   1                  │   Gerir tipos de propriedades                                               │\n");
    printf("├──────────────────────┼─────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│   2                  │   Listar as minhas visitas do dia por hora ascendente                       │\n");
    printf("├──────────────────────┼─────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│   3                  │   Listar as minhas visitas de um determinado dia por hora ascendente        │\n");
    printf("├──────────────────────┼─────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│   4                  │   Listar as visitas em que o cliente nao compareceu a um determinado dia    │\n");
    printf("├──────────────────────┼─────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│   5                  │   Saber o histórico de visitas de uma propriedade                           │\n");
    printf("├──────────────────────┼─────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│   6                  │   Simular a realização de uma visita                                        │\n");
    printf("├──────────────────────┼─────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│   7                  │   Atender Visita                                                            │\n");
    printf("├──────────────────────┼─────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│   8                  │   Gerar relatório de contas por mes de vendas                               │\n");
    printf("├──────────────────────┼─────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│   9                  │   Editar Perfil                                                             │\n");
    printf("├──────────────────────┼─────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│   10                 │   Sair                                                                      │\n");
    printf("└──────────────────────┴─────────────────────────────────────────────────────────────────────────────┘\n");


}

void menuCliente() {
    printf("┌───────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                             Menu Cliente                                  │\n");
    printf("├──────────────────────┬────────────────────────────────────────────────────┤\n");
    printf("│   Opção              │   Descrição                                        │\n");
    printf("├──────────────────────┼────────────────────────────────────────────────────┤\n");
    printf("│   1                  │   Marcar visita para uma propriedade               │\n");
    printf("├──────────────────────┼────────────────────────────────────────────────────┤\n");
    printf("│   2                  │   Editar Perfil                                    │\n");
    printf("├──────────────────────┼────────────────────────────────────────────────────┤\n");
    printf("│   3                  │   Sair                                             │\n");
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
    printf("│     6      │ Historico de Visitas de todos os agentes uma determinada propriedade         │\n");
    printf("│     7      │ Visitas que realizaram cada agente este mes                                  │\n");
    printf("│     8      │ Gerir Clientes                                                               │\n");
    printf("│     9      │ Gerar um relatório por dia e por mês de contas                               │\n");
    printf("│     10     │ Gerar um relatório de todos os agentes                                       │\n");
    printf("│     11     │ Editar perfil                                                                │\n");
    printf("│     12     │ Sair                                                                         │\n");
    printf("└────────────┴──────────────────────────────────────────────────────────────────────────────┘\n");

}

void submenuvisitas() {


    printf("┌──────────────────────────────────────────────────────────────────────┐\n");
    printf("│                            Gerir Visitas                             │\n");
    printf("├───────┬──────────────────────────────────────────────────────────────┤\n");
    printf("│ Opção │                         Descrição                            │\n");
    printf("├───────┼──────────────────────────────────────────────────────────────┤\n");
    printf("│   1   │ Visitas de hoje por hora ascendente                          │\n");
    printf("│   2   │ Visitas de um determinado dia por hora ascendente            │\n");
    printf("│   3   │ Visitas de hoje de um determinado agente                     │\n");
    printf("│   4   │ Visitas de um determinado dia para um determinado agente     │\n");
    printf("│   5   │ Visitas de hoje por tipo de propriedade                      │\n");
    printf("│   6   │ Visitas de um determinado dia por tipo de propriedade        │\n");
    printf("│   7   │ Visitas do dia em que o cliente não compareceu               │\n");
    printf("│   8   │ Sair                                                         │\n");
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