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
        int grauEntrada;
        int grauSaida;
        int ID;
        int nome;

    public:
        // Atributos
        int grau;
        Vertice(int ID, int nome);
        Vertice(int ID, int nome, double valor);
        // Getters
        int getID();
        int getNome();
        double getValor();
        Aresta* getRootAresta();
        Vertice* getProximo();
        int getGrauEntrada();
        int getGrauSaida();
        // Setters
        void setGrauEntrada(int grauEntrada);
        void setGrauSaida(int grauSaida);
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
