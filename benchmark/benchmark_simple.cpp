#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include "InsertOrErase.h"

int main() {
  using reloj = std::chrono::steady_clock;
  // Caso pequeño
  int n = 10000;
  int q = 10000;

  std::vector<int> secuencia;
  secuencia.reserve(n);
  for (int i = 1; i <= n; ++i) secuencia.push_back(i);

  std::vector<pc2::Consulta> consultas;
  consultas.reserve(q);

  // generador simple para operaciones (esto es didáctico)
  std::mt19937 rng(12345);
  std::uniform_int_distribution<int> dist_tipo(1, 2);
  std::uniform_int_distribution<int> dist_pos(1, n);

  for (int i = 0; i < q; ++i) {
    int tipo = dist_tipo(rng);
    int x = dist_pos(rng);
    if (tipo == 1) {
      int y = n + i + 1;  // nuevos valores
      consultas.push_back({tipo, x, y});
    } else {
      consultas.push_back({tipo, x, 0});
    }
  }

  auto inicio = reloj::now();
  std::vector<int> resultado =
      pc2::resolverInsertarOAumentar(secuencia, consultas);
  auto fin = reloj::now();

  auto dur_ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio)
          .count();

  std::cout << "Tiempo total (ms): " << dur_ms << "\n";
  std::cout << "Tamaño resultado: " << resultado.size() << "\n";
  return 0;
}