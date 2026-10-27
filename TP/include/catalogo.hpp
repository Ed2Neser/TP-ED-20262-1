#ifndef CATALOGO_HPP
#define CATALOGO_HPP
#include "lista_cruzada.hpp"
#include "vetor_tripletas.hpp"

class Catalogo // Classe que gerencia as transições entre as representções da tabela de modificadores.
{
private:
    ListaCruzada *lista_cruzada;     // Representação da tabela de modificadores como uma lista cruzada.
    VetorTripletas *vetor_tripletas; // Representação da tabela de modificadores como um vetor de tripletas.
    char modo;                       // L = lista cruzada, T = vetor de tripletas
    int num_mods, num_atts, num_itens;

public:
    Catalogo(char modoInicial);
    ~Catalogo();

    void setModificador(int item, int atributo, int valor);
    int getModificador(int item, int atributo);
    int getNumMods();

    int getLinhaItem(int item, int *&atributos, int *&modificadores);
    int getColunaAtributo(int atributo, int *&itens, int *&modificadores);

    double calcularPoder(int item);
    double calcularEquilibrio(int item, double poder);
    double produtoInterno(int item, double *vetorBuild);

    void mudarModo(char novoModo, int numItens, int numAtributos, int numMods);
};
#endif