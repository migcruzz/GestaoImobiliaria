cmake_minimum_required(VERSION 3.27)
project(Programa C)

set(CMAKE_C_STANDARD 11)

add_executable(Programa main.c
        Funcoes/Administrador/adm.c
        Funcoes/AgentesImobiliarios/agentes_imobiliarios.c
        Funcoes/Clientes/clientes.c
        Funcoes/Login/login.c
        Funcoes/Propriedades/propriedades.c
        Funcoes/Visitas/visitas.c)
