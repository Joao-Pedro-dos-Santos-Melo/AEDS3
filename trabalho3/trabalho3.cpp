#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cmath>
#include <time.h>

void add2(int caminho[5][5], int v1, int v2, int i, int peso);

void addtri(int caminho[5][5], int v1, int v2, int peso);

void add4(int caminho[5][5], int i, int v2, int pai, int peso);

void add3(int caminho[5][5], int j, int v1, int pai, int peso){ // tem espaço mas é de grau 3
    caminho[j][0] = v1;
    caminho[j][1] = pai;
    caminho[j][2] = peso;
    caminho[j][4] = 0;
}


void busca(int matriz[], int caminho[5][5], int contV, int v){
    matriz[caminho[v][0] * contV] = 1;
    for(int i = 1; i < contV; i++){
        for(int j = 0; j < 5; j++){
            if(matriz[caminho[v][0] * contV + i] > caminho[j][2]){ // verifica se add ou nao a aresta
                if(matriz[i * contV] == 1){ // verifica se o vertice é preto
                    add2(caminho, v, i, j, matriz[caminho[v][0] * contV + i]);
                }else{
                    if(caminho[v][3] < 3){ // verifico o grau do vertice
                        add4(caminho, j, i, caminho[v][0], matriz[caminho[v][0] * contV + i]);
                        matriz[i * contV] = 1;
                    }else{
                        if(caminho[j][3] == 1){
                            matriz[caminho[j][0] * contV] = 0;
                            add3(caminho, j, i, caminho[v][0], matriz[caminho[v][0] * contV + i]);
                        }
                    }
                }
            }
        }
    }
    caminho[v][4] = 1;
    int cont = 0;
    while(cont < 5){
        if(caminho[cont][4] == 1){
            cont++;
        }else{
            if(v < 4){
                v++;
            }else{
                v = 0;
            }
            busca(matriz, caminho, contV, v);
        }
    }
}


void zeraMatriz(int matriz[], int contV){ 
    for(int i = 1; i < contV; i++){ // zera so primeira coluna que vou usar como cor do vertice
        matriz[i * contV] = 0;
    }
}

void sorteiaAresta(int arestas[][3], int matriz[], int contV, int t){
    for(int i = 0; i < t; i++){ //preeche a matriz de arestas
        for(int j = 0; j < 2; j++){
            int x = rand() % (contV); //sorteia o vertice
            if(x == 0){ //tiro o vertice 0
                x = 1;
            }
            arestas[i][j] = x; //guarda na matriz
        }
        arestas[i][2]= matriz[arestas[i][0] * contV + arestas[i][1]]; //guardo o peso da aresta
    }
}

int maiorAresta(int arestas[][3], int t){
    int maior = 0;
    int ind;
    for(int i = 0; i < t; i++){
        if(arestas[i][2] > maior){
            maior = arestas[i][2];
            ind = i;
        }
    }
    return ind;
}

void inicializaCaminho(int v1, int v2, int peso, int caminho[5][5]){
    caminho[0][0] = v1;   // 0 é o vertice
    caminho[0][1] = v2;   // 1 é o pai do vertice
    caminho[0][2] = peso; // 2 é o peso da aresta que os liga
    caminho[0][3] = 1;    // 3 é o grau do vertice
    caminho[0][4] = 0;    // 4 é se esta finalizado
    caminho[1][0] = v2;
    caminho[1][1] = v1;
    caminho[1][2] = peso;
    caminho[1][3] = 1;
    caminho[1][4] = 0;
    for(int i = 2; i < 5; i++){
        for(int j = 0; j < 5; j++){
            caminho[i][j] = 0;
        }
    }
}

void salvaCaminhoFinal(int caminhoF[5][3], int caminhoI[5][5]){
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 3; j++)
            caminhoF[i][j] = caminhoI[i][j];
}

int somaC(int caminho[5][5]){
    bool r = false;
    int salva;
    for(int i = 0; i < 5; i++){
        for(int j = i; j < 5; j++){
            if(caminho[i][0] == caminho[j][1] && caminho[i][1] == caminho[j][0]){
                salva = i;
                r = true;
                break;
            }
            
        }
        if(r == true){
            break;
        }
    }
    int soma = 0;
    if(salva > -1 && salva < 5){
        for(int i = 0; i < 5; i++){
            soma = soma + caminho[i][2];
        }
        soma = soma - caminho[salva][2];
    }else{
        for(int i = 0; i < 5; i++){
            soma = soma + caminho[i][2];
        }
    }
    return soma;
}


int main(){
    char nomeA[30] = "eil101.txt";
    time_t t_i, t_f;
    int contV = 0;
    int contA;
    int vertice = 0;
    int x = 0;
    int y = 0;
    //Abrir e ler o tamanho da matriz
    FILE *arq;
    arq = fopen( nomeA, "rt");
    while(!feof(arq)){ // percorro o arquivo para pegar a quantidade de vertices
        fscanf(arq, "%d %d %d\n", &vertice, &x, &y); //leio do arquivo
        contV++;
    }
    contA = contV*(contV-1)/2;
    fclose(arq);
    int lista[contV + 1][2]; //criando lista para guardar o posição do vertice
    int matriz[(contV + 1) * (contV + 1)]; //criando matriz adj
    arq = fopen( nomeA, "rt");
    while(!feof(arq)){ // percorro o arquivo para pegar a quantidade de vertices
        fscanf(arq, "%d %d %d\n", &vertice, &x, &y); //leio do arquivo
        lista[vertice][0] = x;
        lista[vertice][1] = y;
    }
    fclose(arq);
    for(int i = 1; i <= contV; i++){ //preenchendo matriz adj
        for(int j = i; j <= contV; j++){
            if(i != j){
                double r = (lista[i][0] - lista[j][0])*(lista[i][0] - lista[j][0]) + (lista[i][1] - lista[j][1])*(lista[i][1] - lista[j][1]); //distancia euclidiana
                r = sqrt(r); //distancia eculidiana
                matriz[i * (contV + 1) + j] = (int)r; //add peso na matriz
                matriz[j * (contV + 1) + i] = (int)r;
            }else{
                matriz[i * (contV +1) + j] = 0; // peso do vertice pra ele mesmo
            }
        }
    }

    printf("\n");
    int t = contA/10; //tamnho matriz que guarda as arestas randomicas
    int arestas[t][3]; //matriz de aresta randomicas
    t_i = time(NULL); //set time inicio
    t_f = time(NULL); //set time fim
    int caminhoInicial[5][5];
    int caminhoFinal[5][3];
    int somaCF = 0;
    int somaCI = 10;
    while(difftime(t_f, t_i) < 20){
        zeraMatriz(matriz, contV+1); // zero as cores dos vertices
        sorteiaAresta(arestas, matriz, (contV+1), t); //sorteio as arestas
        int indA = maiorAresta(arestas, t); // escolho a de maior peso
        inicializaCaminho(arestas[indA][0], arestas[indA][1], arestas[indA][2], caminhoInicial); // inicializo o caminho inicial desta tentativa
        matriz[caminhoInicial[0][0] * (contV+1)] = 1;
        matriz[caminhoInicial[0][1] * (contV+1)] = 1;
        busca(matriz, caminhoInicial, contV+1, 0);
        somaCI = somaC(caminhoInicial);
        if(somaCF < somaCI){
            salvaCaminhoFinal(caminhoFinal, caminhoInicial); // atualizo o caminho fianl 
            somaCF = somaCI; // atualizo o peso total do caminho
        }
        t_f = time(NULL);
    }
    printf("\n------------------------------------------------------\n");
    printf("%s\n", nomeA);
    for(int i = 0; i< 5; i++){
        printf("%d ", caminhoFinal[i][0]);
    }
    printf("\n");
    printf("%d\n\n", somaCF);
    return 0;
}

void add2(int caminho[5][5], int v1, int v2, int i, int peso){ // o vertice é preto
    if(caminho[i][1] == caminho[v1][1]){
        addtri(caminho, v1, i, peso);
    }
}

void addtri(int caminho[5][5], int v1, int v2, int peso){  
    if(caminho[v1][2] > caminho[v2][2]){ // p1 for maior
        caminho[v2][1] = caminho[v1][0];
        caminho[v2][2] = peso ; 
    }else{
        caminho[v1][1] = caminho[v2][0];
        caminho[v1][2] = peso;
    }
}

void add4(int caminho[5][5], int i, int v2, int pai, int peso){ // vertice branco, grau menor que 3
    caminho[i][0] = v2;
    caminho[i][1] = pai;
    caminho[i][2] = peso;
    caminho[i][4] = 0;
    caminho[pai][3]++;
}