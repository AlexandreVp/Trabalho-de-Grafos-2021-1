#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

using namespace std;

class Vertice;

// Definição da Classe Aresta
class Aresta {

    // Atributos
    private:
        int VerticeID;
        Aresta* proximo;
        Vertice* proximoVertice;
        double valor;

    public:
        // Construtor
        Aresta(int VerticeID, Aresta* proximo, Vertice* proximoVertice, double valor);

        // Getters
        int getVerticeID();
        Aresta* getProximo();
        double getValor();
        Vertice* getProximoVertice();
        
        // Setters
        void setVerticeID(int VerticeID);
        void setProximo(Aresta* proximo);
        void setValor(double valor);
};

#endif // ARESTA_H_INCLUDED