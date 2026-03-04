#include<ctime> // Para utilizar time(NULL), necesario para srand() y rand().
#include "tablero.h" // Para poder utilizar las funciones de 'tablero.cpp', las variables y constantes globales de 'tablero.h' y los #include en 'tablero.h'.

// Las constantes globales están escritas con mayúscula, y se pueden consultar en 'tablero.h'.
// Las variables locales están escritas en minúscula.

int main() {
	// Inicializar fábrica de numeros randomicos.
	// Para poder utilizar 'rand()'.
	// Utiliza time(NULL) porque usa el tiempo actual para poder tener aleatoriedad.
	srand(time(NULL));
	
	// Arreglos y variables para la Tabla de Percepciones.
	string percepciones[MAX_REGISTROS]; // Se crea un vector para guardar percepciones con un Maximo de Registros.
	string acciones[MAX_REGISTROS]; // Se crea aun vector para guardar acciones con un Maximo de Registros.
	int total_percepciones = 0; // Total de Percepciones Actuales. Al comienzo: cero.
	
	// Crear la matriz_tablero.
	string matriz_tablero[FILAS][COLUMNAS];
	
	// Inicializar la matriz_tablero con "-" en todas sus posiciones.
	inicializar_tablero(matriz_tablero);
	
	// Colocar ratón en la posición de la puerta.
	colocar_raton(matriz_tablero);
	
	// Colocar elementos.
	colocar_elemento(matriz_tablero, "G", 5);
	colocar_elemento(matriz_tablero, "T", 5);
	colocar_elemento(matriz_tablero, "Q", 1);
	
	// Imprimir tablero por primera vez con todos los elementos posicionados.
	imprimir_tablero(matriz_tablero);
	
	// Guardar la posición inicial del ratón. Se actualizará cada que el ratón se mueva.
	int fila_raton = PUERTA_FILA;
	int columna_raton = PUERTA_COLUMNA;
	
	// Comenzar el juego.
	while(true) {
		cout << "============ Presiona ENTER para mover al ratón una casilla ============" << endl; // Imprime la instrucción.
		cin.get(); // Recibe el ENTER.
		
		// Antes de mover al ratón: Para la tabla de percepciones...
        string percepcion = obtener_percepcion(matriz_tablero, fila_raton, columna_raton); // Sensor, se percibe alrededor del ratón.
        string accion; // Aún no se registra, sino hasta después de mover al ratón.
		
		if(!mover_raton(matriz_tablero, fila_raton, columna_raton, accion)) { // Si mover_raton() retorna false...
			break; // Termina el juego. El ratón cayó en una Trampa o en el Queso.
		}
		// Si mover_raton() retorna true, el ratón se movió y el juego continúa.
		
		 // Registrar percepción si no existe ya.
        if (!percepcion_existe(percepciones, total_percepciones, percepcion)) { // Si la percepción no existe ya...
            percepciones[total_percepciones] = percepcion; // Registrar la percepción.
            acciones[total_percepciones] = accion; // Registrar la acción. ( 'accion' se modifica en mover_raton() ).
            total_percepciones++; // Aumenta el total de percepciones.
        }
		
		// Imprimir Tablero y Tabla de Percepciones después del movimiento.
        imprimir_tablero(matriz_tablero);
        imprimir_tabla(percepciones, acciones, total_percepciones);
	}
			
	return 0;
}
