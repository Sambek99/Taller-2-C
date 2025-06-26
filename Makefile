# Define el nombre del ejecutable final
TARGET = Programa

# Archivos fuente (todos los .c que forman tu programa)
SRCS = main.c utilidades.c

# Archivos objeto (se generarán automáticamente a partir de los .c)
OBJS = $(SRCS:.c=.o)

# Compilador a usar (gcc es el estándar en sistemas tipo Unix, MinGW en Windows)
CC = gcc

# Opciones de compilación:
# -Wall: Habilita todas las advertencias (¡MUY recomendado!)
# -Wextra: Habilita advertencias adicionales (también recomendado)
# -std=c11: Usa el estándar C11
# -g: Incluye información de depuración (para usar con depuradores como GDB)
# -I. : Busca archivos de cabecera (.h) en el directorio actual (importante para personas.h)
CFLAGS = -Wall -Wextra -std=c11 -g -I.

# Opciones de enlazado:
# (Actualmente no necesitamos librerías adicionales, pero si las tuvieras irían aquí)
LDFLAGS =

# --- Reglas de compilación ---

# Regla por defecto: Compilar el ejecutable
# Depende de todos los archivos objeto
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)
	@echo "-----------------------------------"
	@echo "¡Programa '$(TARGET)' compilado con éxito!"
	@echo "Para ejecutar: ./$(TARGET) <cantidad> -[p|e|a]"
	@echo "-----------------------------------"

# Regla para compilar archivos .c a .o
# Make sabe cómo compilar un .c a un .o automáticamente.
# Por ejemplo, para main.o, make buscará main.c.
# Para utilidades.o, make buscará utilidades.c.
# La opción -c indica solo compilar, no enlazar.
# $(CFLAGS) se aplica durante esta fase de compilación.

# Regla para limpiar los archivos generados (ejecutable y archivos objeto)
clean:
	@echo "Limpiando archivos generados..."
	rm -f $(TARGET) $(OBJS)
	@echo "Limpieza completada."

.PHONY: all clean
