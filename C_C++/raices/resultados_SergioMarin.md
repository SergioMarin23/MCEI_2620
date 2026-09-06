
# Resultados — Búsqueda de raíces con GSL
**Sergio Marín** · Métodos Computacionales para Ingeniería (MCEI_M)

Se implementaron los seis métodos de la GSL (bisección, false position, Brent,
Newton, secante y Steffenson) sobre dos funciones.


## Función 1: f(x) = x³ − 5x + 1
- **Intervalo (métodos cerrados):** [0, 1]
- **Valor inicial (métodos abiertos):** x₀ = 0.5
- **Tolerancia:** 1e-8
- **Raíz encontrada:** 0.2016396757

| Método         | Raíz         | Iteraciones | f(raíz)  | Observaciones |
|----------------|--------------|-------------|----------|---------------|
| Bisección      | 0.2016396755 | 29          | 9.0e-10  | El mas lento|
| False position | 0.2016396757 | 8           | 0.0      | Rápido para la función trabajada|
| Brent          | 0.2016396757 | 6           | 0.0      | Es eficiente y rápido |
| Newton         | 0.2016396757 | 4           | 0.0      | El más rápido; le favoreció el Xo escogido |
| Secante        | 0.2016396757 | 5           | -0.0     | No necesita derivadas porque las aproxima |
| Steffenson     | 0.2016396757 | 5           | 0.0      | Empata con el método de la secante |


---
## Función 2: g(x) = e^{−x} − x

- **Intervalo (métodos cerrados):** [0, 1]
- **Valor inicial (métodos abiertos):** x₀ = 0.5
- **Tolerancia:** 1e-8
- **Raíz encontrada:** 0.5671432904

| Método         | Raíz         | Iteraciones | f(raíz)  | Observaciones |
|----------------|--------------|-------------|----------|---------------|
| Bisección      | 0.5671432894 | 28          | 1.6e-9   | El más lento, como en F1. |
| False position | 0.5671432904 | 7           | 0.0      | Un paso menos que en F1. |
| Brent          | 0.5671432904 | 6           | 0.0      | Igual de eficiente que en F1. |
| Newton         | 0.5671432904 | 4           | -0.0     | Converge con facilidad y muy rápido |
| Secante        | 0.5671432904 | 4           | 0.0      | Uno de los más rápidos y no necesita derivadas, las aproxima |
| Steffenson     | 0.5671432904 | 4           | -0.0     | Iguala a Newton. |

---
## Comparación entre F1 y F2 (sección 13)

| Aspecto              | F1: x³−5x+1                          | F2: e^{−x}−x                     |
|----------------------|--------------------------------------|----------------------------------|
| Número de raíces     | 3 raíces reales                      | 1 raíz única                     |
| Derivada f'          | 3x²−5, se anula en x≈±1.29           | −e^{−x}−1, **siempre negativa**  |
| Iter. método abierto | Newton 4, secante/steff 5            | Todos 4 (empatan)                |
| Precisión final      | f(raíz) ~ 1e-10                      | f(raíz) ~ 1e-9                   |

La diferencia clave: F2 no tiene derivada nula ni raíces múltiples, así que la sensibilidad al valor 
inicial es mucho menor. Los métodos abiertos, aquí son tan seguros como los cerrados por la 
geometría de la función.

