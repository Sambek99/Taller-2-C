#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>   

#include "personas.h" 

/* --- FUNCIONES PARA LA ESTRUCTURA PROFESOR --- */

void inicializarDatosProfesor(Profesor* p) {
    if (p == NULL) {
        fprintf(stderr, "Error: Puntero a Profesor es NULL en inicializarDatosProfesor.\n");
        return;
    }

    printf("Nombre del profesor: ");
    fgets(p->nombre, sizeof(p->nombre), stdin);
    p->nombre[strcspn(p->nombre, "\n")] = '\0';

    printf("Carrera: ");
    fgets(p->carrera, sizeof(p->carrera), stdin);
    p->carrera[strcspn(p->carrera, "\n")] = '\0';

    do {
        printf("Numero de materias dictando (2-3): ");
        scanf("%d", &p->numMateriasDictando);
        while (getchar() != '\n'); // Limpiar buffer
        if (p->numMateriasDictando < 2 || p->numMateriasDictando > 3) {
            printf("Error: El profesor debe dictar entre 2 y 3 materias.\n");
        }
    } while (p->numMateriasDictando < 2 || p->numMateriasDictando > 3);

    p->materiasDictando = (Materia*)calloc(p->numMateriasDictando, sizeof(Materia));
    if (p->materiasDictando == NULL) {
        perror("Error al asignar memoria para las materias del profesor");
        p->numMateriasDictando = 0;
    }
    else {
        // Inicializar las materias dictando
        for (int i = 0; i < p->numMateriasDictando; i++) {
            printf("Ingrese los datos de la materia %d:\n", i + 1);
            crearMateriaProfesor(&p->materiasDictando[i]);
        }
    }
}

// Función para mostrar los datos de una materia específica (para profesores)
void leerDatosMateriaProfesor(Materia* m) {
    if (m == NULL) {
        fprintf(stderr, "Error: Puntero a Materia es NULL en leerDatosMateriaProfesor.\n");
        return;
    }
    printf("  Nombre de la materia: %s\n", m->nombre);
    printf("  Paralelo: %d\n", m->paralelo);
}

// Función para mostrar la información de un profesor
void mostrarProfesor(const Profesor* p) {
    if (p == NULL) {
        printf("No hay datos de profesor para mostrar.\n");
        return;
    }
    printf("\n--- INFORMACION DEL PROFESOR ---\n");
    printf("Nombre: %s\n", p->nombre);
    printf("Carrera: %s\n", p->carrera);
    printf("Materias dictando (%d):\n", p->numMateriasDictando);
    for (int i = 0; i < p->numMateriasDictando; i++) {
        leerDatosMateriaProfesor(&p->materiasDictando[i]);
    }
    printf("-------------------------------\n");
}

// Función para liberar la memoria asignada a un profesor (incluyendo sus materias)
void liberarProfesor(Profesor* p) {
    if (p == NULL) return; // No hay nada que liberar

    // Primero, liberar la memoria de las materias dictadas
    if (p->materiasDictando != NULL) {
        free(p->materiasDictando);
        p->materiasDictando = NULL; 
    }
}


/* --- FUNCIONES PARA LA ESTRUCTURA ESTUDIANTE --- */

// Función para inicializar los datos de un estudiante existente y asignar memoria para sus materias.
void inicializarDatosEstudiante(Estudiante* e) {
    if (e == NULL) {
        fprintf(stderr, "Error: Puntero a Estudiante es NULL en inicializarDatosEstudiante.\n");
        return;
    }

    printf("Nombre del estudiante: ");
    fgets(e->nombre, sizeof(e->nombre), stdin);
    e->nombre[strcspn(e->nombre, "\n")] = '\0';

    printf("Nivel: ");
    scanf("%d", &e->nivel);
    while (getchar() != '\n');

    printf("Carrera: ");
    fgets(e->carrera, sizeof(e->carrera), stdin);
    e->carrera[strcspn(e->carrera, "\n")] = '\0';

    do {
        printf("Numero de materias tomando (3-7): ");
        scanf("%d", &e->numMateriasTomando);
        while (getchar() != '\n');
        if (e->numMateriasTomando < 3 || e->numMateriasTomando > 7) {
            printf("Error: El estudiante debe tomar entre 3 y 7 materias.\n");
        }
    } while (e->numMateriasTomando < 3 || e->numMateriasTomando > 7);

    e->materiasTomando = (Materia*)calloc(e->numMateriasTomando, sizeof(Materia));
    if (e->materiasTomando == NULL) {
        perror("Error al asignar memoria para las materias del estudiante");
        e->numMateriasTomando = 0;
    }
    else {
        // Inicializar las materias tomando
        for (int i = 0; i < e->numMateriasTomando; i++) {
            printf("Ingrese los datos de la materia %d:\n", i + 1);
            crearMateriaEstudiante(&e->materiasTomando[i]);
        }
    }
}

// Función para leer los datos de una materia específica (para estudiantes)
void leerDatosMateriaEstudiante(Materia* m) {
    if (m == NULL) {
        fprintf(stderr, "Error: Puntero a Materia es NULL en leerDatosMateriaEstudiante.\n");
        return;
    }
    printf("  Nombre de la materia: %s\n", m->nombre);
    printf("  Creditos: %d\n", m->creditos);
}

// Función para mostrar la información de un estudiante
void mostrarEstudiante(const Estudiante* e) {
    if (e == NULL) {
        printf("No hay datos de estudiante para mostrar.\n");
        return;
    }
    printf("\n--- INFORMACION DEL ESTUDIANTE ---\n");
    printf("Nombre: %s\n", e->nombre);
    printf("Nivel: %d\n", e->nivel);
    printf("Carrera: %s\n", e->carrera);
    printf("Materias tomando (%d):\n", e->numMateriasTomando);
    for (int i = 0; i < e->numMateriasTomando; i++) {
        leerDatosMateriaEstudiante(&e->materiasTomando[i]);
    }
    printf("----------------------------------\n");
}

// Función para liberar la memoria asignada a un estudiante (incluyendo sus materias)
void liberarEstudiante(Estudiante* e) {
    if (e == NULL) return;

    if (e->materiasTomando != NULL) {
        free(e->materiasTomando);
        e->materiasTomando = NULL;
    }
}

void crearMateriaProfesor(Materia* m) {
    if (m == NULL) return;
    printf("  Nombre de la materia: ");
    fgets(m->nombre, sizeof(m->nombre), stdin);
    m->nombre[strcspn(m->nombre, "\n")] = '\0';
    printf("  Paralelo: ");
    scanf("%d", &m->paralelo);
    while (getchar() != '\n');
}

void crearMateriaEstudiante(Materia* m) {
    if (m == NULL) return;
    printf("  Nombre de la materia: ");
    fgets(m->nombre, sizeof(m->nombre), stdin);
    m->nombre[strcspn(m->nombre, "\n")] = '\0';
    printf("  Creditos: ");
    scanf("%d", &m->creditos);
    while (getchar() != '\n');
}
