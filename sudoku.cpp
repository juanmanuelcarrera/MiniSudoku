// JUAN MANUEL CARRERA GARC�A  

// Inclusi�n de bibliotecas : 
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int N = 9;					// Constante el tama�o de la matriz del tablero.

typedef int tTablero [N][N];		// Tipo matriz entera para colocar numeros, utilizada para declarar tablero de juego y tablero soluci�n.
typedef bool tTab [N][N];			// Tipo matriz booleana para colocar booleanos para saber si es casilla inicial o no.

typedef int tPosiblesNum [N];		// Tipo array de enteros utilizado en la funcion de posibles candidatos para almacenarlos.

typedef struct {				// Estructura del tablero de juego que incluye :
	int casillavac;					// Un contador para saber las casillas vacias que hay en el tablero de juego.
	tTablero jugar;					// jugar -> Tipo tTablero (enteros) que lo usamos como tablero de juego.
	tTab boolean;					// boolean -> Tipo tTab (booleanos) que lo utilizamos para colocar a true las posiciones en la que hay valores iniciales.
} tSudk;		

typedef struct {				// Estructura que incluye :
	tSudk juego;					// Estructura del tablero de juego.
	tTablero solucion;				// Matriz del tablero soluci�n.
} tJuego;

typedef struct {		 // Estructura que contiene: 
	tPosiblesNum digit;		// El array con los posibles valores y
	int cont;				//  un contador para saber cuantos valores almacenamos en cada momento.
} tCandidatos;

// COMENTARIOS DEL FUNCIONAMIENTO DE LAS FUNCIONES Y PROCEDIMIENTOS DEBAJO DEL MAIN ().

// Funci�n del men� :

int menu ();	// Funci�n que devuelve un entero con la opci�n del men� elegida;

// Funciones y procedimientos inicializacion : 

void inicializacion (tJuego& sudoku);	// Procedimiento que acepta el sudoku y lo inicaliza a 0 y FALSE seg�n corresponda.

bool cargarTablero (tJuego& sudoku, ifstream& arch);	// Procedimiento que acepta el sudoku y un archivo de texto y coloca los valores iniciales.

void cargarSolucion (tJuego& sudoku, ifstream& solu);	// Procedimiento que acepta el sudoku y un archivo de texto y coloca los valores soluci�n.

void inicializaStructuraCandidatos (tCandidatos& cand);	// Procedimiento que acepta la estructura de candidatos para una casilla y la inicializa a 0.

// Procedimiento para pintar tablero :

void pintaTablero (tJuego sudoku);	 // Procedimiento que acepta el sudoku y pinta el tablero correspondiente.



// Funciones y procedimientos del menu (switch) :

// Funciones y procedimientos genericas :

int pedirDigito ();		// Funci�n que devuelve un d�gito entre 1 y 9;

void pedirFilaColumna (int& fil, int& colum);		// Procedimiento que acepta una fila y una colunma y la devuelve con un valor entre 1 y 9.

bool casillaVacia (tJuego sudoku, int fil, int colum);		// Funci�n que acepta el sudoku, una fila y una columna y nos dice si esa casilla est� vac�a o no.
	
bool estaEnLaFila (tJuego sudoku, int fil, int digito);		// Funci�n que acepta el sudoku, una fila y un d�gito y nos dice si el n�mero est� en esa fila.

bool estaEnLaColumna (tJuego sudoku, int colum, int digito);	// Funci�n que acepta el sudoku, una columna y un d�gito y nos dice si el n�mero est� en esa columna.

bool estaEnLaRegion (tJuego sudoku, int fil, int colum, int digito);	// Funci�n que acepta el sudoku, una fila, una columna y un d�gito y nos dice si el n�mero est� en esa regi�n.

void calculoCandidatos (tJuego sudoku, int fil, int colum, tCandidatos& cand);	// Procedimiento que acepta el sudoku, una fila, una columna y una estructura de candidatos y nos 
																				// dice los candidatos de la casilla.
bool valorInicial (tJuego sudoku, int fil, int colum);		// Funci�n que acepta el sudoku, una fila y una columna y nos dice si esa casilla es inicial o no.

bool esCandidato (tJuego sudoku, int fil, int colum, int digit);	// Funci�n que acepta el sudoku, una fila, una columna y un d�gito y nos dice si ese n�mero es candidato de esa casilla.

void ponerValor (tJuego& sudoku, int fil, int colum, int digit);	// Procedimiento que acepta el sudoku, una fila, una columna y un n�mero y lo coloca en la casilla.

void borraValor (tJuego& sudoku, int fil, int colum);	// Procedimiento que acepta el sudoku, una fila y una columna y nos borra el valor de esa casilla.

bool valorCorrecto (tJuego sudoku, int fil, int colum);		// Funci�n que acepta el sudoku, una fila y una columna y nos dice si el d�gito de esa casilla es correcto o no.

bool sudokuCorrecto (tJuego sudoku);	// Funci�n que acepta el sudoku y comprueba si es correcto.


// Funciones y procedimientos del men� : 

// Opciones:

void posiblesValores (tJuego sudoku);	// Procedimiento que acepta el sudoku y sirve para ver los posibles valores de una casilla.

void colocarValor (tJuego& sudoku);		// Procedimiento que acepta el sudoku y sirve para colocar un valor en una casilla.

void borrarValor (tJuego& sudoku);		// Procedimiento que acepta el sudoku y sirve para borrar un valor de una casilla.

void mostrarValoresIncorrectos (tJuego sudoku);		// Procedimiento que acepta el sudoku y sirve para mostar los valores incorrectos del juego.

void reiniciaTablero (tJuego& sudoku);		// Procedimiento que acepta el sudoku y sirve para reiniciarlo.

int rellenarCasillasSimples (tJuego& sudoku);	// Funci�n que acepta el sudoku y sirve para rellenar las casillas simples y devuelve un entero con el n�mero de casillas rellenadas.




int main (){
	// Declaraci�n de variables y estructura que contiene el juego completo
	ifstream inicial;
	ifstream solucion;
	tJuego sudok;
	char a;
	int men, conta;
	bool cargaOK = false, final = false;
	string cadSolu = "solsdk1.txt", cadIni = "sudoku1.txt";
		
	// Petici�n de los nombres de los archivos de texto donde estan los valores iniciales y valores solucion del tablero.  
	
	cout << "Nombre de archivo incial (Intro -> archivo por defecto 'sudoku1.txt'): "; a = cin.peek();	
	if (a != '\n')				// Si el usuario introduce salto de l�nea																				
		getline (cin, cadIni);		// dejamos los nombres por defecto.
	else cin.sync();	// El usuario ha introducido salto de l�nea -> limpiamos el buffer de lectura.

	cout << "Nombre de archivo solucion (Intro -> archivo por defecto 'solsdk1.txt'): "; a = cin.peek();
	if (a != '\n')				// Igual que el anterior.
		getline (cin, cadSolu);
	else cin.sync();
	cout << endl;
										//Apertura de archivos.
	inicial.open (cadIni.c_str());		// Transformamos los string de los nombres de los archivos (cadIni y cadSolu)
	solucion.open (cadSolu.c_str());	// en cadenas de c y abrimos los archivos con dichos nombres.

	inicializacion (sudok);		// Inicializamos el sudoku.

	if (inicial.is_open() && solucion.is_open()){		// Comprobamos si los archivos se han abierto correctamente.
													
		cargaOK = cargarTablero (sudok, inicial);		// Comprobamos si la carga de datos del fichero de valores iniciales ha sido correcta.
		if (cargaOK) {								
			
			cargarSolucion (sudok, solucion);		// Cargamos los valores de la soluci�n en su tablero correspondiente (no hay comprobaci�n de errores
													// porque en el gui�n pone que suponemos que el archivo es correcto).
			inicial.close();			// Cerramos los archivos porque ya hemos 
			solucion.close();			// realizado las cargas de los archivos.
			
			pintaTablero (sudok);		// Pintamos el tablero de juego.
					
			//Bucle 
			
			do{
				if (sudok.juego.casillavac > 0){		// Comprobamos si se han completado todas las casillas o si quedan algunas vac�as.
					men = menu ();						// Pedimos una opci�n del men�.

					cout << "Opcion: " << men << endl << endl;	// Mostramos la opci�n elegida.

					switch (men){		// Switch para elegir la opci�n del men�.
					
					case 1: {						// Opci�n 1: Mostrar posibles valores de una casilla.
							posiblesValores (sudok); 
							pintaTablero (sudok);
							}break;
				
					case 2: {						// Opci�n 2: Colocar un valor en una casilla.
							colocarValor (sudok);
							pintaTablero (sudok);
							}; break;
				
					case 3: {						// Opci�n 3: Borrar un valor de una casilla.
							borrarValor (sudok);
							pintaTablero (sudok);
							}; break;
					
					case 4: {						// Opci�n 4: Mostrar valores incorrectos del tablero de juego.
							pintaTablero (sudok);	
							mostrarValoresIncorrectos (sudok); break;	
							}
						
					case 5:{						// Opci�n 5: Reiniciar el tablero de juego.
						   reiniciaTablero (sudok);
						   pintaTablero (sudok);
						   }; break;

					case 6:{						// Opci�n 6: Rellenar casillas simples del tablero de juego.
						   conta = rellenarCasillasSimples (sudok);
						   pintaTablero (sudok);
						   cout << "Se han completado:  " << conta << " celdas" << endl;
						   }; break;
						
					}
				}
				else {					// Comprobaci�n si el sudoku se a completado correctamente. 
					final = true;		// Si es correcto mostramos mensaje de enhorabuena.
					if (sudokuCorrecto (sudok)) cout << endl << "ENHORABUENA HAS CONSEGUIDO SOLUCIONARLO!" << endl;
					else{				// sino mensaje de error y mostramos los valores que no coinciden con la soluci�n.
						cout << endl << "EL SODUKU NO COINCIDE CON LA SOLUCION" << endl;
						mostrarValoresIncorrectos (sudok);
					}
				}
			}while ((men != 0) && (!final));	
			
		}
		else cout << "ERROR EL FICHERO DE INICIALIZACION ES INCORRECTO!! " << endl;		// Errores si ha habido alg�n problema con los ficheros.
				
	}
	else cout << "ERROR AL ABRIR LOS ARCHIVOS! " << endl;

	cin.sync();
	cout << endl << "PULSA INTRO PARA SALIR";
	cin.get (a);
	return 0;
}



// Funciones inicializacion : 

int menu (){		// Funci�n que devuelve un entero con la opci�n del men� elegida.
	int opc = -1;

	do {
		cout << endl;
		cout << "0 - Salir " << endl;
		cout << "1 - Ver posibles valores de casilla" << endl;
		cout << "2 - Colocar un valor en una casilla" << endl;
		cout << "3 - Borrar el valor de una casilla" << endl;
		cout << "4 - Mostrar valores incorrectos" << endl;
		cout << "5 - Reiniciar tablero" << endl;
		cout << "6 - Completar casillas simples" << endl;
		cin >> opc;
		if (opc < 0 || opc > 6) cout << "Error opcion incorrecta!" << endl;
	} while (opc < 0 || opc > 6);
	
	return opc;
}

void inicializacion (tJuego& sudoku){		// Procedimiento de inicializaci�n de los tableros.
	sudoku.juego.casillavac = 81;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			sudoku.juego.jugar [i][j] = 0;			// Inicializo todas las casillas del tablero de juego y el de soluci�n a 0.
			sudoku.solucion [i][j] = 0;
			sudoku.juego.boolean [i][j] = false;	// Inicializo todas las casillas el tablero de juego de boooleanos a false.
		}
	}


}

void inicializaStructuraCandidatos (tCandidatos& cand) {
	for (int i = 0; i < N; i++)
		cand.digit [i] = 0;
	cand.cont = 0;
}

bool cargarTablero (tJuego& sudoku, ifstream& arch){	// Funcion que carga los valores iniciales del tablero de juego y devuelve un booleano si la carga es correcta.	
	int num, fila, colum;
	bool salir = false, todoCorrecto = true;
		
	do {
		arch >> fila >> colum >> num;			// Cargo del archivo de texto los valores inciales del sudoku hasta encontrar centinela -1.
			if (fila == -1) salir = true;		// Hemos encontrado centinela.
			else {
				if ((num >= 1 && num <= 9) && (fila >= 1 && fila <= 9) && (colum >= 1 && colum <= 9)){	// Comprobamos que los datos son correctos
					fila = fila - 1;																	// y ponemos el numero en la fila y columna 
					colum = colum - 1;																	// del tablero de juego y esa misma casilla
					sudoku.juego.jugar [fila][colum] = num;												// la ponemos a true en el de booleanos para
					sudoku.juego.boolean [fila][colum] = true;											// indicar que es casilla inicial y decrementamos	
					sudoku.juego.casillavac--;															// el contador de casillas vacias de la estrucutura.
				}
				else todoCorrecto = false;
			}
	}while (!salir && todoCorrecto);			// Entramos al bucle siempre y cuando no llegemos al centinela y vayamos cargando datos correctamente.

	return todoCorrecto;		// Booleano que devolvemos para indicar que la carga ha sido correcta.
}

void cargarSolucion (tJuego& sudoku, ifstream& solu){	// Procedimiento para cargar la soluci�n.
	int num;

	for (int i = 0; i < N; i++){		// Vamos cargando un numero del fichero y guardandolo en 
		for (int j = 0; j < N; j++){	// en el tablero soluci�n para rellenarlo.
			solu >> num;
			sudoku.solucion [i][j] = num;			
		}
	}
}

void pintaTablero (tJuego sudoku){		// Procedimiento para pintar el tablero de juego.
		
	for (int i = 0; i < N; i++){
		if (i % 3 == 0) cout << " - - - - - - - - - - - - - - - " << endl;	// Cada 3 filas ponemos una fila de guiones y un salto de l�nea.
		else cout << endl;
		for (int j = 0; j < N; j++){
			if (j % 3 == 0) cout << "|";		// Cada 3 columnas ponemos una barra.
			if (sudoku.juego.jugar [i][j] != 0)		// Si el numero en esa posici�n es distinto de 0 lo mostramos.
				cout << " " << sudoku.juego.jugar [i][j] << " ";
			else cout << "   ";
		}
		cout << "|" << endl;
	}
	cout << " - - - - - - - - - - - - - - - " << endl << endl;	// Y al final meto una �ltima l�nea de guiones.

}



// Funciones del menu (switch) :

// Funciones genericas :

int pedirDigito (){		// Funci�n que nos devuelve un d�gito validado.
	int digito = 0;
	
	cout << "Introduce un numero : "; cin >> digito;
	
	while (digito < 1 || digito > 9) {		// Pedimos un d�gito hasta que este sea correcto.
		cout << "Cuidado!! Numeros pertenecientes a [1,9]" << endl;
		cout << "Introduce un numero : "; cin >> digito;
	} 

	return digito;		// Devolvemos el d�gito validado.
}

void pedirFilaColumna (int& fil, int& colum) {		// Funci�n para conseguir una fila y una columna.
	fil = 0;
	colum = 0;

	cout << "Introduce una fila y una columna : "; cin >> fil >> colum;
	
	while ((fil < 1 || fil > 9) || (colum < 1 || colum > 9)) {		// Pedimos fila y columna hasta que sean correctas.
		cout << "cuidado!! Valores pertenecientes a [1,9]" << endl;
		cout << "Introduce una fila y una columna : "; cin >> fil >> colum;
	} 

	fil = fil - 1;			// Modificamos la fila y la columna para trabajar seg�n los �ndices de la matriz de [0,8];	
	colum = colum - 1;

}

bool casillaVacia (tJuego sudoku, int fil, int colum){		// Funci�n que nos devuelve un booleano para saber si una casilla est� vac�a.
	bool vacia = false;

	if (sudoku.juego.jugar [fil][colum] == 0) vacia = true;  // Comprobamos : casillas == 0 -> Es casilla vac�a. 

	return vacia;	// Devolvemos el booleano que nos indica si es casilla vac�a o no.
}

bool estaEnLaFila (tJuego sudoku, int fil, int digito) {		// Funci�n que nos devuelve un booleano para saber si un d�gito est� en esa fila.
	bool siFila = false;

	for (int i = 0; i < N; i++)			// Bucle para comprobar si es el n�mero est� en la fila.
		if (sudoku.juego.jugar [fil][i] == digito) siFila = true;	
		
	return siFila;		// Si el d�gito est� en la fila devuelve true sino false.
}

bool estaEnLaColumna (tJuego sudoku, int colum, int digito) {	// Igual que la funci�n bool estaEnLaFila(...) pero cogiendo la columna.
	bool siColumna = false;

	for (int i = 0; i < N; i++)
		if (sudoku.juego.jugar [i][colum] == digito) siColumna = true;
	
	return siColumna;
}

bool estaEnLaRegion (tJuego sudoku, int fil, int colum, int digito){	// Funci�n para comprobar si un d�gito est� en esa regi�n.
	int auxf, auxc;
	bool siSector = false;

	auxf = fil / 3;		// Para obtener la regi�n:
	auxc = colum / 3;	// hacemos una divisi�n entera de la fila y la columna para colocar 
	auxf = auxf * 3;	// en casillas incial de la regi�n en la que queremos buscar.
	auxc = auxc * 3;

	for (int i = auxf; i < auxf + 3; i++)		// Comprobamos si el n�mero se encuentra en dicha regi�n.
		for (int j = auxc; j < auxc + 3; j++)
			if (sudoku.juego.jugar [i][j] == digito) siSector = true;
	
	return siSector;		// Si el n�mero est� en regi�n devuelve true sino false;
}

void calculoCandidatos (tJuego sudoku, int fil, int colum, tCandidatos& cand){		// Procedimiento con el que calulamos
	bool siFil = false, siColum = false, siSect = false;											// los candidatos de una casilla.
													// Para una casilla en concreto compruebo los n�meros posibles
	for (int i = 1; i <= 9; i++){					// para ellos compruebo si esta en la fila, columna o regi�n y			
		if (esCandidato (sudoku, fil, colum, i)){	// sino est� lo almaceno en un array.
			cand.digit [cand.cont] = i;					
			cand.cont++;			// Si el n�mero es un candidato lo guardo en el array y aumento un contador.
		}							// El array y el contador van en la estructura cand.
	}
}

bool valorInicial (tJuego sudoku, int fil, int colum){		// Funci�n que nos devuelve si una casilla tiene un valor cargado de inicio.
	bool inicial = false;

	if (sudoku.juego.boolean [fil][colum] == true) inicial = true;		// Comprobaci�n comparando la casilla del tablero de juego con el de booleanos.

	return inicial;		// Devuelve true si la casilla es inicial sino false.	
}

bool esCandidato (tJuego sudoku, int fil, int colum, int digit){	// Funci�n que nos devuelve un booleano indicando si un n�mero es candidato para una casilla.
	bool siFil = false, siColum = false, siSect = false;
	bool candidato = false;	

	siFil= estaEnLaFila (sudoku, fil, digit);			// Comprobamos si el d�gito est� en la fila, columna o regi�n. 
	siColum = estaEnLaColumna (sudoku, colum, digit);
	siSect = estaEnLaRegion (sudoku, fil, colum, digit);
			
	if (!siFil && !siColum && !siSect) candidato = true;	// Si el d�gito no esta ni en la fila, ni en la columna, ni en la regi�n 
															// devuelvo un booleano para indicar que es correcto;
	return candidato;	// Si es correcto candidato es true sino false.
}

void ponerValor (tJuego& sudoku, int fil, int colum, int digit){	// Procedimiento para colocar un valor en una casilla.
	sudoku.juego.jugar [fil][colum] = digit;		// Coloco el n�mero en la casilla.
	sudoku.juego.casillavac--;						// Decremento el contador de casillas vac�as, porque se introduce un n�mero nuevo.
}

void borraValor (tJuego& sudoku, int fil, int colum){	// Procedimiento para borrar un valor en una casilla.
	sudoku.juego.jugar [fil][colum] = 0;			// Borro el valor de una casilla para ello la pongo a 0.
	sudoku.juego.casillavac++;						// Incremento el contador, porque recuperamos una casilla.
}

bool valorCorrecto (tJuego sudoku, int fil, int colum){		// Funci�n para comprobar que un n�mero es v�lido.				
	int num;
	bool correcto = true;

	num = sudoku.juego.jugar [fil][colum];
	
	if (num >= 1 && num <= 9)						// Comprobaci�n: si el d�gito es >= 1 y <= 9 es v�lido.
		if (num != sudoku.solucion [fil][colum])	// Comprobamos el n�mero con la matriz sol�cion.
			correcto = false;
	
	return correcto;	// Si el n�mero del tablero de juego coincide con la soluci�n -> correcto igual a true sino false.
}

bool sudokuCorrecto (tJuego sudoku){	// Funci�n que comprueba si el sudoku es correcto.
	int i = 0, j = 0;
	bool correcto = true;
		
	while ((i < N) && (correcto)){		// Comprobamos casilla a casilla comparando el tablero de juego con la soluci�n mientras sea correcto.
		while ((j < N) && (correcto)){
			if (!valorCorrecto (sudoku, i, j)) correcto = false;
			j++;
		}	
		i++;
	}

	return correcto;	// Si el tablero de juego es correcto -> correcto igual a true sino false.
}


// Opciones:

void posiblesValores (tJuego sudoku){		// Funci�n para comprobar y mostrar los posibles valores de una casilla.
	tCandidatos candidatos;
	int fila, columna;
	
	inicializaStructuraCandidatos (candidatos);		// Inicializo la estructura para guardar los candidatos.

	pedirFilaColumna (fila, columna);		// Pido fila y columna para comprobar.
	
	if (casillaVacia (sudoku, fila, columna)){		// Compruebo si es casilla vac�a.
		calculoCandidatos (sudoku, fila, columna, candidatos);	// Calculo los candidatos de la casilla.

		cout << "Los posibles valores son : ";		// Mostramos el array con los posibles valores de esa casilla.
		for (int i = 0; i < candidatos.cont; i++)
			cout << candidatos.digit [i] << "  ";
		cout << endl;
	}
	else cout << "CASILLA NO VACIA!" << endl;	 // Si la casilla no esta vac�a muestro un mensaje en pantalla.
}

void colocarValor (tJuego& sudoku){		// Procedimiento para colocar un n�mero en el tablero de juego.
	int fila, columna, numero;
	bool siFil = false, siColum = false, siSect = false;

	pedirFilaColumna (fila, columna);		// Pido fila, columna y n�mero para colocarlo.
	numero = pedirDigito ();
	
	if (casillaVacia (sudoku, fila, columna)){				// Para poder colocar el valor comprobamos que la casilla este vac�a
		if (esCandidato (sudoku, fila, columna, numero)){	// que el n�mero es candidato (no este ni fila, ni columna, ni regi�n)
			ponerValor (sudoku, fila, columna, numero);		// y finalmente poner el valor en la casilla indicada.
		}
		else cout << "DIGITO NO VALIDO!" << endl;			// Si en la comprobaci�n se produce alg�n error se indica.
	}
	else {
		if (valorInicial (sudoku, fila, columna)) cout << "CASILLA NO MODIFICABLE!" << endl;
		else cout << "CASILLA NO VACIA!" << endl;
	}
}

void borrarValor (tJuego& sudoku){		// Procedimiento para borrar el valor de una casilla.
	int fila, columna;

	pedirFilaColumna (fila, columna);	// Pido fila y columna para borrar esa casilla.

	if (casillaVacia (sudoku, fila, columna))	// Compruebo si la casilla esta vacia y sino si la casilla es modificacle o no
		cout << "CASILLA VACIA!" << endl;		// para borrar el valor o mostrar el error correspondiente.
	else {
		if (valorInicial (sudoku, fila, columna)) cout << "CASILLA NO MODIFICABLE!" << endl;
		else borraValor (sudoku, fila, columna);	// Borramos el valor de la casilla elegida.
	}
}

void mostrarValoresIncorrectos (tJuego sudoku){		// Procedimiento para mostrar los valores incorrectos del sudoku.
	bool errores = false;

	cout << "ERRORES :" << endl;		// Mostramos los errores recorriendo el tablero de juego y comprobando si lo que hay en la
	for (int i = 0; i < N; i++){		// casilla es correcto.
		for (int j = 0; j < N; j++){
			if (!valorCorrecto (sudoku, i, j)){		// Si no es correcto muestro el n�mero err�neo junto con su fila y columna.
				cout << "[" << i + 1 << "," << j + 1 << "]  (" << sudoku.juego.jugar [i][j] << ")" << endl; 
				errores = true;			// Booleano para comprobar si hay errores o no.
			}
		}
	}
	if (!errores) cout << "NO HAY ERRORES!" << endl;	// Si no ha habido errores lo muestro.
}

void reiniciaTablero (tJuego& sudoku){		// Procedimiento para reiniciar el tablero de juego.
	for (int i = 0; i < N; i++){			// Para reiniciarlo recorro el tablero de juego y borro todos los valores
		for (int j = 0; j < N; j++){		// que no sean casilla con valor inicial y si estan vacias no hace falta inicializarlas.
			if ((!valorInicial (sudoku, i, j)) && (!casillaVacia (sudoku, i, j))){
				borraValor (sudoku, i, j);
			}
		}
	}
}

int rellenarCasillasSimples (tJuego& sudoku){	// Funcion que rellena las casillas simples y nos devuleve cuantas se han rellenado.
	int num = 0, cont = 0, digito = 0;
	tCandidatos candidato;

	for (int i = 0; i < N; i++){		
		for (int j = 0; j < N; j++){					// Recorremos el tablero de juego.
			if (casillaVacia (sudoku, i, j)){				// Comprobamos si la casilla esta vac�a.
				inicializaStructuraCandidatos (candidato);		// Inicializo la estructura para guardar el candidato.
				calculoCandidatos (sudoku, i, j, candidato);	// Calculo los candidatos
					if (candidato.cont == 1){					// Si solo hay un candidato -> casilla simple
						digito = candidato.digit [0];			// y coloco en esa casilla dicho candidato.
						ponerValor (sudoku, i, j, digito); 
						cont++;									// Contador para saber cuantos numeros colocamos en cada pasada.
					}
				}
			
		}
	}
	return cont;		// Devuelve el n�mero de casillas rellenados con valores simples.
}

