//
// Created by rober on 15/02/2024.
//


#ifndef PROJETO00_PROFESSOR_H
#include "aluno.h"
#define PROJETO00_PROFESSOR_H
#define TAM_PROFESSOR 50

typedef struct {
    char nome_professor[TAM_NOME];
    int dia,mes,ano,matricula;
    char cpf_professor[TAM_CPF];
    char sexo_professor;
}professor;
int menu_professores();
int cadastrar_professor(professor *ponteiro_professor, int *qtd_professores,int *matricula);
int listar_professores(professor *ponteiro_professor,int qtd_professores);
int atualizar_professor(professor *ponteiro_professor,int qtd_professores);
int excluir_professor(professor *ponteiro_professor,int *qtd_professores);

#endif//PROJETO00_PROFESSOR_H
