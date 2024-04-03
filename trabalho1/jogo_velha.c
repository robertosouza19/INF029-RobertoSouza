#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define LINHA  3
#define COLUNA 3
#define TAM_CELULA 3 //qtd caracters de uma celula +1
#define VERDADE 1
int realiza_jogada(int linhas,int colunas,char matriz[linhas][colunas],char jogador);
void impressao_matriz(int linha,int coluna,char matriz[linha][coluna]);
void remocao_quebra_linha(char *string);
int avalia_celula(int linhas,int colunas,char matriz[linhas][colunas],int linha,int coluna);
int ganhou_jogo(int linhas,int colunas,char matriz[linhas][colunas]);
void limparBuffer();
int empatou_jogo(int linhas,int colunas,char matriz[linhas][colunas]);

int main() {
    int contador = 0;
    int vitoria_jogo;
    int sem_vencedor;
    char jogador1 = 'X';
    char jogador2 = 'O';
    char matriz[LINHA][COLUNA] = {"***","***","***"};

    do{
        if(contador % 2 == 0){// jogador 1
            impressao_matriz(LINHA, COLUNA,matriz);//imprimir
            realiza_jogada(LINHA,COLUNA,matriz,jogador1);//executa celula
            impressao_matriz(LINHA, COLUNA,matriz);
            vitoria_jogo = ganhou_jogo(LINHA,COLUNA,matriz);
            sem_vencedor =  empatou_jogo(LINHA,COLUNA, matriz);
            if(vitoria_jogo == VERDADE){
                printf("parabens ganhou o jogo\n");
            }
            else if(sem_vencedor == VERDADE){
                printf("o jogou empatou\n");
            }
        }
        else{//jogador 2
            impressao_matriz(LINHA, COLUNA,matriz);
            realiza_jogada(LINHA,COLUNA,matriz,jogador2);
            impressao_matriz(LINHA, COLUNA,matriz);
            vitoria_jogo = ganhou_jogo(LINHA,COLUNA,matriz);
            sem_vencedor =  empatou_jogo(LINHA,COLUNA, matriz);
            if(vitoria_jogo == VERDADE){
                printf("parabens ganhou o jogo\n");
            }
            else if(sem_vencedor == VERDADE){
                printf("o jogou empatou\n");
            }
        }
        contador++;
    }while(vitoria_jogo !=VERDADE && sem_vencedor!= VERDADE);





    return 0;
}
void impressao_matriz(int linha,int coluna,char matriz[linha][coluna]){
    char letra;
    printf("====== JOGO DA VELHA ========\n");
    printf("    1   2   3\n--------------\n");//imprimir os numeros acima tabela
    letra = 'A';


    for(int cont = 0;cont < linha;cont++){
        printf("%c",letra);
        for(int jcont = 0;jcont < coluna;jcont++){
            printf("%3c|",matriz[cont][jcont]);//

        }
        printf("\n--------------");
        puts("");
        letra++;
    }

}
int realiza_jogada(int linhas,int colunas,char matriz[linhas][colunas],char jogador){
   int linha,coluna;
   int celula_valida = 0;
    char celula[6];//alfanumerico


        do{

            printf("informe a celula da jogada:\n");
            fgets(celula,TAM_CELULA,stdin);
            remocao_quebra_linha(celula);
            fflush(stdout);
            limparBuffer();
            int tamanho = strlen(celula);//definir tamanho iserido
            if(tamanho !=2){
                celula_valida = -1;
            }
            linha = toupper(celula[0]);//converted caracter para maiusculo garanti linha e miusculo
            linha  = (int)(linha-65);//conversao para um indice
            coluna = (int)celula[1] - 49;
            celula_valida = avalia_celula(LINHA, COLUNA,matriz,linha,coluna);
            if(celula_valida == -1){
                printf("celula invalida\n");

            }
            else if(celula_valida == -2){
                printf("a celula ja foi prenchida\n");
            }
            setbuf(stdin,NULL);
        }while(celula_valida != 1);

        matriz[linha][coluna] = jogador;

    return 1;
}
void remocao_quebra_linha(char *string){
    int cont = 0;
    while(string[cont]!='\0'){
        if(string[cont] == '\n'){
            string[cont] = '\0';
        }
        cont++;
    }
}

int avalia_celula(int linhas,int colunas,char matriz[linhas][colunas],int linha,int coluna){
    // * representa celula vazia linha ou coluna 3 *  deve ser iginorada na avaliacao do vencedor
    if(linha < 0 || linha > 2){
        return -1;
    }
    else if(coluna < 0 || coluna > 2){
        return  -1;
    }
    else if(matriz[linha][coluna] =='O'|| matriz[linha][coluna] == 'X'){
        return -2;
    }
   return 1;
}
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int ganhou_jogo(int linhas,int colunas,char matriz[linhas][colunas]) {
    int icont,jcont,contador = 0,kcont;
    int ordem_matriz = 3;
    char primeiro_elemento;
    //laco pecorrer as linhas
    //nao deve comparar celulas com valor * pois elas estao vazias
    for(icont = 0;icont < linhas;icont++){
        primeiro_elemento = matriz[icont][0];//inicio de cada linha
        for(jcont = 0;jcont < colunas;jcont++){
            if( (primeiro_elemento !='*')&&(matriz[icont][jcont] == primeiro_elemento) ){
                contador++;
            }
        }
        if(contador == 3){
            return  1;
        }
        else{
            contador = 0;
        }
    }//pecorre colunas
    for(kcont = 0;kcont < 3;kcont++){
        primeiro_elemento = matriz[0][kcont];
        for(icont = 0;icont < linhas;icont++){
            for(jcont = 0;jcont < colunas;jcont++){
                if ( (primeiro_elemento !='*') && (matriz[icont][jcont] == primeiro_elemento)&& (jcont == kcont) ){
                    contador++;
                }
            }

        }
        if(contador == 3){
            return  1;
        }
        else{
            contador = 0;
        }
    }//percorrer a diagonal principal
    primeiro_elemento = matriz[0][0];
    for(kcont = 0;kcont < 3;kcont++){
        if( (primeiro_elemento != '*')&&(primeiro_elemento == matriz[kcont][kcont]) ){
            contador++;
        }
    }
    if(contador == 3){
        return 1;
    }
    else{
       contador = 0;
    }
    //pecorrer a diagonal secundaria
    primeiro_elemento = matriz[0][2];
    for(icont = 0;icont < linhas;icont++){
        for(jcont = 0;jcont < colunas;jcont++){
            if((primeiro_elemento != '*')&&(icont + jcont == ordem_matriz -1) &&(primeiro_elemento == matriz[icont][jcont]) ){
                contador++;
            }
            if(contador == 3){
                return 1;
            }
        }
    }
    return  -1;

}
int empatou_jogo(int linhas,int colunas,char matriz[linhas][colunas]){
    int icont,jcont,contador = 0,kcont;
    char primeiro_valor;
    for(icont = 0;icont < linhas;icont++){//linhas
        primeiro_valor = matriz[icont][0];
        for(jcont = 0;jcont < colunas;jcont++){
            if ( (primeiro_valor !='*' && matriz[icont][jcont]!='*')&&(matriz[icont][jcont]!=primeiro_valor) ){
                contador++;
                break;
            }
        }
    }

    //colunas
    for(kcont = 0;kcont < 3;kcont++){
        primeiro_valor = matriz[0][kcont];
        for(icont = 0;icont < linhas;icont++){
            for(jcont = 0;jcont < colunas;jcont++){
                if ( (primeiro_valor !='*' && matriz[icont][jcont]!='*')&&(matriz[icont][jcont]!=primeiro_valor) ){
                    contador++;
                    icont = 3;
                    break;
                }
            }
        }

    }

    //diagonal principal
    primeiro_valor = matriz[0][0];
    for(icont = 0;icont < 3;icont++){
        if ( (primeiro_valor !='*' && matriz[icont][icont]!='*')&&(matriz[icont][icont]!=primeiro_valor) ){
            contador++;

            break;
        }
    }
    //diagonal secundaria
    primeiro_valor = matriz[2][0];
    for(icont = 0;icont < linhas;icont++){
        for(jcont = 0;jcont < colunas;jcont++){
            if(icont + jcont == 2){ //codicao para pecorrer diagonal secundaria
                if ( (primeiro_valor !='*' &&  matriz[icont][jcont]!='*')&&(matriz[icont][jcont]!=primeiro_valor) ){
                    contador++;
                    icont = 3;
                    break;
                }
            }

        }
    }
    if(contador == 8){
        return  1;
    }
    else{
        return -1;
    }

}