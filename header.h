#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estrutura do Utente
typedef struct {
    int id;
    char nome[100];
    int idade;
    int canal;
    int hora;
    int minuto;
    char estado[50];
} Utente;

void menuPrincipal(void);
void administracao(void);
void enfermagem(void);
void medico(void);
void gestao(void);

#endif