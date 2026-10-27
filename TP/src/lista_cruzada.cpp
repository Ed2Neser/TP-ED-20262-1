#include "lista_cruzada.hpp"
#include <cmath>

ListaCruzada::ListaCruzada()
{
    this->num_linhas = 10;
    this->num_colunas = 10;
    this->linhas = new Celula *[10];
    this->colunas = new Celula *[10];
    for (int i = 0; i < 10; i++)
    {
        linhas[i] = new Celula{i, -1, 0, nullptr, nullptr}; // sentinelas
    }
    for (int j = 0; j < 10; j++)
    {
        colunas[j] = new Celula{-1, j, 0, nullptr, nullptr}; // sentinelas
    }
}
ListaCruzada::~ListaCruzada()
{
    // liberação das linhas e seus dados
    for (int i = 0; i < num_linhas; i++)
    {
        Celula *celulaAtual = linhas[i];
        while (celulaAtual != nullptr)
        {
            Celula *proximaCelula = celulaAtual->prox_atributo;
            delete celulaAtual;
            celulaAtual = proximaCelula;
        }
    }

    // liberação das cabeças de coluna, que faltaram
    for (int j = 0; j < num_colunas; j++)
    {
        delete colunas[j];
    }

    delete[] linhas;
    delete[] colunas;
}

Celula *ListaCruzada::AntLinha(int item, int atributo) const
{
    Celula *celulaAtual = linhas[item];
    if (celulaAtual == nullptr)
    {
        return nullptr; // indica que o item não existe na lista cruzada
    }
    while (celulaAtual->prox_atributo != nullptr && celulaAtual->prox_atributo->atributo < atributo)
    {
        celulaAtual = celulaAtual->prox_atributo;
    }
    return celulaAtual; // celula anterior à célula (i, j) na mesma linha
}
Celula *ListaCruzada::AntColuna(int item, int atributo) const
{

    Celula *celulaAtual = colunas[atributo];
    if (celulaAtual == nullptr)
    {
        return nullptr; // indica que o atributo não existe na lista cruzada
    }
    while (celulaAtual->prox_item != nullptr && celulaAtual->prox_item->item < item)
    {
        celulaAtual = celulaAtual->prox_item;
    }
    return celulaAtual; // celula anterior à célula (i, j) na mesma coluna
}

void ListaCruzada::redimensionarLinhas()
{
    int novaCapacidade = num_linhas * 2;
    Celula **novas = new Celula *[novaCapacidade];
    for (int i = 0; i < num_linhas; i++)
    {
        novas[i] = linhas[i];
    }
    for (int i = num_linhas; i < novaCapacidade; i++)
    {
        novas[i] = new Celula{i, -1, 0, nullptr, nullptr};
    }
    delete[] linhas;
    linhas = novas;
    num_linhas = novaCapacidade;
}
void ListaCruzada::redimensionarColunas()
{
    int novaCapacidade = num_colunas * 2;
    Celula **novas = new Celula *[novaCapacidade];
    for (int j = 0; j < num_colunas; j++)
    {
        novas[j] = colunas[j];
    }
    for (int j = num_colunas; j < novaCapacidade; j++)
    {
        novas[j] = new Celula{-1, j, 0, nullptr, nullptr};
    }
    delete[] colunas;
    colunas = novas;
    num_colunas = novaCapacidade;
}

void ListaCruzada::setValorCelula(int item, int atributo, int valor)
{
    while (item >= num_linhas)
    {
        redimensionarLinhas();
    }
    while (atributo >= num_colunas)
    {
        redimensionarColunas();
    }

    Celula *anteriorLinha = AntLinha(item, atributo);
    Celula *anteriorColuna = AntColuna(item, atributo);
    Celula *atual = anteriorLinha->prox_atributo;

    bool existe = (atual != nullptr && atual->atributo == atributo);

    if (existe)
    {
        if (valor == 0)
        {
            // remove
            anteriorLinha->prox_atributo = atual->prox_atributo;
            anteriorColuna->prox_item = atual->prox_item;
            delete atual;
        }
        else
        {
            // atauliza
            atual->valor = valor;
        }
    }
    else
    {
        if (valor != 0)
        {
            // insere
            Celula *novaCelula = new Celula{item, atributo, valor, anteriorLinha->prox_atributo, anteriorColuna->prox_item};
            anteriorLinha->prox_atributo = novaCelula;
            anteriorColuna->prox_item = novaCelula;
        }
    }
}

int ListaCruzada::getValorCelula(int item, int atributo)
{
    if (item < 0 || item >= num_linhas || atributo < 0 || atributo >= num_colunas) // defesa
    {
        return 0;
    }
    Celula *anterior = AntLinha(item, atributo);
    Celula *atual = anterior->prox_atributo;
    if (atual != nullptr && atual->atributo == atributo)
        return atual->valor;
    return 0;
}
int ListaCruzada::getNumLinhas()
{
    return num_linhas;
}
int ListaCruzada::getNumColunas()
{
    return num_colunas;
}

int ListaCruzada::getLinhaItem(int item, int *&atributos, int *&modificadores)
{
    atributos = nullptr;
    modificadores = nullptr;
    if (item < 0 || item >= num_linhas)
        return 0;
    int qntd = 0;
    Celula *p = linhas[item]->prox_atributo; // primeira celula nao cabeça
    while (p != nullptr)
    {
        qntd++;
        p = p->prox_atributo;
    }

    if (qntd == 0)
        return 0;

    modificadores = new int[qntd];
    atributos = new int[qntd];

    p = linhas[item]->prox_atributo;
    int id = 0;
    while (p != nullptr)
    {
        atributos[id] = p->atributo;
        modificadores[id] = p->valor;
        p = p->prox_atributo;
        id++;
    }
    return qntd;
}

int ListaCruzada::getColunaAtributo(int atributo, int *&itens, int *&modificadores)
{
    itens = nullptr;
    modificadores = nullptr;
    if (atributo < 0 || atributo >= num_colunas)
        return 0;
    int qntd = 0;
    Celula *p = colunas[atributo]->prox_item; // primeira celula nao cabeça
    while (p != nullptr)
    {
        qntd++;
        p = p->prox_item;
    }

    if (qntd == 0)
        return 0;

    modificadores = new int[qntd];
    itens = new int[qntd];

    p = colunas[atributo]->prox_item;
    int id = 0;
    while (p != nullptr)
    {
        itens[id] = p->item;
        modificadores[id] = p->valor;
        p = p->prox_item;
        id++;
    }
    return qntd;
}

double ListaCruzada::calcularPoder(int item)
{
    if (item < 0 || item >= num_linhas)
    {
        return 0.0;
    }

    double soma = 0.0;
    Celula *p = linhas[item]->prox_atributo;
    while (p != nullptr)
    {
        soma += (double)p->valor;
        p = p->prox_atributo;
    }
    return (soma);
}

double ListaCruzada::calcularEquilibrio(int item, int numAtributosCadastrados)
{
    if (item < 0 || item >= num_linhas)
    {
        return 0.0;
    }
    if (numAtributosCadastrados == 0)
        return 1;

    double poder = calcularPoder(item);

    double media = poder / numAtributosCadastrados;

    double desvio = 0.0;

    for (int i = 0; i < numAtributosCadastrados; i++)
    {
        double mod = getValorCelula(item, i);
        double sqr = (mod - media) * (mod - media);
        desvio += (sqr);
    }

    desvio = std::sqrt(desvio / numAtributosCadastrados);

    return 1 / (1 + desvio);
}

double ListaCruzada::produtoInterno(int item, double *vetorBuild, int numAtributosCadastrados)
{
    if (numAtributosCadastrados == 0)
        return 0.0;

    double soma_vb = 0.0;
    double soma_v_sqr = 0.0;
    double soma_b_sqr = 0.0;

    int *atts = nullptr;
    int *mods = nullptr;
    int qntd = getLinhaItem(item, atts, mods);

    for (int i = 0; i < qntd; i++)
    {
        int m = mods[i];
        soma_vb += m * vetorBuild[atts[i]];
        soma_v_sqr += m * m;
    }

    for (int i = 0; i < numAtributosCadastrados; i++)
    {
        soma_b_sqr += vetorBuild[i] * vetorBuild[i];
    }

    delete[] atts;
    delete[] mods;

    if (soma_v_sqr == 0.0 || soma_b_sqr == 0.0)
        return 0.0;
    return soma_vb / (std::sqrt(soma_v_sqr) * std::sqrt(soma_b_sqr));
}

int *ListaCruzada::obterTodosElementos(int numMods)
{
    if (numMods <= 0)
    {
        return nullptr;
    }

    int *elementos = new int[numMods * 3];
    int id = 0;

    for (int i = 0; i < num_linhas; i++)
    {
        Celula *p = linhas[i]->prox_atributo;
        while (p != nullptr)
        {
            if (id < numMods * 3)
            {
                elementos[id] = p->atributo;
                elementos[id + 1] = p->item;
                elementos[id + 2] = p->valor;
                id += 3;
            }
            p = p->prox_atributo;
        }
    }
    return elementos;
}