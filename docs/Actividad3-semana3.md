# Actividad 3 - CC232

## Integrantes

- Marco Antonio Huamani Bonifacio - 20232741D

## Bloque 1: Preguntas de reflexión

1. Cuando una estructura deja de ser contigua y pasa a ser dinámica, ya no la pienso como una fila de casillas pegadas. En una estructura contigua todo está seguido en memoria, pero en una dinámica cada nodo puede estar en otra parte y se conecta con enlaces.

2. El acceso por rango es cuando quiero ir directo a una posición, como `A[i]`. En cambio, el acceso por posición o por enlace me obliga a caminar nodo por nodo desde el inicio hasta llegar al sitio que busco.

3. En una lista enlazada, insertar o borrar en un punto específico sale barato porque solo se cambian unos pocos enlaces. Lo que cuesta más es encontrar ese punto, ya que casi siempre hay que recorrer la lista.

4. `SLList` encaja bien con `Stack` y `Queue` porque trabaja muy bien con los extremos. En una pila uso el frente para `push` y `pop`, y en una cola puedo agregar al final y sacar por el inicio sin hacer recorridos largos.

5. `SLList` no calza tan natural con un `Deque` completo porque no tiene enlace hacia atrás. Si quiero borrar por el final, primero tengo que buscar el nodo anterior, y eso ya no es tan barato.

6. El nodo centinela `dummy` en `DLList` ayuda bastante porque evita varios casos especiales. Gracias a eso, la lista vacía, el primer nodo y el último se manejan con la misma lógica, sin tanto if raro.

7. En `DLList`, `getNode(i)` puede empezar por el inicio o por el final, según cuál esté más cerca. Por eso el recorrido cuesta `O(min(i, n-i))`, y luego las operaciones locales como `set`, `add` y `remove` se hacen con cambios pequeños en los enlaces.

8. La idea principal de `SEList` es no guardar un nodo por cada elemento, sino agrupar varios elementos en bloques. Eso baja la cantidad de punteros y hace que la estructura sea más práctica entre acceso y espacio.

9. `SEList` reutiliza una `BDeque` basada en `ArrayDeque` porque dentro de cada bloque conviene trabajar con memoria contigua. Así mover, leer y reorganizar elementos dentro del bloque sale más simple y más rápido.

10. `DengList` sirve como una capa extra para usar operaciones más completas como `sort`, `dedup` y `reverse`. No reemplaza a las estructuras de Morin, porque Morin sigue siendo la base de cómo están armados los nodos y de cómo se mantiene la estructura por dentro.

## Bloque 2: Demos y lo que se ve al ejecutar el código

### Tabla de seguimiento de demos

| Archivo | Lo que más se nota | Idea estructural | Razón de costo, espacio o diseño |
| ------- | ------------------ | ---------------- | -------------------------------- |
| `demo_sllist.cpp` | Se ve cómo alternan `push` y `add` sin complicarse demasiado. | La `SLList` maneja bien la cabeza y, cuando existe, también el final. | Conviene cuando trabajas sobre todo con extremos, pero buscar algo en el medio sigue siendo lento. |
| `demo_dllist.cpp` | La inserción en medio se nota muy limpia. | Cada nodo sabe quién está antes y quién está después. | Una vez que llegas al lugar correcto, editar la lista no cuesta mucho. El centinela `dummy` evita casos borde. |
| `demo_selist.cpp` | Aunque se vea como una lista normal al imprimirla, por dentro usa bloques. | Mezcla nodos enlazados con bloques contiguos. | Busca un punto medio entre rapidez para leer y menor gasto de memoria. |
| `demo_deng_list.cpp` | Aparecen operaciones como `sort` y `dedup` sin que uno tenga que programarlas desde cero. | Deng agrega utilidades de alto nivel sobre una lista. | Vale la pena si primero conviertes la estructura y luego aplicas una operación pesada. |
| `demo_morin_deng_bridge.cpp` | El resultado final se mantiene aunque pase por el puente. | El puente conecta la lista de Morin con las herramientas de Deng. | Se reutiliza código en vez de rehacer estructuras completas. |
| `demo_min_structures.cpp` | El mínimo sale de inmediato, sin revisar toda la estructura otra vez. | La estructura guarda información extra para responder rápido. | Se gasta un poco más de memoria, pero se gana mucha rapidez al consultar `min()`. |
| `demo_linked_adapters.cpp` | Una estructura simple termina funcionando como pila, cola o deque según el adaptador. | El adaptador cambia la interfaz, no la base interna. | Es una forma práctica de reutilizar una lista ya hecha sin duplicar trabajo. |
| `demo_contiguous_vs_linked.cpp` | Se nota el contraste entre buscar por índice y hacer inserciones. | Compara memoria contigua con nodos enlazados. | Los arreglos suelen ganar en acceso; las listas suelen ganar cuando hay muchas modificaciones locales. |

### Lo que yo diría al mirar las demos

1. En la demo de `SLList`, lo que más me ayuda a entenderla es ver que el mismo tipo de lista puede comportarse como pila o cola según cómo la use.
2. En `DLList`, la operación que más llama la atención es insertar en la mitad, porque no hace falta mover todo lo demás, solo ajustar enlaces.
3. En `SEList`, aunque por dentro se reacomoden datos entre bloques, al recorrerla sigue saliendo el orden lógico correcto.
4. La demo de Deng muestra que la lista puede tener funciones más “listas para usar”, como eliminar repetidos o ordenar, sin escribir todo a mano.
5. El puente Morin-Deng deja claro que se pueden reutilizar algoritmos ya hechos sin cambiar la estructura base.
6. En las estructuras `Min`, lo que se nota es que no hay búsqueda completa cada vez que piden el mínimo, porque esa información ya se guardó antes.
7. `LinkedQueue` me parece el ejemplo más claro de adaptador, porque usa una lista por debajo pero me deja verla como cola.
8. La comparación entre contiguo y enlazado deja la idea más simple: los arreglos ayudan mucho para leer rápido, pero las listas ayudan más cuando hay que editar sin mover todo.

## Bloque 3: El código de las estructuras

1. La prueba pública de `SLList` revisa lo básico que uno esperaría: agregar al final, meter al inicio, ver el primer dato, sacar datos y comprobar que el tamaño siga bien.

2. En `DLList`, la prueba pública valida insertar por índice, leer con `get`, borrar con `remove(i)` y que el tamaño no se descontrole.

3. En `SEList`, la prueba pública revisa el ciclo más importante: `add(i, x)`, `get(i)`, `set(i, x)`, `remove(i)` y `size`.

4. `test_public_extras.cpp` agrega más cobertura sobre métodos del curso: en `SLList` mira `secondLast`, `reverse` y `checkSize`; en `DLList` mira `rotate`, `isPalindrome` y `checkSize`; además prueba `MinStack`, `MinQueue`, `MinDeque` y `XorList`.

5. `test_public_linked_adapters.cpp` verifica que los adaptadores respeten su comportamiento: `LinkedStack` como LIFO, `LinkedQueue` como FIFO y `LinkedDeque` funcionando bien por ambos lados.

6. `test_public_deng_bridge.cpp` muestra que sí hay integración real entre Morin y Deng, porque permite usar `stable_sort_with_deng`, `dedup_with_deng` y `reverse_with_deng` sin rehacer `DLList` ni `SEList`.

7. `stress_selist_week3.cpp` mete carga fuerte a `SEList`: agrega muchos elementos, borra varios por el frente, vuelve a insertar y al final comprueba que el tamaño lógico siga correcto.

8. Una prueba pública sí demuestra que la API responde bien en casos concretos y representativos.

9. Pero una prueba pública sola no demuestra complejidad formal, ni garantiza que no haya errores escondidos, ni prueba todos los casos posibles.

10. Por eso pasar pruebas sirve bastante, pero no alcanza para explicar bien la estructura: igual hay que hablar de enlaces, reglas internas y costo de las operaciones.

### Cuadro corto para leer pruebas

| Si pasa esto... | Puedo decir que... | Igual debo explicar... |
| --------------- | ------------------ | ---------------------- |
| Pruebas públicas | La estructura funciona en casos normales | Las reglas internas y la complejidad |
| Stress específico | Resiste un patrón de carga concreto | Otros patrones y casos extremos |

## Bloque 4: Entendiendo el código a fondo

1. En `SLList`, `head` marca el inicio, `tail` da acceso rápido al final y `n` guarda cuántos nodos hay. Esos tres datos ayudan a no recorrer la lista cada vez.
2. En `push`, el nuevo nodo se coloca al frente; en `pop`, el frente se mueve al siguiente nodo. Si la lista queda vacía, también hay que dejar `tail` en nulo.
3. `secondLast()` es difícil en una lista simple porque no se puede ir hacia atrás. Entonces toca empezar en `head` y avanzar hasta encontrar el nodo que apunta al último.
4. `reverse()` funciona con unos pocos punteros temporales y va volteando los enlaces uno por uno. No necesita otra estructura auxiliar, solo cambiar el sentido de los punteros.
5. `checkSize()` recorre toda la lista y cuenta nodos para ver si coincide con `n`. Eso ayuda a detectar si algún enlace quedó mal después de una operación.
6. En `DLList`, `getNode(i)` puede arrancar desde el inicio o desde el final porque compara cuál camino es más corto.
7. En `DLList::addBefore`, se actualizan los enlaces de los nodos vecinos y del nodo nuevo. El `dummy` hace que insertar al inicio o al final sea mucho más limpio.
8. `rotate()` no mueve elemento por elemento. Solo cambia qué nodo se toma como inicio y reajusta los extremos para que la lista siga bien conectada.
9. `isPalindrome()` aprovecha que se puede avanzar desde ambos lados al mismo tiempo. Así compara el inicio y el final hasta llegar al centro.
10. En `SEList`, `Location` representa la posición exacta de un dato: en qué bloque está y en qué lugar del bloque se encuentra.
11. `spread()` reparte elementos cuando un bloque se llena demasiado, y `gather()` junta elementos cuando varios bloques quedan muy vacíos.
12. El tamaño del bloque `b` cambia el balance de la estructura: bloques más grandes ayudan a leer mejor, pero bloques más chicos suelen facilitar algunos cambios locales.

## Bloque 5: Adaptadores de estructuras enlazadas

1. `LinkedStack` reutiliza `SLList` casi directo: `push`, `pop` y `top` solo llaman a las operaciones de la lista.

2. `LinkedQueue` también se apoya en `SLList`: agrega por atrás, saca por delante y mira el frente con `peek`.

3. `LinkedDeque` encaja mejor sobre `DLList` porque necesita trabajar con dos extremos y la lista doblemente enlazada ya tiene esa base.

4. En `MinStack`, cada entrada guarda el valor y el mínimo acumulado hasta ese punto. Por eso el mínimo se puede consultar rápido sin volver a recorrer todo.

5. `MinQueue` usa dos pilas para mantener el orden FIFO. Cuando hace falta, pasa elementos de una pila a la otra y así también puede responder al mínimo mirando ambas.

6. `MinDeque` usa rebalanceo entre `front_` y `back_` para que un lado no quede abandonado. Eso ayuda a que las operaciones sigan siendo estables.

7. Implementar una estructura desde cero no es lo mismo que adaptar una ya existente. Por ejemplo, `LinkedStack` no crea una lógica nueva de nodos: solo reusa `SLList` con otra cara.

8. En este bloque, las operaciones de los extremos suelen defenderse como constantes, mientras que en `MinQueue` y `MinDeque` algunas se defienden como amortizadas por los traslados internos.

### Mapa corto de costos

| Estructura | Operaciones más claras | Idea simple |
| ---------- | ---------------------- | ----------- |
| `LinkedStack` | `push`, `pop`, `top` en O(1) | Todo pasa por la cabeza de `SLList` |
| `LinkedQueue` | `add`, `remove`, `front` en O(1) | Entra por atrás, sale por delante |
| `LinkedDeque` | `add/remove` en extremos O(1) | Usa doble enlace |
| `MinQueue` | `add/remove/front/min` O(1) amortizado | A veces hay transferencias grandes |
| `MinDeque` | `front/back/remove` O(1) amortizado | El rebalanceo puede costar más en momentos puntuales |

## Bloque 6: Deng como refuerzo y puente

1. `DengList` trae operaciones que normalmente uno no ve tan completas en una lista básica, como ordenar estable o quitar repetidos de forma directa.
2. La ventaja grande es que esas funciones se pueden usar sin cambiar toda la estructura de la semana. Así no se rompe lo que ya estaba hecho.
3. `to_deng` pasa los datos al formato de Deng, y `assign_from_deng` los devuelve ya procesados.
4. Con `stable_sort_with_deng` no hace falta escribir un ordenamiento aparte dentro de `DLList` o `SEList`.
5. `dedup_with_deng` limpia duplicados y se parece a la idea teórica de `deduplicate()` o `uniquify()`, solo que aquí se usa el puente para apoyarse en Deng.
6. `reverse_with_deng` muestra bien la reutilización: si la interfaz es común, el algoritmo para invertir puede servir sobre distintas listas.
7. Convertir de una estructura a otra sí tiene un costo extra de `O(n)`, pero muchas veces vale la pena si luego vas a aplicar una operación complicada y te ahorras programarla de nuevo.

## Bloque 7: Comparación enlazado vs contiguo

1. `ArrayDeque` usa memoria contigua y circular; `LinkedDeque` usa nodos doblemente enlazados. Eso cambia tanto la forma de guardar datos como los costos que se sienten en uso real.

2. Decir que una estructura tiene mejor localidad de memoria significa que sus datos cercanos también están cerca en memoria física. Eso ayuda a la caché y hace que los recorridos sean más cómodos para el procesador.

3. La representación enlazada favorece más las inserciones y eliminaciones locales, sobre todo cuando ya estás parado en el nodo correcto.

4. En el benchmark, `random_get_arraydeque` contra `random_get_dllist` sirve mejor para hablar de acceso aleatorio. Para hablar de extremos, la comparación más clara es entre las operaciones de `ArrayDeque` y `LinkedDeque`, o entre la cola contigua y la cola enlazada.

5. El benchmark no debe tomarse como una verdad absoluta porque depende de la máquina, del compilador, de las opciones de compilación y del patrón de uso.

6. `XorList` muestra una idea de ahorro de espacio: en vez de guardar dos punteros por nodo, guarda uno solo mezclando información con XOR.

7. El problema práctico de `XorList` es que se vuelve más difícil de entender, depurar y mantener. Aunque ahorre espacio, no siempre compensa esa complicación.

### Cuadro comparativo rápido

| Punto | Contigua (`ArrayDeque`) | Enlazada (`LinkedDeque`/`DLList`) |
| ----- | ----------------------- | --------------------------------- |
| Representación | Datos juntos en memoria | Nodos separados enlazados |
| Acceso por índice | Suele ser más rápido | Requiere recorrido |
| Inserción/eliminación local | Puede mover elementos | Ajusta enlaces |
| Localidad de caché | Mejor | Peor en general |
| Flexibilidad | Menor | Mayor |

## Bloque 8: Cierre para la sustentación

Cuando uno pasa de arreglos dinámicos a estructuras enlazadas, cambia bastante la forma de pensar la memoria. En un arreglo los datos están pegados, pero en una lista enlazada los nodos pueden estar dispersos y unidos por enlaces. Por eso ya no tiene tanto sentido hablar de buscar por rango como si todo estuviera en una sola fila; ahora importa más llegar por posición o por enlace.

La ventaja de eso es clara: insertar o borrar en un punto específico suele ser mucho más barato, porque no hay que mover toda la estructura. Solo se cambian algunos enlaces y listo. Ahí es donde `SLList`, `DLList` y `SEList` muestran sus diferencias: la primera es simple y fuerte en los extremos, la segunda da más libertad con doble enlace y centinela, y la tercera intenta mezclar acceso razonable con mejor uso de espacio.

También se ve que los adaptadores y el puente Morin-Deng son útiles porque separan bien la estructura de la interfaz. Si la base está bien hecha, después puedes reutilizar algoritmos y presentar nuevas operaciones sin escribir todo otra vez. En resumen, no se elige entre arreglos y listas por gusto, sino por el tipo de trabajo que más va a hacer el programa: leer mucho y en orden, o modificar seguido sin mover todo.
