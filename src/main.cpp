#include <iostream>
#include <vector>

#include "InsertOrErase.h"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int cantidad_inicial;
  std::cin >> cantidad_inicial;

  std::vector<int> secuencia_inicial(cantidad_inicial);
  for (int i = 0; i < cantidad_inicial; ++i) {
    std::cin >> secuencia_inicial[i];
  }

  int cantidad_consultas;
  std::cin >> cantidad_consultas;

  std::vector<pc2::Consulta> consultas;
  consultas.reserve(cantidad_consultas);

  for (int i = 0; i < cantidad_consultas; ++i) {
    int tipo;
    std::cin >> tipo;

    if (tipo == 1) {
      int x;
      int y;
      std::cin >> x >> y;
      consultas.push_back({tipo, x, y});
    } else {
      int x;
      std::cin >> x;
      consultas.push_back({tipo, x, 0});
    }
  }

  std::vector<int> respuesta =
      pc2::resolverInsertarOAumentar(secuencia_inicial, consultas);

  for (int i = 0; i < static_cast<int>(respuesta.size()); ++i) {
    if (i > 0) {
      std::cout << ' ';
    }
    std::cout << respuesta[i];
  }
  std::cout << '\n';
  return 0;
}