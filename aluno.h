//
// Created by rober on 15/02/2024.
//

#ifndef PROJETO00_ALUNO_H
#define PROJETO00_ALUNO_H
#define TAM_ALUNO 100
#define TAM_NOME 50
#define TAM_CPF 12
#define TAM_DATA 12
#define ERRO (-1)
typedef struct {
    char nome_aluno[TAM_NOME];
    int dia,mes,ano,matricula;
    char cpf_aluno[TAM_CPF];
    char sexo_aluno;
    int qtd_discipinas_cursadas;
}aluno;

void limpeza_memoria();
void remocao_quebra_linha(char *string);
int menu_principal();
int menu_alunos();
int listar_alunos(aluno *ponteiro_aluno,int qtd_alunos);
int cadastrar_aluno(aluno *ponteiro_aluno, int *qtd_alunos,int *matricula);
int quebra_data(const char *data,int *dia,int *mes,int *ano);
int valida_data(int dia,int mes,int ano);
int valida_cpf(const char *cpf);
int digitos_iguais_cpf(char const *cpf);
int valida_sexo(char sexo);
void saida_formatada_cpf(char *cpf);
int cpf_igual_no_cadastro(void *ponteiro,int tipo_ponteiro,char *cpf,int qtd_usuarios);
int atualizar_aluno(aluno *ponteiro_aluno,int qtd_alunos);
int busca_matricula(void *ponteiro,int matricula,int qtd_usuarios,int tipo_ponteiro);
int verifica_cpf_atualizacao(void *ponteiro,int qtd_pessoas,int minha_posicao,int tipo_ponteiro,char*cpf);
int excluir_aluno(aluno *ponteiro_aluno,int *qtd_alunos);
#endif//PROJETO00_ALUNO_H
