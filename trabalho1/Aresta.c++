#include "Vertice.c++"

struct Aresta {
    int peso;
    Vertice v1;
    Vertice v2;
};
    // bool add(int contV,Vertice matriz[contV + 1][contV - 1], Aresta aresta, Aresta arvore[], int fimA){
    //     bool r = false;
    //     r = verifica(aresta.v1, aresta.v2, matriz);
    //     if(r == true){
    //         int j = 1;
    //         while(matriz[aresta.v1.num][j] != NULL){j++;}
    //         matriz[aresta.v1.num][j] = aresta.v2;
    //         arvore[fimA] = aresta;
    //         j = 1;
    //         while(matriz[aresta.v2.num][j] != NULL){j++;}
    //         matriz[aresta.v2.num][j] = aresta.v1;
    //     }
    //     return r;
    // }
