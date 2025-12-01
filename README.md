# Librería DAUNT BOOKS – Sistema de Catalogación y Recomendación

Proyecto desarrollado en C++ que simula el funcionamiento de un sistema de catalogación de libros con funcionalidades avanzadas de búsqueda y recomendación utilizando una Tabla Hash para optimizar el acceso por autor.


# Características principales

- Registro de nuevas publicaciones con datos como título, autor, disciplina, calificación y volumen de distribución.
-  Recomendación Premium por autor basada en la mejor calificación otorgada por un panel de expertos.
- Ranking de influencia por disciplina, ordenado por unidades vendidas (volumen de distribución).
- Gestión eficiente mediante estructura hash, garantizando búsquedas rápidas (O(1) promedio).
- Interfaz en consola, simple y funcional.

# Tecnologías utilizadas

- Lenguaje: C++
- Paradigma: Programación estructurada
- Estructuras de datos: Tabla Hash, arrays, búferes de entrada
- Algoritmos: Bubble Sort, hashing simple por suma de caracteres

## Estructura del código
```bash
struct Libro {
    char titulo[100];
    char autor[50];
    int volumen;
    int calificacion;
    char disciplina[50];
    char extracto[200];
};
```

# El sistema usa:
```bash
Libro* tablaHash[TAM_TABLA][MAX_LIBROS];
int contadorLibros[TAM_TABLA];
```

**Para almacenar los libros categorizados por autor según su hash.**

# Funcionalidades del menú
- Opción	Descripción
-	Incorporar nueva publicación
- Recomendación Premium por autor
- Ranking de influencia por disciplina
-	Salir del sistema
- Ejecución
- Compilar

# Ejemplo de salida (recomendación por autor)
- Recomendación Premium para "George Orwell"
- Título: 1984
- Autor Principal: George Orwell
- Calificación del Panel de Expertos: 10/10
- Volumen de Distribución: 450000 unidades
- Disciplina Principal: Distopia
- Extracto: Una sociedad controlada por un régimen totalitario.

# Complejidad Algorítmica
**Función	Complejidad**
- insertarLibro()	O(1) promedio
- MejorLibroPorAutor()	O(n) en caso de colisiones
- rankingDisciplina()	O(n²) por Bubble Sort
- hashFuncion()	O(k), siendo k longitud del nombre del autor


# Autor
**Manuela Henao Bedoya**

# Licencia
**Este proyecto está bajo la licencia MIT.**
