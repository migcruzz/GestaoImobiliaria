#ifndef PROGRAMA_TIPOSDADOS_H
#define PROGRAMA_TIPOSDADOS_H


//// Tipos de dados:

// Array
typedef struct agente{
    char nome [30];
    char NIF [10]; // 9 caracteres mais o \0
    char morada [50];
    char telefone [10]; // 9 caracteres mais o \0
    int id_agente;
    //char data_nascimento [10]; // 9 caracteres mais o \0
    int dia_nascimento;
    int mes_nascimento;
    int ano_nascimento;
    int role;
    char palavra_passe [21]; // 20 caracteres mais o \0
    int disponibilidade;
}AGENTE;

// Lista ligada
typedef struct cliente{
    char nome [30];
    char NIF [10]; // 9 caracteres mais o \0
    char telefone [10]; // 9 caracteres mais o \0
    int id_cliente;
    int role;
    char palavra_passe [21]; // 20 caracteres mais o \0
}CLIENTE;

// Array
typedef struct admin{
    char nome [30];
    char NIF [10]; // 9 caracteres mais o \0
    int role;
    int id_admin;
    char palavra_passe [21]; // 20 caracteres mais o \0
}ADMIN;

// Lista Ligada
typedef struct propriedade{
    float preco;
    char morada [101]; // 100 para letras e 1 para 0 \0
    char nome [51]; // 50 para letras e 1 para 0 \0
    int tipo_imovel;
    int popular;
    int id_propriedade;
    int tipo_comercial;
}PROPRIEDADE;

// Lista Ligada
typedef struct visita{
    int dia;
    int mes;
    int ano;
    int id_cliente;
    int id_agente;
    int id_propriedade;
    int duracao; // em minutos tendo em atenção que um dia tem 1440 minutos.
    int hora_marcacao; // em minutos tendo em atenção que um dia tem 1440 minutos.
    char relatorio [3000];
    char detalhes_intresse_cliente [3000];
    int casa_aberta;
}VISITA;

//// Listas Ligadas:

typedef struct lista_cliente{
    CLIENTE cliente;
    struct lista_cliente *seguinte;
    struct lista_cliente *anterior;
}LISTA_CLIENTE;

typedef struct lista_propriedade{
    PROPRIEDADE propriedade;
    struct lista_propriedade *seguinte;
    struct lista_propriedade *anterior;
}LISTA_PROPRIEDADE;

typedef struct lista_visita{
    VISITA visita;
    struct lista_visita *seguinte;
    struct lista_visita *anterior;
}LISTA_VISITA;

#endif //PROGRAMA_TIPOSDADOS_H
