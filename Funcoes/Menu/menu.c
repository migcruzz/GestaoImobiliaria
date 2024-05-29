#include <stdio.h>
#include <stdlib.h>
#include <string.h>




void submenupropriedade() {
    int opcao;
    while (1) {
        printf("Gerir tipos de propriedades:\n");
        printf("1. Criar propriedade\n");
        printf("2. Editar propriedade\n");
        printf("3. Remover propriedade\n");
        printf("4. Listar propriedades\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf(" escolheu a Sub-opção 1.1.\n");
                break;
            case 2:
                printf(" escolheu a Sub-opção 1.2.\n");
                break;
            case 3:
                printf(" escolheu a Sub-opção 1.3.\n");
                break;

            case 4:
                printf(" escolheu a Sub-opção 1.4.\n");
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
        printf("\n");
    }
}

void submenuagentes() {
    int opcao;
    while (1) {
        printf("Submenu 2:\n");
        printf("1. Criar agentes\n");
        printf("2. Sub-opção 2.2\n");
        printf("3. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Você escolheu a Sub-opção 2.1.\n");
                break;
            case 2:
                printf("Você escolheu a Sub-opção 2.2.\n");
                break;
            case 3:
                return;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
        printf("\n");
    }
}

void sair() {
    printf("Saindo do programa.\n");
    exit(0);
}

void menu() {
    printf("Menu Principal:\n");
    printf("1. Gerir tipos de propriedades\n");
    printf("2. Gerir agentes\n");
    printf("2. Gerir agentes\n");
    printf("3. Sair\n");
    printf("Escolha uma opção: ");
}

