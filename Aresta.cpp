#include "Aresta.h"
#include "Vertice.h"

// Construtor 
Aresta::Aresta(int VerticeID, Aresta* proximo, Vertice* proximoVertice, double valor){
    this->proximoVertice = proximoVertice;
    this->VerticeID = VerticeID;
    this->proximo = proximo;
    this->valor = valor;
}

// Getters
int Aresta::getVerticeID(){
    return this->VerticeID;
}

Aresta* Aresta::getProximo(){
    return this->proximo;
}

double Aresta::getValor(){
    return this->valor;
}

Vertice* Aresta::getProximoVertice(){
    return this->proximoVertice;
}

// Setters
void Aresta::setVerticeID(int VerticeID){
    this->VerticeID = VerticeID;
}

void Aresta::setProximo(Aresta* proximo){
    this->proximo = proximo;
}

void Aresta::setValor(double valor){
    this->valor = valor;
}
