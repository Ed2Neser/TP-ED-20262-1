#include "aventureiro.hpp"
#include "catalogo.hpp"

Aventureiro::Aventureiro(int id, std::string nome, bool usarModoImediato)
    : id(id), nome(nome), build(), vetor_build_imediato(nullptr), capacidade_atributos(0), modo_imediato(usarModoImediato)
{
}

Aventureiro::~Aventureiro()
{
    delete[] vetor_build_imediato;
}

void Aventureiro::redimensionarVetorBuild() // dobra o tamanho do vetor denso
{
    int novoTamanho = capacidade_atributos == 0 ? 1 : capacidade_atributos * 2;
    int *novoVetor = new int[novoTamanho]();

    // Copia os valores antigos para o novo vetor
    for (int i = 0; i < capacidade_atributos; ++i)
    {
        novoVetor[i] = vetor_build_imediato[i];
    }

    // Libera a memória do vetor antigo
    delete[] vetor_build_imediato;

    // Atualiza o ponteiro e a capacidade
    vetor_build_imediato = novoVetor;
    capacidade_atributos = novoTamanho;
}

int Aventureiro::getId()
{
    return id;
}

std::string Aventureiro::getNome()
{
    return nome;
}

Pilha &Aventureiro::getBuild()
{
    return build;
}

int *Aventureiro::getVetorBuildImediato()
{
    return vetor_build_imediato;
}

// estrategia (para testes) de build sob demanda (custo de consulta  O(n))
int *Aventureiro::computarBuildSobDemanda(Catalogo *catalogo, int numAtributosCadastrados)
{
    // Implementação da computação da build sob demanda
    return nullptr;
}