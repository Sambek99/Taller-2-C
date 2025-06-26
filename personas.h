#ifndef PERSONAS_H
#define PERSONAS_H

typedef struct {
    char nombre[50];    
    int paralelo;       
    int creditos;       
} Materia;

// --- Definición de la estructura Profesor ---
typedef struct {
    char nombre[100];        
    char carrera[50];        
    Materia *materiasDictando; 
    int numMateriasDictando;  
} Profesor;

// --- Definición de la estructura Estudiante ---
typedef struct {
    char nombre[100];         
    int nivel;                
    char carrera[50];
    Materia *materiasTomando; 
    int numMateriasTomando;  
} Estudiante;

// --- Prototipos de funciones para Profesor ---
void inicializarDatosProfesor(Profesor* p);
void leerDatosMateriaProfesor(Materia* m);
void mostrarProfesor(const Profesor* p);
void liberarProfesor(Profesor* p); // Solo libera las materias internas, no el Profesor *p si es parte de un arreglo
void crearMateriaProfesor(Materia* m);

// --- Prototipos de funciones para Estudiante ---
void inicializarDatosEstudiante(Estudiante* e);
void leerDatosMateriaEstudiante(Materia* m);
void mostrarEstudiante(const Estudiante* e);
void liberarEstudiante(Estudiante* e); // Solo libera las materias internas
void crearMateriaEstudiante(Materia* m);

#endif // PERSONAS_H    