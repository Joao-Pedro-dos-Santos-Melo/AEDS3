#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "Aresta.c++"
//#include "Vertice.c++"
int contA2;
void quick(int esq, int dir, int vet[][3]){
    int pivo = esq, i,ch,j;         
    for(i=esq+1;i<=dir;i++){        
        j = i;                      
        if(vet[j][0] < vet[pivo][0]){     
            ch = vet[j][0];               
            while(j > pivo){           
                vet[j][0] = vet[j-1][0];      
                j--;                    
            }
            vet[j][0] = ch;               
            pivo++;                    
        }
    }
    if(pivo-1 >= esq){              
        quick(esq,pivo-1, vet);      
    }
    if(pivo+1 <= dir){              
        quick(pivo+1,dir, vet);      
    }
 }


int main(){
    int contV = 0;
    int contA = 0;
    int peso = 0;
    int verticePrimeiro = 0;
    int verticeSegundo = 0;
    int l = 0;
    //Abrir e ler o tamanho da matriz
    FILE *arq;
    arq = fopen( "dados2.txt", "rt");
    while(!feof(arq)){
        fscanf(arq, "%d %d %d\n", &peso, &verticePrimeiro, &verticeSegundo);
        printf("%d %d %d\n", peso , verticePrimeiro, verticeSegundo);
        contA++;
        if(contV < verticePrimeiro){
            contV = verticePrimeiro;
        }
        if(contV < verticeSegundo){
            contV = verticeSegundo;
        }
    }
    printf("numero de vertices %d \n", contV);
    printf("numerto de arestas %d \n", contA);
    contA2 = contA;
    fclose(arq);
    //criando matriz adjacente
    arq = fopen( "dados2.txt", "rt");
    int matriz[contV + 1][contV + 1];
    for(int i = 0; i <= contV; i++){
        for(int j = 0; j <= contV; j++){
            matriz[i][j] = 0;
        }
    }
    int arestas[contA - 1][3];
    for(int i = 0; i < contA; i++){
        for(int j = 0; j < 3; j++){
            arestas[i][j] = 0;
        }
    }
    int i = 0;
    while(!feof(arq)){
        fscanf(arq, "%d %d %d\n", &peso, &verticePrimeiro, &verticeSegundo);
        arestas[i][0] = peso; //peso fica na posicao 0 (primeira linha)
        arestas[i][1] = verticePrimeiro; //v1 fica na posicao 1 (segunda linha)
        arestas[i][2] = verticeSegundo; //v2 fica na posicao 2 (terceira linha)
        matriz[verticePrimeiro][verticeSegundo] = peso;
        matriz[verticeSegundo][verticePrimeiro] = peso;
        i++;
    }
    printf("\n=============================================================================================================\n");
    for(int i = 1; i <= contV; i++){
        for(int j = 1; j <= contV; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    fclose(arq);
    printf("\n=============================================================================================================\n");
    //quick sort
    for(int i = 0; i <= contA; i++){
        for(int j = 0; j < 3; j++){
            printf("%d ", arestas[i][j]);
        }
        printf("\n");
    }
    quick(0, contA, arestas);
    printf("\n=============================================================================================================\n");
    for(int i = 0; i <= contA; i++){
        for(int j = 0; j < 3; j++){
            printf("%d ", arestas[i][j]);
        }
        printf("\n");
    }
    // //arvore geradoura minima
    // int floresta[contV + 1][contV];
    // int arvore[3][contV - 1];
    return 0;
}