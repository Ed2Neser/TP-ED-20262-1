#ifndef FILA_HPP
#define FILA_HPP

struct Encomenda
{
    int aventureiro_id;
    int item_id;
};

class Fila // Estrutura de dados do tipo fila. Dinâmica.
{
private:
    int *elementos;
    int tamanho;
    int capacidade;
    int novo;  // Índice do próximo elemento a ser inserido na fila.
    int velho; // Índice do próximo elemento a ser removido da fila.

public:
    Fila(int capacidade);
    ~Fila();
    void enfileirar(int elemento);
    int desenfileirar(); // retorna int caso eu queria trabalhar com isso
    void redimensionar();
    int getTamanho();
    int getCapacidade();
};
#endif