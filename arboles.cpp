#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <iostream>

using namespace std;

bool enc = false;
bool op34;  // filtra si se utilizó buscar un nodo, o dar su altura
int altura; // Sirve para devolver la altura.
// Se declara un struct de tipo nodo, el cual define la estructura de cada nodo del árbol
struct nodo {
	int dato;
	nodo* izquierda = NULL;
	nodo* derecha = NULL;
	nodo *padre = NULL;
} *arbol;

// Función para insertar
void insertar(int dato, nodo*& arbol, nodo *padre) {
	if (arbol == NULL) { // Si se llega a un nodo nulo, se generará uno nuevo con el dato
		arbol = new nodo;
		arbol->dato = dato;
		arbol->padre = padre;
	}
	// Se va recorrriendo las ramas según si el dato es mayor o menor que el valor del nodo actual
	else {
		if (dato <= arbol->dato) {
			insertar(dato, arbol->izquierda, arbol);
		}
		else
			insertar(dato, arbol->derecha, arbol);
	}
}

// Función para imprimir
// Se utiliza de manera recursiva avanzando primero a los nodos de la derecha
void imprimir(int cont, nodo* arbol) {
	if (arbol == NULL) {
		return;			
	}
	else {			// Se van recorriendo los nodos de derecha a izquierda, regresando e impriendo el valor del nodo 
					// cuando este no tenga hijo derecho o ya se haya recorrido
		imprimir(cont + 1, arbol->derecha);
		for (int i = 0; i <= cont; i++)
			cout << "    ";
		cout << arbol->dato << 
        endl;
		imprimir(cont + 1, arbol->izquierda);
	}
}

// Función para buscar si existe / altura
// Igualmente es recursiva, avanzando primero por los nodos de la derecha
void buscar(int dato, nodo* arbol, int cont) {
	if (altura <= cont) {
		altura = cont; // Se utiliza un contador para la altura
	}
	if (arbol == NULL) {
		return;
	}
	else {
		if (dato == arbol->dato) {
			if (op34) // El valor es verdadero cuando se accede desde la opción 4, imprimiendo el dato y su altura
				cout << "Se encontró el dato " << dato << " en la altura: " << cont << endl;
			enc = true; // Si encuantra el valor, enc cambiará a true, para imprimir si se encontró el valor en la opción 3
		}
		buscar(dato, arbol->derecha, cont + 1);
		buscar(dato, arbol->izquierda, cont + 1);
	}

}

// Función para lleva a cabo la eliminación de un nodo
// en realidad si el nodo a eliminar tiene hijos, se sustituye el valor de este por el que lo reemplazaría, y este ultimo se elimina
// nodo más a la derecha si existe subárbol izquierdo == "nodo x", se termina borrando nodo x
void cambio(nodo *arbol){
	nodo *eliminar = NULL; // Apuntador para el nodo a eliminar
	eliminar = arbol;

	if (arbol->padre == NULL){	// Se ingresará al if si el nodo a eliminar es la raíz, y admás existe un subárbol izquierdo
		if (eliminar->izquierda != NULL)
			eliminar = eliminar->izquierda; // Se avanza a la izquierda
		while (eliminar->derecha != NULL && arbol != NULL){
			eliminar = eliminar->derecha; // se avanza al nodo que esté más a la derecha si es que existen
		}
		arbol->dato = eliminar->dato; // Se recibe el dato del nodo que esté más a la derecha del subárbol izquierdo (nodo x)
		if (eliminar->izquierda != NULL){ // Si el nodo x tiene hijo (solo puede ser a la izq), se enlazan el padre de x y su hijo de x
			eliminar->padre->izquierda = eliminar->izquierda;
			eliminar->izquierda->padre = eliminar->padre;
		}
		else{ // En caso de que x no tenga hijo
			if (arbol->izquierda == eliminar)
				arbol->izquierda = NULL; // Si solo avanzo al subarbol izq, se enlaza la izq de árbol con nulo
			else
				eliminar->padre->derecha = NULL; // Caso contrario se enlaza el la derecha del padre de x con nulo
		}
		
	}
	else{ // Se entra aquí cuando el nodo a eliminar no es raíz
	if (eliminar->izquierda != NULL){// Se entra si existe subárbol izquierdo
			eliminar = eliminar->izquierda; // Se avanza a la raíz del subárbol izq
		while (eliminar->derecha != NULL && arbol != NULL){
			eliminar = eliminar->derecha; // Se avanza al elemento que esté más a la derecha (nodo x)
		}
		arbol->dato = eliminar->dato; // Se manda el dato del nodo x al nodo que se quería eliminar
		if (eliminar->izquierda != NULL){ // Si el nodo x tiene un hijo (por lógica solo el izquierdo) se enlaza el padre de x con su hijo de x
			if (eliminar->padre->izquierda == eliminar){
				eliminar->padre->izquierda = eliminar->izquierda;
				eliminar->izquierda->padre = eliminar->padre;
			}													// Se busca dar al hijo de x la posición de x (enlazar con padre de x padre)
			else{
			eliminar->padre->derecha = eliminar->izquierda;
			eliminar->izquierda->padre = eliminar->padre;
			} 
		}
		else{ // En caso de que x no tenga hijos se iguala el hijo derecho del padre a x
			if (eliminar->padre->derecha == eliminar)
				eliminar->padre->derecha = NULL;			// Se busca dar a la posición de x el valor de nulo (enlazar con padre de x)
			if (eliminar->padre->izquierda == eliminar)
				eliminar->padre->izquierda = NULL;
		}
	}
	else if (eliminar->derecha != NULL){// en caso de que existasubárbol derecho y no izquierdo, 
		arbol = arbol->derecha;
		if (eliminar->padre->derecha == eliminar)
			eliminar->padre->derecha = arbol;
		else										// Se busca suplir la posición de x con la de su hijo o nulo (se enlaza con padre)
			eliminar->padre->izquierda = arbol;
		arbol->padre = eliminar->padre;
	}
	}
	
	delete eliminar;    // Se elimina el nodo sobrante y se apunta a NULL
	eliminar = NULL;
}

// La función sirve para buscar el nodo a eliminar
bool borrar(int dato, nodo *arbol){
	bool encontrado = false;
	if (arbol->dato == dato){

		// Si el nodo con el dato no es un nodo hoja, se llamará a otra función para unir a los hijos
		if (arbol->izquierda != NULL || arbol->derecha != NULL){
			cambio(arbol);
		}
		
		// caso contrario se elimina, y al padre se le enlaza con NULL
		else{
			if (arbol->padre->derecha == arbol)
				arbol->padre->derecha = NULL;		// Se busca de que lado estaba enlazado al padre
			if (arbol->padre->izquierda == arbol)
				arbol->padre->izquierda = NULL;
			delete arbol;
			arbol = NULL;	
		}
		return true;
	}
	else

	// Se utiliza recursividad para avanzar a través del arbol mientras alguno de los hijos del nodo actual no sean nulos, y así buscar en todos los nodos
	// recorriendo de arriba hacia abajo, y de izquierda a derecha (Pre-orden)
	if (arbol->izquierda != NULL || arbol->derecha != NULL){	
		if(dato < arbol->dato){
			encontrado = borrar(dato, arbol->izquierda);
		}
		else if (dato > arbol->dato){
			encontrado = borrar(dato, arbol->derecha);
		}
	}
	return encontrado;
}

// Esta función sirve para que el usuario introduzca el dato que quiere borrar
void borrar_op(){
	int dato;
	nodo *temp;
	cout<<"¿Qué dato quiere eliminar?\n";
	cin>>dato;

	// En caso de que el dato sea igual al nodo raíz y no existan nodos en la parte izquierda del árbol, la parte derecha será el árbol nuevo, siendo el primer nodo derecho la raíz
	if(arbol->dato == dato && arbol->izquierda == NULL){
		temp = arbol;
		arbol = arbol->derecha;
		delete temp;
		temp = NULL;
		cout<<"\n\nEliminado con éxito\n";
	}
	else

	// Caso contrario, se buscara el dato más adentro, y si se llega a encontrar, la función devolverá true
	if (borrar(dato, arbol)){
		cout<<"\n\nEliminado con éxito\n";
	}
	else{
		cout<<"\n\n¡No se encontró el dato!\n";
	}
}

// Función booleana que devuelve true si se introduce 1 o false si se introduce 2
bool seguro(){
	int op = 0;
	do{
		cout<<"\t¿Está seguro de eliminar todo?\n\n1. Si\n2. No\n\nOpción: ";
		cin>>op;
	}while (op != 1 && op != 2);		// Se cuestiona al usuario si está seguro de querer borrar el árbol
	if (op == 1)
		return true;
	if (op == 2)
		return false;
}

// Está función borra todo el árbol
void del_all(nodo *&arbol){
	if (arbol->izquierda != NULL)		//Se utiliza recursión para avanzar por todo el árbol, eliminando los nodos de izquierda a derecha
		del_all(arbol->izquierda);
	if (arbol->derecha != NULL)
		del_all(arbol->derecha);
	if (arbol->derecha == NULL && arbol->derecha == NULL){ // Se revisa si los nodos tienen hijos, en caso de no tener, se elimina el nodo
		delete arbol;
		arbol = NULL;
	}
}

int main() {
	setlocale(LC_ALL, "spanish");
	int op = 0;
	int dato;
	do {
		cout << "\tMenú\n";
		cout << "1. Insertar nodo \n2. Mostrar árbol\n3. Buscar si existe un número\n4. Altura de un nodo\n5. Altura del árbol binario\n";
		cout << "Opción: ";
		cin >> op;
		switch (op) {
		case 1:
			cout << "Dame el número a insertar: ";
			cin >> dato;
			insertar(dato, arbol, NULL);
			break;
		case 2:
			system("cls");
			imprimir(0, arbol);
			system("pause");
			break;
		case 3:
			if (arbol == NULL) {
				cout << "No se ha creado ningún nodo\n";
			}
			else {
				op34 = false;
				enc = false;
				cout << "Inserte el número a buscar: ";
				cin >> dato;
				system("cls");
				buscar(dato, arbol, 1);
				if (enc == false) {
					cout << "No se encontró el número\n";
				}
				else {
					cout << "Si existe el número " << dato << " dentro del árbol\n";
				}
			}
			system("pause");
			break;
		case 4:
			if (arbol == NULL) {
				cout << "No se ha creado ningún nodo\n";
			}
			else {
				op34 = true;
				enc = false;
				cout << "Inserte el número a buscar: ";
				cin >> dato;
				system("cls");
				buscar(dato, arbol, 1);
				if (enc == false) {
					cout << "No se encontró el número\n";
				}
			}
			system("pause");
			break;
		case 5:
			buscar(0, arbol, 0);
			cout << "La altura del arbol es: " << altura << endl;
			system("pause");
			break;
		case 8:
			if (arbol == NULL){
				cout<<"No se ha creado ningún nodo\n";
				
			}
			else
				borrar_op();
			system("pause");
			break;
		case 9:
			system("cls");
			if (arbol == NULL){
				cout<<"No se ha creado ningún nodo\n";
			}
			else
			if (seguro()){
				del_all(arbol);
			}
			else{
				cout<<"\n¡Operación Cancelada!\n";
			}
				
		system("pause");
		break;
		}
		system("CLS");
	} while (op != 10);

    cin.ignore();
    cin.get();
    return 0;
}