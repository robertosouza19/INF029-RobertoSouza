#include <stdio.h>
#include "aluno.h"
#include "professor.h"
#include "disciplina.h"
#include "relatorios.h"


int main() {
    int retorna_matricula;
    int opcao,opcao_aluno,opcao_professor,opcao_disciplina,opcao_relatorio;
    int qtd_disciplinas = 0;
    disciplina lista_disciplinas[TAM_DISCIPLINA],*ponteiro_disciplina;
    ponteiro_disciplina = lista_disciplinas;
    aluno lista_alunos[TAM_ALUNO];
    aluno *ponteiro_aluno;
    professor lista_professores[TAM_PROFESSOR];
    professor *ponteiro_professor;
    ponteiro_professor = lista_professores;
    int qtd_alunos = 0;
    int qtd_professores = 0;
    int matricula = 0;
    int codigo_disciplina = 0;
    ponteiro_aluno = lista_alunos;
     inicializacao(ponteiro_disciplina);
    do{
        opcao = menu_principal();
        switch(opcao){
            case 0://sair
                printf("progama encerrado\n");
                break;
            case 1://alunos
                do{
                    opcao_aluno = menu_alunos();
                    switch(opcao_aluno){
                        case 0://sair
                            opcao = 0;
                            printf("progama encerrado\n");
                            break;
                        case 1://voltar
                            break;
                        case 2://adicionar alunos
                            cadastrar_aluno(ponteiro_aluno,&qtd_alunos,&matricula);
                            break;
                        case 3://listar alunos
                            listar_alunos(ponteiro_aluno,qtd_alunos);
                            break;
                        case 4:// atualizar alunos
                            atualizar_aluno(ponteiro_aluno,qtd_alunos);
                            break;


                        case 5://deletar alunos
                            retorna_matricula = excluir_aluno(ponteiro_aluno, &qtd_alunos);
                            if(qtd_disciplinas == 0){
                                printf("aluno excluido com sucesso\n");
                            }
                            else{
                                exclusao_aluno_todas_disciplinas(ponteiro_disciplina, qtd_disciplinas, retorna_matricula);
                            }
                            break;
                        default:
                            printf("opcao invalida\n");
                    }

                }while(opcao_aluno!= 0 && opcao_aluno != 1);
                break;
            case 2:// professores
                do{
                    opcao_professor = menu_professores();
                    switch (opcao_professor) {
                        case 0://sair
                            opcao = 0;
                            printf("progama encerrado\n");
                            break;
                        case 1://voltar
                            break;
                        case 2://adicionar professor
                            cadastrar_professor(ponteiro_professor,&qtd_professores,&matricula);
                            break;
                        case 3://listar professores cadastrados
                            listar_professores(ponteiro_professor,qtd_professores);
                            break;
                        case 4://atualizar dados de professores
                            atualizar_professor(ponteiro_professor,qtd_professores);
                            break;
                        case 5://deletar professores
                            excluir_professor(ponteiro_professor,&qtd_professores);
                            break;
                        default:
                            printf("opcao invalida\n");



                    }

                }while(opcao_professor != 0 && opcao_professor != 1);

            break;
            case 3://disciplinas
                do{
                    opcao_disciplina = menu_disciplina();
                    switch(opcao_disciplina){
                        case 0://sair do progama
                            opcao = 0;
                            printf("progama encerrado\n");
                            break;
                        case 1://voltar
                            break;
                        case 2://cadastra disciplina
                            cadastro_disciplina(ponteiro_disciplina,&qtd_disciplinas,ponteiro_professor,
                                                qtd_professores,&codigo_disciplina);
                            break;
                        case 3://substitui professor
                            subistitui_professor(ponteiro_disciplina,qtd_disciplinas,
                                                     ponteiro_professor,qtd_professores);
                            break;
                        case 4://inserir aluno
                            inserir_alunos_disciplina(ponteiro_disciplina,
                                                      qtd_disciplinas,ponteiro_aluno,qtd_alunos);
                            break;
                        case 5://excluir aluno da disciplina
                            exclusao_aluno_disciplina(ponteiro_disciplina,qtd_disciplinas);
                            break;
                        case 6://exibir dados da disciplina
                            exibir_disciplina(ponteiro_disciplina, qtd_disciplinas,ponteiro_professor,
                                              qtd_professores,ponteiro_aluno,qtd_alunos);
                            break;

                        default:
                            printf("opcao invalida\n");

                    }

                }while(opcao_disciplina != 0 && opcao_disciplina != 1);
            break;
            case 4://relatorios4
                do{
                    opcao_relatorio = menu_relatorio();
                    switch(opcao_relatorio){
                        case 0://sair
                            opcao = 0;
                            printf("progama encerrado com sucesso\n");
                            break;
                        case 1://voltar
                            break;
                        case 2://listar alunos
                            listar_alunos(ponteiro_aluno,qtd_alunos);
                            break;
                        case 3://listar professores
                            listar_professores(ponteiro_professor,qtd_professores);
                            break;
                        case 4://listar disciplinas s/alunos
                            exibir_disciplina_sem_professor(ponteiro_disciplina,qtd_disciplinas,
                                                            ponteiro_aluno,qtd_alunos);
                            break;
                        case 5://lista dados da disciplina
                            imprimir_a_disciplina(ponteiro_disciplina,qtd_disciplinas,ponteiro_aluno,qtd_alunos,
                                                      ponteiro_professor,qtd_professores);
                            break;
                        case 6://listar alunos por sexo
                            listar_alunos_sexo(ponteiro_aluno,qtd_alunos);
                            break;
                        case 7://alunos em ordem alfabetica
                            exibir_aluno_ordem_alfabetica(ponteiro_aluno,qtd_alunos);
                            break;
                        case 8://exibir alunos por  data
                            exibir_alunos_data(ponteiro_aluno,qtd_alunos);
                            break;
                        case 9://listar professores por sexo
                            listar_professores_sexo(ponteiro_professor,qtd_professores);
                        break;
                        case 10://exibir professores ordem alfabetica
                            exibir_professores_ordem_alfabetica(ponteiro_professor,qtd_professores);
                            break;
                        case 11://exibir professores dat nascimento exibir dos mais novos ate mais velhos
                            exibir_professore_data(ponteiro_professor,qtd_professores);
                            break;
                        case 12://exibir os alunos que estao matriculado no minimo 3 materias
                            exibir_qtd_disciplinas_alunos(ponteiro_aluno,qtd_alunos,ponteiro_disciplina,qtd_disciplinas);
                            break;
                            default:
                            printf("opcao invalida\n");

                    }


                }while(opcao_relatorio != 0 && opcao_relatorio != 1);
                break;
            default:
                printf("opcao invalida\n");
        }



    }while(opcao != 0);
    return 0;
}
