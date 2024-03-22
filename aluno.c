//
// Created by rober on 15/02/2024.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "aluno.h"
#include "professor.h"

void limpeza_memoria() {

    int c;
    {
        while ((c = fgetc(stdin)) != '\n' && c != EOF);

    }
}
int menu_principal(){
    int opcao = -1;
    printf("========== escola ================\n");
    printf("0-sair\n");
    printf("1-alunos\n");
    printf("2-professores\n");
    printf("3-disciplinas\n");
    printf("4-relatorios\n");
    scanf("%d",&opcao);
    limpeza_memoria();
    return opcao;

}

int menu_alunos(){
    int opcao_aluno = -1;
    printf("========== alunos ================\n");
    printf("0-sair\n");
    printf("1-voltar\n");
    printf("2-adicionar alunos\n");
    printf("3-listar alunos\n");
    printf("4-atualizar alunos\n");
    printf("5-deletar alunos\n");
    scanf("%d",&opcao_aluno);
    limpeza_memoria();
    return opcao_aluno;

}


int cadastrar_aluno(aluno *ponteiro_aluno, int *qtd_alunos,int *matricula) {
    if(*qtd_alunos == TAM_ALUNO){
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
    int cpf_ja_foi_cadastrado;
    int tipo_ponteiro = 1;
    printf("informe o nome do aluno:\n");
    fgets(nome,TAM_NOME,stdin);
    remocao_quebra_linha(nome);
    do{
        printf("informe a data de nascimento do aluno:dd-mm-aaaa\n");
        fgets(data_nascimento,TAM_DATA,stdin);
        remocao_quebra_linha(data_nascimento);
        quebra_data(data_nascimento,&dia,&mes,&ano);
        data_esta_correta = valida_data(dia,mes,ano);
        if(data_esta_correta!= 1){
            printf("data invalida\n");
        }

    }while(data_esta_correta!= 1);

    do{

        printf("informe o cpf do aluno:\n");
        fgets(cpf,TAM_CPF,stdin);
        remocao_quebra_linha(cpf);

        cpf_esta_correto = valida_cpf(cpf);
        if(cpf_esta_correto != 1){
            printf("cpf invalido\n");
        }
        else{
           cpf_ja_foi_cadastrado = cpf_igual_no_cadastro(ponteiro_aluno,tipo_ponteiro,cpf,*qtd_alunos);

            if(cpf_ja_foi_cadastrado == 1){
                printf("cpf ja cadastrado\n");
                limpeza_memoria();
            }

        }
        //

    }while(cpf_esta_correto != 1 || cpf_ja_foi_cadastrado == 1);

    do{
        limpeza_memoria();//buffer
        printf("informe o sexo do aluno:[m/f]\n");
        scanf("%c",&sexo);
        sexo_correto = valida_sexo(sexo);
        if(sexo_correto != 1){
            printf("sexo invalido\n");
        }

    }while(sexo_correto !=1);

//salvando informacoes nas structs de alunos
    strcpy(ponteiro_aluno[*qtd_alunos].nome_aluno,nome);
    ponteiro_aluno[*qtd_alunos].dia = dia;
    ponteiro_aluno[*qtd_alunos].mes = mes;
    ponteiro_aluno[*qtd_alunos].ano= ano;
    strcpy(ponteiro_aluno[*qtd_alunos].cpf_aluno,cpf);
    ponteiro_aluno[*qtd_alunos].sexo_aluno = sexo;
    *matricula = *matricula +1;
    ponteiro_aluno[*qtd_alunos].matricula = *matricula;
    *qtd_alunos = *qtd_alunos +1;
    printf("cadastro do aluno realizado com sucesso\n");
    return 1;
}
void remocao_quebra_linha(char *string){
    int contador = 0;
    while(string[contador]!='\0'){
        if (string[contador] == '\n') {
            string[contador] = '\0';
        }


        contador++;
    }
}
int quebra_data(const char *data,int *dia,int *mes,int *ano){
    int contador = 0;
    int icont;
    char dias[3],meses[3],anos[5];
    while(data[contador]!='-'&& contador < 2){
        dias[contador] = data[contador];
        contador++;
    }
    dias[contador] = '\0';
    for(contador = contador +1,icont = 0;data[contador]!='-'&& icont < 2;icont++,contador++){
        meses[icont] = data[contador];
    }
    meses[icont] = '\0';
    for(contador = contador +1,icont = 0;icont < 4;icont++,contador++){
        anos[icont] = data[contador];
    }
    *dia = atoi(dias);
    *mes = atoi(meses);
    *ano = atoi(anos);

    return 1;
}
int valida_data(int dia,int mes,int ano){
    int ano_bissexto = 0;
    int data_valida = 0;
    if( (ano % 4 == 0 && ano % 100 != 0)||(ano % 400 == 0) ){
        ano_bissexto = 1;

    }
    if( (dia >= 1 && dia <= 31)&&(mes== 1 || mes == 3|| mes == 5|| mes == 7||mes == 8|| mes == 10 || mes == 12) ){
        data_valida = 1;
    }
    else if( (dia >= 1 && dia <= 30) && ( mes == 4 || mes == 6 || mes == 9 || mes == 11)){

        data_valida = 1;
    }
    else if( (dia >= 1 && dia <= 28)&&(mes == 2)){
        data_valida = 1;
    }
    else if( (dia >= 1 && dia <= 29) && (mes == 2) && (ano_bissexto == 1) ){
        data_valida = 1;
    }

    return data_valida;//se 0 invalida se for 1 e valida
}
int valida_cpf(const char *cpf){
    if( (digitos_iguais_cpf(cpf) == 1) ){
        return -1;

    }
    int digitos_cpf[11];
    int icont;
    int soma = 0;
    int resto;
    int primeiro_dig_verificador = 0,segundo_dig_verificador = 0;
    int fator_multiplicacao = 10;
    for(icont = 0;icont < 11;icont++){
        digitos_cpf[icont] = (int)cpf[icont]-48;//conversao para int guarda no vetor
    }
    icont = 0;
    while(fator_multiplicacao >= 2){
        soma = soma + fator_multiplicacao*digitos_cpf[icont];
        fator_multiplicacao--;
        icont++;
    }
    resto = soma % 11;
    int penultimo_digito = digitos_cpf[9];
    int ultimo_digito =  digitos_cpf[10];
    if( (resto == 0 || resto == 1)&&(penultimo_digito == 0) ){
        primeiro_dig_verificador = 1;
    }
    else if( (resto >= 2 && resto <=10)&& (penultimo_digito == 11-resto) ){
        primeiro_dig_verificador = 1;

    }
    //avaliacao do segundo digito verificador
    fator_multiplicacao = 11;
    soma = 0;
    icont = 0;
    while(fator_multiplicacao >= 2){
        soma = soma + fator_multiplicacao*digitos_cpf[icont];
        fator_multiplicacao--;
        icont++;
    }
    resto = soma % 11;

    if( (resto == 0 || resto == 1)&&(ultimo_digito == 0) ){
        segundo_dig_verificador = 1;
    }
    else if( (resto >= 2 && resto <=10)&& (ultimo_digito == 11-resto) ){
        segundo_dig_verificador = 1;

    }
    if(primeiro_dig_verificador == 1 && segundo_dig_verificador == 1){
        return 1;//cpf_valido
    }
    else{
        return 0;//cpf invalido
    }


}
int digitos_iguais_cpf(char const *cpf){

    for(int cont = 1;cpf[cont]!='\0';cont++){
        if(cpf[0]!=cpf[cont]){
            return 0;//nao tem digitos iguais
        }
    }
    return 1;//tem digitos iguais
}
int valida_sexo(char sexo){
    if(sexo == 'm'|| sexo =='M' || sexo =='F' || sexo =='f'){
        return 1;
    }
    else{
        return 0;
    }
}
int listar_alunos(aluno *ponteiro_aluno,int qtd_alunos){
    if(qtd_alunos == 0){
        printf("nao existem alunos cadastrados.\n");
        return -1;
    }
    printf("========== listagem de alunos ================\n");
    for(int cont = 0;cont < qtd_alunos;cont++){

        printf("nome:.............................%s\n",ponteiro_aluno[cont].nome_aluno);
        printf("matricula:........................%d\n",ponteiro_aluno[cont].matricula);
        printf("data:.............................%d-%d-%d\n",ponteiro_aluno[cont].dia,ponteiro_aluno[cont].mes,ponteiro_aluno[cont].ano);
        saida_formatada_cpf( ponteiro_aluno[cont].cpf_aluno);
        printf("sexo:.............................%c\n",ponteiro_aluno[cont].sexo_aluno);
        printf("\n");
    }
    return 1;

}
void saida_formatada_cpf(char *cpf){
    printf("cpf:..............................");
    for(int cont = 0;cont < 11;cont++){
        printf("%c",cpf[cont]);
        if( cont == 2){
            printf(".");
        }
        else if(cont == 5){
            printf(".");
        }
        else if(cont == 8){
            printf("-");
        }
    }
    printf("\n");
}
int cpf_igual_no_cadastro(void *ponteiro,int tipo_ponteiro,char *cpf,int qtd_usuarios){
    //criacao dos ponteiros
    aluno *ponteiro_aluno;
    professor *ponteiro_professor;
    if(tipo_ponteiro == 1){
       ponteiro_aluno = (aluno*)ponteiro; //cast para aluno
       for(int cont = 0;cont < qtd_usuarios;cont++){
           if(strcmp(cpf,ponteiro_aluno[cont].cpf_aluno) == 0){
               return 1;//cpf localizado

           }

       }
    }
    else if (tipo_ponteiro == 2){
        ponteiro_professor = (professor*)ponteiro;
        for(int cont = 0;cont < qtd_usuarios;cont++){
            if(strcmp(cpf,ponteiro_professor[cont].cpf_professor) == 0){
                return 1;//cpf localizado
            }
        }

    }
    return 0;//nao localizado

}
int atualizar_aluno(aluno *ponteiro_aluno,int qtd_alunos){
    if(qtd_alunos == 0){
        printf("nao existem alunos cadastrados.\n");
        return -1;
    }

    int matricula;
    char nome[TAM_NOME];
    int posicao_aluno;
    int tipo_ponteiro = 1;
    char data_nascimento[TAM_DATA];
    char cpf[TAM_CPF];
    char sexo;
    int sexo_correto;
    int dia,mes,ano;
    int data_esta_correta;
    int cpf_ja_existe;
    int cpf_esta_correto;
    printf("informe a matricula do aluno que deseja alterar  dados\n");
    scanf("%d",&matricula);
    posicao_aluno = busca_matricula(ponteiro_aluno, matricula,qtd_alunos,tipo_ponteiro);
    if(posicao_aluno == -1){
        printf("aluno nao localizado\n");
        return -1;
    }
    limpeza_memoria();
    printf("informe o novo nome do aluno:\n");
    fgets(nome,TAM_NOME,stdin);
    remocao_quebra_linha(nome);
    do{
        printf("informe a nova data de nascimento do aluno:dd-mm-aaaa\n");
        fgets(data_nascimento,TAM_DATA,stdin);
        remocao_quebra_linha(data_nascimento);
        quebra_data(data_nascimento,&dia,&mes,&ano);
        data_esta_correta = valida_data(dia,mes,ano);
        if(data_esta_correta!= 1){
            printf("data invalida\n");
        }

    }while(data_esta_correta!= 1);

    do{

        printf("informe o novo cpf aluno:\n");
        fgets(cpf,TAM_CPF,stdin);
        remocao_quebra_linha(cpf);

        cpf_esta_correto = valida_cpf(cpf);
        if(cpf_esta_correto != 1){
            printf("cpf invalido\n");
        }
        else{
            cpf_ja_existe = verifica_cpf_atualizacao(ponteiro_aluno,qtd_alunos,posicao_aluno,tipo_ponteiro,cpf);
            if(cpf_ja_existe == 1){
                printf("cpf ja cadastrado\n");
                getchar();
            }
        }


    }while(cpf_esta_correto != 1 || cpf_ja_existe == 1);

    do{
        //limpeza_memoria();//buffer
        getchar();
        printf("informe o sexo do aluno:[m/f]\n");
        scanf("%c",&sexo);
        sexo_correto = valida_sexo(sexo);
        if(sexo_correto != 1){
            printf("sexo invalido\n");
        }

    }while(sexo_correto !=1);
    //salvando dados
    strcpy(ponteiro_aluno[posicao_aluno].nome_aluno,nome);
    ponteiro_aluno[posicao_aluno].dia = dia;
    ponteiro_aluno[posicao_aluno].mes = mes;
    ponteiro_aluno[posicao_aluno].ano = ano;

return 1;
}
int busca_matricula(void *ponteiro,int matricula,int qtd_usuarios,int tipo_ponteiro){
    aluno *ponteiro_aluno;
    professor *ponteiro_professor;
    if(tipo_ponteiro == 1){
        ponteiro_aluno = (aluno*)ponteiro;
        for(int cont = 0;cont < qtd_usuarios;cont++){
            if(matricula == ponteiro_aluno[cont].matricula){
                return cont;//localizei a matricula
            }
        }

    }
    else if(tipo_ponteiro == 2){
        ponteiro_professor = (professor*)ponteiro;
        for(int cont = 0;cont < qtd_usuarios;cont++){
            if(matricula == ponteiro_professor[cont].matricula){
                return cont;//localizei a matricula
            }
        }

    }


    return -1;
}
int verifica_cpf_atualizacao(void *ponteiro,int qtd_pessoas,int minha_posicao,int tipo_ponteiro,char*cpf){
    //funcao verifica se o novo cpf igual demais do cadastro ele deve percorre array exeto posicao do cpf atual
    aluno *ponteiro_aluno;
    professor *ponteiro_professor;
    if(tipo_ponteiro == 1){
        ponteiro_aluno = (aluno*)ponteiro;
        for(int cont = 0;cont < qtd_pessoas;cont++){
            if(cont != minha_posicao){
                if(strcmp(ponteiro_aluno[cont].cpf_aluno,cpf) == 0){
                    return 1;
                }
            }
        }

    }
    else if(tipo_ponteiro == 2){
        ponteiro_professor = (professor*)ponteiro;
        for(int cont = 0;cont < qtd_pessoas;cont++){
            if(cont != minha_posicao){
                if(strcmp(ponteiro_professor[cont].cpf_professor,cpf) == 0){
                    return 1;
                }
            }
        }
    }

        return 0;
}
int excluir_aluno(aluno *ponteiro_aluno,int *qtd_alunos){
    if(*qtd_alunos == 0){
        printf("nao existe alunos cadastrados\n");
        return 0;
    }
    int matricula;
    int posicao_aluno;
    int tipo_ponteiro = 1;//aluno
    printf("informe a matricula do aluno que deseja excluir:\n");
    scanf("%d",&matricula);
    posicao_aluno = busca_matricula(ponteiro_aluno,matricula,*qtd_alunos,tipo_ponteiro);
    if(posicao_aluno == -1){
        printf("aluno nao localizado\n");
        return -1;
    }
    for(int icont = posicao_aluno;icont < *qtd_alunos-1;icont++){
        ponteiro_aluno[icont].matricula = ponteiro_aluno[icont + 1].matricula;
        strcpy(ponteiro_aluno[icont].nome_aluno,ponteiro_aluno[icont +1].nome_aluno);
        ponteiro_aluno[icont].dia = ponteiro_aluno[icont + 1].dia;
        ponteiro_aluno[icont].mes = ponteiro_aluno[icont + 1].mes;
        ponteiro_aluno[icont].ano= ponteiro_aluno[icont + 1].ano;
        strcpy(ponteiro_aluno[icont].cpf_aluno,ponteiro_aluno[icont+1].cpf_aluno);
        ponteiro_aluno[icont].sexo_aluno = ponteiro_aluno[icont+1].sexo_aluno;

    }
    *qtd_alunos = *qtd_alunos - 1;



    return matricula;
}
