#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include<iostream>
#include<stdio.h>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<math.h>
#include<fstream>
#include"Grafo.h"

using namespace std;

// Funçao que recebe uma string numerica e retorna seu valor em inteiro
int retornaStringParaInteiro(string str)
{
    stringstream s(str); 
    int x = 0; 
    s >> x; 
    return x;
}

// Funçao que recebe uma inteiro e retorna seu valor como string
string retornaIntParaString(int i)
{
    string str;
    stringstream ss;

    ss << i;
    ss >> str;
    return str;
}

// Funcao que verifica a inexistencia de multiarestas e self loops
bool verificaInexistenciaMultiaresta(string ID1, string ID2, Grafo* g)
{
    int intID1 = retornaStringParaInteiro(ID1);
    int intID2 = retornaStringParaInteiro(ID2);

    bool v1 = g->verificaConexao(intID1, intID2);
    // cout << "vertice " << intID1 << " para " << intID2 << ": valor de verificaConexao eh " << v1 << endl;
    bool v2 = g->verificaConexao(intID2, intID1);
    // cout << "vertice " << intID2 << " para " << intID1 << ": valor de verificaConexao eh " << v2 << endl;
    
    // Caso nao exista aresta entre os vertices (grafo nao direcionado)
    if (!g->getDirecionado()) {
        if (!v1 && !v2) {
            return true;
        }
    }
    // Caso nao exista para (grafo direcionado)
    else {
        if (!v1) {
            return true;
        }
    }

    // Caso exista aresta entre os vertices
    return false;
}

// Funcao auxiliar que le um arquivo em forma de lista de adjacencia
// e cria um grafo de acordo com as informacoes passadas no arquivo
int criaGrafoListaAdj(Grafo* g, ifstream& entrada)
{
    string linha;
    int N;
    int cont = 0;
    // Peso padrao para grafos nao ponderados
    double valPadraoNaoPonderado = 1;

    if(entrada.is_open())
    {

        // Eh lida a primeira linha do arquivo que contem o numero de vertices do grafo
        getline(entrada,linha);
        N = retornaStringParaInteiro(linha);
        while(!entrada.eof())
        {
            cont = 0;
            string v1, v2, val;
            getline(entrada,linha);
            
            // Salva a primeira parte da linha, que contem o primeiro vertice de uma aresta
            while(linha[cont] != ' ' )
            {
                v1 += linha[cont];
                cont++;
            }
            cont++;
            // Salva a segunda parte da linha, que contem o segundo vertice de uma aresta
            while(linha[cont] != ' ')
            {
                v2 += linha[cont];
                cont++;
            }
            // Se grafo for ponderado salva os pesos contidos no arquivo
            if(g->getPonderado()){
                cont++;
                // Salva a terceira parte da linha, que contem o peso da aresta dada
                while(linha[cont] >= '0' && linha[cont] <= '9')
                {
                    val += linha[cont];
                    cont++;
                }
            }
            int iv1 = retornaStringParaInteiro(v1), iv2 = retornaStringParaInteiro(v2), ival = retornaStringParaInteiro(val);
            
            if(!g->getVertice(iv1))
                g->addVertice(iv1);
            if(!g->getVertice(iv2))
                g->addVertice(iv2);

            // Impede multiaresta e selfloop
            bool verifica = verificaInexistenciaMultiaresta(v1, v2, g) && (v1 != v2);

            // Se nao houver multiaresta ou self loop
            if(verifica){
                if(g->getPonderado()){
                    // Adiciona aresta entre os vertices v1 e v2
                    g->addAresta(iv1,iv2,ival);
                }
                else{
                    // Adiciona aresta entre os vertices v1 e v2
                    // Aresta com peso 1, ja que instancia nao é ponderada nas arestas
                    g->addAresta(iv1,iv2,valPadraoNaoPonderado);
                }
            }

        }
    }
    else
    {
        cerr << "Erro ao abrir arquivo!" << endl;
        return 0;
    }
    return N;
}




// Menu com as funcoes do trabalho
static int menu(Grafo* gP,ofstream& saida)
{
    int userInput;
    cout << endl << "INSIRA SUA OPCAO:" << endl;
    cout << "Funcionalidades em grafos ponderados" << endl;
    cout << "(1) Fecho transitivo direto" << endl;
    cout << "(2) Fecho transitivo indireto" << endl;
    cout << "(3) Algoritmo de Dijkstra para caminho minimo" << endl;
    cout << "(4) Algoritmo de Floyd para caminho minimo" << endl;
    cout << "(5) Algoritmo de Prim para arvore geradora" << endl;
    cout << "(6) Algoritmo de Kruskal para arvore geradora minima" << endl;
    cout << "(7) Caminhamento em profundidade" << endl;
    cout << "(8) Ordenacao Topologica" << endl;
    cout << "(9) Guloso Heuristica Prim" << endl;
    cout << "----" << endl;
    cout << "(0) Encerrar operacao" << endl;
    cin >> userInput;

    int vertice;

    switch(userInput)
    {
        case 0: 
            return 0;
        case 1: 
            cout << "Qual o vertice de origem? ";
            
            cin >> vertice;
            if(gP->getVertice(vertice)){
                cout << ">>>Fecho transitivo direto do vertice " << vertice << ":" << endl;
                gP->fechoTransitivoDireto(vertice);
            }
            else{
                cout << "Vertice invalido!" << endl;
            }
            break;
        case 2: 
            cout << "Qual o vertice de origem? ";
            
            cin >> vertice;
            if(gP->getVertice(vertice)){
                cout << "--> Fecho transitivo indireto: " << endl;
                gP->fechoTransitivoIndireto(vertice);
            }
            else{
                cout << "Vertice invalido!" << endl;
            }
            break;
        case 3: 
            cout << "Qual o vertice de origem? ";
            int inicio;
            cin >> inicio;
            if(gP->getVertice(inicio)){
                cout << "--> Caminhos minimos com algoritmo de Dijkstra: " << endl;
                gP->dijkstra(inicio);
            }
            else{
                cout << "Vertice invalido!" << endl;
            }
            break;
        case 4: 
            cout << "--> Caminhos minimos com algoritmo de Floyd: " << endl;
            gP->floyd();
            break;
        case 5: 
            cout << "--> >Algoritmo de Prim "  << endl;
            gP->prim();
            break;
        case 6: 
            cout << "--> Algoritmo de Kruskal: "  << endl;
            gP->kruskal();
            break;
        case 7: 
            cout << "--> Caminhamento em profundidade: "  << endl;
            gP->camProfundidade(0);
            break;
        case 8: 
            cout << "--> Ordenacao Topologica: "  << endl;
            gP->ordenacaoTopologica();
            break;
        case 9:
            cout << "--> Guloso Heuristica Prim: " << endl;
            gP->gulosoHeuristicaPrim();
        default: 
            return 5;      
    }
    return userInput;
}

#endif
