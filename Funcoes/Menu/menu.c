#include <stdio.h>
#include <stdlib.h>
#include <string.h>





void submenupropriedadeAgente() {
        printf("Gerir tipos de propriedades:\n");
        printf("1. Criar propriedade\n");
        printf("2. Editar propriedade\n");
        printf("3. Remover propriedade\n");
        printf("4. Listar propriedades\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        printf("\n");
}

void submenuagentes() {
    int opcao;

        printf("Gerir Agentes:\n");
        printf("1. Criar agentes\n");
        printf("2. Editar agentes\n");
        printf("3. Remover agentes\n");
        printf("4. Listar todos os agentes\n");
        printf("5. Colocar agente como Indisponivel");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        printf("\n");
    }


void sair() {
    printf("Saindo do programa.\n");
    exit(0);
}

//Menu /agente imobiliario

void menuAgente() {
    printf("Menu Principal:\n");
    printf("1. Gerir tipos de propriedades\n");
    printf("2. Editar Perfil\n");
    printf("3. Listar as visitas do dia por hora ascendente\n");
    printf("6. Saber o historico de visitas de uma determinada propriedade\n");
    printf("7. Simular a realização de uma visita\n");
    printf("3. Sair\n");
    printf("Escolha uma opção: ");
}

void menuAdmin(){
    printf("Menu Principal:\n");
    printf("1. Gerir tipos de propriedades\n");
    printf("2. Quanto fatorou cada propriedade hoje e este mes\n");
    printf("3. Historico de visitas de uma determinada propriedade\n");
    printf("4. Gerir agentes\n");
    printf("5. Quantas visitas realizou cada agente no dia e em determinado dia\n");
    printf("6. Listar agentes por ordem alfabética \n");
    printf("7. Listar agentes por idade ascendente \n");
    printf("8. Listar todas as visitas do dia por hora ascendente\n");
    printf("9. Simular a realização de uma visita\n");
    printf("10. Listar as visitas em que o cliente nao compareceu num determinado dia\n");
    printf("11. Gerar um relatorio por dia e por mes de contas");
    printf("12. Gerar um relatorio de todos os agentes");
    printf("13. Sair\n");
    printf("Escolha uma opção: ");
}
