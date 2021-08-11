#ifndef FUNCOESAUXILIARES_H_INCLUDED
#define FUNCOESAUXILIARES_H_INCLUDED

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

// Funcao que verifica a existencia de multiarestas e self loops
bool verificaMultiaresta(string ID1, string ID2, Grafo* g)
{
    int intID1 = retornaStringParaInteiro(ID1);
    int intID2 = retornaStringParaInteiro(ID2);

    bool v1 = g->verificaConexao(intID1, intID2);
    // cout << "vertice " << intID1 << " para " << intID2 << ": valor de verificaConexao eh " << v1 << endl;
    bool v2 = g->verificaConexao(intID2, intID1);
    // cout << "vertice " << intID2 << " para " << intID1 << ": valor de verificaConexao eh " << v2 << endl;
    // Caso nao exista aresta entre os vertices
    if (!g->getDirecionado()) {
        if (!v1 && !v2) {
            return true;
        }
    }
    else {
        if (!v1) {
            return true;
        }
    }

    return false;
}

// Funcao auxiliar que le um arquivo em forma de lista de adjacencia
// e cria um grafo de acordo com as informacoes passadas no arquivo
int criaGrafoListaAdj(Grafo* g, ifstream& entrada)
{
    string linha;
    int N;

    if(entrada.is_open())
    {

        // Eh lida a primeira linha do arquivo que contem o numero de vertices do grafo
        getline(entrada,linha);
        N = retornaStringParaInteiro(linha);
        // Cria a quantidade N de vertices lida na linha acima
        for(int i = 0; i < N; i++)
        {
            g->addVertice(i);
             // Adicionou vertices
        }
        while(!entrada.eof())
        {
            int cont = 0;
            string v1,v2,val;
            getline(entrada,linha);
            int vertice1,vertice2;

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
            cont++;
            // Salva a terceira parte da linha, que contem o peso da aresta dada
            while(linha[cont] >= '0' && linha[cont] <= '9')
            {
                val += linha[cont];
                cont++;
            }

            // Impede multiaresta e selfloop
            bool verifica = verificaMultiaresta(v1, v2, g) && (v1 != v2);

            // Se nao houver multiaresta ou self loop
            if(verifica){
                // Adiciona aresta entre os vertices v1 e v2
                g->addAresta(retornaStringParaInteiro(v1),retornaStringParaInteiro(v2),retornaStringParaInteiro(val));
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


// Funcao auxiliar que le um arquivo em forma de MATRIZ DE ADJACENCIA
// e cria um grafo de acordo com as informacoes passadas no arquivo
int criaGrafoMatrizAdj(Grafo* g, ifstream& entrada)
{
    string linha;
    int N;

    if(entrada.is_open())
    {

        // Le segunda linha do arquivo que contem o numero de vertices do grafo
        getline(entrada,linha);
        getline(entrada,linha);
        N = retornaStringParaInteiro(linha);
        // Cria a quantidade N de vertices lida na linha acima
        for(int i = 0; i < N; i++)
        {
            g->addVertice(i);
             // Adicionou vertice
        }

        while(linha != "*****************CONNECTIONS****************")
            getline(entrada,linha);
        getline(entrada,linha);

        int i = 0; // Contador para as linhas da matriz de adjacencias
        while(!entrada.eof())
        {
            for(int j = 2*i + 2; j < 2*N; j++)
            {
                if(linha[j] != ' ' && linha[j] - '0') // Caso nao seja espaço ou 0
                {
                    int v1 = i; // Primeiro vertice da aresta (variavel apenas para facilidade de leitura de codigo)
                    int v2 = j/2; // Segundo vertice da aresta
                    
                    bool verifica = verificaMultiaresta(retornaIntParaString(v1), retornaIntParaString(v2), g) && (v1 != v2);

                    // Se nao houver multiaresta ou self loop
                    if(verifica){
                        // Adiciona aresta entre os vertices v1 e v2
                        g->addAresta(v1,v2,1); // Aresta com peso 1 pois instancia nao é ponderada nas arestas
                    }           
                }
            }
            i++;
            // Le a proxima linha
            getline(entrada,linha);
        }
    }
    else
    {
        cerr << "Erro ao abrir arquivo!" << endl;
        return 0;
    }
    return N;
}

// Funcao auxiliar que imprimime no console a frequencia de graus para cada grau
// que possui frequencia relativa nao nula no grafo
void imprimeFreqGraus(Grafo* g)
{
    float* freqGraus = new float[g->getN()];
    int* listaGraus = new int[g->getN()];
    listaGraus = g->getListaDeGraus();
    int N = g->getN();

    for(int i=0; i < N; i++)
        freqGraus[i] = 0;

    for(int i=0; i < N; i++)
        freqGraus[listaGraus[i]]++;

    cout << ">>>Frequencia de graus nao nulas:" << endl;
    for(int i=0; i < N; i++)
    {
        freqGraus[i] /= N;
        if(freqGraus[i])
            cout << "f(" << i << "): " << freqGraus[i] << endl;
    }    
    cout << endl;

    delete[] freqGraus; 
    delete[] listaGraus;
    
}






// Menus para escolha de opcoes

// Menu para grafos nao ponderados
static int menuNaoPonderado(Grafo* g)
{
    int userInput;
    cout << "*Funcionalidades de grafos nao ponderados:" << endl;
    cout << "INSIRA SUA OPCAO:" << endl;
    cout << "1: Numero de vertices do grafo" << endl;
    cout << "2: Numero de arestas do grafo" << endl;
    cout << "3: Grau medio dos vertices do grafo" << endl;
    cout << "4: Frequencias nao nulas de graus" << endl;
    cout << "***" << endl;
    cout << "5: Utilizar funcionalidades de grafos ponderados" << endl;
    cout << "0: Encerrar operacao" << endl;
    cin >> userInput;
    switch(userInput)
    {
        case 0: 
            return 0;
        case 1: 
            cout << ">>>Numero de vertices: " << g->getN() << endl << endl;
            break;
        case 2: 
            cout << ">>>Numero de arestas: " << g->getM() << endl << endl;
            break;
        case 3: 
            cout << ">>>Grau medio: " << g->getGrauMedio() << endl << endl;
            break;
        case 4: 
            imprimeFreqGraus(g);
            break;
        case 5:
            return 5;;
        default: return 5;       
    }
    return userInput;
}


// Menu com as funcoes do trabalho
static int menu(Grafo* gP,ofstream& saida)
{
    int userInput;
    cout << endl << "INSIRA SUA OPCAO:" << endl;
    cout << "Funcionalidades em grafos ponderados" << endl;
    cout << "(1) a)Fecho transitivo direto" << endl;
    cout << "(2) b)Fecho transitivo indireto" << endl;
    cout << "(3) c)Algoritmo de Dijkstra para caminho minimo" << endl;
    cout << "(4) d)Algoritmo de Floyd para caminho mínimo" << endl;
    cout << "(5) e)Algoritmo de Prim para arvore geradora" << endl;
    cout << "(6) f)Algoritmo de Kruskal para arvore geradora minima" << endl;
    cout << "(7) g)Caminhamento em profundidade" << endl;
    cout << "(8) h)Ordenacao Topologica" << endl;
    cout << "***" << endl;
    cout << "Funcionalidades em grafos nao ponderados" << endl;
    cout << "9: Utilizar funcionalidades de grafos nao ponderados" << endl;
    cout << "0: Encerrar operacao" << endl;
    cin >> userInput;

    int vertice;

    switch(userInput)
    {
        case 0: 
            return 0;
        case 1: 
            cout << "Qual o vertice de origem? (0 a " << gP->getN() - 1 << ") : ";
            
            cin >> vertice;
            if(vertice >= 0 && vertice <= gP->getN() - 1){
                cout << ">>>Fecho transitivo direto do vertice " << vertice << ":" << endl;
                gP->fechoTransitivoDireto(vertice);
            }
            else{
                cout << "Vertice inválido!" << endl;
            }
            break;
        case 2: 
            cout << "Qual o vertice de origem? (0 a " << gP->getN() - 1 << ") : ";
            
            cin >> vertice;
            if(vertice >= 0 && vertice <= gP->getN() - 1){
                cout << ">>>Fecho transitivo indireto: " << endl;
                gP->fechoTransitivoIndireto(vertice);
            }
            else{
                cout << "Vertice inválido!" << endl;
            }
            break;
        case 3: 
            cout << "Qual o vertice de origem? (0 a " << gP->getN() - 1 << ") : ";
            int inicio;
            cin >> inicio;
            if(inicio >= 0 && inicio <= gP->getN() - 1){
                cout << ">>>Caminhos minimos com algoritmo de Dijkstra: " << endl;
                gP->dijkstra(inicio);
            }
            else{
                cout << "Vertice inválido!" << endl;
            }
            break;
        case 4: 
            cout << ">>>Caminhos minimos com algoritmo de Floyd: " << endl;
            gP->floyd();
            break;
        case 5: 
            cout << ">>>>Algoritmo de Prim "  << endl;
            gP->prim();
            break;
        case 6: 
            cout << ">>>Algoritmo de Kruskal: "  << endl;
            gP->kruskal();
            break;
        case 7: 
            cout << ">>>Caminhamento em profundidade: "  << endl;
            gP->camProfundidade(0);
            break;
        case 8: 
            cout << ">>>Ordenacao Topologica: "  << endl;
            gP->ordenacaoTopologica(gP);
            break;
        case 9: 
            menuNaoPonderado(gP);
            break;
        default: 
            return 5;      
    }
    return userInput;
}



// Funcao que configura a saida do programa expondo as informacoes do grafo
void criaSaida(Grafo* g, ofstream& saida)
{

    int* listaGraus = new int[g->getN()];
    listaGraus = g->getListaDeGraus();
    int N = g->getN();

    saida << N << endl << g->getM() << endl << g->getGrauMedio() << endl;


    float* freqGraus = new float[g->getN()];


    for(int i=0; i < N; i++)
        freqGraus[i] = 0;

    for(int i=0; i < N; i++)
        freqGraus[listaGraus[i]]++;

    for(int i=0; i < N; i++)
    {
        freqGraus[i] /= N;
        saida << "f(" << i << "): " << freqGraus[i] << endl;
    }    

    delete[] freqGraus;
    delete[] listaGraus;

}


#endif
