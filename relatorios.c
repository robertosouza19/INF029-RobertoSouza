//
// Created by rober on 14/03/2024.
//

#include "relatorios.h"
#include "aluno.h"
# include "professor.h"
#include "disciplina.h"
#include <stdio.h>
#include <string.h>

int menu_relatorio(){
    int opcao_relatorio = ERRO;
    printf("========== relatorios ================\n");
    printf("0-sair\n");
    printf("1- voltar\n");
    printf("2- listar alunos\n");
    printf("3- listar professores\n");
    printf("4- exibir dados das disciplinas sem professores\n");
    printf("5- exibir dados de uma disciplina\n");
    printf("6- listar alunos por sexo\n");
    printf("7- listar alunos em ordem alfabetica\n");
    printf("8 -listar alunos por data de nascimento\n");
    printf("9 -listar professores por sexo\n");
    printf("10 -listar professores por ordem alfabetica\n");
    printf("11 -listar professores por dat d nascimento\n");
    printf("12 - listar alunos matriculados pelo menos 3 materias\n");
    scanf("%d",&opcao_relatorio);
    getchar();
    return opcao_relatorio;

}
int exibir_disciplina_sem_professor(disciplina *ponteiro_disciplina,int qtd_disciplinas,aluno *ponteiro_aluno,int qtd_alunos){
    if(qtd_disciplinas == 0){
        printf("nao existem disciplinas cadastradas\n");
        return -1;
    }

    int  tipo_ponteiro;
    printf("==================== dados da das disciplinas ==========================\n");
    for(int icont = 0;icont < qtd_disciplinas;icont++){
        printf("nome disciplina:...........................%s",ponteiro_disciplina[icont].nome_disciplina);
        printf("codigo disciplina:.........................%d\n",ponteiro_disciplina[icont].codigo_disciplina);
        printf("semestre:..................................%d\n",ponteiro_disciplina[icont].semestre);


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
int imprimir_a_disciplina(disciplina *ponteiro_disciplina,int qtd_disciplinas,aluno *ponteiro_aluno,int qtd_alunos,
professor *ponteiro_professor,int qtd_professores){
    if(qtd_disciplinas == 0){
        printf("nao existem disciplinas cadastradas\n");
        return -1;
    }
    int codigo_disciplina;
    int posicao;

    printf("informe qual disciplina que consultar\n");
    scanf("%d",&codigo_disciplina);
    int indice =  busca_disciplina(ponteiro_disciplina,qtd_disciplinas,codigo_disciplina);
    if(indice == ERRO){
        printf("a disciplina nao existe\n");
        return ERRO;
    }
    printf("nome disciplina:...........................%s",ponteiro_disciplina[indice].nome_disciplina);
    printf("codigo disciplina:.........................%d\n",ponteiro_disciplina[indice].codigo_disciplina);
    printf("semestre:..................................%d\n",ponteiro_disciplina[indice].semestre);
    int tipo_ponteiro = 2;//professor
    int posicao_professor = busca_matricula(ponteiro_professor,
                                        ponteiro_disciplina[indice].professor,qtd_professores,tipo_ponteiro);
    if(posicao_professor == ERRO){
        printf("professor nao definido\n");
    }
    else{
        printf("professor:..................................%s\n",ponteiro_professor[posicao_professor].nome_professor);
    }
    tipo_ponteiro = 1;
    int fim = ponteiro_disciplina[indice].fim_aluno;
    for(int jcont = 0;jcont <  fim;jcont++ ){
         posicao = busca_matricula(ponteiro_aluno,ponteiro_disciplina[indice].alunos[jcont],
                                     qtd_alunos,tipo_ponteiro);
        printf("aluno:..................................%s\n",ponteiro_aluno[posicao].nome_aluno);
    }
    puts("");
    return 1;
}
int listar_alunos_sexo(aluno *ponteiro_aluno,int qtd_alunos){
    if(qtd_alunos == 0){
        printf("nao ha alunos matriculados\n");
        return ERRO;
    }
    printf("========== masculino ================\n");
    for(int cont = 0;cont < qtd_alunos;cont++){
        if(ponteiro_aluno[cont].sexo_aluno == 'm'|| ponteiro_aluno[cont].sexo_aluno == 'M'){

            printf("nome:.............................%s\n",ponteiro_aluno[cont].nome_aluno);
            printf("matricula:........................%d\n",ponteiro_aluno[cont].matricula);
            printf("data:.............................%d-%d-%d\n",ponteiro_aluno[cont].dia,ponteiro_aluno[cont].mes,ponteiro_aluno[cont].ano);
            saida_formatada_cpf( ponteiro_aluno[cont].cpf_aluno);
            printf("sexo:.............................%c\n",ponteiro_aluno[cont].sexo_aluno);
            printf("\n");
        }



    }printf("========== feminino ================\n");
    for(int cont = 0;cont < qtd_alunos;cont++){
        if(ponteiro_aluno[cont].sexo_aluno == 'f'|| ponteiro_aluno[cont].sexo_aluno == 'F'){
            printf("========== feminino ================\n");
            printf("nome:.............................%s\n",ponteiro_aluno[cont].nome_aluno);
            printf("matricula:........................%d\n",ponteiro_aluno[cont].matricula);
            printf("data:.............................%d-%d-%d\n",ponteiro_aluno[cont].dia,ponteiro_aluno[cont].mes,ponteiro_aluno[cont].ano);
            saida_formatada_cpf( ponteiro_aluno[cont].cpf_aluno);
            printf("sexo:.............................%c\n",ponteiro_aluno[cont].sexo_aluno);
            printf("\n");
        }



    }

    return 1;
}
void copia_vetores(aluno *ponteiro_aluno,aluno *copia_lista,int qtd_alunos){
    for(int cont = 0;cont < qtd_alunos;cont++){
        strcpy(copia_lista[cont].nome_aluno,ponteiro_aluno[cont].nome_aluno);//nome
        copia_lista[cont].dia = ponteiro_aluno[cont].dia;//dia
        copia_lista[cont].mes = ponteiro_aluno[cont].mes;//mes
        copia_lista[cont].ano = ponteiro_aluno[cont].ano;//ano
        strcpy(copia_lista[cont].cpf_aluno,ponteiro_aluno[cont].cpf_aluno);//cpf
        copia_lista[cont].matricula = ponteiro_aluno[cont].matricula;//matricula
        copia_lista[cont].sexo_aluno = ponteiro_aluno[cont].sexo_aluno;//sexo
    }
}
int exibir_aluno_ordem_alfabetica(aluno *ponteiro_aluno,int qtd_alunos){
    if(qtd_alunos == 0){
        printf("nao existem alunos cadastrados\n");
        return ERRO;
    }
    int cont,jcont;
    char aux_sexo,aux_cpf[TAM_CPF],aux_nome[TAM_NOME];
    int aux_matricula,aux_dia,aux_mes,aux_ano;
    aluno copia_lista[TAM_ALUNO];
    copia_vetores(ponteiro_aluno,copia_lista,qtd_alunos);
    //ordenacao
    for(cont = 0 ;cont < qtd_alunos -1;cont++){

        for(jcont = cont + 1;jcont  < qtd_alunos;jcont++){
            strcpy(aux_nome,copia_lista[cont].nome_aluno);
            aux_matricula = copia_lista[cont].matricula;
            aux_dia = copia_lista[cont].dia;
            aux_mes = copia_lista[cont].mes;
            aux_ano = copia_lista[cont].ano;
            strcpy(aux_cpf,copia_lista[cont].cpf_aluno);
            aux_sexo = copia_lista[cont].sexo_aluno;
            if(strcmp(copia_lista[cont].nome_aluno,copia_lista[jcont].nome_aluno)  > 0){
                strcpy(copia_lista[cont].nome_aluno,copia_lista[jcont].nome_aluno);
                strcpy(copia_lista[jcont].nome_aluno,aux_nome);

                copia_lista[cont].matricula = copia_lista[jcont].matricula;
                copia_lista[jcont].matricula = aux_matricula;

                copia_lista[cont].dia = copia_lista[jcont].dia;
                copia_lista[jcont].dia = aux_dia;

                copia_lista[cont].mes = copia_lista[jcont].mes;
                copia_lista[jcont].mes = aux_mes;

                copia_lista[cont].ano= copia_lista[jcont].ano;
                copia_lista[jcont].ano = aux_ano;

                strcpy(copia_lista[cont].cpf_aluno,copia_lista[jcont].cpf_aluno);
                strcpy(copia_lista[jcont].cpf_aluno,aux_cpf);

                copia_lista[cont].sexo_aluno = copia_lista[jcont].sexo_aluno;
                copia_lista[jcont].sexo_aluno = aux_sexo;



            }
        }
    }
    //impressao



    return 1;
}

int exibir_alunos_data(aluno *ponteiro_aluno,int qtd_alunos){
    if(qtd_alunos == 0){
        printf("nao existem alunos cadastrados\n");
        return ERRO;
    }
    int cont,jcont;
    char aux_sexo,aux_cpf[TAM_CPF],aux_nome[TAM_NOME];
    int aux_matricula,aux_dia,aux_mes,aux_ano;
    aluno copia_lista[TAM_ALUNO];
    copia_vetores(ponteiro_aluno,copia_lista,qtd_alunos);

    for(cont = 0 ;cont < qtd_alunos -1;cont++){

        for(jcont = cont + 1;jcont  < qtd_alunos;jcont++){
            strcpy(aux_nome,copia_lista[cont].nome_aluno);
            aux_matricula = copia_lista[cont].matricula;
            aux_dia = copia_lista[cont].dia;
            aux_mes = copia_lista[cont].mes;
            aux_ano = copia_lista[cont].ano;
            strcpy(aux_cpf,copia_lista[cont].cpf_aluno);
            aux_sexo = copia_lista[cont].sexo_aluno;
            int dia = (int)copia_lista[cont].dia;
            int dia2 = (int)copia_lista[jcont].dia;
            int mes = (int)copia_lista[cont].mes;
            int mes2 = (int)copia_lista[jcont].mes;
            int ano = (int)copia_lista[cont].ano;
            int ano2 = (int)copia_lista[jcont].ano;




            if(verifica_data(dia,mes,ano,dia2,mes2,ano2) == 1){
                strcpy(copia_lista[cont].nome_aluno,copia_lista[jcont].nome_aluno);
                strcpy(copia_lista[jcont].nome_aluno,aux_nome);

                copia_lista[cont].matricula = copia_lista[jcont].matricula;
                copia_lista[jcont].matricula = aux_matricula;

                copia_lista[cont].dia = copia_lista[jcont].dia;
                copia_lista[jcont].dia = aux_dia;

                copia_lista[cont].mes = copia_lista[jcont].mes;
                copia_lista[jcont].mes = aux_mes;

                copia_lista[cont].ano= copia_lista[jcont].ano;
                copia_lista[jcont].ano = aux_ano;

                strcpy(copia_lista[cont].cpf_aluno,copia_lista[jcont].cpf_aluno);
                strcpy(copia_lista[jcont].cpf_aluno,aux_cpf);

                copia_lista[cont].sexo_aluno = copia_lista[jcont].sexo_aluno;
                copia_lista[jcont].sexo_aluno = aux_sexo;



            }
        }
    }
    impressao_aluno(copia_lista,qtd_alunos);

    return 1;
}
int verifica_data(int dia,int mes,int ano,int dia2,int mes2,int ano2){//compara duas datas deve trocar se data 1 menor
    if(ano < ano2){//realizar troca
        return 1;
    }
    else if (ano > ano2){//nao troca
        return ERRO;
    }

    if(mes < mes2){//realizar troca
        return 1;
    }
    else if (mes > mes2){//nao troca
        return ERRO;
    }

    if(dia < dia2){//realizar troca
        return 1;
    }
    else if(dia > dia2) {//nao troca
        return ERRO;
    }
    else{
        return ERRO;//dia e igual
    }

}
void impressao_aluno(aluno *copia_lista,int qtd_alunos){
    for(int cont = 0;cont < qtd_alunos;cont++){

        printf("nome:.............................%s\n",copia_lista[cont].nome_aluno);
        printf("matricula:........................%d\n",copia_lista[cont].matricula);
        printf("data:.............................%d-%d-%d\n",copia_lista[cont].dia,copia_lista[cont].mes,copia_lista[cont].ano);
        saida_formatada_cpf( copia_lista[cont].cpf_aluno);
        printf("sexo:.............................%c\n",copia_lista[cont].sexo_aluno);
        printf("\n");
    }
}
int listar_professores_sexo(professor *ponteiro_professor,int qtd_professores){
    if(qtd_professores == 0){
        printf("nao ha professores matriculados\n");
        return ERRO;
    }
    printf("========== masculino ================\n");
    for(int cont = 0;cont < qtd_professores;cont++){
        if(ponteiro_professor[cont].sexo_professor == 'm'|| ponteiro_professor[cont].sexo_professor == 'M'){

            printf("nome:.............................%s\n",ponteiro_professor[cont].nome_professor);
            printf("matricula:........................%d\n",ponteiro_professor[cont].matricula);
            printf("data:.............................%d-%d-%d\n",ponteiro_professor[cont].dia,ponteiro_professor[cont].mes,ponteiro_professor[cont].ano);
            saida_formatada_cpf( ponteiro_professor[cont].cpf_professor);
            printf("sexo:.............................%c\n",ponteiro_professor[cont].sexo_professor);
            printf("\n");
        }



    }
    for(int cont = 0;cont < qtd_professores;cont++){
        if(ponteiro_professor[cont].sexo_professor == 'f'|| ponteiro_professor[cont].sexo_professor == 'F'){
            printf("========== feminino ================\n");
            printf("nome:.............................%s\n",ponteiro_professor[cont].nome_professor);
            printf("matricula:........................%d\n",ponteiro_professor[cont].matricula);
            printf("data:.............................%d-%d-%d\n",ponteiro_professor[cont].dia,ponteiro_professor[cont].mes,ponteiro_professor[cont].ano);
            saida_formatada_cpf( ponteiro_professor[cont].cpf_professor);
            printf("sexo:.............................%c\n",ponteiro_professor[cont].sexo_professor);
            printf("\n");
        }



    }

    return 1;
}
int exibir_professores_ordem_alfabetica(professor *ponteiro_professor,int qtd_professores){
    if(qtd_professores == 0){
        printf("nao existem professores cadastrados\n");
        return ERRO;
    }
    int cont,jcont;
    char aux_sexo,aux_cpf[TAM_CPF],aux_nome[TAM_NOME];
    int aux_matricula,aux_dia,aux_mes,aux_ano;
    professor copia_lista[TAM_PROFESSOR];
    copia_vetores_professor(ponteiro_professor,copia_lista,qtd_professores);
    //ordenacao
    for(cont = 0 ;cont < qtd_professores -1;cont++){

        for(jcont = cont + 1;jcont  < qtd_professores;jcont++){
            strcpy(aux_nome,copia_lista[cont].nome_professor);
            aux_matricula = copia_lista[cont].matricula;
            aux_dia = copia_lista[cont].dia;
            aux_mes = copia_lista[cont].mes;
            aux_ano = copia_lista[cont].ano;
            strcpy(aux_cpf,copia_lista[cont].cpf_professor);
            aux_sexo = copia_lista[cont].sexo_professor;
            if(strcmp(copia_lista[cont].nome_professor,copia_lista[jcont].nome_professor)  > 0){
                strcpy(copia_lista[cont].nome_professor,copia_lista[jcont].nome_professor);
                strcpy(copia_lista[jcont].nome_professor,aux_nome);

                copia_lista[cont].matricula = copia_lista[jcont].matricula;
                copia_lista[jcont].matricula = aux_matricula;

                copia_lista[cont].dia = copia_lista[jcont].dia;
                copia_lista[jcont].dia = aux_dia;

                copia_lista[cont].mes = copia_lista[jcont].mes;
                copia_lista[jcont].mes = aux_mes;

                copia_lista[cont].ano= copia_lista[jcont].ano;
                copia_lista[jcont].ano = aux_ano;

                strcpy(copia_lista[cont].cpf_professor,copia_lista[jcont].cpf_professor);
                strcpy(copia_lista[jcont].cpf_professor,aux_cpf);

                copia_lista[cont].sexo_professor = copia_lista[jcont].sexo_professor;
                copia_lista[jcont].sexo_professor = aux_sexo;



            }
        }
    }
    impressao_professor(copia_lista,qtd_professores);
    //impressao



    return 1;
}
void copia_vetores_professor(professor *ponteiro_professor,professor *copia_lista,int qtd_professores){
    for(int cont = 0;cont < qtd_professores;cont++){
        strcpy(copia_lista[cont].nome_professor,ponteiro_professor[cont].nome_professor);//nome
        copia_lista[cont].dia = ponteiro_professor[cont].dia;//dia
        copia_lista[cont].mes = ponteiro_professor[cont].mes;//mes
        copia_lista[cont].ano = ponteiro_professor[cont].ano;//ano
        strcpy(copia_lista[cont].cpf_professor,ponteiro_professor[cont].cpf_professor);//cpf
        copia_lista[cont].matricula = ponteiro_professor[cont].matricula;//matricula
        copia_lista[cont].sexo_professor = ponteiro_professor[cont].sexo_professor;//sexo
    }
}
void impressao_professor(professor *copia_lista,int qtd_professores){
    for(int cont = 0;cont < qtd_professores;cont++){

        printf("nome:.............................%s\n",copia_lista[cont].nome_professor);
        printf("matricula:........................%d\n",copia_lista[cont].matricula);
        printf("data:.............................%d-%d-%d\n",copia_lista[cont].dia,copia_lista[cont].mes,copia_lista[cont].ano);
        saida_formatada_cpf( copia_lista[cont].cpf_professor);
        printf("sexo:.............................%c\n",copia_lista[cont].sexo_professor);
        printf("\n");
    }
}
int exibir_professore_data(professor *ponteiro_professor,int qtd_professores){
    if(qtd_professores == 0){
        printf("nao existem professores cadastrados\n");
        return ERRO;
    }
    int cont,jcont;
    char aux_sexo,aux_cpf[TAM_CPF],aux_nome[TAM_NOME];
    int aux_matricula,aux_dia,aux_mes,aux_ano;
    professor copia_lista[TAM_PROFESSOR];
    copia_vetores_professor(ponteiro_professor,copia_lista,qtd_professores);


    for(cont = 0 ;cont < qtd_professores -1;cont++){

        for(jcont = cont + 1;jcont  < qtd_professores;jcont++){
            strcpy(aux_nome,copia_lista[cont].nome_professor);
            aux_matricula = copia_lista[cont].matricula;
            aux_dia = copia_lista[cont].dia;
            aux_mes = copia_lista[cont].mes;
            aux_ano = copia_lista[cont].ano;
            strcpy(aux_cpf,copia_lista[cont].cpf_professor);
            aux_sexo = copia_lista[cont].sexo_professor;
            int dia = (int)copia_lista[cont].dia;
            int dia2 = (int)copia_lista[jcont].dia;
            int mes = (int)copia_lista[cont].mes;
            int mes2 = (int)copia_lista[jcont].mes;
            int ano = (int)copia_lista[cont].ano;
            int ano2 = (int)copia_lista[jcont].ano;




            if(verifica_data(dia,mes,ano,dia2,mes2,ano2) == 1){
                strcpy(copia_lista[cont].nome_professor,copia_lista[jcont].nome_professor);
                strcpy(copia_lista[jcont].nome_professor,aux_nome);

                copia_lista[cont].matricula = copia_lista[jcont].matricula;
                copia_lista[jcont].matricula = aux_matricula;

                copia_lista[cont].dia = copia_lista[jcont].dia;
                copia_lista[jcont].dia = aux_dia;

                copia_lista[cont].mes = copia_lista[jcont].mes;
                copia_lista[jcont].mes = aux_mes;

                copia_lista[cont].ano= copia_lista[jcont].ano;
                copia_lista[jcont].ano = aux_ano;

                strcpy(copia_lista[cont].cpf_professor,copia_lista[jcont].cpf_professor);
                strcpy(copia_lista[jcont].cpf_professor,aux_cpf);

                copia_lista[cont].sexo_professor = copia_lista[jcont].sexo_professor;
                copia_lista[jcont].sexo_professor = aux_sexo;



            }
        }
    }
    impressao_professor(copia_lista,qtd_professores);

    return 1;
}
void calcula_disciplinas_do_aluno(aluno *ponteiro_aluno,int qtd_alunos,disciplina *ponteiro_disciplina,int qtd_disciplinas){
    int matricula_aluno;
    int quantidade_disciplina;
    for(int cont = 0;cont < qtd_alunos;cont++){
        quantidade_disciplina = 0;
        matricula_aluno = ponteiro_aluno[cont].matricula;
       for(int contador = 0;contador < qtd_disciplinas;contador++){

           if(pesquisa_aluno_disciplina(ponteiro_disciplina,contador,
                                        matricula_aluno,ponteiro_disciplina[contador].fim_aluno)!=ERRO){

               quantidade_disciplina++;
           }
       }
        ponteiro_aluno[cont].qtd_discipinas_cursadas = quantidade_disciplina;




    }


}
int exibir_qtd_disciplinas_alunos(aluno *ponteiro_aluno,int qtd_alunos,disciplina *ponteiro_disciplina,int qtd_disciplinas){
    if(qtd_alunos == 0 || qtd_disciplinas == 0){
        printf("nao ha alunos ou disciplinas cadastrados\n");
        return ERRO;
    }
    calcula_disciplinas_do_aluno(ponteiro_aluno,qtd_alunos,ponteiro_disciplina ,qtd_disciplinas);
    for(int cont = 0;cont < qtd_alunos;cont++){
        if(ponteiro_aluno[cont].qtd_discipinas_cursadas >=3){
            printf("nome:.............................%s\n",ponteiro_aluno[cont].nome_aluno);
            printf("matricula:........................%d\n",ponteiro_aluno[cont].matricula);
            printf("data:.............................%d-%d-%d\n",ponteiro_aluno[cont].dia,ponteiro_aluno[cont].mes,ponteiro_aluno[cont].ano);
            saida_formatada_cpf( ponteiro_aluno[cont].cpf_aluno);
            printf("sexo:.............................%c\n",ponteiro_aluno[cont].sexo_aluno);
            printf("disciplinas:.......................%d\n",ponteiro_aluno[cont].qtd_discipinas_cursadas);
            printf("\n");
        }

    }

    return 1;
}