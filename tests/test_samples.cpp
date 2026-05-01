#include <cassert>
#include <iostream>
#include <vector>

#include "InsertOrErase.h"

int main() {
  {
    std::vector<int> secuencia_inicial = {2, 1, 4, 3};
    std::vector<pc2::Consulta> consultas = {
        {2, 1, 0}, {1, 4, 5}, {2, 2, 0}, {1, 5, 1}};

    std::vector<int> esperado = {4, 5, 1, 3};
    std::vector<int> obtenido =
        pc2::resolverInsertarOBorrar(secuencia_inicial, consultas);

    assert(obtenido == esperado);
  }
  {
    std::vector<int> secuencia_inicial2 = {3, 1, 4, 5, 9, 2};
    std::vector<pc2::Consulta> consultas2 = {{2, 5, 0}, {1, 3, 5}, {1, 9, 7},
                                             {2, 9, 0}, {2, 3, 0}, {1, 2, 3},
                                             {2, 4, 0}};

    std::vector<int> esperado2 = {5, 1, 7, 2, 3};
    std::vector<int> obtenido2 =
        pc2::resolverInsertarOBorrar(secuencia_inicial2, consultas2);

    assert(obtenido2 == esperado2);
  }
  std::cout << "Pruebas simples listas\n";
  return 0;
}