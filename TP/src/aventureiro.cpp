#include "../include/aventureiro.hpp"
#include "../include/catalogo.hpp"

Aventureiro::Aventureiro(int id, std::string nome)
    : id(id), nome(nome), build()
{
}

Aventureiro::~Aventureiro()
{
}

int Aventureiro::getId()
{
    return id;
}

std::string Aventureiro::getNome()
{
    return nome;
}

Pilha *Aventureiro::getBuild()
{
    return &build;
}

void Aventureiro::equiparItem(int itemId)
{
    this->build.empilhar(itemId);

} // adiciona o item à build e atualiza o vetor denso
int Aventureiro::desequiparItem()
{
    return this->build.desempilhar();
}