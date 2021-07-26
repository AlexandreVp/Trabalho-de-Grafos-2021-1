#ifndef Vertice_H_INCLUDED
#define Vertice_H_INCLUDED

class Aresta;

// Definição da Classe Vertice
class Vertice {

    private:
        // Atributos
        double valor;
        int color;
        Aresta* rootAresta;
        Vertice* proximo;


    public:
        // Atributos
        int grau;
        int ID;
        Vertice(int ID);
        Vertice(int ID, double valor);
        // Getters
        int getID();
        double getValor();
        Aresta* getRootAresta();
        Vertice* getProximo();
        // Setters
        void setProximo(Vertice* proximo);
        void setValor(double valor);
        void setRootAresta(Aresta* rootAresta);
        // Outros Metodos
        void conectarAresta(int connID, double valor);
        void conectarAresta(Aresta* e);
        bool removerAresta(int connID);
        bool operator < (Vertice& v)
        {
            return (this->valor < v.getValor());
        }
};

#endif
