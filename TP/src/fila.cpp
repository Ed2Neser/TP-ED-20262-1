#include "fila.hpp"

Fila::Fila() : elementos(nullptr), tamanho(0), capacidade(10), novo(0), velho(0)
{
    elementos = new Encomenda[capacidade];
}

Fila::~Fila()
{
    delete[] elementos;
}

void Fila::enfileirar(Encomenda elemento)
{

    if (tamanho == capacidade)
    {
        redimensionar();
    }
    elementos[novo] = elemento;
    novo = (novo + 1) % capacidade;
    tamanho++;
}

Encomenda Fila::desenfileirar()
{
    if (tamanho == 0)
    {
        Encomenda emptyEncomenda = {-1, -1}; // Retorna uma Encomenda vazia ou com valores inválidos
        return emptyEncomenda;
    }
    Encomenda elemento = elementos[velho];
    velho = (velho + 1) % capacidade;
    tamanho--;
    return elemento;
}

void Fila::redimensionar()
{
    Encomenda *temp = new Encomenda[capacidade * 2];
    for (int i = 0; i < tamanho; i++)
    {
        temp[i] = elementos[(velho + i) % capacidade];
    }
    delete[] elementos;
    elementos = temp;
    capacidade *= 2;
    novo = tamanho;
    velho = 0;
}

int Fila::getTamanho()
{
    return tamanho;
}

int Fila::getCapacidade()
{
    return capacidade;
}
