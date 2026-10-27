
#include "vetor_tripletas.hpp"

VetorTripletas::VetorTripletas(int numItens, int numAtributos) {}

VetorTripletas::~VetorTripletas() {}

void VetorTripletas::adicionar(Tripleta tripletas) {}
void VetorTripletas::remover(Tripleta tripletas) {}

int VetorTripletas::getModificador(int id_item, int id_atributo) {}

int VetorTripletas::getTamanho() {}
int VetorTripletas::getCapacidade() {}

void VetorTripletas::redimensionar() {}
void VetorTripletas::ordenarPorItem() {}
void VetorTripletas::ordenarPorAtributo() {}

int VetorTripletas::getLinhaItem(int item, int *&atributos, int *&modificadores) {}
int VetorTripletas::getColunaAtributo(int atributo, int *&itens, int *&modificadores) {}

double VetorTripletas::calcularPoder(int item) {}
double VetorTripletas::calcularEquilibrio(int item, double poder) {}
double VetorTripletas::produtoInterno(int item, double *vetor_build, int numAtributosCadastrados) {}

Tripleta VetorTripletas::*begin() {}
Tripleta VetorTripletas::*end() {}
