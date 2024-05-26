

#ifndef PROGRAMA_TIPOSDADOS_H
#define PROGRAMA_TIPOSDADOS_H

typedef struct agente{
    char nome [30];
    char NIF [10]; // 9 caracteres mais o \0
    char morada [50];
    char telefone [10]; // 9 caracteres mais o \0
    unsigned int id_agente;
    char data_nascimento [10]; // 9 caracteres mais o \0
    int role;
    char palavra_passe [21]; // 20 caracteres mais o \0
    bool disponibilidade;
}AGENTE;

typedef struct cliente{
    char nome [30];
    char NIF [10]; // 9 caracteres mais o \0
    char telefone [10]; // 9 caracteres mais o \0
    unsigned int id_cliente;
    int role;
    char palavra_passe [21]; // 20 caracteres mais o \0
}CLIENTE;


typedef struct admin{
    char nome [30];
    char NIF [10]; // 9 caracteres mais o \0
    int role;
    unsigned int id_admin;
    char palavra_passe [21]; // 20 caracteres mais o \0
}ADMIN;

typedef struct propriedade{
    float preco;
    int tipo;
    bool popular;
    unsigned int id_propriedade;
}PROPRIEDADE;

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
    bool casa_aberta;
}VISITA;

#endif //PROGRAMA_TIPOSDADOS_H
