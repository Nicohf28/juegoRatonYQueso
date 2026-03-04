#include "tablero.h" // Para poder utilizar las variables globales y los #include de 'tablero.h'.

// ============== Funciones: Tablero ==================
void inicializar_tablero(string matriz_tablero[FILAS][COLUMNAS]) {
	for(int i=0; i<FILAS; i++) {
		for(int j=0; j<COLUMNAS; j++) {
			matriz_tablero[i][j] = "-";
		}
	}
}

void imprimir_tablero(string matriz_tablero[FILAS][COLUMNAS]) {
	for(int i=0; i<FILAS; i++) {
		for(int j=0; j<COLUMNAS; j++) {
			cout << matriz_tablero[i][j] << " ";
		}
		cout << endl;
	}
}

// ============== Funciones: Ratón ==================
void colocar_raton(string matriz_tablero[FILAS][COLUMNAS]) {
	matriz_tablero[PUERTA_FILA][PUERTA_COLUMNA] = "R";
}

/*   En esta función...
     i=0 -> Arriba | i=1 -> Abajo | i=2 -> Izquierda | i=3 -> Derecha   */
bool mover_raton(string matriz_tablero[FILAS][COLUMNAS], int &fila_raton, int &columna_raton, string &accion) { // & significa que al modificar la variable aquí, se modifica su valor en el main.
	// Técnica: Arreglos de desplazamiento. (Matemáticamente funciona, Ej. [3,3]).
	// Para que el ratón perciba qué hay en las 4 direcciones.
    int df[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    string nombres[4] = {"ARRIBA", "ABAJO", "IZQUIERDA", "DERECHA"}; // Arreglo de 4 elementos tipo String.
    
    while(true) {
    	// Se elige una dirección Random para moverse a continuación...
        int dir = rand() % 4; // Número random entre 0 y 3.
        int nf = fila_raton + df[dir]; // fila adyacente a revisar.
        int nc = columna_raton + dc[dir]; // columna adyacente a revisar.
        
        // Validar si hay una pared en la dirección/posición...
        if (nf < 0 || nf >= FILAS || nc < 0 || nc >= COLUMNAS) // Si hay pared en la direacción/posición...
            continue; // busca otra dirección/posición a la que intentar avanzar.
            
        // Evitar Gato.
        if (matriz_tablero[nf][nc] == "G") { // Si hay un gato en la dirección/posición...
            cout << "miau!" << endl; // Se lanza una alerta.
            continue; // No se mueve al ratón, para que no se mueva hacia el gato. Se busca otra dirección/posición a la que intentar avanzar.
        }
        
        // Caer en Trampa: Fin del juego.
        if (matriz_tablero[nf][nc] == "T") { // Si hay una trampa en la dirección/posición...
            cout << "El raton cayo en una trampa. Perdiste." << endl; // Se avisa al jugador la pérdida de la partida.
            accion = NOMBRES_ACCIONES[dir]; // Se registra la acción aunque se pierda, para la tabla de percepciones.
            return false; // Se retorna false para acabar con la partida.
        }
        
        // Caer en el Queso: Ganar el juego.
        if (matriz_tablero[nf][nc] == "Q") { // Si hay un queso en la posición...
            cout << "El raton encontro el queso. GANASTE!" << endl; // Se avisa al jugador el gane de la partida.
            accion = NOMBRES_ACCIONES[dir]; // Se registra la acción, para la tabla de percepciones.
            return false; // Se retorna false para acabar con la partida (ganando).
        }
        
        // Actualizar tablero después de movimiento.
        matriz_tablero[fila_raton][columna_raton] = "-"; // La posición anterior, se deja vacía de nuevo. Pues ya el ratón se movió de ahí.
        fila_raton = nf; // Actualizamos la fila del ratón.
        columna_raton = nc; // Actualizamos la columna del ratón.
        matriz_tablero[fila_raton][columna_raton] = "R"; // Actualizamos la posición del ratón en el tablero efectiva y visualmente.
        
        // Registro de la acción realizada, si no se ha terminado la partida (No cayó en Trampa o Queso).
        accion = NOMBRES_ACCIONES[dir]; 
        
        // Si al moverse hay gato adyacente aún, otro miau!
        if (hay_gato_adyacente(matriz_tablero, fila_raton, columna_raton)) {
            cout << "miau!" << endl;
        }
        
        return true; // Continua la partida. (Caso: Casilla Vacía o Gato Adyacente).
    }
    return false; // Termina la partida. (Caso: Queso o Trampa).
}

// ============== Funciones: Elementos (Gatos, Trampas, Queso) ==================
void colocar_elemento(string matriz_tablero[FILAS][COLUMNAS], string elemento, int cantidad) {
	int colocados = 0;
	
	while(colocados < cantidad) {
		int fila = rand() % FILAS-1;
		int columna = rand() % COLUMNAS-1;
		
		if(matriz_tablero[fila][columna] == "-") {
			matriz_tablero[fila][columna] = elemento;
			colocados++;
		}
	}
}

// ============== Funciones: Percepción ==================
string obtener_percepcion(string tablero[FILAS][COLUMNAS], int fila_raton, int columna_raton) {
	// Técnica: Arreglos de desplazamiento. (Matemáticamente funciona, Ej. [3,3]).
	// Para que el ratón perciba qué hay en las 4 direcciones.
	/* df = {-1, 1, 0, 0};
       dc = {0, 0, -1, 1}; */
    string arriba    = ver_casilla(tablero, fila_raton - 1, columna_raton); // Obtener lo que está arriba.
    string izquierda = ver_casilla(tablero, fila_raton, columna_raton - 1); // Obtener lo que está a la izquierda.
    string derecha   = ver_casilla(tablero, fila_raton, columna_raton + 1); // Obtener lo que está a la derecha.
    string abajo     = ver_casilla(tablero, fila_raton + 1, columna_raton); // Obtener lo que está abajo.

    return "A:" + arriba +
           " I:" + izquierda +
           " D:" + derecha +
           " B:" + abajo; // Retornar la percepción, concatenando.
} // A (Arriba), I(Izquierda), D(Derecha), B(Abajo).

string ver_casilla(string tablero[FILAS][COLUMNAS], int fila_vista, int columna_vista) {
    if (fila_vista < 0 || fila_vista >= FILAS || columna_vista < 0 || columna_vista >= COLUMNAS) // Si la posición es pared...
        return "X";  // Retornar "X"

    return tablero[fila_vista][columna_vista]; // De lo contrario, retornar lo que hay en la casilla.
}

bool percepcion_existe(string percepciones[], int total, string percepcion) {
    for (int i = 0; i < total; i++) { // Revisa todas las percepciones en el arreglo 'percepciones[MAX_REGISTROS]'.
        if (percepciones[i] == percepcion) // Si la percepción en el arreglo es la misma que se acaba de tomar...
            return true; // se retorna true.
    }
    return false; // Si la percepción tomada no existía ya en el arreglo, se retorna false.
}

void imprimir_tabla(string percepciones[],
                    string acciones[],
                    int total) {

    cout << "\n      Percepciones     |     Accion     \n";
    cout << "------------------------------------------\n";

    for (int i = 0; i < total; i++) {
        cout << percepciones[i];
        cout << " | ";
        cout << acciones[i] << endl;
    }
}

// ============== Funciones: Auxiliares ==================
/*   En esta función...
     i=0 -> Arriba | i=1 -> Abajo | i=2 -> Izquierda | i=3 -> Derecha   */
bool hay_gato_adyacente(string matriz_tablero[FILAS][COLUMNAS], int fila_raton, int columna_raton) {
	// Técnica: Arreglos de desplazamiento. (Matemáticamente funciona, Ej. [3,3]).
	// Para que el ratón perciba gatos.
    int df[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

	// Verifica las 4 direcciones.
    for (int i = 0; i < 4; i++) {
        int nf = fila_raton + df[i]; // Fila adyacente a revisar.
        int nc = columna_raton + dc[i]; // Columna adyacente a revisar.

        if (nf >= 0 && nf < FILAS && nc >= 0 && nc < COLUMNAS) { // Si la casilla en la dirección sí es dentro del tablero.
            if (matriz_tablero[nf][nc] == "G") { // Verificar si hay un gato.
                return true; // Si lo hay, retorna true.
            }
        }
    }
    return false; // Si no hay un gato en ninguna posición alrededor, retorna false.
}
