#include "catalogo.hpp"

Catalogo::Catalogo(int numItens, int numAtributos, char modoInicial) : modo(modoInicial), lista_cruzada(nullptr), vetor_tripletas(nullptr)
{
    if (modoInicial == 'L')
    {
        lista_cruzada = new ListaCruzada(numItens, numAtributos);
    }
    else if (modoInicial == 'T')
    {
        vetor_tripletas = new VetorTripletas(numItens, numAtributos);
    }
}
Catalogo::~Catalogo()
{
    delete lista_cruzada;
    delete vetor_tripletas;
}

void Catalogo::setModificador(int item, int atributo, int valor)
{
    if (modo == 'L')
    {
        lista_cruzada->setCelula(item, atributo, valor);
    }
    else if (modo == 'T')
    {
        Tripleta tripleta = {atributo, item, valor};
        vetor_tripletas->adicionar(tripleta); // método terá de verificar se já existe e atualizar ou adicionar
    }
}
void Catalogo::removerModificador(int item, int atributo)
{

    if (modo == 'L')
    {
        lista_cruzada->removerCelula(item, atributo);
    }
    else if (modo == 'T')
    {
        Tripleta tripleta = {atributo, item, 0}; // valor não é relevante para remoção
        vetor_tripletas->remover(tripleta);      // método terá de verificar se existe e remover
    }
}

int Catalogo::getModificador(int item, int atributo)
{
    if (modo == 'L')
    {
        return lista_cruzada->getValorCelula(item, atributo);
    }
    else if (modo == 'T')
    {
        return vetor_tripletas->getModificador(item, atributo);
    }
}

int *Catalogo::percorrerLinhaItem(int item)
{
    if (modo == 'L')
    {
        return lista_cruzada->percorrerLinhaItem(item);
    }
    else if (modo == 'T')
    {
        return vetor_tripletas->percorrerLinhaItem(item);
    }
}

int *Catalogo::percorrerColunaAtributo(int atributo)
{
    if (modo == 'L')
    {
        return lista_cruzada->percorrerColunaAtributo(atributo);
    }
    else if (modo == 'T')
    {
        return vetor_tripletas->percorrerColunaAtributo(atributo);
    }
}

double Catalogo::calcularPoder(int item)
{
    if (modo == 'L')
    {
        return lista_cruzada->calcularPoder(item);
    }
    else if (modo == 'T')
    {
        return vetor_tripletas->calcularPoder(item);
    }
}

double Catalogo::calcularEquilibrio(int item, double poder)
{
    if (modo == 'L')
    {
        return lista_cruzada->calcularEquilibrio(item, poder);
    }
    else if (modo == 'T')
    {
        return vetor_tripletas->calcularEquilibrio(item, poder);
    }
}

double Catalogo::produtoInterno(int item, int *vetorBuild, int numAtributosCadastrados)
{
    if (modo == 'L')
    {
        return lista_cruzada->produtoInterno(item, vetorBuild, numAtributosCadastrados);
    }
    else if (modo == 'T')
    {
        return vetor_tripletas->produtoInterno(item, vetorBuild, numAtributosCadastrados);
    }
}

void Catalogo::mudarModo(char novoModo, int numItens, int numAtributos, int numMods)
{
    if ((modo == novoModo) || (novoModo != 'L' && novoModo != 'T'))
    {
        return; // Programação defensiva
    }
    else if (novoModo == 'L')
    {
        this->lista_cruzada = new ListaCruzada(numItens, numAtributos);

        for (Tripleta t : *(this->vetor_tripletas))
        {
            lista_cruzada->setCelula(t.item_id, t.atributo_id, t.valor);
        }
        modo = 'L';
        delete[] vetor_tripletas; // Libera a memória do vetor de tripletas antigo
    }
    else if (novoModo == 'T')
    {
        this->vetor_tripletas = new VetorTripletas(numItens, numAtributos);
        int *celulas = lista_cruzada->obterTodosElementos(numMods);
        if (celulas == nullptr)
        {
            for (int i = 0; i < numMods * 3; i += 3)
            {
                Tripleta tripleta = {celulas[i], celulas[i + 1], celulas[i + 2]};
                vetor_tripletas->adicionar(tripleta);
            }
        }

        modo = 'T';
        delete[] lista_cruzada; // Libera a memória da lista cruzada antiga
        delete[] celulas;       // Libera a memória do array de células
    }
}