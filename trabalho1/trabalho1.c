#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "Aresta.c++"
//#include "Vertice.c++"

void main(){
    Scanner in = new Scanner(new FileReader("dados2.txt"));
        int contV = 0;
        int line;
        int contA = 0;
        //Lendo e contando as arestas e vertices
        while (in.hasNextLine()) {
            line = in.nextInt();
            contA++;
            line = in.nextInt();
            if(contV < line){
                contV = line;
            }
            line = in.nextInt();
            if(contV < line){
                contV = line;
            }

        }
        System.out.println("O numero de vertices é " + contV + ". Esse numero de Arestas " + contA);
        //Criando matriz de lista de conexoes e a lista de arestas
        int peso = 0;
        int verticePrimeiro = 0;
        int verticeSegundo = 0;
        Vertice matriz[][] = new Vertice[contV + 1][contV];
        Scanner on = new Scanner(new FileReader("dados2.txt"));
        Aresta arestas[] = new Aresta[contA];
        int contI = 0;
        while (on.hasNextLine()) {
            peso = on.nextInt();
            verticePrimeiro = on.nextInt();
            if(matriz[verticePrimeiro][0] == null){
                matriz[verticePrimeiro][0] = new Vertice();
                matriz[verticePrimeiro][0].num = verticePrimeiro;
            }
            verticeSegundo = on.nextInt();
            if(matriz[verticeSegundo][0] == null){
                matriz[verticeSegundo][0] = new Vertice();
                matriz[verticeSegundo][0].num = verticeSegundo;
            }
            arestas[contI] = new Aresta();
            arestas[contI].v1 = matriz[verticePrimeiro][0];
            arestas[contI].v2 = matriz[verticeSegundo][0];
            arestas[contI].peso = peso;
            contI++;
        }
        for(int i = 0; i < contA; i++){
            System.out.println("Peso: " + arestas[i].peso + "| Vertce: " + arestas[i].v1.num + "| Vertice: " + arestas[i].v2.num);
        }
        Aresta arvore[] = new Aresta[contV - 1];
        //Buble Sort
        Aresta aux = new Aresta();
        System.out.println("===========================================================================");
        for(int i = 0; i < contA; i++){
            for(int j = i; j <contA; j++){
                if(arestas[i].peso > arestas[j].peso){
                    aux = arestas[i];
                    arestas[i] = arestas[j];
                    arestas[j] = aux;
                }
            }
        }
        //Print Arestas
        for(int i = 0; i < contA; i++){
            System.out.println("Peso: " + arestas[i].peso + "| Vertce: " + arestas[i].v1.num + "| Vertice: " + arestas[i].v2.num);
        }
        System.out.println("===========================================================================");

        //Arvore Geradora Minima (Kruskel)
        boolean r = true;
        arvore[0] = arestas[0];
        matriz[arvore[0].v1.num][1] = arvore[0].v2;
        matriz[arvore[0].v2.num][1] = arvore[0].v1;
        int fimA = 1;
        for(int i = 1; i < contA && arvore[contV - 2] == null; i++){
            for(int j = 1; j <= contV; j++){
                matriz[j][0].cor = 0;
            }
            r = arestas[i].add(contV ,matriz[contV + 1][contV - 1], arestas[i], arvore, fimA);
            if(r == true){
                System.out.println("Aresta; " + arestas[i].v1.num + " " + arestas[i].v2.num + "| Peso: " + arestas[i].peso + " Adiciona ha Arvore.");
                fimA++;
            }
        }
        System.out.println("===========================================================================");
        int soma = 0;
        for(int i = 0; i < fimA; i++){
            soma = arvore[i].peso + soma;
            System.out.println("Peso = " + arvore[i].peso + "| Arestas " + arvore[i].v1.num + "| Arestas " + arvore[i].v2.num);
        }
        System.out.println("Peso total da arvore : " + soma);
        System.out.println("===========================================================================");
        Vertice vPrincipal = new Vertice();
        Aresta APrimaria = new Aresta();
        Aresta aSecundaria = new Aresta();
        for(int i = contV -1 ; i > contV/2; i--){
            vPrincipal = arvore[i].v1;

        }
}