#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "Aresta.c++"
//#include "Vertice.c++"
int c = 0;
void quick(int esq, int dir, int vet[][3]){
    int pivo = esq, i,ch,j, av1, av2;         
    for(i=esq+1;i<=dir;i++){        
        j = i;                      
        if(vet[j][0] < vet[pivo][0]){     
            ch = vet[j][0];
            av1 = vet[j][1];
            av2 = vet[j][2];               
            while(j > pivo){           
                vet[j][0] = vet[j-1][0];
                vet[j][1] = vet[j-1][1];
                vet[j][2] = vet[j-1][2];      
                j--;                    
            }
            vet[j][0] = ch;  
            vet[j][1] = av1;
            vet[j][2] = av2;             
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

bool verifica(int f[], int v1, int v2, int contV){
    bool r = true;
    f[v1 * (contV) + 0] = 1;
    for(int j = 1; f[v1 * contV + j] != 0; j++){
        if (f[v1 * contV + j] == v2) {
            return false;
        } else {
            if (f[v1 * contV + j] == 0) {
                r = verifica( f, f[v1 * contV + j], v2, contV);
            }
        }
        if(r == false){
            return r;
        }
    }
    return r;
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
    fclose(arq);
    //criando matriz adjacente
    arq = fopen( "dados2.txt", "rt");
    int matriz[contV + 1][contV + 1];
    for(int i = 0; i <= contV; i++){
        for(int j = 0; j <= contV; j++){
            matriz[i][j] = 0;
        }
    }
    int arestas[contA][3];
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
    for(int i = 0; i < contA; i++){
        for(int j = 0; j < 3; j++){
            printf("%d ", arestas[i][j]);
        }
        printf("\n");
    }
    quick(0, contA, arestas);
    printf("\n=============================================================================================================\n");
    for(int i = 0; i < contA; i++){
        for(int j = 0; j < 3; j++){
            printf("%d ", arestas[i][j]);
        }
        printf("\n");
    }
    printf("\n=============================================================================================================\n");
     //arvore geradoura minima
    int floresta[(contV + 1)*(contV + 1)];
    for(int i = 0; i <= contV; i++){
        for(int j = 0; j <= contV; j++){
            floresta[(i *(contV+1) + j)] = 0;
        }
    }
    int arvore[contV -1][3];
    arvore[contV - 2][0] = 0;
    arvore[contV - 2][1] = 0;
    arvore[contV - 2][2] = 0;
    arvore[0][0] = arestas[0][0];
    arvore[0][1] = arestas[0][1];
    arvore[0][2] = arestas[0][2];
    bool r = true;
    int fimA = 1;
    c = contV + 1;
    for(int i = 1; i < contA && arvore[contV - 2][0] == 0; i++){
        for(int j = 1; j <= contV; j++){
            floresta[(j*(contV + 1))+ 0] = 0;
        }
        r = false;
        r = verifica(floresta ,arestas[i][1], arestas[i][2], (contV+1));
        if(r == true){
            int j = 1;
            while(floresta[arestas[i][1]*(contV + 1) + j] != 0){j++;}
            floresta[arestas[i][1]*(contV + 1) + j] = arestas[i][2];
            arvore[fimA][0] = arestas[i][0];
            arvore[fimA][1] = arestas[i][1];
            arvore[fimA][2] = arestas[i][2];
            j = 1;
            while(floresta[arestas[i][2]*(contV + 1) + j] != 0){j++;}
            floresta[arestas[i][2]*(contV + 1) + j] = arestas[i][1];
            printf("Aresta: %d %d | Peso: %d | Add a Arvore\n", + arestas[i][1], arestas[i][2], arestas[i][0]);
            fimA++;
        }
    }
    printf("\n=============================================================================================================\n");
    int soma = 0;
    printf("Arvore\n");
    for(int i = 0; i < contV - 1; i++){
        printf("%d %d %d\n", arvore[i][0], arvore[i][1], arvore[i][2]);
        soma = soma + arvore[i][0];
    }
    printf("Peso da arvore: %d\n", soma);

    return 0;
}