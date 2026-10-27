#ifndef FORJA_HPP
#define FORJA_HPP

#include "atributo.hpp"
#include "aventureiro.hpp"
#include "catalogo.hpp"
#include "fila.hpp"
#include "item.hpp"

#include <string>

enum class Metrica
{
    PODER,
    EQUILIBRIO,
    SINERGIA
};

struct MetricaPonderada
{
    Metrica metrica;
    double peso;
};

struct ItemRecomendado
{
    int itemId;
    double pontuacao;
};

struct ResultadoEncomendas
{
    // nao esquecer que devem ser liberados com delete[] pelo chamador
    Encomenda *elementos;
    int tamanho;
};

struct ModificadorConsulta
{
    int id;
    int valor;
};

struct ResultadoModificadores
{
    // nao esquecer que devem ser liberados com delete[] pelo chamador
    ModificadorConsulta *elementos;
    int tamanho;
};

struct AtributoBuild
{
    int id;
    long long total;
};

struct ResultadoBuild
{
    // nao esquecer que devem ser liberados com delete[] pelo chamador
    AtributoBuild *elementos;
    int tamanho;
};

struct ResultadoRecomendacoes
{
    // nao esquecer que devem ser liberados com delete[] pelo chamador
    ItemRecomendado *elementos;
    int tamanho;
};

class Forja
{
private:
    Atributo *atributos;
    int num_atributos;
    int capacidade_atributos;

    Item *itens;
    int num_itens;
    int capacidade_itens;

    Aventureiro **aventureiros;
    long long **builds;
    int **itens_equipados;
    int num_aventureiros;
    int capacidade_aventureiros;

    Catalogo catalogo;
    Fila fila;

    void atualizarBuild(int aventureiroId, int itemId, int quantidade);

public:
    explicit Forja(char modoInicial);
    ~Forja();

    Forja(const Forja &) = delete;
    Forja &operator=(const Forja &) = delete;

    int cadastrarAtributo(const std::string &nome);
    int cadastrarItem(const std::string &nome);
    int cadastrarAventureiro(const std::string &nome);

    void definirModificador(int itemId, int atributoId, int valor);
    int encomendar(int aventureiroId, int itemId);
    ResultadoEncomendas trabalhar(int turnos);
    bool desequipar(int aventureiroId, int &itemId);
    void alterarModo(char novoModo);

    const Atributo &getAtributo(int atributoId) const;
    const Item &getItem(int itemId) const;
    Aventureiro &getAventureiro(int aventureiroId);
    const Aventureiro &getAventureiro(int aventureiroId) const;

    int getNumAtributos() const;
    int getNumItens() const;
    int getNumAventureiros() const;

    ResultadoModificadores consultarItem(int itemId);
    ResultadoModificadores consultarAtributo(int atributoId);
    ResultadoBuild consultarBuild(int aventureiroId) const;
    ResultadoRecomendacoes recomendar(
        int aventureiroId,
        int quantidade,
        const MetricaPonderada *metricas,
        int numMetricas);
};

#endif
