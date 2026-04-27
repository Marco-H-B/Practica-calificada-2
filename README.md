# PC2 - CC232

## Estudiante

- Nombre: Marco Antonio Huamani Bonifacio
- Código: 20232741D
- Problema: [AtCoder ABC344 E - Insertor Erase](https://atcoder.jp/contests/abc344/tasks/abc344_e)

### Referencia oficial

- Archivo de asignación: [Problemas-Evaluacion2.csv](https://github.com/kapumota/CC-232/blob/main/Practicas/Practica2_CC232/Problemas-Evaluacion2.csv)

### Tema principal

- Semana: 4
- Estructura o técnica principal: Lista doble + mapa de valor a nodo (iterador)

### Resumen de la solución

- Mantengo la secuencia en una lista doble para poder insertar después de un elemento y borrar un elemento en tiempo constante local.

- Guardo en un mapa la posición de cada valor dentro de la lista.

- Las consultas de insertar y borrar se resuelven en tiempo O(1) promedio.

### Complejidad

- Tiempo: O(N + Q) promedio
- Espacio: O(N)

### Invariante o idea clave

- Cada valor que existe tiene una entrada en el mapa.
- El iterador que esta en el mapa siempre va al nodo correcto dentro de la lista.
- Después de la consulta, la secuencia sigue con valores diferentes.

### Archivos relevantes

- include/
- src/
- tests/
- Ejercicio/
- demos/
- resultados/
- benchmark/
- docs/
- video/

### Compilación

cmake -S . -B build
cmake --build build

### Ejecución

./build/pc2_main

### Pruebas

ctest --test-dir build --output-on-failure

### Casos de prueba

1. Caso base: Como esta en el enunciado.
2. Caso : Borrar y volver a insertar cerca del inicio y final.
3. Caso extremo: N y Q cercamos a 2e5.

### Historial de commits

- 'Completo la plantilla del  README, agrego mis restricciones al .gitignore y tambien subo el ejercicio'
- 'Creo el CMake, los esqueleetos de main.cpp y test_samples.cpp'
- 'Completo la solucion del problema con lista doble y mapa'
- 'Agrego las actividades 1, 2 y 3'

### Declaración de autoría

Declaro que entiendo el código entregado, que puedo explicarlo, compilarlo, ejecutarlo y modificarlo sin ayuda externa durante la grabación.

### Demos

- Ejemplo de demostración y script en la carpeta `demos/`.
- Ejecutar el ejemplo:

```bash
chmod +x demos/run_example.sh
./demos/run_example.sh
```

El script compilará el proyecto y ejecutará `pc2_main` usando `demos/input1.txt`.

### Resultados

- Salidas de ejecución y resultados de pruebas guardados en `resultados/`.
- Archivos incluidos:
	- `resultados/output1.txt` : salida esperada para el demo.
	- `resultados/output1_run.txt` : salida real producida por el ejecutable en el demo.
	- `resultados/ctest_output.txt` : salida de `ctest` con resultados de tests.

Estos archivos sirven como evidencia de compilación y ejecución para el video.
