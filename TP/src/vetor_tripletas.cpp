
#include "../include/vetor_tripletas.hpp"
#include <cmath>

VetorTripletas::VetorTripletas()
{
    this->capacidade = 10; // Capacidade inicial de segurança
    this->tamanho = 0;
    this->tripletas = new Tripleta[this->capacidade];
}

VetorTripletas::~VetorTripletas()
{
    delete[] tripletas;
}

int VetorTripletas::indiceInicialItem(int item) const
{
    int inicio = 0;
    int fim = tamanho;
    while (inicio < fim)
    {
        int meio = inicio + (fim - inicio) / 2;
        if (tripletas[meio].item_id < item)
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio;
        }
    }
    return inicio;
}

void VetorTripletas::redimensionar()
{
    this->capacidade *= 2;
    Tripleta *temp = new Tripleta[this->capacidade];

    for (int i = 0; i < this->tamanho; i++)
    {
        temp[i] = this->tripletas[i];
    }

    delete[] this->tripletas;
    this->tripletas = temp;
}

void VetorTripletas::adicionar(Tripleta t)
{
    // Atualiza uma célula existente ou remove-a quando o novo valor é zero.
    int indice = indiceInicialItem(t.item_id);
    while (indice < tamanho && tripletas[indice].item_id == t.item_id &&
           tripletas[indice].atributo_id < t.atributo_id)
    {
        indice++;
    }

    if (indice < tamanho && tripletas[indice].item_id == t.item_id &&
        tripletas[indice].atributo_id == t.atributo_id)
    {
        if (t.valor == 0)
        {
            remover(t);
        }
        else
        {
            tripletas[indice].valor = t.valor;
        }
        return;
    }

    if (t.valor == 0)
    {
        return;
    }

    if (tamanho == capacidade)
    {
        redimensionar();
    }

    int deslocamento = tamanho;
    while (deslocamento > indice)
    {
        tripletas[deslocamento] = tripletas[deslocamento - 1];
        deslocamento--;
    }

    tripletas[indice] = t;
    tamanho++;
}

void VetorTripletas::remover(Tripleta t)
{
    int indice = indiceInicialItem(t.item_id);
    while (indice < tamanho && tripletas[indice].item_id == t.item_id &&
           tripletas[indice].atributo_id < t.atributo_id)
    {
        indice++;
    }
    if (indice == tamanho || tripletas[indice].item_id != t.item_id ||
        tripletas[indice].atributo_id != t.atributo_id)
    {
        return;
    }

    for (int i = indice; i < tamanho - 1; i++)
    {
        tripletas[i] = tripletas[i + 1];
    }
    tamanho--;
}

int VetorTripletas::getModificador(int id_item, int id_atributo)
{
    int indice = indiceInicialItem(id_item);
    while (indice < tamanho && tripletas[indice].item_id == id_item &&
           tripletas[indice].atributo_id < id_atributo)
    {
        indice++;
    }
    if (indice < tamanho && tripletas[indice].item_id == id_item &&
        tripletas[indice].atributo_id == id_atributo)
    {
        return tripletas[indice].valor;
    }
    return 0;
}

int VetorTripletas::getTamanho()
{
    return tamanho;
}

int VetorTripletas::getCapacidade()
{
    return capacidade;
}

void VetorTripletas::ordenarPorItem()
{
    // insertion sort, por ser estável, in-place e boa referência pra otimizar durante a Análise Exp.
    for (int i = 1; i < tamanho; i++)
    {
        Tripleta chave = tripletas[i];
        int j = i - 1;
        while (j >= 0 && (tripletas[j].item_id > chave.item_id ||
                          (tripletas[j].item_id == chave.item_id && tripletas[j].atributo_id > chave.atributo_id)))
        {
            tripletas[j + 1] = tripletas[j];
            j = j - 1;
        }
        tripletas[j + 1] = chave;
    }
}

void VetorTripletas::ordenarPorAtributo()
{
    // insertion sort, por ser estável, in-place e boa referência pra otimizar durante a Análise Exp.
    for (int i = 1; i < tamanho; i++)
    {
        Tripleta chave = tripletas[i];
        int j = i - 1;
        while (j >= 0 && (tripletas[j].atributo_id > chave.atributo_id ||
                          (tripletas[j].atributo_id == chave.atributo_id && tripletas[j].item_id > chave.item_id)))
        {
            tripletas[j + 1] = tripletas[j];
            j = j - 1;
        }
        tripletas[j + 1] = chave;
    }
}

int VetorTripletas::getLinhaItem(int item, int *&atributos, int *&modificadores)
{
    atributos = nullptr;
    modificadores = nullptr;
    int inicio = indiceInicialItem(item);
    int fim = inicio;
    while (fim < tamanho && tripletas[fim].item_id == item)
    {
        fim++;
    }
    int qntd = fim - inicio;

    if (qntd == 0)
    {
        return 0;
    }

    atributos = new int[qntd];
    modificadores = new int[qntd];
    int idx = 0;

    for (int i = inicio; i < fim; i++)
    {
        atributos[idx] = tripletas[i].atributo_id;
        modificadores[idx] = tripletas[i].valor;
        idx++;
    }
    return qntd;
}
int VetorTripletas::getColunaAtributo(int atributo, int *&itens, int *&modificadores)
{
    int qntd = 0;
    for (int i = 0; i < tamanho; i++)
    {
        if (tripletas[i].atributo_id == atributo)
        {
            qntd++;
        }
    }

    if (qntd == 0)
    {
        itens = nullptr;
        modificadores = nullptr;
        return 0;
    }

    itens = new int[qntd];
    modificadores = new int[qntd];
    int idx = 0;

    for (int i = 0; i < tamanho; i++)
    {
        if (tripletas[i].atributo_id == atributo)
        {
            itens[idx] = tripletas[i].item_id;
            modificadores[idx] = tripletas[i].valor;
            idx++;
        }
    }
    return qntd;
}

double VetorTripletas::calcularPoder(int item)
{
    double soma = 0.0;
    int indice = indiceInicialItem(item);
    while (indice < tamanho && tripletas[indice].item_id == item)
    {
        soma += static_cast<double>(tripletas[indice].valor);
        indice++;
    }
    return soma;
}

double VetorTripletas::calcularEquilibrio(int item, int numAtributosCadastrados)
{
    if (numAtributosCadastrados == 0)
    {
        return 1.0;
    }

    int inicio = indiceInicialItem(item);
    int fim = inicio;
    double poder = 0.0;
    while (fim < tamanho && tripletas[fim].item_id == item)
    {
        poder += static_cast<double>(tripletas[fim].valor);
        fim++;
    }

    double media = poder / numAtributosCadastrados;
    double soma = 0.0;
    for (int i = inicio; i < fim; i++)
    {
        double diferenca = tripletas[i].valor - media;
        soma += diferenca * diferenca;
    }
    soma += (numAtributosCadastrados - (fim - inicio)) * media * media;
    double desvio = std::sqrt(soma / numAtributosCadastrados);
    return 1 / (1 + desvio);
}
double VetorTripletas::produtoInterno(int item, double *vetor_build, int numAtributosCadastrados)
{
    double normaBuild = 0.0;
    for (int i = 0; i < numAtributosCadastrados; i++)
    {
        normaBuild += vetor_build[i] * vetor_build[i];
    }
    return produtoInterno(item, vetor_build, normaBuild);
}

double VetorTripletas::produtoInterno(int item, double *vetor_build, double normaBuild)
{
    double soma_vb = 0.0;
    double soma_v_sqr = 0.0;

    int *atts = nullptr;
    int *mods = nullptr;
    int qntd = getLinhaItem(item, atts, mods);

    for (int i = 0; i < qntd; i++)
    {
        int m = mods[i];
        soma_vb += m * vetor_build[atts[i]];
        soma_v_sqr += static_cast<double>(m) * m;
    }

    delete[] atts;
    delete[] mods;

    if (soma_v_sqr == 0.0 || normaBuild == 0.0)
        return 0.0;
    return soma_vb / (std::sqrt(soma_v_sqr) * std::sqrt(normaBuild));
}

Tripleta *VetorTripletas::begin()
{
    return tripletas;
}

Tripleta *VetorTripletas::end()
{
    return tripletas + tamanho;
}
