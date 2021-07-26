#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <fstream>
#include <vector>
#include "Vertice.h"
#include "Aresta.h"
#include "fstream"

using namespace std;

struct ArestaKruskalPrim{
    Vertice* v1;
    Vertice* v2;
    int valor;

    friend bool operator==(const ArestaKruskalPrim a1, const ArestaKruskalPrim a2) {
        return (a1.v1 == a2.v2) && (a1.v2 == a2.v2) && (a1.valor == a2.valor);
    };

    friend bool operator<(const ArestaKruskalPrim a1, const ArestaKruskalPrim a2) {
        return a1.valor < a2.valor;
    };
};

class Grafo {

    private:
        Vertice* rootVertice; // Vertice raiz do grafo
        int n, m; // Quantizacao de vertices e arestas
        bool direcionado; // Suporte para grafo direcionado
        vector<ArestaKruskalPrim> arestas; // Onde eh armazenadas as arestas 

    public:
        int listaGraus[];
        // Cria um grafo vazio com suporte para arestas direcionadas
        Grafo();

        // Funcao para inserir o primeiro vertice do grafo, ID = 0
        // int addVertice(int ID); 
        // Adiciona um vertice com ID e valor
        int addVertice(int ID);
        // Remocao de um vertice do grafo
        bool removerVertice(int ID);
        // Percorre o grafo dado o ID do vertice e retorna o ponteiro para o mesmo
        Vertice* getVertice(int ID);
        // Retorna o vertice raiz do grafo
        Vertice* getRootVertice();

        double getArestaValor(int ID1, int ID2);
        // Funcao para adicionar uma aresta ponderada entre dois vertices com ID dados e valor dado
        bool addAresta(int ID1, int ID2, double valor); 
        bool removerAresta(int ID1, int ID2);

        // Retorna o numero de vertices
        int getN();
        // Funcao que determina se o grafo tem vertices (true se nao tem vertices)
        bool ehVazioVertice();
        // Funcao que determina se o grafo tem arestas (true se nao tem arestas)
        bool ehVazioAresta();
        // Funcao que percorre o grafo e imprime o ID de seus vertices
        void printVertices();
        // Funcao que salva o grafo em um arquivo de saida
        void salvaVertices(ofstream& saida);
        // Funcao que imprime as arestas do grafo
        void printArestas();
        // Funcao para o calculo do grau medio dos vertices do grafo
        float getGrauMedio();
        // Funcao para a obtencao de uma lista dos graus de cada vertice do grafo
        int* getListaDeGraus();
        vector<int> getListaIDVertices();

        ////////////////////////////
        int* camLargura(int ID);
        void camProfundidade(int ID);
        void dijkstra(int ID1);
        void kruskal();
        double** floyd();
        void prim();

};



#endif // GRAFO_H