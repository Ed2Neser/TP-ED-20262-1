#include "forja.hpp"

#include <cmath>
#include <stdexcept>

namespace
{
    template <typename T>
    void redimensionar(T *&elementos, int tamanho, int &capacidade)
    {
        if (tamanho < capacidade)
        {
            return;
        }

        int novaCapacidade = capacidade == 0 ? 10 : capacidade * 2;
        T *novosElementos = new T[novaCapacidade];
        try
        {
            for (int i = 0; i < tamanho; i++)
            {
                novosElementos[i] = elementos[i];
            }
        }
        catch (...)
        {
            delete[] novosElementos;
            throw;
        }

        delete[] elementos;
        elementos = novosElementos;
        capacidade = novaCapacidade;
    }

    struct ValorMetrica
    {
        int itemId;
        double valor;
    };

    struct PontuacaoCentesimos
    {
        int itemId;
        long long valor;
    };

    bool precede(const ValorMetrica &a, const ValorMetrica &b)
    {
        if (a.valor != b.valor)
        {
            return a.valor > b.valor;
        }
        return a.itemId < b.itemId;
    }

    bool precede(const PontuacaoCentesimos &a, const PontuacaoCentesimos &b)
    {
        if (a.valor != b.valor)
        {
            return a.valor > b.valor;
        }
        return a.itemId < b.itemId;
    }

    void ordenar(ValorMetrica *elementos, int tamanho)
    {
        for (int i = 1; i < tamanho; i++)
        {
            ValorMetrica atual = elementos[i];
            int j = i - 1;
            while (j >= 0 && precede(atual, elementos[j]))
            {
                elementos[j + 1] = elementos[j];
                j--;
            }
            elementos[j + 1] = atual;
        }
    }

    void ordenar(PontuacaoCentesimos *elementos, int tamanho)
    {
        for (int i = 1; i < tamanho; i++)
        {
            PontuacaoCentesimos atual = elementos[i];
            int j = i - 1;
            while (j >= 0 && precede(atual, elementos[j]))
            {
                elementos[j + 1] = elementos[j];
                j--;
            }
            elementos[j + 1] = atual;
        }
    }

    double arredondarSeisCasas(double valor)
    {
        return std::round(valor * 1000000.0) / 1000000.0;
    }
}

Forja::Forja(char modoInicial)
    : atributos(nullptr),
      num_atributos(0),
      capacidade_atributos(0),
      itens(nullptr),
      num_itens(0),
      capacidade_itens(0),
      aventureiros(nullptr),
      builds(nullptr),
      itens_equipados(nullptr),
      num_aventureiros(0),
      capacidade_aventureiros(0),
      catalogo(modoInicial),
      fila()
{
    if (modoInicial != 'L' && modoInicial != 'T')
    {
        throw std::invalid_argument("O modo da forja deve ser L ou T.");
    }
}

Forja::~Forja()
{
    for (int i = 0; i < num_aventureiros; i++)
    {
        delete aventureiros[i];
        delete[] builds[i];
        delete[] itens_equipados[i];
    }
    delete[] aventureiros;
    delete[] builds;
    delete[] itens_equipados;
    delete[] atributos;
    delete[] itens;
}
int Forja::cadastrarAtributo(const std::string &nome)
{
    redimensionar(atributos, num_atributos, capacidade_atributos);

    long long **novasBuilds = nullptr;
    if (num_aventureiros > 0)
    {
        novasBuilds = new long long *[num_aventureiros];
        int criadas = 0;
        try
        {
            for (; criadas < num_aventureiros; criadas++)
            {
                novasBuilds[criadas] = new long long[num_atributos + 1];
                for (int atributoId = 0; atributoId < num_atributos; atributoId++)
                {
                    novasBuilds[criadas][atributoId] = builds[criadas][atributoId];
                }
                novasBuilds[criadas][num_atributos] = 0;
            }
        }
        catch (...)
        {
            for (int i = 0; i < criadas; i++)
            {
                delete[] novasBuilds[i];
            }
            delete[] novasBuilds;
            throw;
        }
    }

    try
    {
        atributos[num_atributos] = Atributo{num_atributos, nome};
    }
    catch (...)
    {
        for (int i = 0; i < num_aventureiros; i++)
        {
            delete[] novasBuilds[i];
        }
        delete[] novasBuilds;
        throw;
    }

    for (int i = 0; i < num_aventureiros; i++)
    {
        delete[] builds[i];
        builds[i] = novasBuilds[i];
    }
    delete[] novasBuilds;

    num_atributos++;
    catalogo.setNumAtributos(num_atributos);
    return num_atributos - 1;
}

int Forja::cadastrarItem(const std::string &nome)
{
    redimensionar(itens, num_itens, capacidade_itens);

    int **novosEquipamentos = nullptr;
    if (num_aventureiros > 0)
    {
        novosEquipamentos = new int *[num_aventureiros];
        int criados = 0;
        try
        {
            for (; criados < num_aventureiros; criados++)
            {
                novosEquipamentos[criados] = new int[num_itens + 1];
                for (int itemId = 0; itemId < num_itens; itemId++)
                {
                    novosEquipamentos[criados][itemId] = itens_equipados[criados][itemId];
                }
                novosEquipamentos[criados][num_itens] = 0;
            }
        }
        catch (...)
        {
            for (int i = 0; i < criados; i++)
            {
                delete[] novosEquipamentos[i];
            }
            delete[] novosEquipamentos;
            throw;
        }
    }

    try
    {
        itens[num_itens] = Item{num_itens, nome};
    }
    catch (...)
    {
        for (int i = 0; i < num_aventureiros; i++)
        {
            delete[] novosEquipamentos[i];
        }
        delete[] novosEquipamentos;
        throw;
    }

    for (int i = 0; i < num_aventureiros; i++)
    {
        delete[] itens_equipados[i];
        itens_equipados[i] = novosEquipamentos[i];
    }
    delete[] novosEquipamentos;

    num_itens++;
    return num_itens - 1;
}

int Forja::cadastrarAventureiro(const std::string &nome)
{
    if (num_aventureiros == capacidade_aventureiros)
    {
        int novaCapacidade = capacidade_aventureiros == 0 ? 10 : capacidade_aventureiros * 2;
        Aventureiro **novosAventureiros = new Aventureiro *[novaCapacidade];
        long long **novasBuilds = nullptr;
        int **novosEquipamentos = nullptr;
        try
        {
            novasBuilds = new long long *[novaCapacidade];
            novosEquipamentos = new int *[novaCapacidade];
        }
        catch (...)
        {
            delete[] novosAventureiros;
            delete[] novasBuilds;
            delete[] novosEquipamentos;
            throw;
        }

        for (int i = 0; i < num_aventureiros; i++)
        {
            novosAventureiros[i] = aventureiros[i];
            novasBuilds[i] = builds[i];
            novosEquipamentos[i] = itens_equipados[i];
        }
        delete[] aventureiros;
        delete[] builds;
        delete[] itens_equipados;
        aventureiros = novosAventureiros;
        builds = novasBuilds;
        itens_equipados = novosEquipamentos;
        capacidade_aventureiros = novaCapacidade;
    }

    long long *novaBuild = nullptr;
    int *novosEquipamentos = nullptr;
    Aventureiro *novoAventureiro = nullptr;
    try
    {
        novaBuild = new long long[num_atributos];
        novosEquipamentos = new int[num_itens];
        for (int i = 0; i < num_atributos; i++)
        {
            novaBuild[i] = 0;
        }
        for (int i = 0; i < num_itens; i++)
        {
            novosEquipamentos[i] = 0;
        }
        novoAventureiro = new Aventureiro(num_aventureiros, nome);
    }
    catch (...)
    {
        delete[] novaBuild;
        delete[] novosEquipamentos;
        delete novoAventureiro;
        throw;
    }

    aventureiros[num_aventureiros] = novoAventureiro;
    builds[num_aventureiros] = novaBuild;
    itens_equipados[num_aventureiros] = novosEquipamentos;
    num_aventureiros++;
    return num_aventureiros - 1;
}

void Forja::definirModificador(int itemId, int atributoId, int valor)
{
    getItem(itemId);
    getAtributo(atributoId);

    int valorAnterior = catalogo.getModificador(itemId, atributoId);
    catalogo.setModificador(itemId, atributoId, valor);

    long long diferenca = static_cast<long long>(valor) - valorAnterior;
    if (diferenca == 0)
    {
        return;
    }

    for (int idAventureiro = 0; idAventureiro < num_aventureiros; idAventureiro++)
    {
        int quantidade = itens_equipados[idAventureiro][itemId];
        builds[idAventureiro][atributoId] += diferenca * quantidade;
    }
}

int Forja::encomendar(int aventureiroId, int itemId)
{
    getAventureiro(aventureiroId);
    getItem(itemId);
    fila.enfileirar(Encomenda{aventureiroId, itemId});
    return fila.getTamanho();
}

ResultadoEncomendas Forja::trabalhar(int turnos)
{
    if (turnos < 0)
    {
        throw std::invalid_argument("O numero de turnos nao pode ser negativo.");
    }

    int quantidade = turnos < fila.getTamanho() ? turnos : fila.getTamanho();
    Encomenda *forjadas = quantidade == 0 ? nullptr : new Encomenda[quantidade];

    for (int i = 0; i < quantidade; i++)
    {
        Encomenda encomenda = fila.desenfileirar();
        aventureiros[encomenda.aventureiro_id]->equiparItem(encomenda.item_id);
        itens_equipados[encomenda.aventureiro_id][encomenda.item_id]++;
        atualizarBuild(encomenda.aventureiro_id, encomenda.item_id, 1);
        forjadas[i] = encomenda;
    }

    ResultadoEncomendas resultado = {forjadas, quantidade};
    return resultado;
}

bool Forja::desequipar(int aventureiroId, int &itemId)
{
    Aventureiro &aventureiro = getAventureiro(aventureiroId);
    if (aventureiro.getBuild()->getTamanho() == 0)
    {
        itemId = -1;
        return false;
    }

    itemId = aventureiro.desequiparItem();
    itens_equipados[aventureiroId][itemId]--;
    atualizarBuild(aventureiroId, itemId, -1);
    return true;
}

void Forja::alterarModo(char novoModo)
{
    if (novoModo != 'L' && novoModo != 'T')
    {
        throw std::invalid_argument("O modo da forja deve ser L ou T.");
    }

    catalogo.mudarModo(novoModo, num_itens, num_atributos, catalogo.getNumMods());
}

const Atributo &Forja::getAtributo(int atributoId) const
{
    if (atributoId < 0 || atributoId >= num_atributos)
    {
        throw std::out_of_range("Identificador de atributo inexistente.");
    }
    return atributos[atributoId];
}

const Item &Forja::getItem(int itemId) const
{
    if (itemId < 0 || itemId >= num_itens)
    {
        throw std::out_of_range("Identificador de item inexistente.");
    }
    return itens[itemId];
}

Aventureiro &Forja::getAventureiro(int aventureiroId)
{
    if (aventureiroId < 0 || aventureiroId >= num_aventureiros)
    {
        throw std::out_of_range("Identificador de aventureiro inexistente.");
    }
    return *aventureiros[aventureiroId];
}

const Aventureiro &Forja::getAventureiro(int aventureiroId) const
{
    if (aventureiroId < 0 || aventureiroId >= num_aventureiros)
    {
        throw std::out_of_range("Identificador de aventureiro inexistente.");
    }
    return *aventureiros[aventureiroId];
}

int Forja::getNumAtributos() const
{
    return num_atributos;
}

int Forja::getNumItens() const
{
    return num_itens;
}

int Forja::getNumAventureiros() const
{
    return num_aventureiros;
}

ResultadoModificadores Forja::consultarItem(int itemId)
{
    getItem(itemId);

    int *atributosItem = nullptr;
    int *modificadores = nullptr;
    int tamanho = catalogo.getLinhaItem(itemId, atributosItem, modificadores);
    ModificadorConsulta *resultado = nullptr;
    try
    {
        resultado = tamanho == 0 ? nullptr : new ModificadorConsulta[tamanho];
        for (int i = 0; i < tamanho; i++)
        {
            resultado[i] = ModificadorConsulta{atributosItem[i], modificadores[i]};
        }
    }
    catch (...)
    {
        delete[] resultado;
        delete[] atributosItem;
        delete[] modificadores;
        throw;
    }
    delete[] atributosItem;
    delete[] modificadores;

    for (int i = 1; i < tamanho; i++)
    {
        ModificadorConsulta atual = resultado[i];
        int j = i - 1;
        while (j >= 0 && resultado[j].id > atual.id)
        {
            resultado[j + 1] = resultado[j];
            j--;
        }
        resultado[j + 1] = atual;
    }

    ResultadoModificadores consulta = {resultado, tamanho};
    return consulta;
}

ResultadoModificadores Forja::consultarAtributo(int atributoId)
{
    getAtributo(atributoId);

    int *itensAtributo = nullptr;
    int *modificadores = nullptr;
    int tamanho = catalogo.getColunaAtributo(atributoId, itensAtributo, modificadores);
    ModificadorConsulta *resultado = nullptr;
    try
    {
        resultado = tamanho == 0 ? nullptr : new ModificadorConsulta[tamanho];
        for (int i = 0; i < tamanho; i++)
        {
            resultado[i] = ModificadorConsulta{itensAtributo[i], modificadores[i]};
        }
    }
    catch (...)
    {
        delete[] resultado;
        delete[] itensAtributo;
        delete[] modificadores;
        throw;
    }
    delete[] itensAtributo;
    delete[] modificadores;

    for (int i = 1; i < tamanho; i++)
    {
        ModificadorConsulta atual = resultado[i];
        int j = i - 1;
        while (j >= 0 && resultado[j].id > atual.id)
        {
            resultado[j + 1] = resultado[j];
            j--;
        }
        resultado[j + 1] = atual;
    }

    ResultadoModificadores consulta = {resultado, tamanho};
    return consulta;
}

ResultadoBuild Forja::consultarBuild(int aventureiroId) const
{
    getAventureiro(aventureiroId);

    int tamanho = 0;
    for (int i = 0; i < num_atributos; i++)
    {
        if (builds[aventureiroId][i] != 0)
        {
            tamanho++;
        }
    }

    AtributoBuild *resultado = tamanho == 0 ? nullptr : new AtributoBuild[tamanho];
    int indice = 0;
    for (int i = 0; i < num_atributos; i++)
    {
        if (builds[aventureiroId][i] != 0)
        {
            resultado[indice++] = AtributoBuild{i, builds[aventureiroId][i]};
        }
    }

    ResultadoBuild consulta = {resultado, tamanho};
    return consulta;
}

ResultadoRecomendacoes Forja::recomendar(
    int aventureiroId,
    int quantidade,
    const MetricaPonderada *metricas,
    int numMetricas)
{
    getAventureiro(aventureiroId);
    if (quantidade < 0 || numMetricas < 0 || (numMetricas > 0 && metricas == nullptr))
    {
        throw std::invalid_argument("Parametros de recomendacao invalidos.");
    }
    for (int i = 0; i < numMetricas; i++)
    {
        if (metricas[i].peso <= 0.0 ||
            (metricas[i].metrica != Metrica::PODER &&
             metricas[i].metrica != Metrica::EQUILIBRIO &&
             metricas[i].metrica != Metrica::SINERGIA))
        {
            throw std::invalid_argument("Metrica ou peso de recomendacao invalido.");
        }
    }

    long long *pontuacoes = nullptr;
    double *buildDensa = nullptr;
    ValorMetrica *ranking = nullptr;
    PontuacaoCentesimos *candidatos = nullptr;
    ItemRecomendado *resultado = nullptr;
    int tamanho = 0;
    try
    {
        pontuacoes = num_itens == 0 ? nullptr : new long long[num_itens];
        buildDensa = num_atributos == 0 ? nullptr : new double[num_atributos];
        ranking = num_itens == 0 ? nullptr : new ValorMetrica[num_itens];
        candidatos = num_itens == 0 ? nullptr : new PontuacaoCentesimos[num_itens];

        for (int itemId = 0; itemId < num_itens; itemId++)
        {
            pontuacoes[itemId] = 0;
        }
        for (int atributoId = 0; atributoId < num_atributos; atributoId++)
        {
            buildDensa[atributoId] = static_cast<double>(builds[aventureiroId][atributoId]);
        }

        for (int indiceMetrica = 0; indiceMetrica < numMetricas; indiceMetrica++)
        {
            const MetricaPonderada &metrica = metricas[indiceMetrica];
            for (int itemId = 0; itemId < num_itens; itemId++)
            {
                double valor;
                switch (metrica.metrica)
                {
                case Metrica::PODER:
                    valor = catalogo.calcularPoder(itemId);
                    break;
                case Metrica::EQUILIBRIO:
                    valor = catalogo.calcularEquilibrio(itemId);
                    break;
                case Metrica::SINERGIA:
                    valor = catalogo.produtoInterno(itemId, buildDensa);
                    break;
                default:
                    throw std::invalid_argument("Metrica de recomendacao desconhecida.");
                }
                ranking[itemId] = ValorMetrica{itemId, arredondarSeisCasas(valor)};
            }
            ordenar(ranking, num_itens);

            long long pesoEmCentesimos = static_cast<long long>(
                std::round(metrica.peso * 100.0));
            for (int posicao = 0; posicao < num_itens; posicao++)
            {
                pontuacoes[ranking[posicao].itemId] +=
                    static_cast<long long>(num_itens - posicao) * pesoEmCentesimos;
            }
        }

        int numCandidatos = 0;
        for (int itemId = 0; itemId < num_itens; itemId++)
        {
            if (itens_equipados[aventureiroId][itemId] == 0)
            {
                candidatos[numCandidatos++] = PontuacaoCentesimos{itemId, pontuacoes[itemId]};
            }
        }
        ordenar(candidatos, numCandidatos);

        tamanho = quantidade < numCandidatos ? quantidade : numCandidatos;
        resultado = tamanho == 0 ? nullptr : new ItemRecomendado[tamanho];
        for (int i = 0; i < tamanho; i++)
        {
            resultado[i] = ItemRecomendado{
                candidatos[i].itemId,
                static_cast<double>(candidatos[i].valor) / 100.0};
        }
    }
    catch (...)
    {
        delete[] pontuacoes;
        delete[] buildDensa;
        delete[] ranking;
        delete[] candidatos;
        delete[] resultado;
        throw;
    }

    delete[] pontuacoes;
    delete[] buildDensa;
    delete[] ranking;
    delete[] candidatos;

    ResultadoRecomendacoes consulta = {resultado, tamanho};
    return consulta;
}

void Forja::atualizarBuild(int aventureiroId, int itemId, int quantidade)
{
    int *atributosItem = nullptr;
    int *modificadores = nullptr;
    int tamanho = catalogo.getLinhaItem(itemId, atributosItem, modificadores);

    for (int i = 0; i < tamanho; i++)
    {
        builds[aventureiroId][atributosItem[i]] +=
            static_cast<long long>(quantidade) * modificadores[i];
    }
    delete[] atributosItem;
    delete[] modificadores;
}
