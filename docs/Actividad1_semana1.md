## Actividad 1 - CC232

### Integrantes

- Marco Antonio Huamani Bonifacio (20232741D)
- Yaimar Alexis Cabello Quevedo (20244712D)

#### Bloque 1

1. **Expliquen con sus palabras la diferencia entre problema, algoritmo, ADT e implementación.**

    - **Problema:** Es básicamente el "qué" queremos resolver. Es la definición teórica donde dejamos claro qué entra (inputs válidos) y qué queremos que salga (outputs esperados), pero sin preocuparnos todavía de cómo lo vamos a lograr. Es la necesidad pura.
    - **Algoritmo:** Aquí ya entramos al "cómo" lógico. Es ese procedimiento abstracto, paso a paso, que nos garantiza que si le damos la entrada del problema, nos devolverá la salida correcta. Es como la receta, pero escrita en papel, independiente de cualquier computadora.
    - **ADT (Tipo de Dato Abstracto):** Es un modelo conceptual que nos dice qué datos vamos a guardar y qué podemos hacer con ellos (las operaciones). Funciona como una "interfaz" o un contrato: te dice qué funciones tienes disponibles, pero te oculta los detalles internos de cómo están guardados los datos.
    - **Implementación:** Es cuando aterrizamos todo lo anterior a la realidad. Es escribir el código real en un lenguaje como C++, lidiando con la sintaxis, la gestión de la memoria del sistema y las limitaciones del hardware. Es la ejecución física del algoritmo y del ADT.

2. **En bubble_sort.cpp, expliquen qué observable conecta correctitud y costo.**

    - El punto de unión aquí es el **conteo de intercambios (swaps) y comparaciones**. Si el arreglo termina ordenado, podemos decir que el algoritmo es correcto (correctitud). Sin embargo, el "costo" no lo vemos en el resultado final, sino en el camino: al contar cuántas veces tuvimos que comparar o mover elementos, podemos medir cuánto esfuerzo le costó a la máquina llegar a ese resultado. Sin esos contadores, sabríamos que el algoritmo funciona, pero no qué tan caro es ejecutarlo.

3. **En power.cpp, expliquen por qué power mejora la idea de una versión ingenua.**

    - La versión ingenua es "fuerza bruta": si quieres calcular $a^n$, multiplicas $a$ por sí misma $n$ veces, lo que te da un costo lineal que crece con cada unidad del exponente. La versión mejorada de `power` es mucho más inteligente porque usa **"divide y vencerás"**. Al dividir el exponente a la mitad en cada paso recursivo, reducimos drásticamente la cantidad de multiplicaciones. Pasamos de un crecimiento lineal a uno logarítmico, lo cual es una mejora de rendimiento brutal cuando el exponente es muy grande.

4. **En fibonacci.cpp, expliquen por qué una función puede ser correcta y aun así ser una mala elección práctica.**

    - Porque la "correctitud" solo te asegura que la respuesta sea la correcta, pero no te dice cuánto tiempo vas a esperar por ella. La versión recursiva pura de Fibonacci es matemáticamente perfecta y correcta, pero en la práctica es un desastre para números grandes. Esto pasa porque "no tiene memoria" y recalcula los mismos subproblemas miles de veces (creando un árbol de llamadas redundantes). El tiempo de ejecución crece de forma exponencial, haciendo que algo simple se vuelva inmanejable en una computadora real.

5. **En count_ones.cpp, expliquen por qué el tamaño de entrada no siempre coincide con el valor numérico.**

    - En este contexto de bits, lo que nos importa no es qué tan "grande" se vea el número en base 10, sino su estructura binaria. El tamaño del problema aquí se mide por los **bits encendidos (unos)** o por la cantidad de bits totales que lo representan. Por ejemplo, el número $2^{30}$ es enorme en valor numérico, pero en binario es solo un "1" seguido de ceros; un algoritmo eficiente lo resolvería en una sola operación, demostrando que el costo depende de la representación binaria y no de la magnitud decimal.

6. **En demo_adt_secuencia.cpp, expliquen por qué la misma interfaz puede convivir con representaciones distintas.**

    - Esto es gracias al concepto de encapsulamiento. La interfaz actúa como un **contrato fijo**: el usuario sabe que puede llamar a funciones como `insertar()` o `eliminar()`. Lo que pase "detrás de cámaras" (si usamos un arreglo estático, una lista enlazada o memoria dinámica) no debería importarle al usuario mientras el contrato se cumpla. Esto nos da la libertad de cambiar la estructura interna para optimizar el rendimiento sin que el resto del programa deje de funcionar.

#### Bloque 2

**Tabla de Demos**

| Archivo | Salida u observable importante | Idea algorítmica | Argumento de costo |
| :--- | :--- | :--- | :--- |
| `demo_bubblesort.cpp` | Contador de comparaciones y swaps realizados. | Ordenar moviendo repetidamente el elemento más pesado al final mediante intercambios adyacentes. | El esfuerzo crece de forma cuadrática $O(n^2)$. Si duplicas los datos, el trabajo se cuadruplica. |
| `demo_power.cpp` | Total de multiplicaciones o profundidad de la recursión. | Exponenciación rápida dividiendo el exponente a la mitad en cada paso. | Costo logarítmico $O(\log n)$. Es extremadamente eficiente, incluso para exponentes gigantescos. |
| `demo_fibonacci.cpp` | Tiempo de ejecución total y número de llamadas recursivas. | Cálculo de la serie mediante recursión simple o métodos iterativos. | La recursión ingenua tiene un costo exponencial $O(2^n)$, mientras que la iterativa es lineal $O(n)$. |
| `demo_countones.cpp` | Número de iteraciones del bucle frente a los bits del número. | Algoritmo de Brian Kernighan para "apagar" el bit más a la derecha en cada paso. | El costo es $O(k)$, donde $k$ es la cantidad de bits en '1', siendo independiente del valor total del número. |

**Respuestas a las preguntas**

1. **En demo_bubblesort.cpp, ¿qué salida sirve para defender costo y no solo resultado?**
   - Lo que realmente defiende el costo es el **conteo de operaciones (comparaciones e intercambios)**. Ver el arreglo ordenado al final es solo la prueba de que el algoritmo no falló, pero ver que para un arreglo de 10 elementos se hicieron 45 comparaciones es lo que nos permite hablar científicamente sobre su complejidad y eficiencia.

2. **En demo_power.cpp, ¿qué comparación concreta muestra una mejora algorítmica?**
   - La diferencia se nota al comparar la cantidad de multiplicaciones realizadas. Mientras la versión ingenua va paso a paso (si el exponente es 1000, hace 1000 multiplicaciones), la versión con "divide y vencerás" lo resuelve en aproximadamente 10 pasos. Esa reducción de 1000 a 10 es la prueba irrefutable de una mejora algorítmica real.

3. **En demo_fibonacci.cpp, ¿qué crecimiento se vuelve defendible?**
   - El crecimiento **lineal** es el único defendible para aplicaciones reales. En la demo se nota que mientras la recursión explota en tiempo (crecimiento exponencial) y hace que la PC sufra con valores pequeños como $n=45$, la versión lineal (iterativa) termina instantáneamente, demostrando ser la opción lógica para escalar el problema.

4. **En demo_countones.cpp, ¿qué ejemplo ayuda más a distinguir valor numérico de tamaño en bits?**
   - El ejemplo perfecto es comparar una potencia de 2, como 1024, con el número 7. Aunque 1024 es mucho mayor en valor, el algoritmo solo hace **una iteración** porque solo tiene un bit encendido. En cambio, con el 7 (que es 111 en binario), hace **tres iteraciones**. Esto deja claro que el trabajo del algoritmo está ligado a la estructura de bits y no a qué tan grande sea el número en la recta numérica.

#### Bloque 3

1. **¿Qué funciones o ideas están verificando las pruebas públicas?**
   - Principalmente verifican la **correctitud funcional**. Se aseguran de que los algoritmos de ordenamiento, potencias, Fibonacci y conteo de bits devuelvan los valores esperados para un set de datos de prueba. Buscan confirmar que hayamos manejado bien la lógica básica y los casos especiales (como exponentes 0 o arreglos vacíos) antes de pasar a pruebas más complejas.

2. **¿Qué sí demuestra una prueba pública?**
   - Demuestra que tu código "pasa el filtro" para los casos que los profesores consideraron esenciales. Es una evidencia de que la lógica básica es correcta para los ejemplos proporcionados y que la estructura de tu programa es compatible con lo solicitado.

3. **¿Qué no demuestra una prueba pública?**
   - No es una garantía de perfección total. No demuestra que el código sea eficiente (podría ser muy lento y pasar la prueba si no hay límite de tiempo) ni garantiza que no vaya a fallar con entradas raras o extremas que no estaban en el archivo de pruebas original. Pasar el test público no significa que el algoritmo sea óptimo, solo que funciona para esos casos.

4. **Elijan una pregunta de preguntas_semana1.md y respóndanla bien.**
   - **Pregunta 55:** *Explica por qué power(a, n) puede ser mejor que una versión ingenua como powerBF(a, n).*
   - **Respuesta:** La gran diferencia radica en la estrategia. La versión ingenua (`powerBF`) es lineal ($O(n)$): si quieres calcular $2^{64}$, haces 64 multiplicaciones. En cambio, `power` usa la propiedad $(a^{n/2})^2$. Esto permite que en cada paso el problema se reduzca a la mitad. Para $2^{64}$, solo necesitarías unas 6 o 7 multiplicaciones. A nivel computacional, pasar de un esfuerzo que crece con $n$ a uno que crece con $\log n$ es la diferencia entre un programa que escala y uno que se vuelve lento innecesariamente.

5. **Usen la rúbrica para autoevaluarse en:**
   - **Comprensión conceptual:** **Logrado.** Tenemos claro que un algoritmo es la lógica, el ADT es el modelo y la implementación es el código final.
   - **Sustentación de correctitud:** **Logrado.** Entendemos que no basta con que "salga el número", sino que hay que validar que el algoritmo progresa hacia el caso base y maneja los estados correctamente.
   - **Análisis de eficiencia:** **Logrado.** Identificamos las diferencias críticas entre costos constantes, lineales, logarítmicos y el peligroso costo exponencial.

#### Bloque 4

1. **¿Qué diferencia observable deja demo_const_refs.cpp entre lectura, modificación y copia?**
   - Lectura: Usa referencia constante (const &). No altera el estado del original ni gasta memoria extra creando copias.
   - Modificación: Trabaja directamente en la dirección de memoria del objeto original. El cambio se aplica ahí mismo.
   - Copia: Asigna una nueva dirección de memoria para un objeto totalmente nuevo. El estado del original se queda intacto.

2. **En bench_vector_growth.cpp, ¿qué cambia con reserve?**
   - Sin reserve: El vector debe realizar costosas reasignaciones dinámicas cuando se queda sin capacidad (pide nueva memoria, copia los datos y borra la anterior) .Con reserve: Se pre-asigna toda la memoria necesaria en un solo bloque desde el inicio. Esto elimina las reasignaciones y hace que la inserción de datos sea significativamente más rápida.

3. **En bench_vector_ops.cpp, ¿por qué push_back, insert(begin()) e insert(middle) no cuestan lo mismo?**

   - La diferencia de costos radica en el desplazamiento de elementos en la memoria contigua: , por ejemplo push_back tiene un costo de $O(1)$ porque solo añade el elemento al final del bloque sin mover los otros , insert(begin()) cuesta $O(n)$ porque obliga a desplazar absolutamente todos los elementos una posición hacia la derecha y insert(middle) tiene un costo intermedio, ya que solo es necesario desplazar la mitad de los elementos.

4. **En bench_cache_effects.cpp, ¿qué intuición deja sobre localidad de memoria?**

   - El benchmark evidencia la importancia de la localidad espacial. El recorrido secuencial de un vector es muy rápido porque sus datos están contiguos, lo que permite que la memoria caché del procesador los precargue eficientemente. En contraste, el acceso aleatorio y las listas (std::list) son lentos porque acceden a direcciones de memoria dispersas, provocando constantes fallos en la caché.

#### Bloque 5

1. **Según Ejercicios0.md, ¿cuál es el orden correcto antes de optimizar?**

   - Primero, elegir bien el algoritmo.
    Segundo, verificar que el programa sea correcto.
    Tercero, medir el rendimiento.
    Cuarto y último, explorar optimizaciones más avanzadas del compilador.

2. **¿Qué quiere mostrar stl_optimizacion_demostracion.cpp con reserve, nth_element, partial_sort y lower_bound?**

   - El código demuestra que elegir el algoritmo correcto de la STL (Standard Template Library) tiene mayor impacto en el rendimiento que   realizar microajustes manuales. 
    reserve: Reduce las costosas realocaciones de memoria y copias de elementos.
    nth_element y partial_sort: Optimizan la obtención de medianas o Top-K, evitando el alto costo computacional de ordenar todo el arreglo.
    lower_bound: Permite realizar consultas en tiempo logarítmico aprovechando la excelente localidad de memoria de un vector previamente ordenado.

3. **¿Qué tipo de evidencia puede producir resolver_ejercicios0_v4.2.sh?**

    - Archivos ejecutables, archivos de salida estándar (.out / .stdout.txt) y de error (.err / .stderr.txt).
    Logs detallados de la compilación (.compile.log) que registran warnings e iteraciones del compilador.
    Un reporte estructurado en formato Markdown (reporte_ejercicios0.md) que tabula métricas clave como el tiempo de ejecución en segundos, el tamaño del binario en bytes y los códigos de estado de salida.

4. **¿Qué limitaciones de entorno menciona INSTRUCCIONES_Ejercicios0_v4.2.md?**

    Las herramientas de desinfección (ASan, UBSan o TSan) pueden presentar fallos al momento de enlazar (linkear).
    La herramienta de cobertura gcov puede necesitar configuraciones adicionales según el sistema.
    La herramienta de profiling gprof suele fallar o ser incapaz de generar perfiles de rendimiento útiles en estos entornos.

5. **¿Por qué esta parte no reemplaza la discusión de correctitud de Semana1?**

   - Porque la correctitud lógica de un programa es un prerrequisito innegociable antes de aplicar cualquier optimización. El documento es explícito al advertir que los flags de optimización agresiva (como -O3) y el uso de funciones avanzadas de la STL no sustituyen la necesidad de "una prueba bien hecha". Un algoritmo que se ejecuta extremadamente rápido, pero arroja resultados incorrectos, carece de validez.

#### Bloque 6

**¿Qué cambia cuando pasamos de defender correctitud básica en Semana1 a comparar implementaciones con evidencia experimental?**

     - Al pasar a la evidencia experimental, la especificación se vuelve más estricta porque el código debe prepararse para integrarse con herramientas de medición y benchmarks. La correctitud deja de ser la meta final y pasa a ser un requisito mínimo, ya que de nada sirve que el código vuele si bota un resultado incorrecto. En cuanto al costo, pasamos de contar operaciones teóricas a medir microsegundos reales, donde nos damos cuenta de que la representación en memoria importa muchísimo; por ejemplo, tener datos contiguos le facilita la vida a la memoria caché y acelera el programa más que cualquier truco lógico manual. Por último, queda una advertencia metodológica clave: medir tiempos en una PC es engañoso por el ruido del sistema operativo, así que siempre hay que mantener constantes las variables y repetir las pruebas varias veces para obtener promedios confiables.

#### Autoevaluación breve

- **Qué podemos defender con seguridad:** La diferencia entre eficiencia y correctitud, y por qué los algoritmos de "divide y vencerás" son superiores a la fuerza bruta.
- **Qué todavía confundimos:** A veces la implementación exacta de ciertos ADTs complejos en C++ puede ser retadora por la sintaxis de punteros.
- **Qué evidencia usaríamos en una sustentación:** Los contadores de operaciones y las gráficas de tiempo de ejecución de las demos, ya que muestran el comportamiento real del código frente al crecimiento de $n$.