//
// Created by rober on 15/02/2024.
//

#ifndef PROJETO00_DISCIPLINA_H
#define PROJETO00_DISCIPLINA_H
#include "aluno.h"
#include "professor.h"
#define TAM_DISCIPLINA 10
#define     QTD_ALUNOS_DISCIPLINA 30
typedef struct{
    char nome_disciplina[TAM_NOME];
    int codigo_disciplina;
    int professor;
    int semestre;
    int alunos[QTD_ALUNOS_DISCIPLINA];
    int inicio_aluno;//marca inicio vetor de alunos
    int fim_aluno;//marca fim guarda qtd alunos inseridos na disciplina
}disciplina;


int menu_disciplina();
int cadastro_disciplina(disciplina *ponteiro_disciplina,int *qtd_disciplinas,professor *ponteiro_professor,
                       int qtd_professores,int *codigo_disciplina);
int exibir_disciplina(disciplina *ponteiro_disciplina,int qtd_disciplinas,
                      professor *ponteiro_professor,int qtd_professores,aluno *ponteiro_aluno,
                      int qtd_alunos);
int busca_disciplina(disciplina *ponteiro_disciplina,int qtd_disciplinas,int codigo_disciplina);
int subistitui_professor(disciplina *ponteiro_disciplina,int qtd_disciplinas,
                         professor *ponteiro_professor,int qtd_professores);
int inserir_alunos_disciplina(disciplina *ponteiro_disciplina,int qtd_disciplina,
                              aluno *ponteiro_aluno,int qtd_alunos);


void inicializacao(disciplina *ponteiro_disciplina);
int pesquisa_aluno_disciplina(disciplina *ponteiro_disciplina,int posicao_disciplina,
                                       int matricula,int fim);
int exclusao_aluno_disciplina(disciplina *ponteiro_discipina,int qtd_disciplinas);
int interroper_iserir_alunos();
int exclusao_aluno_todas_disciplinas(disciplina *ponteiro_disciplina, int qtd_disciplinas, int matricula);
#endif//PROJETO00_DISCIPLINA_H
