#ifndef LISTA_CRUZADA_HPP
#define LISTA_CRUZADA_HPP

struct Celula
{
    int item, atributo, valor;         // item = linha, atributo = coluna, valor = modificação
    Celula *prox_item, *prox_atributo; // ponteiros para a próxima célula na linha e na coluna
    //     prox linha  prox coluna      (não nulos) em uma mesma coluna/linha
    // para os cabeças, valor = 0.
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

    void redimensionarLinhas();
    void redimensionarColunas();

public:
    ListaCruzada();
    ~ListaCruzada();

    void setValorCelula(int item, int atributo, int valor);
    int getValorCelula(int item, int atributo);

    int getNumLinhas();
    int getNumColunas();

    int getLinhaItem(int item, int *&atributos, int *&modificadores);
    int getColunaAtributo(int atributo, int *&itens, int *&modificadores);

    double calcularPoder(int item);
    double calcularEquilibrio(int item, int numAtributosCadastrados);
    double produtoInterno(int item, double *vetor_build, int numAtributosCadastrados);
    double produtoInterno(int item, double *vetor_build, double normaBuild);

    int *obterTodosElementos(int numMods); // retorna um array no formato [atributo, item, valor...]
};
#endif
