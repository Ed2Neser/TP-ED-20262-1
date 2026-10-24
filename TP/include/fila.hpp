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
    Encomenda *elementos;
    int tamanho;
    int capacidade;
    int novo;  // Índice do próximo elemento a ser inserido na fila.
    int velho; // Índice do próximo elemento a ser removido da fila.

public:
    Fila();
    ~Fila();
    void enfileirar(Encomenda elemento);
    Encomenda desenfileirar(); // retorna Encomenda caso eu queria trabalhar com isso
    void redimensionar();
    int getTamanho();
    int getCapacidade();
};
#endif