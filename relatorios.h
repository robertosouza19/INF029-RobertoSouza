//
// Created by rober on 14/03/2024.
//

#ifndef PROJETO00_RELATORIOS_H
#define PROJETO00_RELATORIOS_H
#include "aluno.h"
#include "disciplina.h"
int menu_relatorio();
int exibir_disciplina_sem_professor(disciplina *ponteiro_disciplina,int qtd_disciplinas,aluno *ponteiro_aluno,int qtd_alunos);
int imprimir_a_disciplina(disciplina *ponteiro_disciplina,int qtd_disciplinas,aluno *ponteiro_aluno,int qtd_alunos,
                          professor *ponteiro_professor,int qtd_professores);
int listar_alunos_sexo(aluno *ponteiro_aluno,int qtd_alunos);
int listar_professores_sexo(professor *ponteiro_professor,int qtd_professores);
int exibir_aluno_ordem_alfabetica(aluno *ponteiro_aluno,int qtd_alunos);
int exibir_alunos_data(aluno *ponteiro_aluno,int qtd_alunos);
int verifica_data(int dia,int mes,int ano,int dia2,int mes2,int ano2);
void impressao_aluno(aluno *copia_lista,int qtd_alunos);
void impressao_professor(professor *copia_lista,int qtd_professores);
void copia_vetores_professor(professor *ponteiro_professor,professor *copia_lista,int qtd_professores);
int exibir_professores_ordem_alfabetica(professor *ponteiro_professor,int qtd_professores);
void copia_vetores(aluno *ponteiro_aluno,aluno *copia_lista,int qtd_alunos);
int exibir_professore_data(professor *ponteiro_professor,int qtd_professores);
void calcula_disciplinas_do_aluno(aluno *ponteiro_aluno,int qtd_alunos,disciplina *ponteiro_disciplina ,int qtd_disciplinas);
int exibir_qtd_disciplinas_alunos(aluno *ponteiro_aluno,int qtd_alunos,disciplina *ponteiro_disciplina,int qtd_disciplinas);
#endif //PROJETO00_RELATORIOS_H
