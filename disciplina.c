//
// Created by rober on 15/02/2024.
//

#include "aluno.h"
#include "professor.h"
#include "disciplina.h"
#include <stdio.h>
#include <string.h>


int menu_disciplina() {
    int opcao_disciplina = -1;
    printf("========== disciplinas ================\n");
    printf("0 - sair\n");
    printf("1 - voltar\n");
    printf("2 - cadastrar disciplina\n");
    printf("3 - subistituir professor\n");
    printf("4 - inserir aluno na disciplina\n");
    printf("5 - excluir aluno disciplina\n");
    printf("6 - exibir dados da disciplina\n");
    scanf("%d",&opcao_disciplina);
    getchar();
    return opcao_disciplina;
}

int cadastro_disciplina(disciplina *ponteiro_disciplina,int *qtd_disciplinas,professor *ponteiro_professor,
                        int qtd_professores,int *codigo_disciplina){
    if(*qtd_disciplinas == TAM_DISCIPLINA){
        printf("lista de disciplinas cheia\n");
        return -1;
    }
    char nome_disciplina[TAM_NOME];
    int semestre;
    int tipo_professor = 2;
    int matricula_professor;
    int professor_encontrado;


    printf("informe o nome da disciplina:\n");
    fgets(nome_disciplina,TAM_NOME,stdin);
    do{
        printf("informe o semestre da disciplina:\n");
        scanf("%d",&semestre);
        if(semestre <= 0){
            printf("semestre invalido!!!\n");

        }
    }while(semestre <= 0);

    do{
        printf("informe a matricula professor que deseja adicionar a disciplina:\n");
        scanf("%d",&matricula_professor);
        professor_encontrado = busca_matricula(ponteiro_professor,matricula_professor,
                                               qtd_professores,tipo_professor);
        if(professor_encontrado == -1){
            printf("professor nao localizado no sistema escola\n");
        }
    }while(professor_encontrado == -1);

    strcpy(ponteiro_disciplina[*qtd_disciplinas].nome_disciplina,nome_disciplina);
    ponteiro_disciplina[*qtd_disciplinas].semestre = semestre;
    ponteiro_disciplina[*qtd_disciplinas].professor = matricula_professor;
    *codigo_disciplina = *codigo_disciplina +1;//incrementado codigo
    ponteiro_disciplina[*qtd_disciplinas].codigo_disciplina = *codigo_disciplina;
    printf("cadastro da disciplina feito com sucesso\n");
    *qtd_disciplinas = *qtd_disciplinas + 1;
    return 1;
}
int exibir_disciplina(disciplina *ponteiro_disciplina,int qtd_disciplinas,
                      professor *ponteiro_professor,int qtd_professores,aluno *ponteiro_aluno,int qtd_alunos){
    if(qtd_disciplinas == 0){
        printf("nao existem disciplinas cadastradas\n");
        return -1;
    }
    int posicao_professor;//posicao do professor no cadastro de professores
    int  tipo_ponteiro;
    printf("==================== dados da das disciplinas ==========================\n");
    for(int icont = 0;icont < qtd_disciplinas;icont++){
        printf("nome disciplina:...........................%s",ponteiro_disciplina[icont].nome_disciplina);
        printf("codigo disciplina:.........................%d\n",ponteiro_disciplina[icont].codigo_disciplina);
        printf("semestre:..................................%d\n",ponteiro_disciplina[icont].semestre);

        tipo_ponteiro = 2;//professor
        posicao_professor = busca_matricula(ponteiro_professor,
                                            ponteiro_disciplina[icont].professor,qtd_professores,tipo_ponteiro);
        if(posicao_professor == ERRO){
            printf("professor nao definido\n");
        }
        else{
            printf("professor:..................................%s\n",ponteiro_professor[posicao_professor].nome_professor);
        }


        int fim = ponteiro_disciplina[icont].fim_aluno;
        tipo_ponteiro = 1;
        for(int jcont = 0;jcont <  fim;jcont++ ){
            int indice = busca_matricula(ponteiro_aluno,ponteiro_disciplina[icont].alunos[jcont],qtd_alunos,tipo_ponteiro);
            printf("aluno:..................................%s\n",ponteiro_aluno[indice].nome_aluno);
        }
        puts("");
    }
    puts("");
    return 1;
}


int busca_disciplina(disciplina *ponteiro_disciplina,int qtd_disciplinas,int codigo_disciplina){
    for(int icont = 0;icont < qtd_disciplinas;icont++){
        if(codigo_disciplina == ponteiro_disciplina[icont].codigo_disciplina){
            return icont;
        }
    }
    return -1;//nao encontrou
}
 int subistitui_professor(disciplina *ponteiro_disciplina,int qtd_disciplinas,
                          professor *ponteiro_professor,int qtd_professores){
    if(qtd_disciplinas == 0){
        printf("nao existe disciplinas cadastradas\n");
        return -1;
    }
    int tipo_ponteiro = 2;
    int codigo_disciplina,posicao_disciplina;
    int matricula_professor,posicao_professor;
    printf("informe o codigo da disciplina:\n");
    scanf("%d",&codigo_disciplina);
    posicao_disciplina = busca_disciplina(ponteiro_disciplina,qtd_disciplinas,codigo_disciplina);
     if(posicao_disciplina == -1){
         printf("disciplina nao localizada\n");
         return -1;
     }

     do{
         printf("informe matricula do professor para substitui:\n");
         scanf("%d",&matricula_professor);
         posicao_professor = busca_matricula(ponteiro_professor,

                                             matricula_professor,qtd_professores,tipo_ponteiro);
         if(posicao_professor == -1){
             printf("professor nao localizado\n");
         }
     }while(posicao_professor == -1);
    ponteiro_disciplina[posicao_disciplina].professor = matricula_professor;
    printf("troca do professor realizada com sucesso\n");
     return  1;
}


int pesquisa_aluno_disciplina(disciplina *ponteiro_disciplina,int posicao_disciplina,
                                       int matricula,int fim){
    for(int cont = 0;cont < fim;cont++){
       if(matricula == ponteiro_disciplina[posicao_disciplina].alunos[cont]){
           return cont;//ja existe este aluno retorna a posicao do aluno
       }
    }
    return -1;//nao existe o aluno
}

int exclusao_aluno_disciplina(disciplina *ponteiro_discipina,int qtd_disciplinas){
    int codigo_disciplina;
    int posicao_disciplina;
    int matricula_aluno;
    int posicao_aluno;
    int fim;
    printf("informe o codigo da disciplina:\n");
    scanf("%d",&codigo_disciplina);
    posicao_disciplina = busca_disciplina(ponteiro_discipina,qtd_disciplinas,codigo_disciplina);
    if(posicao_disciplina == -1){
        printf("disciplina nao localizada\n");
        return -1;
    }
    printf("informe a matricula do aluno:\n");
    scanf("%d",&matricula_aluno);
    fim = ponteiro_discipina[posicao_disciplina].fim_aluno;
    posicao_aluno = pesquisa_aluno_disciplina(ponteiro_discipina,posicao_disciplina,
                                              matricula_aluno,fim);
    if(posicao_aluno == -1){
        printf("o aluno nao foi localizado na disciplina\n");
        return -1;
    }
    for(int cont = posicao_aluno;cont < fim;cont++){
        ponteiro_discipina[posicao_disciplina].alunos[cont] = ponteiro_discipina[posicao_disciplina].alunos[cont+1];
    }
    ponteiro_discipina[posicao_disciplina].fim_aluno--;
    printf("aluno excluido da disciplina com sucesso\n");


    return 1;
}//avalia este criterio
int inserir_alunos_disciplina(disciplina *ponteiro_disciplina,int qtd_disciplina,aluno *ponteiro_aluno,int qtd_alunos){
    int codigo,posicao_disciplina,cont;
    int aluno_repetido,fim;
    int matricula,matricula_valida,tipo_ponteiro = 1;
    printf("informe o codigo da disciplina:\n");
    scanf("%d",&codigo);
    posicao_disciplina = busca_disciplina(ponteiro_disciplina,qtd_disciplina,codigo);
    if(posicao_disciplina == -1){
        printf("disciplina nao localizada\n");
        return ERRO;
    }
    ponteiro_disciplina[posicao_disciplina].inicio_aluno =  ponteiro_disciplina[posicao_disciplina].fim_aluno;//assume ultima posicao aluno
    cont = ponteiro_disciplina[posicao_disciplina].inicio_aluno;//marca o inicio do laco
    while(cont  < QTD_ALUNOS_DISCIPLINA){
            do{
                printf("informe a matricula do aluno:\n");
                scanf("%d",&matricula);
                matricula_valida = busca_matricula(ponteiro_aluno,matricula,qtd_alunos,tipo_ponteiro);
                fim = ponteiro_disciplina[posicao_disciplina].fim_aluno;
                aluno_repetido = pesquisa_aluno_disciplina(ponteiro_disciplina,posicao_disciplina,
                matricula,fim);
                if(matricula_valida == ERRO){
                    printf("aluno nao localizado\n");
                }
                if(aluno_repetido!=ERRO){
                    printf("aluno ja esta na disciplina\n");
                }
            }while(matricula_valida == ERRO || aluno_repetido!= ERRO);
        ponteiro_disciplina[posicao_disciplina].alunos[cont] = matricula;
        ponteiro_disciplina[posicao_disciplina].fim_aluno++;//tamanho alunos
        cont++;
        if(cont < QTD_ALUNOS_DISCIPLINA){
            if(interroper_iserir_alunos() == 1){
                break;
            }
        }

    }
    return 1;
}
void inicializacao(disciplina *ponteiro_disciplina){
    for(int cont = 0;cont < TAM_DISCIPLINA;cont++){
        ponteiro_disciplina[cont].inicio_aluno = 0;
        ponteiro_disciplina[cont].fim_aluno = 0;
    }
}
int interroper_iserir_alunos(){
    char opcao;
    getchar();
    printf("deseja continuar iserir alunos:[s/n]\n");
    scanf("%c",&opcao);

    if(opcao == 'n' || opcao == 'N'){
        return 1;//nao deseja continuar
    }
    else  {
        return ERRO;
    }

}


int exclusao_aluno_todas_disciplinas(disciplina *ponteiro_disciplina, int qtd_disciplinas, int matricula) {
    for(int contador = 0;contador < qtd_disciplinas;contador++){
        int posicao_disciplina = contador;
        int fim = ponteiro_disciplina[posicao_disciplina].fim_aluno;
        int posicao_aluno_disciplina = pesquisa_aluno_disciplina(ponteiro_disciplina,posicao_disciplina,
                                                                 matricula,fim);
        if(posicao_aluno_disciplina !=ERRO){
            //excluir aluno na disciplinas
            for(int cont = posicao_aluno_disciplina;cont < fim;cont++){
                ponteiro_disciplina[posicao_disciplina].alunos[cont] =
                        ponteiro_disciplina[posicao_disciplina].alunos[cont +1];
            }
            ponteiro_disciplina[posicao_disciplina].fim_aluno--;
        }

    }
    printf("aluno excluido com sucesso\n");
    return 1;
}
