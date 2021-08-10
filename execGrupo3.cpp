#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <fstream>
#include <vector>
#include "Grafo.h"
#include "utils.h"

using namespace std;

int main(int argc, const char* argv[])
{
    Grafo* g = new Grafo();

    // Criando arquivos de entrada e saida
    ifstream entrada;
    ofstream saida;
    entrada.open(argv[1], ios::in);
    saida.open(argv[2], ios::out | ios::trunc);

    // Obtendo a informacao se o grafo eh direcionado ou nao
    bool ehDirecionado;
    cout << "Seu grafo eh direcionado? (1) Direcionado ou (0) Nao Direcionado: ";
    cin >> ehDirecionado;
    cout << "Eh direcionado: " << ehDirecionado;
    cout << '\n' << endl;

    g->setDirecionado(ehDirecionado);

    // Obtendo a informacao se o grafo eh ponderado ou nao
    bool ehPonderado;
    cout << "Seu grafo eh Ponderado? (1) Ponderado ou (0) Nao Ponderado: ";
    cin >> ehPonderado;
    cout << "Eh ponderado: " << ehPonderado;
    cout << '\n' << endl;

    g->setPonderado(ehPonderado);
    
    // Criando grafo a partir de uma lista de adjacencia
    criaGrafoListaAdj(g, entrada);

    // Print de arestas (apenas para teste)
    g->printArestas();
    
    while(menu(g,saida));
    

    return 0;
}