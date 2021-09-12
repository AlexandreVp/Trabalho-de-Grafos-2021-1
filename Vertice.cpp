#include "Vertice.h"
#include "Aresta.h"
#include <stdlib.h>
#include <iostream>

// Construtor
Vertice::Vertice(int ID, int Nome)
{
    this->valor = 0;
    this->ID = ID;
    this->Nome = Nome;
    this->rootAresta = NULL;
    this->grau = 0;
    this->grauEntrada = 0;
    this->grauSaida = 0;
}

Vertice::Vertice(int ID, int Nome, double valor)
{
    this->valor = valor;
    this->ID = ID;
    this->Nome = Nome;
    this->rootAresta = NULL;
    this->grau = 0;
    this->grauEntrada = 0;
    this->grauSaida = 0;
}

// Getters
int Vertice::getGrauEntrada()
{
    return this->grauEntrada;
};

int Vertice::getGrauSaida()
{
    return this->grauSaida;
};

int Vertice::getID()
{
    return this->ID;
}

int Vertice::getNome()
{
    return this->Nome;
}

double Vertice::getValor()
{
    return this->valor;
}

Aresta *Vertice::getRootAresta()
{
    return this->rootAresta;
}

Vertice *Vertice::getProximo()
{
    return this->proximo;
}

// Setters
void Vertice::setGrauEntrada(int grauEntrada)
{
    this->grauEntrada = grauEntrada;
};

void Vertice::setGrauSaida(int grauSaida)
{
    this->grauSaida = grauSaida;
};

void Vertice::setValor(double valor)
{
    this->valor = valor;
}

void Vertice::setRootAresta(Aresta *rootAresta)
{
    this->rootAresta = rootAresta;
}

void Vertice::setProximo(Vertice *proximo)
{
    this->proximo = proximo;
}

// Outros Metodos
void Vertice::conectarAresta(Aresta *e)
{
    e->setProximo(this->rootAresta);
    this->rootAresta = e;
}

void Vertice::conectarAresta(int connID, double valor)
{
    Aresta *p = new Aresta(connID, NULL, this, valor);
    this->conectarAresta(p);
}

bool Vertice::removerAresta(int connID)
{
    if (this->rootAresta == NULL)
    {
        return false;
    }
    else
    {
        Aresta *a = NULL;
        Aresta *p = this->rootAresta;
        while (p != NULL)
        {
            if (p->getVerticeID() == connID)
            {
                // Remove aresta
                if (a == NULL)
                {
                    this->rootAresta = p->getProximo();
                }
                else
                {
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