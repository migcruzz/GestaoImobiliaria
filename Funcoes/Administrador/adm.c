#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../VariaveisGlobais/variaveis_globais.h"
#include "../../TiposDados/TiposDados.h"


int inserir_administrador(ADMIN administrador[], ADMIN novo_administrador, int posicaoInserir) {

    if(administrador[posicaoInserir].id_admin != posicaoInserir + 1){administrador[posicaoInserir].id_admin = posicaoInserir + 1;}
    if (strcmp(administrador[posicaoInserir].nome, novo_administrador.nome) != 0){strcpy(administrador[posicaoInserir].nome, novo_administrador.nome);}
    if (strcmp(administrador[posicaoInserir].NIF, novo_administrador.NIF) != 0){strcpy(administrador[posicaoInserir].NIF, novo_administrador.NIF);}
    if (strcmp(administrador[posicaoInserir].palavra_passe, novo_administrador.palavra_passe) != 0){strcpy(administrador[posicaoInserir].palavra_passe, novo_administrador.palavra_passe);}
    if (administrador[posicaoInserir].role != novo_administrador.role){administrador[posicaoInserir].role = novo_administrador.role;}
    return 0;
}

int imprimir_administrador(ADMIN administrador[], int posicaoImprimir) {

    if(posicaoImprimir != 0){
        printf("-------------------------------------------------------------------------");
        printf("-------------------------------------------------------------------------");
        printf("\n O administrador com o nome %s tem os seguintes dados:\n",administrador[posicaoImprimir].nome);
        printf("-------------------------------------------------------------------------");
        printf("\nO NIF do administrador e %s\n",administrador[posicaoImprimir].NIF);
        printf("\nA palavra passe do administrador e %s\n",administrador[posicaoImprimir].palavra_passe);
        printf("\nA role do agente e %d\n",administrador[posicaoImprimir].role);
        printf("-------------------------------------------------------------------------");
    }

    return 0;
}

int criar_administrador(ADMIN administrador[], ADMIN novo_administrador) {

    int novaPosicao = -1;

    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
        if (administrador[i].id_admin == 0) {
            novaPosicao = i;
            break;
        }
    }

    if (novaPosicao != -1) {
        inserir_administrador(administrador, novo_administrador, novaPosicao);
        return 0;
    }else{
        printf("\nNão tem lugares disponiveis !\n");
        return -1;
    }

}

// Para esta função apenas e editado a disponibilidade os restantes dados não serao inseridos por causa da outra função ter verificações que não o permitem (no caso de )

int editar_administrador(ADMIN administrador[], ADMIN administrador_editado,int id_procura){

    int id_encontrado =0;

    for(int i =0; i < MAX_AGENTES_IMOBILIARIOS; i++){

        if(administrador[i].id_admin == id_procura){
            id_encontrado = administrador[i].id_admin;
        }
    }

    if(id_encontrado == 0){
        printf("\nNao existe o agente que pretende editar !!!\n");
        return -1;
    } else{
        inserir_administrador(administrador, administrador_editado, id_encontrado);
        return 0;
    }

}

// Aqui apenas vai inserir valores vazios (Zero no ID) ou NULL:
int remover_administrador(ADMIN administrador[],int id_procura){

    int id_encontrado =0;

    ADMIN admin_eliminar;

    strcpy(admin_eliminar.nome,"");
    strcpy(admin_eliminar.NIF, "");
    strcpy(admin_eliminar.palavra_passe, "");
    admin_eliminar.role = 0;


    for(int i =0; i < MAX_AGENTES_IMOBILIARIOS; i++){

        if(administrador[i].id_admin == id_procura){
            id_encontrado = administrador[i].id_admin;
        }
    }

    if(id_encontrado == 0){
        printf("\nNao existe o agente que pretende editar !!!\n");
        return -1;
    } else{
        inserir_administrador(administrador, admin_eliminar, id_encontrado);
        return 0;
    }
}

int carregar_do_ficheiro(ADMIN administrador[]){

    ADMIN administrador_lido;
    FILE *ficheiro_administrador = fopen("../Armazenamento/Texto/Admins.txt", "r");
    if (ficheiro_administrador == NULL) {
        printf("\nErro a abrir o ficheiro de administradores !!!!\n");
        return -1;
    }

    while (fscanf(ficheiro_administrador, "%29[^;];%9[^;];%d;%d;%20[^;]",
                  administrador_lido.nome,
                  administrador_lido.NIF,
                  &administrador_lido.role,
                  &administrador_lido.id_admin,
                  administrador_lido.palavra_passe) == 5) {
        inserir_administrador(administrador, administrador_lido,administrador_lido.id_admin -1);
        imprimir_administrador(administrador,administrador_lido.id_admin -1);
    }

    fclose(ficheiro_administrador);

    /*
    char nome [30];
    char NIF [10]; // 9 caracteres mais o \0
    int role;
    int id_admin;
    char palavra_passe [21]; // 20 caracteres mais o \0
*/

    return 0;
}



