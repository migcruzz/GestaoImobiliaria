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

int obterOpcaoMenu() {
    int opcao;
    char entrada[10]; // Tamanho arbitrário para a entrada

    // Solicitar a entrada do usuário
    printf("Escolha uma opção: ");
    scanf("%s", entrada);

    // Validar se a entrada é um número
    if (sscanf(entrada, "%d", &opcao) != 1) {
        printf("Por favor, insira um número válido.\n");
        return -1; // Retornar um valor inválido para indicar erro
    }

    return opcao;
}

int main() {
    LISTA_CLIENTE *ini_lista_cliente = NULL;
    LISTA_CLIENTE *fim_lista_cliente = NULL;

    LISTA_PROPRIEDADE *ini_lista_propriedade = NULL;
    LISTA_PROPRIEDADE *fim_lista_propriedade = NULL;

    LISTA_VISITA *ini_lista_visita =NULL;
    LISTA_VISITA *fim_lista_visita=NULL;

    ADMIN *administrador = NULL;
    AGENTE *agente_imobiliario = NULL;
    CLIENTE *cliente = NULL;

    administrador = (ADMIN *) calloc(MAX_ADMINISTRADORES, sizeof(ADMIN));
    agente_imobiliario = (AGENTE *) calloc(MAX_AGENTES_IMOBILIARIOS, sizeof(AGENTE));
    cliente = (CLIENTE *) calloc(MAX_CLIENTES, sizeof(CLIENTE));

    if (administrador == NULL || agente_imobiliario == NULL) {
        printf("Erro na alocacao de memoria. A sair do programa\n");
        return -1;
    }

    carregar_clientes_do_arquivo(cliente);
    carregar_do_ficheiro_administrador(administrador);
    carregar_agentes_do_arquivo(agente_imobiliario);
    carregar_lista_do_arquivo_binario(&ini_lista_propriedade, &fim_lista_propriedade);

    char username[30];
    char password[21];
    int role;
    int login_resultado;
    int id_admin_logado= -1;
    int id_agente_logado= -1;
    int id_cliente_logado= -1;
    int id_clientes=0;

    while (1) {
        do {
            printf("Bem-vindo! Por favor, insira suas credenciais:\n");
            printf("Nome de usuário: ");
            scanf("%s", username);

            printf("Senha: ");
            scanf("%s", password);

            printf("Função (1 para cliente, 2 para agente, 3 para admin): ");
            scanf("%d", &role);


            login_resultado = login(administrador, agente_imobiliario, cliente, username, password, role);

            if (login_resultado == 0) {
                printf("Login successful. Role: %d\n", role);

                if (role == 1) {
                    // Procurar o cliente com o nome de usuário especificado
                    for (int i = 0; i < MAX_CLIENTES; i++) {
                        if (strcmp(cliente[i].nome, username) == 0) {
                            id_cliente_logado = cliente[i].id_cliente;
                            break;
                        }
                    }
                }else
                if (role == 3) {
                    // Encontre o ID do administrador logado
                    for (int i = 0; i < MAX_ADMINISTRADORES; i++) {
                        if (strcmp(administrador[i].nome, username) == 0) {
                            id_admin_logado = administrador[i].id_admin;
                            break;
                        }
                    }
                }else if(role == 2 ){

                    for (int i = 0; i < MAX_AGENTES_IMOBILIARIOS; i++) {
                        if (strcmp(agente_imobiliario[i].nome, username) == 0) {
                            id_agente_logado = agente_imobiliario[i].id_agente;
                            break;
                        }
                    }

                }if(role == 1 ){

                    for (int i = 0; i < MAX_CLIENTES; i++) {
                        if (strcmp(cliente[i].nome, username) == 0) {
                            id_cliente_logado = cliente[i].id_cliente;
                            break;
                        }
                    }

                }
                break; // Saia do loop se o login for bem-sucedido
            } else {
                printf("O Login falhou.\n");
            }
        } while (login_resultado != 0);

        if (role == 1) {
            while(1){
                menuCliente();
                int opcaoCliente = obterOpcaoMenu();
                switch (opcaoCliente) {
                    case 1:
                        //Gerir TIPOS DE PROPRIEDADE
                        break;
                    case 2:
                        //FATURACAO DE PROPRIEDADES
                        break;

                    case 5:
                        editar_cliente_logado(cliente, id_cliente_logado);
                        break;

                    case 6:
                        //GERIR CLIENTES
                        inserir_clientes_em_arquivo(cliente);
                        return 0;


                }
            }

        } else if (role == 2) {


            while(1){
                menuAgente();
                int opcaoAgente = obterOpcaoMenu();
                switch (opcaoAgente) {
                    case 1:
                        //Gerir TIPOS DE PROPRIEDADE
                        break;
                    case 2:
                        //FATURACAO DE PROPRIEDADES
                        break;

                    case 5:
                        editar_agente_imobiliario_logado(agente_imobiliario, id_agente_logado);
                        break;
                    case 6:
                        //GERIR CLIENTES
                        inserir_agentes_em_arquivo(agente_imobiliario);
                        return 0;

                    case 7:
                        // Gerar um relatório por dia e por mês de contas

                        break;

                    case 8:
                        //  Gerar um relatório de todos os agentes
                        gerar_relatorio_agentes(agente_imobiliario);
                        break;
                    case 9:
                        editar_administrador(administrador, id_admin_logado);
                        break;

                }
            }

        } else if (role == 3) {
            while (1) {
                menuAdmin();
                int opcao = obterOpcaoMenu();

                switch (opcao) {
                    case 1:
                        //PROPRIEDADE
                        submenupropriedadeAgente();
                        int opcaoSub = obterOpcaoMenu();
                        switch (opcaoSub) {
                            case 1:
                                criar_propriedade(&ini_lista_propriedade, &fim_lista_propriedade);
                                break;

                            case 2:
                                editar_propriedade(&ini_lista_propriedade);
                                break;

                            case 3:
                                remover_propriedade(&ini_lista_propriedade);
                                break;

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
                        //FATURACAO DE PROPRIEDADES
                        break;

                    case 3:
                        //GERIR AGENTES
                        submenuagentes();
                        int opcaoSubAgente = obterOpcaoMenu();

                        switch (opcaoSubAgente) {
                            case 1:
                                criar_agente_imobiliario(agente_imobiliario);
                                break;

                            case 2:
                                editar_agente_imobiliario(agente_imobiliario);
                                break;

                            case 3:
                                printf("Digite o ID do agente que deseja remover: ");
                                int id_procura;
                                scanf("%d", &id_procura);
                                remover_agente_imobiliario(agente_imobiliario, id_procura);
                                break;

                            case 4:
                                listar_agente_imobiliario(agente_imobiliario);
                                break;

                            case 5:
                                listar_agente_imobiliario_alfabeto(agente_imobiliario);
                                break;


                            case 6:
                                listar_agente_imobiliario_idade(agente_imobiliario);
                                break;
                            case 7:
                                listar_agente_imobiliario_disponiveis(agente_imobiliario);
                                break;
                            case 8:
                                tornar_agente_indisponivel(agente_imobiliario);
                                break;

                            case 9:
                            default:
                                break;
                        }
                        break;

                    case 4:
                        //LISTAR VISITAS
                        submenuvisitas();
                        int opcaoSubVisitas = obterOpcaoMenu();

                        switch (opcaoSubVisitas) {
                            case 1:
                                //VISITAS DE HOJE POR HORA ASCENDENTE
                                break;

                            case 2:
                                //VISITAS DE UM DIA(DATA) DE UM AGENTE
                                break;

                            case 3:
                                //TODAS AS VISITAS DE UM DETERINADO TIPO DE PROPRIEDADE
                                break;

                            case 4:
                                //VISITAS DO DIA EM QUE O CLIENTE NAO COMPARECEU
                                break;

                            case 5:
                            default:
                                break;
                        }
                        break;

                    case 5:
                        //SIMULAR REALIZAÇÃO DE UMA VISITA
                        break;

                    case 6:
                        //GERIR CLIENTES
                        submenucliente();
                        int opcaoSubCliente = obterOpcaoMenu();

                        switch (opcaoSubCliente) {
                            case 1:
                                //CRIAR CLIENTE
                                criar_cliente(cliente);
                                break;

                            case 2:
                                //EDITAR CLIENTE
                                editar_cliente(cliente);
                                break;

                            case 3:
                                //REMOVER CLIENTE
                                printf("Digite o ID do cliente que deseja remover: ");
                                scanf("%d", &id_clientes);

                                // Chamar a função para remover o cliente
                                remover_cliente(cliente, id_clientes);

                                break;

                            case 4:
                                //LISTAR ALFABETICA
                                listar_cliente_alfabeto(cliente);
                                break;

                            case 5://LISTAR POR NIF
                                listar_cliente_nif(cliente);
                                break;

                            case 6:
                            default:
                                break;
                        }
                        break;


                    case 7:
                        // Gerar um relatório por dia e por mês de contas

                        break;

                    case 8:
                        //  Gerar um relatório de todos os agentes
                        gerar_relatorio_agentes(agente_imobiliario);
                        break;
                    case 9:
                        editar_administrador(administrador, id_admin_logado);
                        break;

                    case 10:
                        inserir_agentes_em_arquivo(agente_imobiliario);
                        inserir_no_ficheiro_administrador(administrador);
                        inserir_clientes_em_arquivo(cliente);
                        salvar_lista_propriedades_ficheiro_binario(ini_lista_propriedade);
                        goto return_to_login;  // Volta para o início do login
                }

                if (opcao == 10) {
                    break;  // Sai do loop interno para retornar ao login
                }

                printf("\n");
            }
        }
    }

    return_to_login:
    limpar_memoria_lista_propriedades(&ini_lista_propriedade, &fim_lista_propriedade);
    free(administrador);
    free(agente_imobiliario);
    free(cliente);
    return 0;
}



