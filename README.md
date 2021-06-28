# Proyecto de Teoría de la Computación - 2021-I
Jorge Luis Neira Riveros - 201910048

## Descripción del proyecto

### Cadena sincronizadora

Dado un AFD *A*, una cadena sincronizadora es una cadena que envía cualquier estado de *A* hacia el mismo estado. Más formalmente, si *A = (Q, Σ, δ, q0, F)*, entonces una cadena *w sincroniza A* si existe un estado *r ∈ Q* tal que, para cualquier estado *q ∈ Q*, al usar la función *δ* desde *q* con la cadena *w*, siempre se llega a *r*. En ese caso, decimos también que *w* es *A-sincronizadora*.

Es posible que no exista cadena sincronizadora para ciertos autómatas. Por lo tanto, denominamos a un AFD *A* sincronizable si existe cadena *A-sincronizadora*.

En el presente proyecto nos centraremos en los siguientes problemas.

**Problema Min-Sinc**. Dado un AFD *A*. Si *A* es sincronizable, encontrar una cadena *A-sincronizadora* con el menor tamaño posible. Si no lo es, devolver “NO”. El problema Min-Sinc es NP-difícil. 

**Problema Dec-Sinc**. Dado un AFD *A*, decidir (responder SI o NO) si *A* es sincronizable. Este problema tiene una algoritmo polinomial.

**Problema Cad-Sinc**. Dado un AFD sincronizable *A*, encontrar una cadena *A-sincronizadora* (no necesariamente mínima).

### Algoritmo exponencial para Min-Sinc

Consiste en construir el AFD potencia del autómata a evaluar. Sea *A* el AFD original y *B* el AFD potencia. Es fácil ver que una cadena sincronizadora en *A* equivale a una cadena en *B*, desde el estado que contiene a todos los estados de *A*, hacia algún estado unitario de *B*.

**Pregunta 1** Implementar un algoritmo exponencial que resuelve Min-Sinc.

* **Entrada:** Un AFD *A* con *n* estados y alfabeto {0, 1}.
* **Salida del algoritmo:** Si *A* es sincronizable, devolver una cadena *A-sincronizadora* de tamaño mínimo, y su tamaño. Si no lo es, devolver “NO”.
* **Tiempo de ejecución del algoritmo**: *O(2<sup>n</sup>)*.

### Algoritmo polinomial para Dec-Sinc

A continuación veremos un algoritmo mucho más rápido para saber si un AFD *A* es sincronizable. Su eficiencia se debe a una propiedad estructural demostrada por Cerny.

**Teorema 3.1.** *Un AFD A es sincronizable, si y solo si para cada par de estados p, q de A existe una cadena w tal que δ(p, w) = δ(q, w)*

Usando esta propiedad, podemos resolver el problema Dec-Sinc en tiempo polinomial, ya que solo debemos verificar si cada par de estados pueden ser sincronizados.

**Pregunta 2.** Implementar un algoritmo polinomial que resuelve Dec-Sinc.
* **Entrada:** Un AFD *A* con *n* estados y alfabeto {0, 1}.
* **Salida del algoritmo:** “SI” si *A* es sincronizable, y “NO” en caso contrario.
* **Tiempo de ejecución del algoritmo**: *O(n<sup>2</sup>)*.

### Algoritmo polinomial para Cad-Sinc

Si además queremos encontrar una cadena sincronizadora (no necesariamente mínima) podemos aplicar el algoritmo de Eppstein. Dicho algoritmo tiene como idea básica concatenar cadenas sincronizadoras para cada par de estados.

**Pregunta 3.** Implementar un algoritmo polinomial que resuelve Cad-Sinc.
* **Entrada:** Un AFD sincronizable *A* con *n* estados y alfabeto {0, 1}.
* **Salida del algoritmo:** Una cadena *A-sincronizadora* (no necesariamente mínima).
* **Tiempo de ejecución del algoritmo**: *O(n<sup>3</sup>)*.

Finalmente, probaremos nuestro algoritmo en este problema.
**Pregunta 4.** Resolver el problema <a href="https://csacademy.com/ieeextreme-practice/task/magical-stones-2/">Magical Stones 2</a>