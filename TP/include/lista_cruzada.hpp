#ifndef LISTA_CRUZADA_HPP
#define LISTA_CRUZADA_HPP

struct Celula
{
    int item, atributo, valor;        // item = linha, atributo = coluna, valor = modificação
    Celula *proxItem, *prox_atributo; // ponteiros para a próxima célula na linha e na coluna
    //     prox linha  prox coluna      (não nulos) em uma mesma coluna/linha
};

class ListaCruzada // Lista cruzada de entidades.
{
private:
    Celula **linhas;  // Vetor de ponteiros para as cabeças das linhas da lista cruzada
    Celula **colunas; // Vetor de ponteiros para as cabeças das colunas da lista cruzada
    int num_linhas;   // Número de linhas (itens)
    int num_colunas;  // Número de colunas (atributos)

    Celula *AntLinha(int item, int atributo) const;  // Retorna a célula anterior à célula (i, j) na mesma linha
    Celula *AntColuna(int item, int atributo) const; // Retorna a célula anterior à célula (i, j) na mesma coluna

public:
    ListaCruzada(int numLinhas, int numColunas);
    ~ListaCruzada();

    void setCelula(int item, int atributo, int valor);
    void removerCelula(int item, int atributo);

    int getValorCelula(int item, int atributo);
    int getNumLinhas();
    int getNumColunas();

    int *percorrerLinhaItem(int item);
    int *percorrerColunaAtributo(int atributo);

    double calcularPoder(int item);
    double calcularEquilibrio(int item, double poder);
    double produtoInterno(int item, int *vetorBuild, int numAtributosCadastrados);

    int *obterTodosElementos(int numMods); // retorna um array no formato [atributo, item, valor...]
};
#endif
