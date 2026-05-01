#pragma once

#include <list>
#include <cassert>
#include <unordered_map>
#include <vector>

namespace pc2 {

  inline void imprimirLista(const std::list<int>& lista);

struct Consulta {
  int tipo;
  int x;
  int y;
};

inline std::vector<int> resolverInsertarOBorrar(
    const std::vector<int>& secuencia_inicial,
    const std::vector<Consulta>& consultas) {
  std::list<int> lista_numeros;
  std::unordered_map<int, std::list<int>::iterator> posicion;

  for (int numero : secuencia_inicial) {
    lista_numeros.push_back(numero);
    auto it = lista_numeros.end();
    --it;
    posicion[numero] = it;
  }

  for (const Consulta& consulta : consultas) {
    if (consulta.tipo == 1) {
      assert(posicion.find(consulta.x) != posicion.end());
      auto it_existente = posicion.find(consulta.x);
      auto it_nuevo =
          lista_numeros.insert(std::next(it_existente->second), consulta.y);
      posicion[consulta.y] = it_nuevo;
      std::cout << "Insertar " << consulta.y << " despues de " << consulta.x << ": ";
      imprimirLista(lista_numeros);
    } else {
      assert(posicion.find(consulta.x) != posicion.end());
      auto it_existente = posicion.find(consulta.x);
      lista_numeros.erase(it_existente->second);
      posicion.erase(it_existente);
      std::cout << "Despues de borrar " << consulta.x << ": ";
      imprimirLista(lista_numeros);
    }
  }

  std::vector<int> resultado;
  resultado.reserve(lista_numeros.size());

  for (int numero : lista_numeros) {
    resultado.push_back(numero);
  }

  return resultado;
}

inline void imprimirLista(const std::list<int>& lista){
  std::cout << "{";
  bool primero = true;
  for (int valor : lista){
    if (!primero) std::cout << ", ";
    std::cout << valor;
    primero = false;
  }
  std::cout << "}" << std::endl;
}

}  // namespace pc2