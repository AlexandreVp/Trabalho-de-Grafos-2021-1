#include "Vertice.h"
#include "Aresta.h"
#include <stdlib.h>
#include <iostream>

// Construtor
Vertice::Vertice(int ID){
    this->valor = 0;
    this->ID = ID;
    this->rootAresta = NULL;
    this->grau = 0;
}

Vertice::Vertice(int ID, double valor){
    this->valor = valor;
    this->ID = ID;
    this->rootAresta = NULL;
    this->grau = 0;
}

// Getters
int Vertice::getID(){
    return this->ID;
}

double Vertice::getValor(){
    return this->valor;
}

Aresta* Vertice::getRootAresta(){
    return this->rootAresta;
}

Vertice* Vertice::getProximo(){
    return this->proximo;
}

// Setters
void Vertice::setValor(double valor){
    this->valor = valor;
}

void Vertice::setRootAresta(Aresta* rootAresta){
    this->rootAresta = rootAresta;
}

void Vertice::setProximo(Vertice* proximo){
    this->proximo = proximo;
}

// Outros Metodos
void Vertice::conectarAresta(Aresta* e){
    e->setProximo(this->rootAresta);
    this->rootAresta = e;
}

void Vertice::conectarAresta(int connID, double valor){
    Aresta* p = new Aresta(connID, NULL, this, valor);
    this->conectarAresta(p);
}

bool Vertice::removerAresta(int connID){
    if(this->rootAresta == NULL){
        return false;
    } else {
        Aresta* a = NULL;
        Aresta* p = this->rootAresta;
        while(p != NULL){
            if(p->getVerticeID() == connID){
                // Remove aresta
                if(a == NULL){
                    this->rootAresta = p->getProximo();
                } else {
                    a->setProximo(p->getProximo());
                }
                p = NULL;
                this->grau--;
                return true;
            }
            a = p;
            p = p->getProximo();
        }
        // Aresta não encontrada
        return false;
    }
}