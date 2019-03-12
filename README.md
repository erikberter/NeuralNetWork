# NeuralNetWork
A little library about Neural Network I'm doing.

# Descripción

La idea de este ejercicio es generalizar un poco el programa que utilizo para hacer redes neuronales e implementar un sistema de multiplicacion de matrices en ez de por clases. Por otro aldo debería crear un alpha variable, aplicar momentum, etc.

# Funcionamiento

Por ahora es una red neural por descenso de gradiente y con momentum.

Para configurar lo que queremos que haga deberemos configurar el archivo config

| Nombre | Descripción | 
| ---| --- |
| net | Establece la estructura de la red neuronal. El primer número indica la cantidad de neuronas de input, el último induca la cantidad de neuronas de output y los del medio indican la cantidad de neuronas en cada hidden layer. Ex. 260 30 4. Una net de 260 inputs, 1 hidden layer de 30 neuronas y 4 neuronas de output.| 
| alpha | El valor del learning rate. |
| momentum | El valor del momentum. |
| maxErr | El error máximo que se acepta en los test cases. Hasta que no se optimice hasta tener un error menos, seguira ejecutandose el programa. |
| neuronWM | El multiplicador del valor de weight de cada neurona. De esta forma el valor aleatorio inicial de cada neurona es de (0, neuronWM). |
| iterN | Es la cantidad de veces que se entrenará y verificará cada red neuronal en cada archivo de datos. |
| actFunctions | Un array indicando la función de activación de cada una de las layers. |
| nDataFiles | Es un int que representa la cantidad de archivos de datos sobre los que la red neuronal va a actuar. |
| nTestFiles | Es un array de int que representa la cantidad de archivos sobre los que se va a testear la erd neuronal  |



# Principal Uso

La idea de este Neural Net va a ser conseguir resultados más optimos que la anterior, Exercise4, a la hora de detectar el idioma de ciertas palabras.

Entre los fallos de la anterior resolución se encontraban la complejidad que suponía probar varios archivos a la vez, el tiempo perdido por la POO o el hecho de que ciertas palabras aun estando en dos idiomas a la vez, las consideraba solo como de uno y generaba error.


## Posibles cosas a hacer

- Aplicar métodos para conseguir entrelazar neuronas de formas más diversas a solo un complete entre diferentes layers
- Aplicar el momentum
- Aplicar algun algoritmo ADAM
- Crear la script que permita multiples lenguajes
- Mejorar la zona de testCases de forma que sea finalmente comprensible
- Crear algún tipo de documentación minima del software
- Crear  un metodo para eliminar completamente ciertas neuronas.
- Crear metodo para cambiar valor en weights entre dos neuronas concretas
- Añadir softMax
- Permitir que no solo funcione hasta que vaya por debajo de un error, sino permitir que siga durante un tiempo para graficar. 
- Crear archivo de python que permita graficar (creo que lo puedo sacar de la cosa que hize para lo de collatz)


## Changelog

- Version 1.0
    1. This version has been taken from the previous repository.