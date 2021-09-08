#include "Grafo.h"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits.h>
#include <math.h>
#include <fstream>
#include <sstream>
#include <time.h>

Grafo::Grafo()
{
	this->n = 0;
	this->m = 0;
	this->rootVertice = NULL;
	this->direcionado = false;
}

bool Grafo::getDirecionado()
{
	return this->direcionado;
}

void Grafo::setDirecionado(bool ehDirecionado)
{
	this->direcionado = ehDirecionado;
}

bool Grafo::getPonderado()
{
	return this->ponderado;
}

void Grafo::setPonderado(bool ehPonderado)
{
	this->ponderado = ehPonderado;
}

Vertice *Grafo::getRootVertice()
{
	return this->rootVertice;
}

int Grafo::addVertice(int ID)
{
	Vertice *v = new Vertice(ID);
	v->setProximo(this->rootVertice);
	this->rootVertice = v;
	this->n++;

	return v->ID;
}

bool Grafo::removerVertice(int ID)
{
	if (this->rootVertice == NULL)
	{
		// Caso grafo seja vazio
		return false;
	}
	else
	{
		Vertice *a = NULL;
		Vertice *p = this->rootVertice;

		while (p != NULL)
		{
			if (p->getID() == ID)
			{
				if (a == NULL)
				{
					this->rootVertice = p->getProximo();
				}
				else
				{
					a->setProximo(p->getProximo());
				}

				p = NULL;
				this->n--;

				return true;
				// Removeu o vertice
			}
			a = p;
			p = p->getProximo();
		}
		// Caso vertice nao seja encontrado
		return false;
	}
}

Vertice *Grafo::getVertice(int ID)
{
	if (this->rootVertice == NULL)
	{
		return NULL;
	}
	else
	{
		Vertice *p = this->rootVertice;
		while (p != NULL)
		{
			if (p->getID() == ID)
			{
				return p;
			}
			p = p->getProximo();
		}
		// Caso o id do vertice nao tenha sido encontrado
		return NULL;
	}
}

// Retorna o valor de uma aresta caso exista
double Grafo::getArestaValor(int ID1, int ID2)
{
	Vertice *v = this->getVertice(ID1);
	Aresta *a = this->getVertice(ID1)->getRootAresta();
	while (a != NULL)
	{
		if (a->getVerticeID() == ID2)
		{
			return a->getValor();
		}
		a = a->getProximo();
	}
	// Retorna 0 se nao houver aresta entre os vertices
	return 0;
}

// Funcao que verifica se existe (true) conexao entre 2 vertices
bool Grafo::verificaConexao(int ID1, int ID2)
{
	Vertice *v = this->getVertice(ID1);
	Aresta *a = this->getVertice(ID1)->getRootAresta();
	while (a != NULL)
	{
		if (a->getVerticeID() == ID2)
		{
			return true;
		}
		a = a->getProximo();
	}
	return false;
}

bool Grafo::addArestaNaoDirecionada(int ID1, int ID2, double valor)
{
	Vertice *a = this->getVertice(ID1);
	Vertice *b = this->getVertice(ID2);
	if (a != NULL && b != NULL)
	{
		// Conecta os vertices e incrementa o grau dos mesmos
		a->conectarAresta(ID2, valor);
		a->grau++;
		b->conectarAresta(ID1, valor);
		b->grau++;
		// Incrementa o numero de arestas do grafo
		this->m++;
		// Atualiza vetor de arestas
		ArestaKruskalPrim aresta;
		aresta.v1 = a;
		aresta.v2 = b;
		aresta.valor = valor;

		ArestaKruskalPrim aresta_equivalente;
		aresta_equivalente.v1 = b;
		aresta_equivalente.v2 = a;
		aresta_equivalente.valor = valor;

		// Confere a necessidade de adicionar a aresta
		// Caso ja exista uma aresta de v1 para v2, nao exista necessidade de adicionar uma de v2 para v1
		if (find(arestas.begin(), arestas.end(), aresta_equivalente) == arestas.end())
		{
			this->arestas.push_back(aresta);
		}

		return true;
	}
	else
		return false;
}

bool Grafo::addArestaDirecionada(int ID1, int ID2, double valor)
{
	Vertice *a = this->getVertice(ID1);
	Vertice *b = this->getVertice(ID2);
	if (a != NULL && b != NULL)
	{
		// Conecta os vertices e incrementa o grau dos mesmos
		a->conectarAresta(ID2, valor);
		a->setGrauSaida(a->getGrauSaida() + 1);
		b->setGrauEntrada(b->getGrauEntrada() + 1);
		// Incrementa o numero de arestas do grafo
		this->m++;
		// Atualiza vetor de arestas
		ArestaKruskalPrim aresta;
		aresta.v1 = a;
		aresta.v2 = b;
		aresta.valor = valor;

		ArestaKruskalPrim aresta_equivalente;
		aresta_equivalente.v1 = b;
		aresta_equivalente.v2 = a;
		aresta_equivalente.valor = valor;

		// Confere a necessidade de adicionar a aresta
		// Se não existe aresta de v1 p v2 eh colocada a aresta
		if (find(arestas.begin(), arestas.end(), aresta) == arestas.end())
		{
			this->arestas.push_back(aresta);
		}
		// Entretanto, se v1 p v2 existe, mas nao v2 p v1, entao a de v2 p v1 eh enserida
		else if (find(arestas.begin(), arestas.end(), aresta_equivalente) == arestas.end())
		{
			this->arestas.push_back(aresta_equivalente);
		}

		return true;
	}
	else
		return false;
}

bool Grafo::addAresta(int ID1, int ID2, double valor)
{
	if (this->direcionado)
	{
		return this->addArestaDirecionada(ID1, ID2, valor);
	}
	return this->addArestaNaoDirecionada(ID1, ID2, valor);
}

bool Grafo::removerAresta(int ID1, int ID2)
{
	Vertice *a = this->getVertice(ID1);
	Vertice *b = this->getVertice(ID2);
	if (a != NULL && b != NULL)
	{
		if (a->removerAresta(ID2))
		{
			if (b->removerAresta(ID1))
			{
				this->m--;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

int Grafo::getN()
{
	return this->n;
}

int Grafo::getM()
{
	return this->m;
}

bool Grafo::ehVazioVertice()
{
	return n == 0;
}

bool Grafo::ehVazioAresta()
{
	return m == 0;
}

void Grafo::printVertices()
{
	Vertice *p = this->rootVertice;
	Aresta *e;
	while (p != NULL)
	{
		std::cout << "[" << p->getID() << "] : "
				  << " grau:" << p->grau << std::endl;
		e = p->getRootAresta();

		while (e != NULL)
		{
			std::cout << e->getVerticeID() << "(" << e->getValor() << ") ";
			e = e->getProximo();
		}

		std::cout << std::endl;
		p = p->getProximo();
	}
}

void Grafo::salvaVertices(ofstream &saida)
{
	Vertice *p = this->rootVertice;
	Aresta *e;
	while (p != NULL)
	{
		saida << "[" << p->getID() << "] : "
			  << " grau:" << p->grau << std::endl;
		e = p->getRootAresta();

		while (e != NULL)
		{
			saida << e->getVerticeID() << "(" << e->getValor() << ") ";
			e = e->getProximo();
		}

		saida << std::endl;
		p = p->getProximo();
	}
}

void Grafo::printArestas()
{
	for (ArestaKruskalPrim aresta : arestas)
	{
		cout << "Aresta(" << aresta.v1->getID() << ", " << aresta.v2->getID() << ") = " << aresta.valor << endl;
	}
}

void Grafo::fechoTransitivoDireto(int ID)
{
}

void Grafo::fechoTransitivoIndireto(int ID)
{
}

int *Grafo::camLargura(int ID)
{

	int *v = new int[this->n];
	int contador = 0;
	std::queue<int> queue;
	queue.push(ID);
	Vertice *topo;
	Aresta *e;

	Vertice *p = this->rootVertice;

	bool *visitado = new bool[this->n];
	int indice = this->getRootVertice()->getID();

	// Preenche o vetor com 0
	for (int i = 0; i < this->n; i++)
	{
		visitado[i] = false;
	}

	std::cout << " -- Sequencia de saida da fila -- " << std::endl;

	while (!queue.empty())
	{
		// Pega o primeiro elemento da fila
		topo = this->getVertice(queue.front());

		std::cout << queue.front() << " --> ";
		queue.pop();

		visitado[topo->getID()] = true;

		v[contador] = topo->getID();
		contador++;

		// Coloca cada vertice adjacente na fila
		e = topo->getRootAresta();
		while (e != NULL)
		{
			if (!visitado[e->getVerticeID()])
			{
				visitado[e->getVerticeID()] = true;
				queue.push(e->getVerticeID());
			}
			e = e->getProximo();
		}
	}

	std::cout << std::endl;

	return v;
}

void Grafo::camProfundidade(int id)
{
	stack<int> pilha;
	bool *visitado = new bool[this->getN()];
	Vertice *v = getVertice(id);

	for (int i = 0; i < this->getN(); i++)
	{
		visitado[i] = false;
	}

	while (true)
	{
		if (!visitado[v->getID()])
		{
			cout << "Visitando vertice " << v->getID() << "...\n";
			visitado[v->getID()] = true;
			pilha.push(v->getID());
		}
		bool encontrado = false;
		Aresta *e = v->getRootAresta();
		while (e != NULL)
		{
			v = getVertice(e->getVerticeID());
			if (visitado[v->getID()] == false)
			{
				encontrado = true;
				break;
			}
			e = e->getProximo();
		}
		if (encontrado)
		{
			v = getVertice(v->getID());
		}
		else
		{
			pilha.pop();
			if (pilha.empty())
				break;
			v = getVertice(pilha.top());
		}
	}
}

vector<int> Grafo::getListaIDVertices()
{
	vector<int> ids;
	Vertice *p = this->getRootVertice();

	while (p != NULL)
	{
		ids.push_back(p->getID());
		p = p->getProximo();
	}

	return ids;
}

typedef struct
{
	int id = 0;
	int proxID = -1;
	int proxIndice = -1;
	bool calculado = false;
	int distancia = 0;
} VerticeDijkstra;

void Grafo::dijkstra(int ID1)
{
	int minIndice;
	int valorAresta;

	vector<int> q = this->getListaIDVertices();
	int restante = q.size();

	VerticeDijkstra *vertices = new VerticeDijkstra[q.size()];

	for (int i = 0; i < q.size(); i++)
	{
		vertices[i].id = q[i];
		// Define valor maximo para distancias desconhecidas
		vertices[i].distancia = INT_MAX;
		vertices[i].proxID = -1;
		vertices[i].proxIndice = -1;

		if (q[i] == ID1)
		{
			// Distancia do vertice a ele mesmo eh sempre 0
			vertices[i].distancia = 0;
		}
	}

	while (restante > 0)
	{

		minIndice = -1;

		for (int i = 0; i < q.size(); i++)
		{
			if (minIndice < 0)
			{
				// Caso o vertice ainda nao tenha sido calculado
				if (vertices[i].calculado == false)
				{
					minIndice = i;
				}
				continue;
			}
			// Se a distancia do vertice i for menor que a distancia do minimo, e esse ainda nao
			// tenha sido utilizado como origem, o indice eh substituido
			if (vertices[i].distancia < vertices[minIndice].distancia && vertices[i].calculado == false)
			{
				minIndice = i;
			}
		}
		// Vertice ja calculado
		vertices[minIndice].calculado = true;
		// Diminui a quantidade de vertices distantes
		restante--;

		for (int i = 0; i < q.size(); i++)
		{
			valorAresta = this->getArestaValor(vertices[minIndice].id, vertices[i].id);

			// Atualiza os valores da distancia em cada vertice de acordo com o volar da aresta
			if (valorAresta > 0 && (vertices[i].distancia > vertices[minIndice].distancia + valorAresta))
			{
				vertices[i].distancia = vertices[minIndice].distancia + valorAresta;
				vertices[i].proxID = vertices[minIndice].id;
				vertices[i].proxIndice = minIndice;
			}
		}
	}

	for (int i = q.size() - 1; i > -1; i--)
	{
		cout << "Distancia de " << ID1 << " a " << vertices[i].id << " = " << vertices[i].distancia << endl;
	}

	delete[] vertices;
}

void Grafo::kruskal()
{
	// Copiando o vetor de arestas de forma ordenada para um vetor auxiliar
	vector<ArestaKruskalPrim> arestas_aux(arestas.size());
	partial_sort_copy(begin(arestas), end(arestas), begin(arestas_aux), end(arestas_aux));

	vector<ArestaKruskalPrim> solucao;
	vector<int> vertices_aux;

	// Armazenando no vetor auxiliar de vertices os indices de 0...N
	for (int i = 0; i < this->getN(); i++)
	{
		vertices_aux.push_back(i);
	}

	int contador = 0;
	int custo_total = 0;

	while (contador < this->getN() - 1)
	{
		// Verificar com a aresta (v1,v2) se v1 e v2 estao na mesma arvore
		// Verificando no vetor auxiliar se o indice de v1 eh igual ao de v2
		if (vertices_aux[arestas_aux[0].v1->getID()] != vertices_aux[arestas_aux[0].v2->getID()])
		{
			// Caso sejam diferentes, colocar na solucao
			solucao.push_back(arestas_aux[0]);
			custo_total += arestas_aux[0].valor;
			contador++;

			// Atualizando os indices no vetor auxiliar
			// De acordo com o menor ID entre os dois vertices colocados na solucao
			if (vertices_aux[arestas_aux[0].v1->getID()] > vertices_aux[arestas_aux[0].v2->getID()])
			{
				int valor_a_ser_substituido = vertices_aux[arestas_aux[0].v1->getID()];
				int valor_correto = vertices_aux[arestas_aux[0].v2->getID()];

				// Para cada indice no vetor auxiliar que tenha que ser substituido
				// Trocar pelo valor correto para indicar que os vertices pertencem a mesma arvore
				for (int i = 0; i < this->getN(); i++)
				{
					if (vertices_aux[i] == valor_a_ser_substituido)
					{
						vertices_aux[i] = valor_correto;
					}
				}
			}
			else
			{
				int valor_a_ser_substituido = vertices_aux[arestas_aux[0].v2->getID()];
				int valor_correto = vertices_aux[arestas_aux[0].v1->getID()];

				for (int i = 0; i < this->getN(); i++)
				{
					if (vertices_aux[i] == valor_a_ser_substituido)
					{
						vertices_aux[i] = valor_correto;
					}
				}
			}
		}

		// Apagar o primeiro elemento do vetor auxiliar de arestas
		// Dessa forma arestas_aux[0] sera sempre a proxima aresta
		arestas_aux.erase(arestas_aux.begin());
	}
	cout << endl
		 << "-- Solucao de AGM pelo algoritmo de Kruskal --" << endl;
	cout << "Sequencia de insercao das arestas: " << endl;
	for (ArestaKruskalPrim aresta : solucao)
		cout << "(" << aresta.v1->getID() << ", " << aresta.v2->getID() << ")"
			 << " --> ";
	cout << endl
		 << "Custo total: " << custo_total << endl;
}

// Para verificaçao de resultado de Floyd
void imprimeMatriz(double **mat, std::size_t N)
{
	cout << "\n Imprimindo matriz : \n";
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cout << *(*(mat + i) + j) << " ";
		}
		cout << endl;
	}
	cout << endl;
}

double **Grafo::floyd()
{

	double **M = new double *[this->n];

	// Preenchendo matriz de distancias com infinito
	for (int i = 0; i < this->n; i++)
	{
		M[i] = new double[this->n];
		for (int j = 0; j < this->n; j++)
		{
			M[i][j] = numeric_limits<double>::infinity();
		}
	}

	// Preenche a matriz inicial M0, nesta:
	// Se existe uma aresta entre os vertices, preenche M(i, j) com o peso da aresta
	// Se nao existe aresta entre os vertices, preenche com infinito
	// Se i = j, ou seja, distancia do vertice a ele mesmo, M(i, j) = 0

	double valorAresta;
	vector<int> id_vertices = this->getListaIDVertices();

	for (int i = 0; i < this->n; i++)
	{
		for (int j = 0; j < this->n; j++)
		{
			if (i != j)
			{
				valorAresta = double(this->getArestaValor(id_vertices[i], id_vertices[j]));
				if (valorAresta > 0)
				{
					M[i][j] = valorAresta;
				}
				else
				{
					M[i][j] = numeric_limits<double>::infinity();
				}
			}
			else
			{
				M[i][j] = 0;
			}
		}
	}

	// Iteraçoes sobre a matriz para verificaçao de distancia para cada vertice k

	for (int k = 0; k < this->n; k++)
	{
		for (int i = 0; i < this->n; i++)
		{
			for (int j = 0; j < this->n; j++)
			{
				// Condiçao para encontrar menor distancia
				if (M[i][j] > (M[i][k] + M[k][j]))
				{
					M[i][j] = M[i][k] + M[k][j];
				}
			}
		}
	}

	cout << "Matriz do algoritmo de Floyd:" << endl;
	imprimeMatriz(M, this->n);

	return M;
}

void Grafo::prim()
{
	// Copiando o vetor de arestas de forma ordenada para um vetor auxiliar
	vector<ArestaKruskalPrim> arestas_aux(arestas.size());
	partial_sort_copy(begin(arestas), end(arestas), begin(arestas_aux), end(arestas_aux));

	ArestaKruskalPrim arestaMinima = arestas_aux[0];
	vector<ArestaKruskalPrim> solucao;
	int custo_total = 0;

	// Adicionando na solucao a aresta minima
	solucao.push_back(arestaMinima);

	custo_total += arestaMinima.valor;
	int id_v1 = arestaMinima.v1->getID();
	int id_v2 = arestaMinima.v2->getID();

	int cont;

	vector<int> prox(this->n);	 // Vetor auxiliar que armazena os prox
	vector<int> custos(this->n); // Vetor auxiliar que armazena os custos

	// Sendo i um vertice do grafo
	// Verifica o custo entre as arestas (i, v1) e (i, v2)
	// Armazena no prox aquele vertice que, junto com i, possui o menor custo
	// Armazenando nos custos o custo dessa aresta entre i e prox
	for (int i = 0; i < this->n; i++)
	{
		int aresta1_val = this->getArestaValor(i, id_v1);
		int aresta2_val = this->getArestaValor(i, id_v2);

		// Faz as verificacoes para evitar problemas com custo infinito
		// Custo infinito = valor da aresta entre os vertices eh 0
		if (aresta1_val > 0 && aresta2_val > 0)
		{
			if (aresta1_val < aresta2_val)
			{
				prox[i] = id_v1;
				custos[i] = aresta1_val;
			}
			else
			{
				prox[i] = id_v2;
				custos[i] = aresta2_val;
			}
		}
		else if (aresta1_val > 0 && aresta2_val == 0)
		{
			prox[i] = id_v1;
			custos[i] = aresta1_val;
		}
		else if (aresta1_val == 0 && aresta2_val > 0)
		{
			prox[i] = id_v2;
			custos[i] = aresta2_val;
		}
		else
		{
			prox[i] = id_v2;
			custos[i] = 0;
		}
	}

	// Setando os prox dos vertices incluidos na solucao como -1
	// -1 sendo o indicador que o vertice ja esta na solucao
	prox[id_v1] = -1;
	prox[id_v2] = -1;
	cont = 0;

	// Encontra o valor minimo entre os custos
	// Encontra o indice em que esta esse menor custo, para saber a qual aresta ele pertence
	while (cont < this->n - 2)
	{
		int index;
		bool isMin = false;
		int min;
		// Realiza a verificacao para que o custo minimo nao esteja com um vertice que ja esta na solucao,
		// verificando se seu prox != -1
		for (int j = 0; j < this->n; j++)
		{
			if (prox[j] != -1)
			{
				if (!isMin && custos[j] > 0)
				{
					min = custos[j];
					isMin = true;
					index = j;
				}
				if (custos[j] < min && custos[j] > 0)
				{
					min = custos[j];
					index = j;
				}
			}
		}

		// A nova aresta minima passa a ser aquela com custo minimo
		ArestaKruskalPrim segunda_aresta_minima;
		segunda_aresta_minima.v1 = this->getVertice(index);
		segunda_aresta_minima.v2 = this->getVertice(prox[index]);
		segunda_aresta_minima.valor = custos[index];

		solucao.push_back(segunda_aresta_minima);
		custo_total += segunda_aresta_minima.valor;

		// O novo vertice na solucao agora recebe prox = -1
		prox[index] = -1;

		// Caso o custo entre o vertice k e o novo vertice na solucao seja menor que o custo atual,
		// atualizar o prox e custos de k para esse vertice adicionado
		for (int k = 0; k < this->n; k++)
		{
			int custo_nova_aresta = this->getArestaValor(k, index);
			if (prox[k] != -1 && custo_nova_aresta != 0 && (custo_nova_aresta < custos[k] || (custos[k] == 0 && custo_nova_aresta > 0)))
			{
				custos[k] = custo_nova_aresta;
				prox[k] = index;
			}
		}

		cont++;
	}
	std::cout << endl
			  << "-- Solucao de AGM pelo algoritmo de Prim --" << endl;
	std::cout << "Sequencia de insercao das arestas: " << endl;
	for (ArestaKruskalPrim aresta : solucao)
		std::cout << "(" << aresta.v1->getID() << ", " << aresta.v2->getID() << ")"
				  << " --> ";
	std::cout << endl
			  << "Custo total: " << custo_total << endl;
}

Vertice *Grafo::getlistaVertices()
{

	Vertice *listaVertices;
	vector<int> listaID = this->getListaIDVertices();
	for (int i = 0; i < (this->getN()); i++)
		listaVertices[i] = *this->getVertice(listaID[i]);

	return listaVertices;
}



void Grafo::auxOT(Vertice* primeiro, std::vector< int > &vect, Vertice** visitados, int n)
{
   Vertice* p = primeiro;
   int j = 0;

    for(int i = 0; i < n; i++)
    {
        visitados[i] = NULL;
    }

    queue<Vertice*> fila;
    fila.push(p);
    visitados[0] = p;

    j++;

        while(!(fila.empty()))
        {
            Vertice* q = fila.front();
            fila.pop();

            vect.push_back(q->getID());

            Aresta* a = q->getRootAresta();


            for(; a != NULL; a = a->getProximo())
            {

                bool jaFoi = false;
                Vertice* aux = a->getProximoVertice();

                for(int i = 0; i < n; i++)
                {
                    if(visitados[i] == aux)
                    {
                        jaFoi = true;
                    }
                }

                if(!jaFoi)
                {
                    fila.push(aux);
                    visitados[j] = aux;
                    j++;
                }
                if(j == n)
                    break;
            }

        }
}









void Grafo::ordenacaoTopologica()
{
	// L ← Lista vazia que irá conter os elementos ordenados

	// S ← Conjunto de todos os nós sem arestas de entrada
	// 	enquanto S é não-vazio faça
	//     remova um nodo n de S
	//     insira n em L
	//     para cada nodo m com uma aresta e de n até m faça
	//         remova a aresta e do grafo
	//         se m não tem mais arestas de entrada então
	//             insira  m em S
	// se o grafo tem arestas então
	//     escrever mensagem de erro (grafo tem pelo menos um ciclo)
	// senão
	//     escrever mensagem  (ordenação topológica proposta: L)

	//Filtrando para apenas trabalhar com grafos direcionados acíclicos:
	// if (this->getM() > this->getN() - 1)
	// {
	// 	cout << "O grafo informado não é aciclico, portanto não é possível Ordenar Topológicamente" << endl;
	// }

	if (!this->getDirecionado())
	{
		cout << "O grafo não é direcionado, portanto não é possível Ordenar Topológicamente" << endl;
	}

	vector<int> listaIDs = this->getListaIDVertices();
	vector<int> ordenacaoTopologica;
	vector<Vertice*> vertices;
	queue<Vertice*> s;
	Vertice* v;
	v = this->getRootVertice();

	Vertice **visitados = new Vertice *[this->getN()]();

	for(;v != NULL;v = v->getProximo()){
		vertices.push_back(v);
		if(v->getGrauEntrada() == 0)
			s.push(v);
	}
	while(!s.empty()){
		Vertice* t = s.front();	
		auxOT(t, ordenacaoTopologica, visitados, this->getN());
        s.pop();
		}

	 cout << "\nOrdenacao topologica: ";
    for (int i = 0; i < (int)ordenacaoTopologica.size(); i++)
    {
        cout << ordenacaoTopologica[i] << ", ";
    }

}