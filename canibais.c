#include <stdio.h>

// Durante todo o codigo, 1 = missionario e 2 = canibal, sendo 0 o espa�o vazio

void inicializarVetor(int esq[], int dir[]){        //Posicionar os primeiros Canibais e missionarios
    for(int i = 0; i < 6; i++){
        esq[i] = 0;

        if(i < 3)
            dir[i] = 1;
        else
            dir[i] = 2;

    }
}

int statusJogo(int esq[], int dir[]){
    int contagem11 = 0, contagem12 = 0, contagem21 = 0, contagem22 = 0; //Verificar se o jogo ja acabou ou nao

    for(int i = 0; i < 6; i++){
        if(esq[i] == 1)
            contagem11++;

        else if(esq[i] == 2)
            contagem12++;

        if(dir[i] == 1)
            contagem21++;
        else if(dir[i] == 2)
            contagem22++;
    }


    if(contagem11 < contagem12 && contagem11 != 0)   // Caso tenha mais canibal do que missionario
        return 0;

    if(contagem21 < contagem22 && contagem21 != 0)   // Caso tenha mais canibal do que missionario
        return 0;

    if(contagem21 == 0 && contagem22 == 0)           // Se o lado direito esta vazio(fim de jogo)
        return 2;

    else                                             //continuar
        return 1;
}

void transportarDirEsq(int *vaga1, int *vaga2, int esq[], int dir[]){      //Trocar da direita pra esquerda

    for(int i = 0; i < 6; i++){
        if(dir[i] == *vaga1 && *vaga1 != 0){
            esq[i] = *vaga1;
            dir[i] = 0;
            *vaga1 = 0;
            continue;
                }

        if(dir[i] == *vaga2 && *vaga2 != 0){
            esq[i] = *vaga2;
            dir[i] = 0;
            *vaga2 = 0;
            continue;
            }
    }
}

void transportarEsqDir(int *vaga1, int *vaga2, int esq[], int dir[]){     //Trocar da esquerda pra direita

    for(int i = 0; i < 6; i++){
        if(esq[i] == *vaga1 && *vaga1 != 0){
            dir[i] = *vaga1;
            esq[i] = 0;
            *vaga1 = 0;
            continue;
        }
        if(esq[i] == *vaga2 && *vaga2 != 0){
            dir[i] = *vaga2;
            esq[i] = 0;
            *vaga2 = 0;
            continue;
            }
    }
}



void imprimirJogo(int vaga1, int esq[], int dir[], int *movimento){

    for(int i = 0; i < 3; i++){
        printf("[%d]|           |[%d]\n", esq[i], dir[i]);
        }

    if(*movimento % 2 == 1)
        printf("   |[%d][0]    |\n", vaga1);

    else if(*movimento % 2 == 0)
        printf("   |     [%d][0]|\n", vaga1);

    for(int i = 0; i < 3; i++){
        printf("[%d]|           |[%d]\n", esq[i+3], dir[i+3]);
        }
}

int main(){

    int esq[6], dir[6];
    int vaga1 = 0, vaga2 = 4, movimento = 0, status = 1;

    printf("Bem vindo ao jogo dos missionarios!\nO objetivo do jogo eh passar todos os missionarios ");
    printf("e canibais para o outro lado do rio.\nMas tome cuidado, se o numero de canibais passar");
    printf(" o de missionarios, o jogo acaba!\n\n");

    inicializarVetor(esq, dir);

    while(status == 1){

        system("clear");

        imprimirJogo(vaga1, esq, dir, &movimento);

        movimento += 1;

        if((movimento % 2) == 1)
            printf("O bote esta indo da direita pra esquerda\n");           //Se o movimento for impar (começa no 1), o bote vai da direita pra esquerda

        else
            printf("O bote esta indo da esquerda pra direita\n");            //Se o movimento for par, como um numero par /2 nao tem resto, o bote vai da direita pra esquerda

        while((vaga1 != 1) && (vaga1 != 2)){
            printf("Quem voce quer levar na primeira vaga? 1 para missionario e 2 para canibal: \n");
            scanf("%d", &vaga1);

            if((vaga1 != 1) && (vaga1 != 2))
                printf("Alternativa invalida!\n");
                continue;
        }

        vaga2 = 3;                                                          //Pra poder cair no while

        while(vaga2 != 1 && vaga2 != 2 && vaga2 != 0){
            printf("Quem voce quer levar na segunda vaga? 1 para missionario e 2 para canibal, 0 para vazio: \n");
            scanf("%d", &vaga2);

            if((vaga2 != 1) && (vaga2 != 2) && (vaga2 != 0))
                printf("Alternativa invalida!\n");
                continue;
        }

        if((movimento % 2) == 1)
            transportarDirEsq(&vaga1, &vaga2, esq, dir);

        if((movimento % 2) == 0)
            transportarEsqDir(&vaga1, &vaga2, esq, dir);

        status = statusJogo(esq, dir);
    }

    if(status == 0)
        printf("Voce perdeu, feche para tentar novamente \n");

    if(status == 2)
        printf("Boa, voce ganhou em %d jogadas! Parabens\n", movimento);


    return 0;
}
