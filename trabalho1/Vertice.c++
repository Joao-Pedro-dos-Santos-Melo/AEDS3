struct Vertice {
    int num;
    int cor = 0;
    Vertice * prox;
};
    // bool verifica(int contV, Vertice v1, Vertice v2, Vertice matriz[contV +1][contV - 1]){
    //     bool r = true;
    //     matriz[v1.num][0].cor = 1;
    //     for(int j = 1; matriz[v1.num][j] != NULL; j++){

    //             if (matriz[v1.num][j].num == v2.num) {
    //                 return false;
    //             } else {
    //                 if (matriz[v1.num][j].cor == 0) {
    //                     r = verifica(contV, &matriz[v1.num][j], v2, matriz[contV +][Contv - 1]);
    //                 }
    //             }
    //             if(r == false){
    //                 return r;
    //             }
    //     }
    //     return r;
    // }
