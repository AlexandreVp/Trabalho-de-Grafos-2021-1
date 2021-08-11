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
        int n, m; // Contadores de vertices e arestas
        bool direcionado; // Suporte para grafo direcionado
        bool ponderado; // Suporte para grafo ponderado ou nao ponderado
        vector<ArestaKruskalPrim> arestas; // Onde eh armazenadas as arestas 

    public:
        int listaGraus[];
        // Cria um grafo vazio com suporte para arestas direcionadas
        Grafo();

        // Retorna (true) para grafo direcionado
        bool getDirecionado();
        // Retorna (true) para grafo ponderado
        bool getPonderado();
        // Retorna o numero de vertices
        int getN();
        // Retorna o numero de arestas
        int getM();
        // Retorna o valor de uma aresta dados dois vertices (0 se nao tem aresta)
        double getArestaValor(int ID1, int ID2);

        // Set se grafo eh direcionado ou nao
        void setDirecionado(bool ehDirecionado);
        // Set se grafo eh ponderado ou nao
        void setPonderado(bool ehPonderado);

        // Adiciona um vertice com ID e valor
        int addVertice(int ID);
        // Remocao de um vertice do grafo
        bool removerVertice(int ID);
        // Percorre o grafo dado o ID do vertice e retorna o ponteiro para o mesmo
        Vertice* getVertice(int ID);
        // Retorna o vertice raiz do grafo
        Vertice* getRootVertice();

        // Funcao que verifica se existe (true) conexao entre 2 vertices
        bool verificaConexao(int ID1, int ID2);
        // Funcao para adicionar uma aresta ponderada entre dois vertices com ID dados e valor dado
        bool addArestaNaoDirecionada(int ID1, int ID2, double valor);
        bool addArestaDirecionada(int ID1, int ID2, double valor);
        bool addAresta(int ID1, int ID2, double valor); 
        bool removerAresta(int ID1, int ID2);

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
        // Retorna uma lista de id's dos vertices
        vector<int> getListaIDVertices();
        // Auxiliar para ordenacao topologica
        void auxOrdenacaoTopologica(Vertice* primeiro, std::vector< int > &vect, Vertice** visitados, int n);

        ////////////////////////////
        void fechoTransitivoDireto(int ID);
        void fechoTransitivoIndireto(int ID);
        void dijkstra(int ID1);
        double** floyd();
        void kruskal();
        void prim();
        void camProfundidade(int ID);
        void ordenacaoTopologica(Grafo* grafo);

};



#endif // GRAFO_H
