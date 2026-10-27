#include "../include/forja.hpp"

#include <iomanip>
#include <iostream>
#include <string>

int main()
{
    std::string comando;
    char modo;

    if (!(std::cin >> comando) || comando != "E" || !(std::cin >> modo))
    {
        return 0;
    }

    Forja forja(modo);
    std::cout << "E " << modo << '\n';

    while (std::cin >> comando)
    {
        if (comando == "E")
        {
            std::cin >> modo;
            forja.alterarModo(modo);
            std::cout << "E " << modo << '\n';
        }
        else if (comando == "A")
        {
            std::string nome;
            std::cin >> nome;
            std::cout << "A " << forja.cadastrarAtributo(nome) << '\n';
        }
        else if (comando == "I")
        {
            std::string nome;
            std::cin >> nome;
            std::cout << "I " << forja.cadastrarItem(nome) << '\n';
        }
        else if (comando == "M")
        {
            int itemId;
            int atributoId;
            int valor;
            std::cin >> itemId >> atributoId >> valor;
            forja.definirModificador(itemId, atributoId, valor);
            std::cout << "M " << forja.getItem(itemId).nome << ' '
                      << forja.getAtributo(atributoId).nome << ' '
                      << valor << '\n';
        }
        else if (comando == "H")
        {
            std::string nome;
            std::cin >> nome;
            std::cout << "H " << forja.cadastrarAventureiro(nome) << '\n';
        }
        else if (comando == "F")
        {
            int aventureiroId;
            int itemId;
            std::cin >> aventureiroId >> itemId;
            std::cout << "F " << forja.encomendar(aventureiroId, itemId) << '\n';
        }
        else if (comando == "Z")
        {
            int turnos;
            std::cin >> turnos;
            ResultadoEncomendas resultado = forja.trabalhar(turnos);
            std::cout << "Z " << resultado.tamanho << '\n';

            if (resultado.tamanho > 0)
            {
                for (int i = 0; i < resultado.tamanho; i++)
                {
                    if (i > 0)
                    {
                        std::cout << ' ';
                    }
                    std::cout << "encomenda_" << i + 1 << ' '
                              << resultado.elementos[i].aventureiro_id << ' '
                              << resultado.elementos[i].item_id;
                }
                std::cout << '\n';
            }

            delete[] resultado.elementos;
        }
        else if (comando == "D")
        {
            int aventureiroId;
            std::cin >> aventureiroId;
            int itemId;
            bool removeu = forja.desequipar(aventureiroId, itemId);
            std::cout << "D " << forja.getAventureiro(aventureiroId).getNome()
                      << ' ';
            if (removeu)
            {
                std::cout << forja.getItem(itemId).nome;
            }
            else
            {
                std::cout << "VAZIO";
            }
            std::cout << '\n';
        }
        else if (comando == "LI")
        {
            int itemId;
            std::cin >> itemId;
            ResultadoModificadores resultado = forja.consultarItem(itemId);
            std::cout << "LI " << forja.getItem(itemId).nome;
            if (resultado.tamanho == 0)
            {
                std::cout << " VAZIO";
            }
            else
            {
                for (int i = 0; i < resultado.tamanho; i++)
                {
                    std::cout << " atributo_" << i + 1 << ' '
                              << resultado.elementos[i].id << ' '
                              << resultado.elementos[i].valor;
                }
            }
            std::cout << '\n';
            delete[] resultado.elementos;
        }
        else if (comando == "LA")
        {
            int atributoId;
            std::cin >> atributoId;
            ResultadoModificadores resultado = forja.consultarAtributo(atributoId);
            std::cout << "LA " << forja.getAtributo(atributoId).nome;
            if (resultado.tamanho == 0)
            {
                std::cout << " VAZIO";
            }
            else
            {
                for (int i = 0; i < resultado.tamanho; i++)
                {
                    std::cout << " item_" << i + 1 << ' '
                              << resultado.elementos[i].id << ' '
                              << resultado.elementos[i].valor;
                }
            }
            std::cout << '\n';
            delete[] resultado.elementos;
        }
        else if (comando == "LH")
        {
            int aventureiroId;
            std::cin >> aventureiroId;
            ResultadoBuild resultado = forja.consultarBuild(aventureiroId);
            std::cout << "LH " << forja.getAventureiro(aventureiroId).getNome();
            if (resultado.tamanho == 0)
            {
                std::cout << " VAZIO";
            }
            else
            {
                for (int i = 0; i < resultado.tamanho; i++)
                {
                    std::cout << " atributo_" << i + 1 << ' '
                              << resultado.elementos[i].id << ' '
                              << resultado.elementos[i].total;
                }
            }
            std::cout << '\n';
            delete[] resultado.elementos;
        }
        else if (comando == "Q")
        {
            int aventureiroId;
            int quantidade;
            int numMetricas;
            std::cin >> aventureiroId >> quantidade >> numMetricas;

            MetricaPonderada *metricas = new MetricaPonderada[numMetricas];
            for (int i = 0; i < numMetricas; i++)
            {
                std::string nomeMetrica;
                double peso;
                std::cin >> nomeMetrica >> peso;

                Metrica metrica = Metrica::PODER;
                if (nomeMetrica == "EQUILIBRIO")
                {
                    metrica = Metrica::EQUILIBRIO;
                }
                else if (nomeMetrica == "SINERGIA")
                {
                    metrica = Metrica::SINERGIA;
                }
                metricas[i] = MetricaPonderada{metrica, peso};
            }

            ResultadoRecomendacoes resultado =
                forja.recomendar(aventureiroId, quantidade, metricas, numMetricas);
            delete[] metricas;

            for (int i = 0; i < resultado.tamanho; i++)
            {
                std::cout << "Q " << i + 1 << ' '
                          << resultado.elementos[i].itemId << ' '
                          << std::fixed << std::setprecision(2)
                          << resultado.elementos[i].pontuacao << '\n';
            }

            delete[] resultado.elementos;
        }
    }

    return 0;
}
