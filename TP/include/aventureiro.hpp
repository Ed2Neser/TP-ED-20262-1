#ifndef AVENTUREIRO_HPP
#define AVENTUREIRO_HPP
#include <string>
#include "pilha.hpp"

class Catalogo;

class Aventureiro // Classe que representa um aventureiro.
{
private:
    int id;
    std::string nome;

    Pilha build; // armazena ids dos itens da build

    // estrategia (para testes) imediata (custo de consulta O(1)) para build
    int *vetor_build_imediato;      // Array que mantém as somas sempre atualizadas
    int capacidade_atributos;       // Tamanho atual alocado para o vetor denso
    bool modo_imediato;             // Define se a instância usa a estratégia imediata
    void redimensionarVetorBuild(); // dobra o tamanho do vetor denso

public:
    // construtor recebe a flag para decidir o modo de operação do experimento
    Aventureiro(int id, std::string nome, bool usarModoImediato);
    ~Aventureiro();

    int getId();
    std::string getNome();
    Pilha &getBuild();

    void equiparItem(int itemId, int multiplicador); // adiciona o item à build e atualiza o vetor denso
    void desequiparItem();                           // remove o ultimo item da build e atualiza o vetor denso
    // essas funções tem efeitos adicionais no modo imediato e no modo sob demanda, mas a interface é a mesma

    int getAtributoImediato(int atributoId); // retorna o valor do atributo no vetor denso

    // Retorna o ponteiro direto para o vetor que já está atualizado em memória (custo O(1))
    int *getVetorBuildImediato();

    // estrategia (para testes) de build sob demanda (custo de consulta  O(n))
    int *computarBuildSobDemanda(Catalogo *catalogo, int numAtributosCadastrados);
};
#endif
