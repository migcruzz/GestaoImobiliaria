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

    administrador = (ADMIN *) calloc(MAX_ADMINISTRADORES, sizeof (ADMIN));
    agente_imobiliario = (AGENTE *) calloc(MAX_AGENTES_IMOBILIARIOS, sizeof (AGENTE));

    if (administrador == NULL || agente_imobiliario == NULL) {
        printf("Erro na alocacao de memoria. A sair do programa\n");
        return -1;
    }

    ///Menu

    int opcao, opcaoSub;
    PROPRIEDADE novaPropriedade;
    //Escolher opcoes do tipo_comercial
    int tipo_comercial;
    int tipo_imovel;
    int popularidade;
    int id_propriedade;

    while (1) {
        menuAgente();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                submenupropriedadeAgente();
                scanf("%d", &opcaoSub);
                switch (opcaoSub) {
                    case 1:
                        printf("Dados da nova propriedade:\n");
                        printf("Nome da propriedade: ");
                        fflush(stdin);
                        fgets( novaPropriedade.nome,50,stdin);
                        printf("Tipo de comércio:\n");
                        printf("1. Vender\n");
                        printf("2. Arrendar\n");
                        printf("Escolha uma opção: ");
                        scanf("%d", &tipo_comercial);

                        if (tipo_comercial == 1) {
                            strcpy(novaPropriedade.tipo_comercial, "Vender");
                        } else if (tipo_comercial == 2) {
                            strcpy(novaPropriedade.tipo_comercial, "Arrendar");
                        } else {
                            printf("Opção inválida. Tipo de comércio não definido.\n");
                            break;
                        }

                        printf("Preco: ");
                        scanf("%f", &novaPropriedade.preco);

                        printf("Tipo de imovel:\n");
                        printf("1. Casa\n");
                        printf("2. Escritorio\n");
                        printf("3. Apartamento\n");
                        printf("4. Garagem\n");
                        printf("5. Armazem\n");
                        printf("Escolha uma opção: ");
                        scanf("%d", &tipo_imovel);

                        switch (tipo_imovel) {
                            case 1:
                                strcpy(novaPropriedade.tipo_imovel, "Casa");
                                break;
                            case 2:
                                strcpy(novaPropriedade.tipo_imovel, "Escritorio");
                                break;
                            case 3:
                                strcpy(novaPropriedade.tipo_imovel, "Apartamento");
                                break;
                            case 4:
                                strcpy(novaPropriedade.tipo_imovel, "Garagem");
                                break;
                            case 5:
                                strcpy(novaPropriedade.tipo_imovel, "Armazem");
                                break;
                            default:
                                printf("Opção inválida. Tipo de imóvel não definido.\n");
                                break;
                        }

                        printf("Popularidade:\n");
                        printf("1. Popular\n");
                        printf("2. Nao Popular\n");
                        scanf("%d", &popularidade);

                        if (popularidade == 1) {
                            novaPropriedade.popular = 1;
                        } else if (popularidade == 2) {
                            novaPropriedade.popular = 0;
                        } else {
                            printf("Opção inválida. Por favor, escolha 1 para 'Popular' ou 2 para 'Não Popular'.\n");
                            break;
                        }

                        // função criar_propriedade

                        if (criar_propriedade(&ini_lista_propriedade, &fim_lista_propriedade, novaPropriedade) == 0) {
                            printf("Propriedade criada com sucesso.\n");
                        } else {
                            printf("Erro ao criar propriedade.\n");
                        }
                        break;


                    case 2:
                        // Código para editar uma propriedade
                        printf("Digite o ID da propriedade que deseja editar: ");
                        scanf("%d", &id_propriedade);

                        // Solicita ao usuário os novos dados para a propriedade
                        printf("Digite os novos dados da propriedade:\n");
                        printf("Nome da propriedade: ");
                        fflush(stdin);
                        fgets( novaPropriedade.nome,50,stdin);

                        printf("Tipo de comércio:\n");
                        printf("1. Vender\n");
                        printf("2. Arrendar\n");
                        printf("Escolha uma opção: ");
                        scanf("%d", &tipo_comercial);

                        if (tipo_comercial == 1) {
                            strcpy(novaPropriedade.tipo_comercial, "Vender");
                        } else if (tipo_comercial == 2) {
                            strcpy(novaPropriedade.tipo_comercial, "Arrendar");
                        } else {
                            printf("Opção inválida. Tipo de comércio não definido.\n");
                            break;
                        }

                        printf("Preco: ");
                        scanf("%f", &novaPropriedade.preco);

                        printf("Tipo de imovel:\n");
                        printf("1. Casa\n");
                        printf("2. Escritorio\n");
                        printf("3. Apartamento\n");
                        printf("4. Garagem\n");
                        printf("5. Armazem\n");
                        printf("Escolha uma opção: ");
                        scanf("%d", &tipo_imovel);

                        switch (tipo_imovel) {
                            case 1:
                                strcpy(novaPropriedade.tipo_imovel, "Casa");
                                break;
                            case 2:
                                strcpy(novaPropriedade.tipo_imovel, "Escritorio");
                                break;
                            case 3:
                                strcpy(novaPropriedade.tipo_imovel, "Apartamento");
                                break;
                            case 4:
                                strcpy(novaPropriedade.tipo_imovel, "Garagem");
                                break;
                            case 5:
                                strcpy(novaPropriedade.tipo_imovel, "Armazem");
                                break;
                            default:
                                printf("Opção inválida. Tipo de imóvel não definido.\n");
                                break;
                        }

                        printf("Popularidade:\n");
                        printf("1. Popular\n");
                        printf("2. Nao Popular\n");
                        scanf("%d", &popularidade);

                        if (popularidade == 1) {
                            novaPropriedade.popular = 1;
                        } else if (popularidade == 2) {
                            novaPropriedade.popular = 0;
                        } else {
                            printf("Opção inválida. Por favor, escolha 1 para 'Popular' ou 2 para 'Não Popular'.\n");
                            break;
                        }
                        novaPropriedade.id_propriedade = id_propriedade;

                        // Chama a função para editar a propriedade
                        if (editar_propriedade(&ini_lista_propriedade, novaPropriedade) == 0) {
                            printf("Propriedade editada com sucesso.\n");
                        } else {
                            printf("Erro ao editar propriedade.\n");
                        }
                        break;

                    case 3:
                        submenuagentes(); // Supondo que esta opção também redireciona para o submenu
                        break;

                    case 4:
                        imprime_todas_propriedades(ini_lista_propriedade);
                        break;

                    case 5:
                        sair();
                        return 0; // Sair do loop e terminar o programa

                    default:
                        printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                        break;
                }
        }
        printf("\n");
    }

    //// FIM DO PROGRAMA
    //// DEALOCAÇÃO DE MEMÓRIA DAS VARIÁVEIS

    free(administrador);
    free(agente_imobiliario);
    return 0;
}
