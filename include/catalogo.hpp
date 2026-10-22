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

    int *itens;     // Array de IDs dos itens cadastrados
    int *atributos; // Array de IDs dos atributos cadastrados

public:
    Catalogo(int numItens, int numAtributos, char modoInicial);
    ~Catalogo();

    void setModificador(int item, int atributo, int valor);
    void removerModificador(int item, int atributo);
    int getModificador(int item, int atributo);

    int *percorrerLinhaItem(int item);
    int *percorrerColunaAtributo(int atributo);

    double calcularPoder(int item);
    double calcularEquilibrio(int item, double poder);
    double produtoInterno(int item, int *vetorBuild, int numAtributosCadastrados);

    void mudarModo(char novoModo, int numItens, int numAtributos, int numMods);
};
#endif