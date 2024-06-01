#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../VariaveisGlobais/variaveis_globais.h"
#include "../../TiposDados/TiposDados.h"


int login(ADMIN *admins, AGENTE *agentes, CLIENTE clientes[], char *username, char *password, int role) {
    // Verifica administradores
    if (role == 3) {
        for (int i = 0; i < MAX_ADMINISTRADORES; i++) {
            if (strcmp(admins[i].nome, username) == 0 && strcmp(admins[i].palavra_passe, password) == 0) {
                return 0; // Login bem-sucedido
            }
        }
    }

    // Verifica agentes
    if (role == 2) {
        for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
            if (strcmp(agentes[i].nome, username) == 0 && strcmp(agentes[i].palavra_passe, password) == 0) {
                return 0; // Login bem-sucedido
            }
        }
    }

    // Verifica clientes
    if (role == 1) {
        for (int i = 0; i < MAX_CLIENTES; i++) {
            if (strcmp(clientes[i].nome, username) == 0 && strcmp(clientes[i].palavra_passe, password) == 0) {
                return 0; // Login bem-sucedido
            }
        }
    }

    return -1; // Login falhou
}