# Actividad 2-CC232

## Integrantes

- Marco Antonio Huamani Bonifacio - 20232741D
- Cabello Quevedo Yaimar Alexis - 20244712D

## Bloque 1: Núcleo conceptual de la semana

### 1. Memoria contigua en un arreglo

Un arreglo usa memoria contigua si sus elementos se guardan en bloques consecutivos de la RAM. En lugar de dispersar los elementos en direcciones aleatorias, el arreglo reserva un bloque único y continuo donde cada elemento ocupa exactamente `sizeof(T)` bytes. Esto se ve en `array.h` donde `T * a` apunta al comienzo del bloque, y cada posición `i` está en `a + i * sizeof(T)`. Esto es la diferencia principal entre arrays y estructuras como listas enlazadas que fragmentan memoria.

### 2. Acceso en O(1)

Acceder a `A[i]` es O(1) porque la memoria contigua permite **direccionamiento directo**:

- El arreglo comienza en una dirección `base`
- Cada elemento ocupa `sizeof(T)` bytes
- La dirección del elemento `i` es: `base + i * sizeof(T)`

El procesador calcula esta dirección mediante una única operación aritmética, sin necesidad de iterar o buscar. No importa si accedemos a `A[0]` o `A[999]`: el costo temporal es el mismo (una lectura de memoria).

### 3. Diferencia entre `size` y `capacity`

- **`size` (n)**: Es el número actual de elementos almacenados en la estructura y refleja cuántos datos válidos contiene.
- **`capacity`**: Es el número total de celdas reservadas en memoria. Es el máximo de elementos que caben sin necesidad de realocación.

En `ArrayStack.h`, `n` es el size y `a.length` es la capacidad. Por ejemplo, si hemos insertado 5 elementos (`size=5`) pero reservamos espacio para 10 (`capacity=10`). La diferencia permite alocar más memoria de la inmediatamente necesaria, amortizando el costo de realloc.

### 4. Por qué un arreglo dinámico no puede crecer "en sitio"

Un arreglo no puede crecer simplemente añadiendo más bytes adyacentes porque:

- La memoria después del bloque actual puede estar **asignada a otro objeto**.
- No hay garantía de que exista espacio contiguo adicional.
- Cambiar la dirección base del arreglo invalidaría todos los punteros externos.

Por eso, `resize()` en `ArrayStack` crea un **nuevo bloque más grande**, copia todos los elementos (`for (int i = 0; i < n; i++) b[i] = a[i]`) y libera el bloque viejo. Esto es seguro pero costoso: O(n).

### 5. Amortización con duplicación

Cuando duplicamos la capacidad en cada resize:

- Insertar n elementos requiere resizes en posiciones 1, 2, 4, 8, ... (potencias de 2).
- El costo total es: 1 + 2 + 4 + ... + n = O(2n - 1) = O(n).
- Amortizado: O(n)/n = O(1) por inserción.

Si creciera linealmente (capacity += c), los resizes sumarían n/c términos de O(n), totalizando O(n²). La duplicación evita esto manteniendo la suma geométrica acotada.

### 6. Comparación ArrayStack vs DengVector

| Aspecto | ArrayStack | DengVector |
| ------- | ---------- | ---------- |
| **Interfaz** | `add(int i, T x)`, `remove(int i)`, `get(i)`, `set(i,x)` | `insert(int r, const T& e)`, `remove(int r)`, `operator[]`, `find(e)`, `traverse(visit)` |
| **Crecimiento** | `capacity = max(2*n, 1)` | `capacity = 2*capacity` |
| **Decrecimiento** | Si `length >= 3*n`: resize a `2*n` | Si `size*4 < capacity` y `capacity > 2*DEFAULT`: divide capacity por 2 |
| **Copia profunda** | Manual (asignación de arrays) | Constructor copia y `operator=` usan `copyFrom()` |
| **Intención didáctica** | Enfoque en estructura lineal simple y amortización | Enfoque en semántica de vector completa (copia, asignación, búsqueda, recorrido) |

### 7. Mejoras de FastArrayStack respecto a ArrayStack

FastArrayStack usa **`std::copy()` y `std::copy_backward()`** en lugar de loops manuales:

- **Implementación eficiente**: `std::copy()` puede usar instrucciones SIMD o memmove optimizadas.
- **Movimiento en caché**: reduce branch mispredictions y mejora localidad de memoria.
- **Complejidad teórica igual**: ambos son O(n-i) para desplazamientos.
- **Mejora práctica significativa**: Fast es ~2-3x más rápido en máquinas reales.

La interfaz y análisis asintótico son idénticos; solo la implementación es más eficiente.

### 8. Idea espacial central de RootishArrayStack

RootishArrayStack organiza elementos en **bloques de tamaño creciente**: 1, 2, 3, 4, ..., r elementos.

- Los primeros r bloques tienen capacidad total de 1+2+3+...+r = r(r+1)/2.
- En lugar de un único arreglo grande, usa **muchos bloques pequeños**.
- Cuando la estructura crece, solo se añade un bloque nuevo (no se realoca todo).

Esto reduce **desperdicio espacial**: si n > r(r+1)/2, se añade un bloque más, pero no se duplica la capacidad total como en ArrayStack.

### 9. Por qué RootishArrayStack usa bloques 1, 2, 3, .., r

Con tamaños 1, 2, 3, ..., r:

- Capacidad total: $\sum_{i=1}^{r} i = \frac{r(r+1)}{2} \approx O(\sqrt{n})$ bloques.
- Cada bloque b tiene exactamente b+1 celdas, lo que permite un mapeo indexado O(log n) mediante fórmula cuadrática (`i2b`).
- Tamaños distintos previenen "grietas" de desperdicio: si usáramos todos iguales, habría muchos vacíos al reducir.

La fórmula `i2b(i) = ceil((-3 + sqrt(9 + 8*i))/2)` invierte la relación r(r+1)/2 = i en O(1).

### 10. Relación entre representación, costo y espacio

| Estructura | Representación | Costo temporal | Desperdicio espacial |
| ---------- | -------------- | -------------- | -------------------- |
| **ArrayStack** | Un arreglo de tamaño capacity | O(1) acceso, O(n) resize | O(n) en peor caso (capacity = 2*n) |
| **FastArrayStack** | Un arreglo (optimización en copia) | O(1) acceso, O(n) resize rápido | O(n) igual a ArrayStack |
| **RootishArrayStack** | Bloques 1,2,3,...,r de tamaño b+1 | O(1) acceso (cálculo i→b), O(n) inserción media | O(√n) bloques, ~O(1) desperdicio promedio |

RootishArrayStack reduce el desperdicio sacrificando un poco de simplicidad en la búsqueda de bloque. Pero conserva la interfaz de lista: acceso, inserción y remoción siguen siendo los mismos métodos lógicos.

## Bloque 2: Demostración y trazado guiado

| Archivo | Salida/observable | Idea estructural | Costo/espacio (resumen) |
| ------- | ----------------- | ---------------- | ----------------------- |
| `include/ArrayStack.h` | add/get/remove, `size` | Arreglo dinámico contiguo | `resize()` O(n) ocasional; O(1) amortizado; desperdicio posible O(n) |
| `include/FastArrayStack.h` | Igual funcionalidad, mejor tiempo práctico | Mismo diseño; usa `std::copy` para mover datos | Constantes mejores; misma complejidad asintótica |
| `include/RootishArrayStack.h` | get/set/add/remove; mapeo índice→bloque | Bloques 1,2,3,... en `blocks` | Acceso O(1); desperdicio ~O(√n), menos que ArrayStack |
| `include/DengVector.h` | `size`/`capacity`, copia profunda | Vector semántico (copia/assign) | Crece por duplicación → O(1) amortizado; manejo de copia explícito |
| `pruebas_publicas/test_public_week2.cpp` | Smoke tests (funcionalidad) | Valida interfaz pública | No mide complejidad; verifica corretitud básica |
| `pruebas_internas/resize_stress_week2.cpp` | Stress de `resize`/`shrink` | Inserciones/borrados masivos | Expone amortización y estabilidad bajo carga |

### 1. Arreglo, longitud y asignación

Se nos muestra que un arreglo ocupa un bloque contiguo de memoria y que la "longitud" lógica (cuántos elementos usamos) puede diferir de la capacidad reservada; también deja claro que el acceso por índice es directo.

### 2. Operación óptima para costo por desplazamiento

Evidencia operaciones como `add(0,x)` o `remove(0)` que desplazan todos los elementos: son las que muestran mejor el costo O(n) por desplazamiento.

### 3. Cambios en la implementación

Demuestra el mismo comportamiento funcional que `ArrayStack` pero con `std::copy`/`std::copy_backward` para mover datos, mejorando tiempos prácticos sin cambiar la complejidad asintótica.

### 4. Ejemplo óptimo para el mapeo de índice lógico a bloque y offset

Usa índices concretos (p. ej. `i=5`) para mostrar `i2b` y `locate(i)`, y cómo eso se traduce en `blocks[b][j]` en la ubicación física.

### 5. Crecimiento de capacity

Imprime `size` y `capacity` tras inserciones, permitiendo ver cuándo se ejecuta `expand()` y justificar el crecimiento por duplicación observando los saltos en `capacity`.

### 6. Similitud conceptual con DengVector

Muestra que `std::vector` y `DengVector` comparten la semántica `size`/`capacity` y el crecimiento amortizado sobre memoria contigua, confirmando la idea de `DengVector` como vector didáctico.

### 7. Demo óptimo para amortización y uso de espacio

Para defender amortización conviene `demo_deng_vector.cpp` (o `demo_arraystack.cpp`) porque muestra la evolución de `capacity`; para defender ahorro de espacio conviene `demo_rootisharraystack_explicado.cpp`, que visualiza bloques y desperdicio reducido.

## Bloque 3: Pruebas públicas, stress y correctitud

### 1. Operaciones mínimas validadas para ArrayStack en prueba pública

`test_public_week2.cpp` valida para `ArrayStack<int>`:

- `add(T x)`: inserta al final (línea `s.add(1)`, `s.add(2)`)
- `add(int i, T x)`: inserta en posición (línea `s.add(1, 99)`)
- `size()`: retorna cantidad de elementos
- `get(int i)`: accede al elemento en índice i
- `remove(int i)`: elimina elemento y retorna su valor

Valida **correctitud básica**: que los datos se guardan donde se espera y se recuperan en orden.

### 2. Operaciones mínimas validadas para FastArrayStack

`test_public_week2.cpp` valida para `FastArrayStack<int>`:

- `add(int i, T x)` con inserciones intermedias
- `get(int i)` acceso posicional
- `size()` coherencia de longitud
- `remove(int i)` eliminación y recuperación correcta

Las mismas operaciones que `ArrayStack`, porque ambas comparten interfaz. Lo que cambia es que FastArrayStack usa `std::copy()` internamente, pero la especificación funcional es idéntica.

### 3. Operaciones mínimas validadas para RootishArrayStack

`test_public_week2.cpp` valida para `RootishArrayStack<int>`:

- `add(int i, T x)` inserciones en bloques
- `size()` coherencia
- `get(int i)` lectura desde bloques
- `set(int i, T x)` modificación
- `remove(int i)` eliminación

Verifica que el mapeo lógico (índice i → bloque b → offset j) **funciona transparentemente**: el usuario no ve bloques, solo una secuencia lineal.

### 4. Qué demuestra una prueba pública

Una prueba pública demuestra que la estructura:

- **Mantiene invariante básico**: tamaño coherente, datos recuperables
- **Funciona en casos típicos**: pequeños volúmenes con operaciones estándar
- **No crashea**: la implementación no tiene segfaults obvios
- **Interfaz correcta**: las operaciones tienen el nombre esperado y retornan tipos correctos

Es un "smoke test" que verifica lo mínimo: que la estructura no está completamente rota.

### 5. Qué NO demuestra una prueba pública

Una prueba pública **no** demuestra:

- **Complejidad temporal real**: O(1) vs O(n) es indistinguible en volúmenes pequeños (< 1000 elementos)
- **Crecimiento y realloc**: solo puede verse con estrés a gran escala
- **Invariantes profundos**: la prueba no valida que `capacity` sea exacto, solo que acceso funcione
- **Comportamiento bajo contención**: concurrencia, caché misses, reales del sistema
- **Correctitud de amortización**: necesita secuencias largas y análisis matemático

### 6. Qué comportamiento intenta estresar `resize_stress_week2.cpp`

`resize_stress_week2.cpp`:

- Inserta **200 elementos** (fuerza múltiples resizes)
- Elimina desde diferentes posiciones (desde final, desde inicio)
- Alcanza **120 elementos en RootishArrayStack** (fuerza crecimiento de múltiples bloques)
- Verifica **reducción**: `remove()` debe mantener invariante y ejecutar `shrink()` si toca el umbral (e.g., `length >= 3*n`)

Esto estresa:

- **Realloc repetido**: asegura que el crecimiento es correcto
- **Desplazamientos grandes**: O(n) en posición 0 es costoso
- **Reducción**: que la estructura no acumule capacidad infinita
- **Integridad tras operaciones masivas**: 1000+ operaciones

### 7. Por qué pasar pruebas no reemplaza explicación de invariantes y complejidad

Las pruebas verifican **comportamiento observable** en instancias pequeñas.  
La **complejidad y correctitud** requieren demostración matemática:

**Ejemplo**:

- Una prueba pública que inserta n=100 y elimina 50 puede pasar en ambas estruturas: ArrayStack y una con realloc ingenuo.
- Pero con n=1M, el realloc ingenuo colapsaría O(n²).
- Solo el análisis teórico (duplicación = O(n) total) lo explica.

Además:

- Las pruebas **no prueban invariantes**: que `size <= capacity`, que bloques están en orden, etc.
- Las pruebas **no prueban causalidad**: por qué funciona, qué garantías mantiene
- Un test puede pasar por suerte, pero un invariante probado es verdad siempre

## Bloque 4: Vector como puente entre teoría y código

### 1. Función de `_size`, `_capacity` y `_elem`

`_size` cuenta los elementos válidos; `_capacity` indica cuánto espacio está reservado; `_elem` es el buffer donde se almacenan los datos. Esta separación permite gestionar la memoria sin cambiar la vista lógica.

### 2. Cuándo ejecutar `expand()`

Se llama justo antes de insertar cuando `size == capacity`. Normalmente duplica la capacidad y copia los datos al nuevo buffer para mantener amortización en inserciones.

### 3. Por qué `insert(r, e)` desplaza elementos

Para dejar libre la posición `r` hay que mover los elementos desde `r` hasta `size-1` una posición a la derecha; ese movimiento preserva el orden y cuesta O(size−r).

### 4. Diferencia entre `remove(r)` y `remove(lo, hi)`

`remove(r)` quita un solo elemento y desplaza el resto; `remove(lo,hi)` elimina un rango completo y desplaza la cola una sola vez, lo que suele ser más eficiente si se borra contiguamente.

### 5. Evidencia de copia profunda

El constructor copia y el `operator=` asignan un nuevo buffer y copian los elementos; en la práctica se demuestra modificando la fuente y comprobando que la copia permanece intacta.

### 6. Por qué `traverse()` es útil

Permite aplicar una operación a cada elemento sin exponer la representación interna, es claro para demos y facilita verificar/comprobar comportamiento uniforme.

### 7. Ventajas de implementar un vector propio

Ayuda a entender gestión de memoria, políticas de crecimiento, semántica de copia y amortización; además permite adaptar comportamiento para experimentos o claridad didáctica.

## Bloque 5: RootishArrayStack - espacio y mapeo

### 1. Distribución de elementos entre bloques

RootishArrayStack almacena elementos en una estructura jerárquica:

- **Bloque 0**: 1 elemento (posiciones lógicas 0)
- **Bloque 1**: 2 elementos (posiciones lógicas 1-2)
- **Bloque 2**: 3 elementos (posiciones lógicas 3-5)
- **Bloque b**: b+1 elementos

Cada bloque es un array dinámico T[] de tamaño exacto b+1.  
Los elementos se mapean **lógicamente** a índices 0, 1, 2, ... manteniendo una secuencia única, pero **físicamente** se distribuyen entre bloques.

En `RootishArrayStack.h`, `blocks` es un `ArrayStack<T*>` que guarda punteros a estos arreglos.

### 2. Capacidad total con r bloques

Con r bloques (bloques 0 a r-1) de tamaños 1, 2, ..., r:

$$\text{Capacidad total} = 1 + 2 + 3 + \ldots + r = \frac{r(r+1)}{2}$$

**Demostración**:

- $\sum_{i=1}^{r} i = \frac{r(r+1)}{2}$ (suma de serie aritmética)

**Ejemplo**:

- Con 4 bloques: capacidad = 4×5/2 = 10
- Con 10 bloques: capacidad = 10×11/2 = 55

Esto implica que con $\sqrt{2n}$ bloques, alcanzamos capacidad $n$. Número de bloques = $O(\sqrt{n})$.

### 3. Qué problema resuelve `i2b(i)`

`i2b(i)` convierte **índice lógico i → número de bloque b** donde reside.

**Problema**: dado índice lógico i (0, 1, 2, ..., n-1), ¿en cuál bloque está?

**Solución**: sabemos que bloque b contiene elementos desde posición $\frac{b(b+1)}{2}$ hasta $\frac{(b+1)(b+2)}{2} - 1$.  
Invertimos: $\frac{b(b+1)}{2} \le i$ implica $b^2 + b - 2i \le 0$.  
Resolviendo: $b = \frac{-1 + \sqrt{1 + 8i}}{2}$, redondeado al entero superior (ceil).

`i2b` calcula: `ceil((-3.0 + sqrt(9.0 + 8.0 * i)) / 2.0)` (fórmula equivalente).

**Costo**: O(1) (una raíz cuadrada y operaciones aritméticas fijas).

### 4. Información que produce `locate(i)` en versión explicada

`locate(i)` en `RootishArrayStackExplicado.h` retorna un par `{b, j}`:

- **b**: número de bloque (0, 1, 2, ...)
- **j**: offset dentro del bloque (0 a b)

```cpp
std::pair<int, int> locate(int i) const {
    const int b = i2b(i);
    const int j = i - b * (b + 1) / 2;
    return {b, j};
}
```

Ejemplo: `locate(5)` con 4 bloques:

- Bloque 0: índices 0 (1 elemento)
- Bloque 1: índices 1-2 (2 elementos)
- Bloque 2: índices 3-5 (3 elementos)
- `i2b(5) = 2`, `j = 5 - 2*3/2 = 5 - 3 = 2`
- Elemento en bloque 2, offset 2: `blocks[2][2]`

Produce una **descripción precisa de ubicación física** a partir de un índice lógico, permitiendo acceso O(1).

### 5. Ganancia en espacio frente a ArrayStack

**ArrayStack**: usa un único arreglo de tamaño `capacity = max(2*n, 1)`.

- Desperdicio: hasta capacity - n celdas = n celdas en peor caso
- Ratio desperdicio/n: O(1) (50% si capacity = 2*n)

**RootishArrayStack**: usa r bloques (bloques 0 a r-1) donde r(r+1)/2 ≈ n.

- $r \approx \sqrt{2n}$
- El último bloque contiene ~r elementos pero solo n%r están llenos
- Desperdicio ≈ r (aproximadamente raíz cuadrada de n)
- Ratio desperdicio/n: O(1/√n) → tiende a 0 cuando n crece

**Ejemplo numérico**:

- n = 1M elementos
- ArrayStack: desperdicio ≈ 1M (50%)
- RootishArrayStack: desperdicio ≈ √(2M) ≈ 1414 (0.14%)

La mejora es enorme para n grande.

### 6. Qué se conserva igual respecto a la interfaz

La interfaz pública es **idéntica**:

- `size()`, `get(i)`, `set(i, x)`, `add(i, x)`, `remove(i)` tienen las mismas firmas
- Comportamiento semántico es el mismo: insertar, acceder, eliminar en índice lógico
- El usuario **no nota** que internamente hay bloques

Esto es ejemplar de **abstracción**: cambiar la representación sin cambiar el contrato.

### 7. Qué parte es más difícil de defender oralmente

#### Más difícil: el mapeo (i2b)

- Requiere derivar/entender la fórmula cuadrática
- Verbalizar cómo se invierte r(r+1)/2 = i en tiempo real es rápido pero no trivial
- Preguntas como "¿qué pasa con i = 100 en 5 bloques?" exigen cálculo rápido

#### Moderado: análisis espacial

- Sumar 1+2+3+...+r es fácil (es r(r+1)/2)
- Pero defender por qué esto implica O(√n) bloques requiere entender que r² ≈ 2n

#### Más fácil: amortización de grow/shrink

- Similar a ArrayStack: agregar/quitar bloques es add/remove en la estructura `blocks`
- El análisis es análogo: grow = O(1) amortizado porque se hace cada O(√n) operaciones

## Bloque 6: DengVector - semántica de vector

### 1. ¿Qué aporta `operator[]` a la idea de vector?

Ofrece acceso posicional directo y familiar (`v[i]`) que oculta la gestión del buffer; implica acceso O(1) y hace que el vector se use como un arreglo dinámico pero seguro.

### 2. ¿Qué supone `find(e)` sobre igualdad entre elementos?

Supone una relación de igualdad definida (por ejemplo `operator==`) y, en la implementación típica, realiza una búsqueda lineal hasta encontrar `e`, por lo que su costo es O(n) en el peor caso; la semántica de igualdad del tipo influye en su comportamiento.

### 3. ¿Qué muestra `traverse()` sobre procesamiento uniforme de toda la estructura?

Demuestra cómo aplicar la misma operación a cada elemento sin exponer la representación; es ideal para inspección, pruebas o aplicar efectos y tiene costo O(n) proporcional al número de elementos.

### 4. ¿Por qué esta lectura refuerza `DengVector`?

La lectura aclara conceptos clave (size vs capacity, políticas de crecimiento, semántica de copia) que se ven en `DengVector`, por lo que complementa las demos y facilita explicar invariantes y costos de forma más segura.

## Bloque 7: Representación y correctitud

### Representación

**Cambio fundamental**: pasar de "usar un arreglo" (como estructura pasiva de almacenamiento) a "diseñar una estructura dinámica basada en arreglo" (como contrato que gestiona memoria y comportamiento).

En representación:

- **Arreglo pasivo**: `int A[100]` es un bloque fijo de memoria, tamaño inmutable, sin abstracción.
- **ArrayStack**: encapsula un arreglo dinámico con invariante n ≤ capacity, maneja resize automático.
- **RootishArrayStack**: abstrae múltiples bloques tras una interfaz lineal única.

La **representación elegida** (un arreglo, dos punteros en DengVector, bloques en RootishArrayStack) determina:

- Cómo se allocan y liberan recursos
- Cómo se mapean índices lógicos a físicos
- Qué transformaciones internas necesita cada operación

### Correctitud

Correctitud significa que **el invariante se mantiene** tras cada operación.

**Invariante de ArrayStack**:

- `0 ≤ n ≤ a.length`
- Los primeros n elementos de `a` contienen datos válidos
- Los elementos restantes son "basura" pero no se acceden

Cada operación mantiene esto:

- `add(i, x)`: si n < capacity, desplaza y escribe (invariante sigue); si n == capacity, crece primero
- `remove(i)`: desplaza izquierda, decrementa n, shrink si es necesario (invariante sigue)

**Invariante de RootishArrayStack**:

- `0 ≤ n ≤ r(r+1)/2` donde r es número de bloques
- Bloque b contiene elementos desde índice $\frac{b(b+1)}{2}$ a $\frac{(b+1)(b+2)}{2} - 1$ (lógicamente)
- El mapeo i2b(i) produce bloque correcto para todo i < n

**Pruebas públicas verifican correctitud operacional**: que get/set/add/remove preservan los datos.  
**Análisis teórico prueba invariantes estructurales**: que mapeo, conteos y distribución son correctos.

---

## Reflexión final: Representación vs Correctitud vs Costo vs Espacio

| Aspecto | ArrayStack | FastArrayStack | RootishArrayStack |
| ------- | ---------- | -------------- | ----------------- |
| **Representación** | array[0..n-1] contiguo | array[0..n-1] contiguo (mismo que ArrayStack) | bloques[0..r-1], bloque b de tamaño b+1 |
| **Correctitud invariante** | n ≤ length, datos en [0..n-1] | Idéntico a ArrayStack | n ≤ r(r+1)/2, mapeo i→(b,j) siempre válido |
| **Costo amortizado add/remove** | O(1) al final, O(n-i) en posición i; amortización por duplicación | O(1) al final, O(n-i) en posición i; FastArrayStack logra el mismo costo asintótico pero con copia más rápida | O(1) al final; O(n-i) promedio en posición i |
| **Desperdicio espacial** | O(n) en peor caso | O(n) igual | O(√n) promedio |

El cambio fundamental: **desacoplamos representación física de interfaz lógica**, permitiendo optimizaciones sin cambiar cómo el usuario ve la estructura.
