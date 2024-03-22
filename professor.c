//
// Created by rober on 15/02/2024.
//

#include "professor.h"
#include "aluno.h"
#include <string.h>
#include <stdio.h>
int menu_professores(){
    int opcao_professor = -1;
    printf("========== professores ================\n");
    printf("0-sair\n");
    printf("1-voltar\n");
    printf("2-adicionar professores\n");
    printf("3-listar professores\n");
    printf("4-atualizar professores\n");
    printf("5-deletar professores\n");
    scanf("%d",&opcao_professor);
    limpeza_memoria();
    return opcao_professor;

}

int cadastrar_professor(professor *ponteiro_professor, int *qtd_professores,int *matricula) {
    if(*qtd_professores == TAM_PROFESSOR){
        printf("lista de alunos cheia\n");
        return -1;
    }
    char nome[TAM_NOME];
    char data_nascimento[TAM_DATA];
    int dia,mes,ano;
    char cpf[TAM_CPF],sexo;
    int data_esta_correta;
    int cpf_esta_correto;
    int sexo_correto;
    int cpf_ja_esta_cadastrado;
    int tipo_ponteiro = 2;
    printf("informe o nome do professor:\n");
    fgets(nome,TAM_NOME,stdin);
    remocao_quebra_linha(nome);
    do{
        printf("informe a data de nascimento do professor:dd-mm-aaaa\n");
        fgets(data_nascimento,TAM_DATA,stdin);
        remocao_quebra_linha(data_nascimento);
        quebra_data(data_nascimento,&dia,&mes,&ano);
        data_esta_correta = valida_data(dia,mes,ano);
        if(data_esta_correta!= 1){
            printf("data invalida\n");
        }

    }while(data_esta_correta!= 1);

    do{
        printf("informe o cpf do professor:\n");
        fgets(cpf,TAM_CPF,stdin);
        remocao_quebra_linha(cpf);
        cpf_esta_correto = valida_cpf(cpf);
        if(cpf_esta_correto != 1){
            printf("cpf invalido\n");
        }
        else{
            cpf_ja_esta_cadastrado = cpf_igual_no_cadastro(ponteiro_professor,tipo_ponteiro,cpf,*qtd_professores);
            if(cpf_ja_esta_cadastrado == 1){
                printf("cpf ja cadastrado\n");
                limpeza_memoria();
            }
        }
    }while(cpf_esta_correto != 1|| cpf_ja_esta_cadastrado == 1);

    do{
        limpeza_memoria();//buffer
        printf("informe o sexo do professor:[m/f]\n");
        scanf("%c",&sexo);
        sexo_correto = valida_sexo(sexo);
        if(sexo_correto != 1){
            printf("sexo invalido\n");
        }

    }while(sexo_correto !=1);

//salvando informacoes nas structs de professores
    strcpy(ponteiro_professor[*qtd_professores].nome_professor,nome);
    ponteiro_professor[*qtd_professores].dia = dia;
    ponteiro_professor[*qtd_professores].mes = mes;
    ponteiro_professor[*qtd_professores].ano= ano;
    strcpy(ponteiro_professor[*qtd_professores].cpf_professor,cpf);
    ponteiro_professor[*qtd_professores].sexo_professor = sexo;
    *matricula = *matricula +1;
    ponteiro_professor[*qtd_professores].matricula = *matricula;
    *qtd_professores = *qtd_professores +1;
    printf("cadastro do professor realizado com sucesso\n");
    return 1;
}


int listar_professores(professor *ponteiro_professor,int qtd_professores){
    if(qtd_professores == 0){
        printf("nao existem alunos cadastrados.\n");
        return -1;
    }
    printf("========== listagem de professores ================\n");
    for(int cont = 0;cont < qtd_professores;cont++){

        printf("nome:.............................%s\n",ponteiro_professor[cont].nome_professor);
        printf("matricula:........................%d\n",ponteiro_professor[cont].matricula);
        printf("data:.............................%d-%d-%d\n",ponteiro_professor[cont].dia,ponteiro_professor[cont].mes,ponteiro_professor[cont].ano);
        saida_formatada_cpf( ponteiro_professor[cont].cpf_professor);
        printf("sexo:.............................%c\n",ponteiro_professor[cont].sexo_professor);
        printf("\n");
    }
    return 1;

}


int atualizar_professor(professor *ponteiro_professor,int qtd_professores){
    if(qtd_professores == 0){
        printf("nao existem professores cadastrados.\n");
        return -1;
    }

    int matricula;
    char nome[TAM_NOME];
    int posicao_professor;
    int tipo_ponteiro = 2;
    char data_nascimento[TAM_DATA];
    char cpf[TAM_CPF];
    char sexo;
    int sexo_correto;
    int dia,mes,ano;
    int data_esta_correta;
    int cpf_ja_existe;
    int cpf_esta_correto;
    printf("informe a matricula do professor que deseja alterar  dados\n");
    scanf("%d",&matricula);
    posicao_professor = busca_matricula(ponteiro_professor, matricula,qtd_professores,tipo_ponteiro);
    if(posicao_professor == -1){
        printf("professor nao localizado\n");
        return -1;
    }
    limpeza_memoria();
    printf("informe o novo nome do professor:\n");
    fgets(nome,TAM_NOME,stdin);
    remocao_quebra_linha(nome);
    do{
        printf("informe a nova data de nascimento do professor:dd-mm-aaaa\n");
        fgets(data_nascimento,TAM_DATA,stdin);
        remocao_quebra_linha(data_nascimento);
        quebra_data(data_nascimento,&dia,&mes,&ano);
        data_esta_correta = valida_data(dia,mes,ano);
        if(data_esta_correta!= 1){
            printf("data invalida\n");
        }

    }while(data_esta_correta!= 1);

    do{

        printf("informe o novo cpf professor:\n");
        fgets(cpf,TAM_CPF,stdin);
        remocao_quebra_linha(cpf);

        cpf_esta_correto = valida_cpf(cpf);
        if(cpf_esta_correto != 1){
            printf("cpf invalido\n");
        }
        else{
            cpf_ja_existe = verifica_cpf_atualizacao(ponteiro_professor,qtd_professores,posicao_professor,tipo_ponteiro,cpf);
            if(cpf_ja_existe == 1){
                printf("cpf ja cadastrado\n");
                getchar();
            }
        }


    }while(cpf_esta_correto != 1 || cpf_ja_existe == 1);

    do{
        //limpeza_memoria();//buffer
        getchar();
        printf("informe o sexo do professor:[m/f]\n");
        scanf("%c",&sexo);
        sexo_correto = valida_sexo(sexo);
        if(sexo_correto != 1){
            printf("sexo invalido\n");
        }

    }while(sexo_correto !=1);
    //salvando dados
    strcpy(ponteiro_professor[posicao_professor].nome_professor,nome);
    strcpy(ponteiro_professor[posicao_professor].cpf_professor,cpf);
    ponteiro_professor[posicao_professor].dia = dia;
    ponteiro_professor[posicao_professor].mes = mes;
    ponteiro_professor[posicao_professor].ano = ano;
    ponteiro_professor[posicao_professor].sexo_professor = sexo;

    return 1;
}

int excluir_professor(professor *ponteiro_professor,int *qtd_professores){
    if(*qtd_professores == 0){
        printf("nao existe professores cadastrados\n");
        return 0;
    }
    int matricula;
    int posicao_professor;
    int tipo_ponteiro = 1;//aluno
    printf("informe a matricula do professor que deseja excluir:\n");
    scanf("%d",&matricula);
    posicao_professor = busca_matricula(ponteiro_professor,matricula,*qtd_professores,tipo_ponteiro);
    if(posicao_professor == -1){
        printf("professor nao localizado\n");
        return -1;
    }
    for(int icont = posicao_professor;icont < *qtd_professores-1;icont++){
        ponteiro_professor[icont].matricula = ponteiro_professor[icont + 1].matricula;
        strcpy(ponteiro_professor[icont].nome_professor,ponteiro_professor[icont +1].nome_professor);
        ponteiro_professor[icont].dia = ponteiro_professor[icont + 1].dia;
        ponteiro_professor[icont].mes = ponteiro_professor[icont + 1].mes;
        ponteiro_professor[icont].ano= ponteiro_professor[icont + 1].ano;
        strcpy(ponteiro_professor[icont].cpf_professor,ponteiro_professor[icont+1].cpf_professor);
        ponteiro_professor[icont].sexo_professor = ponteiro_professor[icont+1].sexo_professor;

    }
    *qtd_professores = *qtd_professores - 1;
    printf("professor excluido com sucesso\n");
    return 1;
}
