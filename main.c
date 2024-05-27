#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TiposDados/TiposDados.h"
#include "Funcoes/Administrador/adm.h"
#include "Funcoes/AgentesImobiliarios/agentes_imobiliarios.h"
#include "Funcoes/Clientes/clientes.h"
#include "Funcoes/Login/login.h"
#include "Funcoes/Propriedades/propriedades.h"
#include "Funcoes/Visitas/visitas.h"
#include "Funcoes/Menu/Menu.h"

#define MAX_AGENTES_IMOBILIARIOS 15
#define  MAX_ADMINISTRADORES 3

int main() {

    //// Definição de listas ligadas (apontadores para o inicio das mesmas):

    LISTA_CLIENTE *ini_lista_cliente;
    LISTA_CLIENTE *fim_lista_cliente;

    LISTA_PROPRIEDADE *ini_lista_propriedade;
    LISTA_PROPRIEDADE *fim_lista_propriedade;

    LISTA_VISITA *ini_lista_visita;
    LISTA_VISITA *fim_lista_visita;

    //// Definição de arrays para  Agentes imobiliarios e administrador (iniciação apenas):

    // apontador para o inicio do array.
    ADMIN *administradores = NULL;
    AGENTE *agente_imobiliario = NULL;

    administradores = (ADMIN *) calloc(1,sizeof (ADMIN));
    agente_imobiliario = (AGENTE *) calloc(1,sizeof (AGENTE));





    return 0;
}
