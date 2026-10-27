#include "pilha.hpp"

Pilha::Pilha() : elementos(nullptr), tamanho(0), capacidade(10)
{
    elementos = new int[capacidade];
}

Pilha::~Pilha()
{
    delete[] elementos;
}

void Pilha::empilhar(int elemento)
{
    if (tamanho == capacidade)
    {
        redimensionar();
    }
    elementos[tamanho] = elemento;
    tamanho++;
}

int Pilha::desempilhar()
{
    if (tamanho == 0)
    {
        return -1; // Retorna um valor inválido caso a pilha esteja vazia
    }
    tamanho--;
    int item = elementos[tamanho];
    elementos[tamanho] = -1;
    return item;
}

void Pilha::redimensionar()
{
    int *temp = new int[capacidade * 2];
    for (int i = 0; i < tamanho; i++)
    {
        temp[i] = elementos[i];
    }
    delete[] elementos;
    elementos = temp;
    capacidade *= 2;
}

int Pilha::getTamanho()
{
    return tamanho;
}

int Pilha::getCapacidade()
{
    return capacidade;
}