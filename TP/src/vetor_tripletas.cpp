
#include "vetor_tripletas.hpp"
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
    // Verifica se já tem, para atualizar
    for (int i = 0; i < tamanho; i++)
    {
        if (tripletas[i].item_id == t.item_id && tripletas[i].atributo_id == t.atributo_id)
        {
            if (t.valor == 0)
            {
                remover(t);
            }
            else
            {
                tripletas[i].valor = t.valor;
            }
            return;
        }
    }

    // valor 0 é ignorado
    if (t.valor == 0)
    {
        return;
    }

    if (tamanho == capacidade)
    {
        redimensionar();
    }

    tripletas[tamanho] = t;
    tamanho++;
}

void VetorTripletas::remover(Tripleta t)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (tripletas[i].item_id == t.item_id && tripletas[i].atributo_id == t.atributo_id)
        {
            // Puxa o restanta pra trás
            for (int j = i; j < tamanho - 1; j++)
            {
                tripletas[j] = tripletas[j + 1];
            }
            tamanho--;
            return;
        }
    }
}

int VetorTripletas::getModificador(int id_item, int id_atributo)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (tripletas[i].item_id == id_item && tripletas[i].atributo_id == id_atributo)
        {
            return tripletas[i].valor;
        }
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
    int qntd = 0;
    for (int i = 0; i < tamanho; i++)
    {
        if (tripletas[i].item_id == item)
        {
            qntd++;
        }
    }

    if (qntd == 0)
    {
        atributos = nullptr;
        modificadores = nullptr;
        return 0;
    }

    atributos = new int[qntd];
    modificadores = new int[qntd];
    int idx = 0;

    for (int i = 0; i < tamanho; i++)
    {
        if (tripletas[i].item_id == item)
        {
            atributos[idx] = tripletas[i].atributo_id;
            modificadores[idx] = tripletas[i].valor;
            idx++;
        }
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
    for (int i = 0; i < tamanho; i++)
    {
        if (tripletas[i].item_id == item)
        {
            soma += (double)tripletas[i].valor;
        }
    }
    return soma;
}

double VetorTripletas::calcularEquilibrio(int item, int numAtributosCadastrados)
{
    double soma = 0.0;
    double media = calcularPoder(item) / numAtributosCadastrados;
    int k = 0;
    for (int i = 0; i < tamanho; i++)
    {
        if (tripletas[i].item_id == item)
        {
            double val = (tripletas[i].valor - media);
            soma += val * val;
            k++;
        }
    }

    double desvio = std::sqrt(soma / numAtributosCadastrados);

    if (k == 0)
    {
        return 0.0;
    }

    return 1 / (1 + desvio);
}
double VetorTripletas::produtoInterno(int item, double *vetor_build, int numAtributosCadastrados)
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
        soma_vb += m * vetor_build[atts[i]];
        soma_v_sqr += m * m;
    }

    for (int i = 0; i < numAtributosCadastrados; i++)
    {
        soma_b_sqr += vetor_build[i] * vetor_build[i];
    }

    delete[] atts;
    delete[] mods;

    if (soma_v_sqr == 0.0 || soma_b_sqr == 0.0)
        return 0.0;
    return soma_vb / (std::sqrt(soma_v_sqr) * std::sqrt(soma_b_sqr));
}

Tripleta *VetorTripletas::begin()
{
    return tripletas;
}

Tripleta *VetorTripletas::end()
{
    return tripletas + tamanho;
}
