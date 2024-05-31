#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../TiposDados/TiposDados.h"

#ifndef PROGRAMA_ADM_H
#define PROGRAMA_ADM_H

 void carregar_do_ficheiro_administrador(ADMIN administrador[]);

int editar_administrador(ADMIN administrador[], int id_admin_logado);

int inserir_no_ficheiro_administrador(ADMIN administrador[]);

void remove_newline(char *string);








#endif //PROGRAMA_ADM_H
