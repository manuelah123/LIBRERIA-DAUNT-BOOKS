#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

#define TAM_TABLA 50
#define MAX_LIBROS 200

struct Libro {
    char titulo[100];
    char autor[50];
    int volumen;
    int calificacion;
    char disciplina[50];
    char extracto[200];
};

Libro* tablaHash[TAM_TABLA][MAX_LIBROS];
int contadorLibros[TAM_TABLA] = {0};

int hashFuncion(const char* clave) {
    int suma = 0;
    for (int i = 0; clave[i] != '\0'; i++) {
        suma += (unsigned char)clave[i];
    }
    return suma % TAM_TABLA;
}

Libro* crearNuevoLibro(const char* titulo, const char* autor, int volumen, int calificacion, const char* disciplina, const char* extracto) {
    Libro* nuevo = new Libro;
    strcpy(nuevo->titulo, titulo);
    strcpy(nuevo->autor, autor);
    nuevo->volumen = volumen;
    nuevo->calificacion = calificacion;
    strcpy(nuevo->disciplina, disciplina);
    strcpy(nuevo->extracto, extracto);
    return nuevo;
}

// Incorporar Nueva Publicación al sistema
void insertarLibro(Libro* libro) {
    int indice = hashFuncion(libro->autor);
    int pos = contadorLibros[indice];
    if (pos < MAX_LIBROS) {
        tablaHash[indice][pos] = libro;
        contadorLibros[indice]++;
        printf("Libro incorporado exitosamente: \"%s\" de %s\n", libro->titulo, libro->autor);
    } else {
       printf("Error: No hay espacio en la tabla hash para mas libros.\n");
    }
}

// Función auxiliar para incorporar libro desde el menú
void incorporarNuevaPublicacion() {
    char titulo[100], autor[50], disciplina[50], extracto[200];
    int volumen, calificacion;
    
    printf("\nIncorporar Nueva Publicacion\n");
    
    printf("Titulo: ");
    fgets(titulo, sizeof(titulo), stdin);
    titulo[strcspn(titulo, "\n")] = '\0';
    
    printf("Autor Principal: ");
    fgets(autor, sizeof(autor), stdin);
    autor[strcspn(autor, "\n")] = '\0';
    
    printf("Volumen de Distribucion (unidades vendidas): ");
    scanf("%d", &volumen);
    getchar();
    
    printf("Calificacion del Panel de Expertos (1-10): ");
    scanf("%d", &calificacion);
    getchar();
    
    // Validar calificación
    if (calificacion < 1 || calificacion > 10) {
        printf("Error: La calificacion debe estar entre 1 y 10.\n");
        return;
    }
    
    printf("Disciplina Principal: ");
    fgets(disciplina, sizeof(disciplina), stdin);
    disciplina[strcspn(disciplina, "\n")] = '\0';
    
    printf("Extracto (Comentarios): ");
    fgets(extracto, sizeof(extracto), stdin);
    extracto[strcspn(extracto, "\n")] = '\0';
    
    Libro* nuevoLibro = crearNuevoLibro(titulo, autor, volumen, calificacion, disciplina, extracto);
    insertarLibro(nuevoLibro);
}

// Recomendación Premium por Autor (Compra Segura) - O(1) promedio
Libro* MejorLibroPorAutor(const char* autor) {
    int indice = hashFuncion(autor);
    Libro* mejor = nullptr;
    // Buscar en el bucket del hash (colisiones manejadas con array)
    for (int i = 0; i < contadorLibros[indice]; i++) {
        Libro* actual = tablaHash[indice][i];
        if (strcmp(actual->autor, autor) == 0) {
            // Encontrar el libro con mayor calificación del panel de expertos
            if (mejor == nullptr || actual->calificacion > mejor->calificacion)
                mejor = actual;
        }
    }
    return mejor;
}

void rankingDisciplina(const char* disciplina) {
    Libro* ranking[MAX_LIBROS];
    int count = 0;

    // Buscar todos los libros de la disciplina (O(n) donde n es el total de libros)
    for (int i = 0; i < TAM_TABLA; i++) {
        for (int j = 0; j < contadorLibros[i]; j++) {
            if (strcmp(tablaHash[i][j]->disciplina, disciplina) == 0) {
                ranking[count++] = tablaHash[i][j];
            }
        }
    }

    if (count == 0) {
        printf("No se encontraron libros en la disciplina \"%s\".\n", disciplina);
        return;
    }
    
    // Ordenar por Volumen de Distribución (mayor a menor) usando Bubble Sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (ranking[j]->volumen < ranking[j + 1]->volumen) {
                Libro* temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }
    
    // Mostrar el ranking de influencia por disciplina
    printf("\nRanking de Influencia por Disciplina: \"%s\"\n", disciplina);
    printf("(Ordenado por Volumen de Distribucion - Mayor a Menor)\n\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, ranking[i]->titulo);
        printf("Autor: %s\n", ranking[i]->autor);
        printf("Volumen de Distribucion: %d unidades\n", ranking[i]->volumen);
        printf("Calificacion del Panel: %d/10\n", ranking[i]->calificacion);
        printf("\n");
    }
    printf("==================================================\n");
}

int main() {
    char buffer[100];
    int opcion;
    
    Libro* libro1 = crearNuevoLibro("El proceso", "Franz Kafka", 400000, 8, "Filosofia", "Un hombre acusado sin conocer su crimen.");
    Libro* libro2 = crearNuevoLibro("Crimen y castigo", "Fiodor Dostoievski", 500000, 10, "Psicologia", "Analisis del crimen, la culpa y la redencion.");
    Libro* libro3 = crearNuevoLibro("El verano en que me enamore", "Jenny Han", 270000, 9, "Romance juvenil", "Una historia sobre el primer amor y el verano.");
    Libro* libro4 = crearNuevoLibro("Emma", "Jane Austen", 350000, 8, "Romance", "Comedia sobre las costumbres y las relaciones.");
    Libro* libro5 = crearNuevoLibro("El retrato de Dorian Gray", "Oscar Wilde", 340000, 9, "Filosofia", "La corrupcion del alma y la vanidad eterna.");
    Libro* libro6 = crearNuevoLibro("Los miserables", "Victor Hugo", 480000, 10, "Drama", "Historia de redencion y justicia social.");
    Libro* libro7 = crearNuevoLibro("La importancia de llamarse Ernesto", "Oscar Wilde", 300000, 8, "Comedia", "Satira elegante de la alta sociedad.");
    Libro* libro8 = crearNuevoLibro("Antes de diciembre", "Joana Marcus", 280000, 8, "Romance juvenil", "Historia sobre el amor adolescente y las decisiones.");
    Libro* libro9 = crearNuevoLibro("El tunel", "Ernesto Sabato", 230000, 9, "Psicologica", "Relato introspectivo de un asesino.");
    Libro* libro10 = crearNuevoLibro("1984", "George Orwell", 450000, 10, "Distopia", "Una sociedad controlada por un regimen totalitario.");
    Libro* libro11 = crearNuevoLibro("Rebelion en la granja", "George Orwell", 380000, 9, "Satira", "Critica politica sobre el poder y la corrupcion.");
    Libro* libro12 = crearNuevoLibro("Frankenstein", "Mary Shelley", 390000, 10, "Terror", "Creador y criatura en conflicto moral.");
    Libro* libro13 = crearNuevoLibro("Sobre heroes y tumbas", "Ernesto Sabato", 270000, 8, "Filosofia", "Novela profunda y simbolica.");
    Libro* libro14 = crearNuevoLibro("La metamorfosis", "Franz Kafka", 410000, 9, "Existencialismo", "Un hombre despierta convertido en insecto.");
    Libro* libro15 = crearNuevoLibro("Los hermanos Karamazov", "Fiodor Dostoievski", 470000, 9, "Filosofia", "Explora la fe, la moral y el conflicto familiar.");
    Libro* libro16 = crearNuevoLibro("Notre Dame de Paris", "Victor Hugo", 400000, 9, "Tragedia", "El amor imposible entre Esmeralda y Quasimodo.");
    Libro* libro17 = crearNuevoLibro("Despues de diciembre", "Joana Marcus", 300000, 9, "Romance juvenil", "Continuacion del amor de Jack y Jenna.");
    Libro* libro18 = crearNuevoLibro("Orgullo y prejuicio", "Jane Austen", 420000, 9, "Romance", "Historia sobre el amor y la sociedad inglesa.");
    Libro* libro19 = crearNuevoLibro("El ultimo hombre", "Mary Shelley", 300000, 8, "Ciencia ficcion", "Relato sobre un futuro apocaliptico.");
    Libro* libro20 = crearNuevoLibro("Siempre nos quedara el verano", "Jenny Han", 260000, 8, "Romance juvenil", "El desenlace del amor de Belly y Conrad.");
    
    insertarLibro(libro1);
    insertarLibro(libro2);
    insertarLibro(libro3);
    insertarLibro(libro4);
    insertarLibro(libro5);
    insertarLibro(libro6);
    insertarLibro(libro7);
    insertarLibro(libro8);
    insertarLibro(libro9);
    insertarLibro(libro10);
    insertarLibro(libro11);
    insertarLibro(libro12);
    insertarLibro(libro13);
    insertarLibro(libro14);
    insertarLibro(libro15); 
    insertarLibro(libro16);
    insertarLibro(libro17);
    insertarLibro(libro18);
    insertarLibro(libro19);
    insertarLibro(libro20);

    do {
        printf("\n========================================\n");
        printf("          LIBRERiA DAUNT BOOKS\n");
        printf("   Sistema de Catalogacion y Recomendacion\n");
        printf("========================================\n");
        printf("1. Incorporar Nueva Publicacion\n");
        printf("2. Recomendacion Premium por Autor (Compra Segura)\n");
        printf("3. Ranking de Influencia por Disciplina\n");
        printf("4. Salir\n");
        printf("========================================\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1: {
                incorporarNuevaPublicacion();
                break;
            }
            case 2: {
                printf("\Recomendacion Premium por Autor (Compra Segura) \n");
                printf("Ingrese el nombre del Autor Principal: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0'; 

                Libro* mejor = MejorLibroPorAutor(buffer);
                if (mejor) {
                    printf("\Recomendacion Premium para \"%s\"\n", buffer);
                    printf("Titulo: %s\n", mejor->titulo);
                    printf("Autor Principal: %s\n", mejor->autor);
                    printf("Calificacion del Panel de Expertos: %d/10\n", mejor->calificacion);
                    printf("Volumen de Distribucion: %d unidades\n", mejor->volumen);
                    printf("Disciplina Principal: %s\n", mejor->disciplina);
                    printf("Extracto: %s\n", mejor->extracto);
                    printf("\n");
                } else {
                    printf("\n  No se encontro ningun libro del autor \"%s\" en la coleccion.\n", buffer);
                }
                break;
            }
            case 3: {
                printf("\nRanking de Influencia por Disciplina \n");
                printf("Ingrese la Disciplina Principal: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                rankingDisciplina(buffer);
                break;
            }
            case 4:
                printf("\nSaliendo del sistema...\n");
                printf("Gracias por usar la Libreria DAUNT BOOKS.\n");
                break;

            default:
                printf("\n✗ Opcion no valida. Por favor, seleccione una opcion del 1 al 4.\n");
                break;
        }

    } while (opcion != 4);

    return 0;
}
