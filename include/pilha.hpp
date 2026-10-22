#ifndef PILHA_HPP
#define PILHA_HPP

class Pilha // estrutura de dados do tipo pilha. Dinâmica. Representa a Build.
{
private:
    int *elementos;
    int tamanho;
    int capacidade;

public:
    Pilha(); // construtor padrão que inicializa a pilha com capacidade inicial de 10 elementos.
    ~Pilha();
    void empilhar(int elemento);
    int desempilhar();
    void redimensionar();
    int getTamanho();
    int getCapacidade();
};

#endif
