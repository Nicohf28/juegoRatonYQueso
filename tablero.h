#ifndef TABLERO_H
#define TABLERO_H

#include<iostream> // Para poder utilizar 'cout' y 'cin'.
#include<cstdlib> // Para utilizar srand() y rand()
#include<string> // Para poder utilizar el tipo string
using namespace std; // Para que todos los 'cout' sean 'std::', y no repetir código.

// Constantes: Tablero.
const int FILAS = 12;
const int COLUMNAS = 10;

// Constantes: Ratón.
const int PUERTA_FILA = 0;
const int PUERTA_COLUMNA = 0;

// Constantes: Percepciones.
const int MAX_REGISTROS = 100;
const string NOMBRES_ACCIONES[4] = {"ARRIBA", "ABAJO", "IZQUIERDA", "DERECHA"};

// Funciones: Tablero.
void inicializar_tablero(string matriz_tablero[FILAS][COLUMNAS]);

void imprimir_tablero(string matriz_tablero[FILAS][COLUMNAS]);

// Funciones: Raton.
void colocar_raton(string matriz_tablero[FILAS][COLUMNAS]);

bool mover_raton(string matriz_tablero[FILAS][COLUMNAS],
				 int &fila_raton, // & significa que al modificar la variable en la función, se modifica su valor en el main.
				 int &columna_raton,
				 string &accion);

// Funciones: Elementos (Gatos, Trampas, Queso).
void colocar_elemento(string matriz_tablero[FILAS][COLUMNAS],
					  string elemento,
					  int cantidad
);

// Funciones: Tabla de Percepciones.
string obtener_percepcion(string matriz_tablero[FILAS][COLUMNAS],
                          int fila_raton,
                          int columna_raton);
                          
bool percepcion_existe(string percepciones[],
                       int total,
                       string percepcion);
                       
string ver_casilla(string tablero[FILAS][COLUMNAS],
                   int fila,
                   int columna);
                   
void imprimir_tabla(string percepciones[],
                    string acciones[],
                    int total);

// Funciones: Auxiliares.
bool hay_gato_adyacente(string matriz_tablero[FILAS][COLUMNAS],
						int fila_raton,
						int columna_raton);

#endif
