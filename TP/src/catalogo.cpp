#include "catalogo.hpp"

Catalogo::Catalogo(char modoInicial) : lista_cruzada(nullptr), vetor_tripletas(nullptr), modo(modoInicial),
                                       num_mods(0), num_atts(0), num_itens(0)
{
    if (modoInicial == 'L')
    {
        lista_cruzada = new ListaCruzada();
    }
    else if (modoInicial == 'T')
    {
        vetor_tripletas = new VetorTripletas();
    }

}
Catalogo::~Catalogo()
{
    delete lista_cruzada;
    delete vetor_tripletas;
}

void Catalogo::setModificador(int item, int atributo, int valor)
{

    int valorAntigo = getModificador(item, atributo);

    if (valorAntigo == 0 && valor != 0)
    {
        num_mods++; // nova célula criada
    }
    else if (valorAntigo != 0 && valor == 0)
    {
        num_mods--; // célula foi removida
    }

    if (modo == 'L')
    {
        lista_cruzada->setValorCelula(item, atributo, valor);
    }
    else if (modo == 'T')
    {
        Tripleta tripleta = {atributo, item, valor};
        vetor_tripletas->adicionar(tripleta); // método terá de verificar se já existe e atualizar ou adicionar
    };
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
    return 0;
}

int Catalogo::getNumMods()
{
    return num_mods;
}

void Catalogo::setNumAtributos(int numAtributos)
{
    num_atts = numAtributos;
}

int Catalogo::getLinhaItem(int item, int *&atributos, int *&modificadores)
{
    if (modo == 'L')
    {
        return lista_cruzada->getLinhaItem(item, atributos, modificadores);
    }
    else if (modo == 'T')
    {
        return vetor_tripletas->getLinhaItem(item, atributos, modificadores);
    }
    atributos = nullptr;
    modificadores = nullptr;
    return 0;
}

int Catalogo::getColunaAtributo(int atributo, int *&itens, int *&modificadores)
{
    if (modo == 'L')
    {
        return lista_cruzada->getColunaAtributo(atributo, itens, modificadores);
    }
    else if (modo == 'T')
    {
        return vetor_tripletas->getColunaAtributo(atributo, itens, modificadores);
    }
    itens = nullptr;
    modificadores = nullptr;
    return 0;
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
    return 0.0;
}

double Catalogo::calcularEquilibrio(int item)
{
    if (modo == 'L')
    {
        return lista_cruzada->calcularEquilibrio(item, num_atts);
    }
    else if (modo == 'T')
    {
        return vetor_tripletas->calcularEquilibrio(item, num_atts);
    }
    return 0.0;
}

double Catalogo::calcularEquilibrio(int item, double)
{
    return calcularEquilibrio(item);
}

double Catalogo::produtoInterno(int item, double *vetorBuild)
{
    if (modo == 'L')
    {
        return lista_cruzada->produtoInterno(item, vetorBuild, num_atts);
    }
    else if (modo == 'T')
    {
        return vetor_tripletas->produtoInterno(item, vetorBuild, num_atts);
    }
    return 0.0;
}

void Catalogo::mudarModo(char novoModo, int numItens, int numAtributos, int numMods)
{
    num_itens = numItens;
    num_atts = numAtributos;
    num_mods = numMods;

    if ((modo == novoModo) || (novoModo != 'L' && novoModo != 'T'))
    {
        return; // Programação defensiva
    }
    else if (novoModo == 'L')
    {
        this->lista_cruzada = new ListaCruzada();

        for (Tripleta t : *(this->vetor_tripletas))
        {
            lista_cruzada->setValorCelula(t.item_id, t.atributo_id, t.valor);
        }
        modo = 'L';
        delete vetor_tripletas; // Libera a memória do vetor de tripletas antigo
        vetor_tripletas = nullptr;
    }
    else if (novoModo == 'T')
    {
        this->vetor_tripletas = new VetorTripletas();
        int *celulas = lista_cruzada->obterTodosElementos(num_mods);
        if (celulas != nullptr)
        {
            for (int i = 0; i < num_mods * 3; i += 3)
            {
                Tripleta tripleta = {celulas[i], celulas[i + 1], celulas[i + 2]};
                vetor_tripletas->adicionar(tripleta);
            }
        }

        modo = 'T';
        delete lista_cruzada; // Libera a memória da lista cruzada antiga
        lista_cruzada = nullptr;
        delete[] celulas; // Libera a memória do array de células
    }
}
