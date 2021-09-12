#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <fstream>
#include <vector>
#include "Grafo.h"
#include "utils.h"

using namespace std;

// GRUPO 3
// ALEXANDRE VIEIRA PEREIRA PACELLI

int main(int argc, const char* argv[])
{
    Grafo* g = new Grafo();

    // Criando arquivos de entrada e saida
    ifstream entrada;
    ofstream saida;
    entrada.open(argv[1], ios::in);
    saida.open(argv[2], ios::out | ios::trunc);

    // Obtendo a informacao se o grafo eh direcionado ou nao
    bool ehDirecionado = true;
    if(argv[3][0] == '0')
        ehDirecionado = false;
    g->setDirecionado(ehDirecionado);

    // Obtendo a informacao se o grafo eh ponderado ou nao
    bool ehPonderado = true;
    if(argv[4][0] == '0')
        ehPonderado = false;
    g->setPonderado(ehPonderado);

    // Obtendo a informacao se sera trabalhada a Arvore Geradora de Rotulacao Minima
    bool pagrm;
    cout << "Voce deseja trabalhar com o problema da Arvore Geradora de Rotulacao Minima? (1) Sim ou (0) Nao: ";
    cin >> pagrm;
    cout << "PAGRM: " << pagrm;
    cout << '\n' << endl;
    
    // Garantindo que para o PAGRM o grafo seja nao direcionado e ponderado
    if (pagrm) {
        g->setDirecionado(0);
        g->setPonderado(1);
    }
    
    // Criando grafo a partir de uma lista de adjacencia
    cout << "Aguarde enquanto o grafo esta sendo criado...\n" << endl;
    criaGrafoListaAdj(g, entrada);

    // Caso PAGRM seja verdadeiro inicializa a contagem da frequencia dos rotulos
    // E altera os pesos das arestas para que possamos utilizar da heuristica de prim no algoritmo guloso
    if (pagrm){
        cout << "Aguarde enquanto os rotulos sao contabilizados...\n" << endl;
        g->contaRotulos();
    }

    //Print de arestas (apenas para testes)
    g->printArestas();
    
    while(menu(g,saida));
    

    return 0;
}