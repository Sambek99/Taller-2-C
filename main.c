#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>   
#include "personas.h"

// Declaraciones EXTERN para las variables globales de getopt
extern char *optarg;
extern int optind, opterr, optopt;

// Una función auxiliar para mostrar el uso correcto del programa
void mostrarUso(const char *nombrePrograma) {
    fprintf(stderr, "Uso: %s <cantidad_personas> -[p|e|a]\n", nombrePrograma);
    fprintf(stderr, "  <cantidad_personas>: Numero de personas a registrar (debe ser mayor a 2).\n");
    fprintf(stderr, "  -[p|e|a]: Tipo de registro:\n");
    fprintf(stderr, "    -p: Solo profesores\n");
    fprintf(stderr, "    -e: Solo estudiantes\n");
    fprintf(stderr, "    -a: Ambos (1 profesor y el resto estudiantes)\n");
}

int main(int argc, char *argv[]) {
    
    int cantidadPersonas = 0;
    char tipoRegistro = ' '; // 'p', 'e', 'a'
    int opt; 

    // --- 1. Intentar leer la cantidad de personas desde argv[1] ---
    // El programa debe recibir al menos 3 argumentos: nombre_programa, cantidad, -tipo
    if (argc < 3) {
        fprintf(stderr, "Error: Numero insuficiente de argumentos en la linea de comandos.\n");

    } else {
        char *endptr;
        long tempCantidad = strtol(argv[1], &endptr, 10); // Base 10

        // Validar si argv[1] es un número y si es mayor igual a 2
        if (*endptr == '\0' && tempCantidad >= 2) {
            cantidadPersonas = (int)tempCantidad;
        }
    }

    // --- 2. Si la cantidad no fue válida por consola, pedirla por scanf ---
    // Este bucle se ejecutará si cantidadPersonas es 0 (no válida desde argv[1]) o <= 2
    do {
        // Solo pedimos si no se ha validado una cantidad correcta de la línea de comandos
        if (cantidadPersonas < 2) {
            printf("Ingrese la cantidad de personas a registrar (debe ser numerica y mayor igual a 2): ");
            if (scanf("%d", &cantidadPersonas) != 1) {
                printf("Entrada invalida. Por favor, ingrese un numero.\n");
                while (getchar() != '\n'); 
                cantidadPersonas = 0;
            } else if (cantidadPersonas < 2) {
                printf("La cantidad debe ser mayor igual a 2.\n");
            }
            while (getchar() != '\n'); 
        }
    } while (cantidadPersonas < 2);

    // --- 3. Validar que la cantidad de personas sea un número positivo ---

    optind = 1; 

    // --- 4. Procesar las opciones (-p, -e, -a) con getopt ---
    const char *optstring = "pea"; // p, e, a son opciones sin argumentos
    opterr = 0; // Deshabilitar mensajes de error automáticos de getopt

    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch (opt) {
            case 'p':
            tipoRegistro = (char)opt; // Guardar el tipo de registro
                break;
            case 'e':
            tipoRegistro = (char)opt; // Guardar el tipo de registro
                break;
            case 'a':
                tipoRegistro = (char)opt; // Guardar el tipo de registro
                break;
            case '?': // Opción desconocida
                fprintf(stderr, "Error: Opcion desconocida -%c.\n", optopt);
                mostrarUso(argv[0] - 2);
                return EXIT_FAILURE;
        }
    }

    // --- 5. Validar que se haya especificado un tipo de registro ---
    if (tipoRegistro == ' ') {
        fprintf(stderr, "Error: Debe especificar el tipo de registro (-p, -e, o -a) en la linea de comandos.\n");
        mostrarUso(argv[0] - 2);
        return EXIT_FAILURE;
    }

    // --- 6. Resumen y Continuación de la lógica de la tarea ---
    printf("\n--- Parametros obtenidos ---\n");
    printf("Cantidad de personas: %d\n", cantidadPersonas);
    printf("Tipo de registro: '%c'\n", tipoRegistro);
    printf("--------------------------\n\n");

    // --- 7. Lógica para manejar los registros de personas ---
    if (tipoRegistro == 'p') {
        // Solo profesores
        for (int i = 0; i < cantidadPersonas; i++) {
            Profesor p;
            inicializarDatosProfesor(&p); // Inicializar datos del profesor
            mostrarProfesor(&p); // Mostrar datos del profesor  
            liberarProfesor(&p); // Liberar memoria de las materias del profesor      
        }
    } else if (tipoRegistro == 'e') {
        // Solo estudiantes
        for (int i = 0; i < cantidadPersonas; i++) {
            Estudiante e;
            inicializarDatosEstudiante(&e); // Inicializar datos del profesor
            mostrarEstudiante(&e); // Mostrar datos del profesor      
            liberarEstudiante(&e); // Liberar memoria de las materias del estudiante
        }
    } else if (tipoRegistro == 'a') {
        // Un profesor y el resto estudiantes
        Profesor p;
        inicializarDatosProfesor(&p); // Inicializar datos del profesor
        mostrarProfesor(&p); // Mostrar datos del profesor
        liberarProfesor(&p); // Liberar memoria de las materias del profesor
        for (int i = 0; i < (cantidadPersonas-1); i++) {
            Estudiante e;
            inicializarDatosEstudiante(&e); // Inicializar datos del profesor
            mostrarEstudiante(&e); // Mostrar datos del profesor    
            liberarEstudiante(&e); // Liberar memoria de las materias del estudiante    
        }
        
    } else {
        fprintf(stderr, "Error: Tipo de registro no reconocido.\n");
        mostrarUso(argv[0] - 2);
        return EXIT_FAILURE;
    }
    return 0; // Salida exitosa
}
