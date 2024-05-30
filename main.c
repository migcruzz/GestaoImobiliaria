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

    //// POPULAR DADOS
    carregar_do_ficheiro_administrador(administrador);
    carregar_do_ficheiro_agente_imobiliario(agente_imobiliario);
    //// FIM POPULAR DADOS



    ///utilizadores logados
    AGENTE agente_logado;
    ADMIN admin_logado;
    CLIENTE cliente_logado;
    //FIM UTILIZADORES LOGADOS


    //OPCOES MENU
    int opcao, opcaoSub, opcaoSubAgente;
    //FIM

    //Dados para criar,editar e eleminar os vários utilizadores
    PROPRIEDADE novaPropriedade;
    AGENTE novoAgente;
    //FIM

    //Escolher opcoes dos dados(introduzir dados)
    int tipo_comercial;
    int tipo_disponibilidade;
    int tipo_imovel;
    int popularidade;
    int id_propriedade;
    int id_agente;
    //FIM


    //LOGIN
    char username[30];
    char password[21];
    int role;
    int login_resultado;
    //FIM LOGIN


    ///Menu
    printf("Bem-vindo! Por favor, insira suas credenciais:\n");
    printf("Nome de usuário: ");
    scanf("%s", username);

    printf("Senha: ");
    scanf("%s", password);

    printf("Função (1 para cliente, 2 para agente, 3 para admin): ");
    scanf("%d", &role);

    login_resultado = login(administrador, agente_imobiliario, ini_lista_cliente, username, password, role);

    if (login_resultado == 0) {
        printf("Login successful. Role: %d\n", role);
    } else {
        printf("O Login falhou.\n");
        free(administrador);
        free(agente_imobiliario);
        return -1;
    }

    if(role==1){
        printf("Escolha se pretende registar ou entrar");

    }else if(role == 2){
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
                            printf("Digite o ID da propriedade que deseja remover: ");
                            scanf("%d", &id_propriedade);


                            if (id_propriedade <= 0) {
                                printf("ID da propriedade inválido. Por favor, insira um ID válido.\n");
                            } else {
                                // Chama a função para remover a propriedade apenas se o ID for válido
                                if (remover_propriedade(&ini_lista_propriedade, id_propriedade) == 0) {
                                    printf("Propriedade removida com sucesso.\n");
                                } else {
                                    printf("Erro ao remover propriedade.\n");
                                }
                            }

                        case 4:
                            imprime_todas_propriedades(ini_lista_propriedade);
                            break;

                        case 5:
                            break;


                        default:
                            printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                            break;
                    }
                    break;
                case 2:
                    submenuagentes();
                    scanf("%d", &opcaoSubAgente);
                    switch (opcaoSubAgente) {
                        case 1:

                            printf("Nome: ");
                            fflush(stdin);
                            fgets(novoAgente.nome,30,stdin);

                            printf("Palavra-Passe: ");
                            fflush(stdin);
                            fgets(novoAgente.palavra_passe,30,stdin);

                            printf("NIF: ");
                            fflush(stdin);
                            fgets(novoAgente.NIF,9,stdin);

                            printf("Morada: ");
                            fflush(stdin);
                            fgets(novoAgente.morada,50,stdin);

                            printf("Telefone: ");
                            fflush(stdin);
                            fgets(novoAgente.telefone,9,stdin);

                            printf("Dia de Nascimento: ");
                            scanf("%d",&novoAgente.dia_nascimento);
                            printf("Mes de Nascimento: ");
                            scanf("%d",&novoAgente.mes_nascimento);
                            printf("Ano de Nascimento: ");
                            scanf("%d",&novoAgente.ano_nascimento);

                            novoAgente.role=2;

                            printf("");

                            if (editar_agente_imobiliario(agente_imobiliario, novoAgente, agente_logado.id_agente) == 0) {
                                printf("Agente imobiliário editado com sucesso.\n");
                            } else {
                                printf("Erro ao editar agente imobiliário.\n");
                            }



                            break;
                        case 2:
                            printf("Você escolheu a Sub-opção 2.2.\n");
                            break;
                        case 3:

                        default:
                            printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                    }



            }
            printf("\n");
        }
    }else if(role ==3){
        while (1) {
            menuAdmin();
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
                            printf("Digite o ID da propriedade que deseja remover: ");
                            scanf("%d", &id_propriedade);


                            if (id_propriedade <= 0) {
                                printf("ID da propriedade inválido. Por favor, insira um ID válido.\n");
                            } else {
                                // Chama a função para remover a propriedade apenas se o ID for válido
                                if (remover_propriedade(&ini_lista_propriedade, id_propriedade) == 0) {
                                    printf("Propriedade removida com sucesso.\n");
                                } else {
                                    printf("Erro ao remover propriedade.\n");
                                }
                            }

                        case 4:
                            imprime_todas_propriedades(ini_lista_propriedade);
                            break;

                        case 5:
                            break;


                        default:
                            printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                            break;
                    }
                    break;
                case 2:
                    //Quanto fatorou cada propriedade hoje e este mes

                   break;

                case 3:
                    //Historico de visitas de uma determinada propriedade
                    break;

                case 4:
                    submenuagentes();
                    scanf("%d", &opcaoSubAgente);
                    switch (opcaoSubAgente) {
                        case 1:
                            //CRIAR AGENTE
                            printf("Nome: ");
                            fflush(stdin);
                            fgets(novoAgente.nome,30,stdin);

                            printf("Palavra-Passe: ");
                            fflush(stdin);
                            fgets(novoAgente.palavra_passe,30,stdin);

                            printf("NIF: ");
                            fflush(stdin);
                            fgets(novoAgente.NIF,9,stdin);

                            printf("Morada: ");
                            fflush(stdin);
                            fgets(novoAgente.morada,50,stdin);

                            printf("Telefone: ");
                            fflush(stdin);
                            fgets(novoAgente.telefone,9,stdin);

                            printf("Dia de Nascimento: ");
                            scanf("%d",&novoAgente.dia_nascimento);
                            printf("Mes de Nascimento: ");
                            scanf("%d",&novoAgente.mes_nascimento);
                            printf("Ano de Nascimento: ");
                            scanf("%d",&novoAgente.ano_nascimento);

                            printf("Disponibilidade:\n");
                            printf("1. Disponivel\n");
                            printf("2. Indisponivel\n");
                            scanf("%d", &tipo_disponibilidade);

                            if (tipo_disponibilidade == 1) {
                                novoAgente.disponibilidade = 1;
                            } else if (tipo_disponibilidade == 2) {
                                novoAgente.disponibilidade = 0;
                            } else {
                                printf("Opção invalida. Por favor, escolha 1 para 'Disponivel' ou 2 para 'Nao Disponivel'.\n");
                                break;
                            }

                            novoAgente.role=2;

                            printf("");

                            if (criar_agente_imobiliario(agente_imobiliario, novoAgente) == 0) {
                                printf("Agente criado com sucesso.\n");
                            } else {
                                printf("Erro ao criar Agente.\n");
                            }

                            break;
                        case 2:
                            //EDITAR AGENTE
                            printf("Digite o ID da propriedade que deseja editar: ");
                            scanf("%d", &id_agente);

                            printf("Nome: ");
                            fflush(stdin);
                            fgets(novoAgente.nome,30,stdin);

                            printf("Palavra-Passe: ");
                            fflush(stdin);
                            fgets(novoAgente.palavra_passe,30,stdin);

                            printf("NIF: ");
                            fflush(stdin);
                            fgets(novoAgente.NIF,9,stdin);

                            printf("Morada: ");
                            fflush(stdin);
                            fgets(novoAgente.morada,50,stdin);

                            printf("Telefone: ");
                            fflush(stdin);
                            fgets(novoAgente.telefone,9,stdin);

                            printf("Dia de Nascimento: ");
                            fflush(stdin);
                            scanf("%d",&novoAgente.dia_nascimento);
                            printf("Mes de Nascimento: ");
                            fflush(stdin);
                            scanf("%d",&novoAgente.mes_nascimento);
                            printf("Ano de Nascimento: ");
                            fflush(stdin);
                            scanf("%d",&novoAgente.ano_nascimento);
                            novoAgente.id_agente = id_agente;

                            printf("Disponibilidade:\n");
                            printf("1. Disponivel\n");
                            printf("2. Indisponivel\n");
                            scanf("%d", &tipo_disponibilidade);

                            if (tipo_disponibilidade == 1) {
                                novoAgente.disponibilidade = 1;
                            } else if (tipo_disponibilidade == 2) {
                                novoAgente.disponibilidade = 0;
                            } else {
                                printf("Opção invalida. Por favor, escolha 1 para 'Disponivel' ou 2 para 'Nao Disponivel'.\n");
                                break;
                            }

                            // Chama a função para editar a propriedade
                            if (editar_agente_imobiliario(agente_imobiliario, novoAgente, id_agente) == 0) {
                                printf("Agente editado com sucesso.\n");
                            } else {
                                printf("Erro ao editar Agente.\n");
                            }
                            break;
                        case 3:
                            //REMOVER AGENTE
                            printf("Digite o ID do agente que deseja remover: ");
                            scanf("%d", &id_agente);


                            if (id_agente <= 0) {
                                printf("ID do Agente inválido. Por favor, insira um ID válido.\n");
                            } else {
                                // Chama a função para remover a propriedade apenas se o ID for válido
                                if (remover_agente_imobiliario(agente_imobiliario, id_agente) == 0) {
                                    printf("Agente removido com sucesso.\n");
                                } else {
                                    printf("Erro ao remover Agente.\n");
                                }
                            }
                            break;

                        case 4:
                        default:
                            break;
                    }
                    break;



                case 5:
                    //Quantas visitas realizou um agente


                    break;

                case 6:
                    //LISTAR POR ORDEM ALFABETICA
                    listar_agente_imobiliario_alfabeto(agente_imobiliario);
                    break;

                case 7:
                    //LISTAR POR ORDEM DE IDADE
                     listar_agente_imobiliario_idade(agente_imobiliario);
                    break;

                case 8:
                    //LISTAR TODAS AS VISITAS DO DIA (Hora POR ASCENDE)

                    break;

                case 9:
                   //SIMULAR A REALIZACAO DE UMA VISITA
                    break;

                case 10:
                    //LISTAR AS VISITAS EM QUE O CLIENTE NAO COMPARECEU NUM DETERMINADO DIA
                    break;

                case 11:
                    //GERAR UM RELATORIO POR DIA E POR MES DE CONTAS
                    break;

                case 12:
                    //GERAR UM RELATORIO DE TODOS OS AGENTES

                    break;

                case 13:
                    inserir_no_ficheiro_agente_imobiliario(agente_imobiliario);
                    return 0;
                    break;

            }
            printf("\n");
        }
    }

        //FIM MENU


    //// FIM DO PROGRAMA
    //// DEALOCAÇÃO DE MEMÓRIA DAS VARIÁVEIS

    free(administrador);
    free(agente_imobiliario);
    return 0;
}
