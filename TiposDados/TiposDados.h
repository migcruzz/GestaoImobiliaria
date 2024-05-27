#ifndef PROGRAMA_TIPOSDADOS_H
#define PROGRAMA_TIPOSDADOS_H


//// Tipos de dados:

// Array
typedef struct agente{
    char nome [30];
    char NIF [10]; // 9 caracteres mais o \0
    char morada [50];
    char telefone [10]; // 9 caracteres mais o \0
    unsigned int id_agente;
    char data_nascimento [10]; // 9 caracteres mais o \0
    int role;
    char palavra_passe [21]; // 20 caracteres mais o \0
    int disponibilidade;
}AGENTE;

// Lista ligada
typedef struct cliente{
    char nome [30];
    char NIF [10]; // 9 caracteres mais o \0
    char telefone [10]; // 9 caracteres mais o \0
    unsigned int id_cliente;
    int role;
    char palavra_passe [21]; // 20 caracteres mais o \0
}CLIENTE;

// Array
typedef struct admin{
    char nome [30];
    char NIF [10]; // 9 caracteres mais o \0
    int role;
    unsigned int id_admin;
    char palavra_passe [21]; // 20 caracteres mais o \0
}ADMIN;

// Lista Ligada
typedef struct propriedade{
    float preco;
    int tipo;
    int popular;
    unsigned int id_propriedade;
}PROPRIEDADE;

// Lista Ligada
typedef struct visita{
    int dia;
    int mes;
    int ano;
    unsigned int id_cliente;
    unsigned int id_agente;
    unsigned int id_propriedade;
    int duracao; // em minutos tendo em atenção que um dia tem 1440 minutos.
    int hora_marcacao; // em minutos tendo em atenção que um dia tem 1440 minutos.
    char relatorio [3000];
    char detalhes_intresse_cliente [3000];
    int casa_aberta;
}VISITA;

//// Listas Ligadas:

typedef struct lista_cliente{
    CLIENTE cliente;
    struct elem *seguinte;
    struct elem *anterior;
}LISTA_CLIENTE;

typedef struct lista_propriedade{
    PROPRIEDADE propriedade;
    struct elem *seguinte;
    struct elem * anterior;
}LISTA_PROPRIEDADE;

typedef struct lista_visita{
    VISITA visita;
    struct elem *seguinte;
    struct elem *anterior;
}LISTA_VISITA;

#endif //PROGRAMA_TIPOSDADOS_H
