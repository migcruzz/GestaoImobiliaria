#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../TiposDados/TiposDados.h"

#ifndef PROGRAMA_LOGIN_H
#define PROGRAMA_LOGIN_H
int login(ADMIN *admins, AGENTE *agentes, LISTA_CLIENTE *clientes, char *username, char *password, int role);

#endif //PROGRAMA_LOGIN_H
