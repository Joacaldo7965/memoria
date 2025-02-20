# Resumen
Las mallas volumétricas son una herramienta clave para representar objetos en 3D. Una técnica utilizada para generar estas mallas a partir de un dominio es el método MixedOcTree,
que subdivide recursivamente el espacio en ocho octantes hasta alcanzar una profundidad
específica, conocida como el nivel de refinamiento. Posteriormente se conservan únicamente los octantes que pertenezcan al interior del dominio, eliminando los demás. En esta memoria se aborda la generación de mallas con bajos niveles de refinamiento, con un enfoque
particular en dominios con regiones estrechas. Para mejorar la representación de estas regiones, se propone un algoritmo basado en la duplicación y proyección de nodos. Los resultados
obtenidos muestran que es posible generar mallas visualmente comparables al código base
utilizando niveles de refinamiento menores, logrando una mejora en tiempos de ejecución
y uso de memoria, tanto para mallas simples como para mallas más complejas.


**Palabras claves:** Mallas volumétricas; Mallado Octree; Elementos mixtos; Proyección de
nodos.

# Resultados
Comparación de resultados de la malla _rh.pial.off_ en distintos niveles de refinamiento, considerando el tiempo de ejecución y memoria utilizada:

<img src="https://github.com/user-attachments/assets/7430df7c-d6bf-41fa-b949-92cd4cafe9c9" alt="Description" width="700">

## Cualitativos
- Malla _knot.off_ con un nivel de refinamiento s=4. La solución propuesta usa κ = 0,4 y δ = 90.
<img src="https://github.com/user-attachments/assets/75b5aa30-a1ab-4aa7-b582-61f8bcb9235e" alt="Description" width="700">


- Malla _rh.pial.off_ con un nivel de refinamiento s=5. La solución propuesta usa κ = 0,6 y δ = 90.
<img src="https://github.com/user-attachments/assets/13e3cf5d-ded5-458f-9f1c-90c768c49d2e" alt="Description" width="700">


- Malla _rh.pial.off_ con un nivel de refinamiento s=6. La solución propuesta usa κ = 0,6 y δ = 90.
<img src="https://github.com/user-attachments/assets/8d04f6b4-caf5-481c-847c-b350dd45946d" alt="Description" width="700">


## Cuantitativos
Se muestran tiempos de ejecución en milisegundos de la propuesta con y sin patrones de superficie (PS) de distintas mallas.  Se muestra el cambio
relativo porcentual con respecto al código base. Los tiempos corresponden al promedio de
5 ejecuciones.

- _knot.off_:

<img src="https://github.com/user-attachments/assets/9b732fd8-53fa-47d6-837d-b28f41bc13cc" alt="Description" width="700">

- _rh.pial.off_:

<img src="https://github.com/user-attachments/assets/a4111d74-a0c1-4acb-a92e-90da5066f766" alt="Description" width="700">

