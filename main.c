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
#include "Funcoes/Menu/menu.h"
#include "VariaveisGlobais/variaveis_globais.h"


int main() {

    //// INICIO DO PROGRAMA

    //// Definição de listas ligadas (apontadores para o inicio das mesmas):

    LISTA_CLIENTE *ini_lista_cliente;
    LISTA_CLIENTE *fim_lista_cliente;

    LISTA_PROPRIEDADE *ini_lista_propriedade;
    LISTA_PROPRIEDADE *fim_lista_propriedade;

    LISTA_VISITA *ini_lista_visita;
    LISTA_VISITA *fim_lista_visita;

    //// Definição de arrays para  Agentes imobiliarios e administrador (iniciação apenas):

    // apontador para o inicio do array.
    ADMIN *administrador = NULL;
    AGENTE *agente_imobiliario = NULL;

    administrador = (ADMIN *) calloc(MAX_ADMINISTRADORES,sizeof (ADMIN));
    agente_imobiliario = (AGENTE *) calloc(MAX_AGENTES_IMOBILIARIOS,sizeof (AGENTE));

    if(administrador == NULL || agente_imobiliario == NULL){
        printf("Erro na alocacao de memoria. A sair do programa\n");
        return -1;
    }

    //// DEALOCAÇÃO DE MOMÓRIA DAS VARIÁVEIS

    free(administrador);
    free(agente_imobiliario);


    //// FIM DO PROGRAMA

    return 0;
}
