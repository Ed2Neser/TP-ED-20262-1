#ifndef AVENTUREIRO_HPP
#define AVENTUREIRO_HPP
#include <string>
#include "pilha.hpp"

class Catalogo;

class Aventureiro // Classe que representa um aventureiro.
{
private:
    int id;
    std::string nome;

    Pilha build; // armazena ids dos itens da build

public:
    // construtor recebe a flag para decidir o modo de operação do experimento
    Aventureiro(int id, std::string nome);
    ~Aventureiro();

    int getId();
    std::string getNome();
    Pilha *getBuild();

    void equiparItem(int itemId); // adiciona o item à build e atualiza o vetor denso
    void desequiparItem();        // remove o ultimo item da build e atualiza o vetor denso
};
#endif
