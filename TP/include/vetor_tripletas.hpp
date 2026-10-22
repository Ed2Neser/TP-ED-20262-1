#ifndef VETOR_TRIPLETAS_HPP
#define VETOR_TRIPLETAS_HPP

// tripleta é uma palavra mt feia pprt
struct Tripleta // Estrutura assistente para armazenar três entidades diferentes.
{
    int atributo_id; // ID do atributo modificado
    int item_id;     // ID do item que gera a modificação
    int valor;       // Magnitude da modificação
};

class VetorTripletas // Vetor de tripletas.
{
private:
    Tripleta *tripletas;
    int tamanho;
    int capacidade;

public:
    VetorTripletas(int numItens, int numAtributos); // inicializa o vetor usando o maior dos parâmetros.
    ~VetorTripletas();

    void adicionar(Tripleta tripletas);
    void remover(Tripleta tripletas);

    int getModificador(int id_item, int id_atributo); // Retorna a tripleta correspondente ao item e atributo fornecidos.
    int getTamanho();
    int getCapacidade();

    void redimensionar();
    void ordenarPorItem();     // Ordena as tripletas pelo ID do item.
    void ordenarPorAtributo(); // Ordena as tripletas pelo ID do atributo.

    int *percorrerLinhaItem(int item);
    int *percorrerColunaAtributo(int atributo);

    double calcularPoder(int item);
    double calcularEquilibrio(int item, double poder);
    double produtoInterno(int item, int *vetorBuild, int numAtributosCadastrados);

    // Métodos para facilitar e usar o "range-based for loop" (for each)
    Tripleta *begin();
    Tripleta *end();
};

#endif