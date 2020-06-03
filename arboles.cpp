#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <iostream>

using namespace std;

bool enc = false;
bool op34;
int altura;
// Se declara un struct de tipo nodo, el cual define la estructura de cada nodo del árbol
struct nodo {
	int dato;
	nodo* izquierda = NULL;
	nodo* derecha = NULL;
	nodo *padre = NULL;
} *arbol;

void insertar(int dato, nodo*& arbol) {
	if (arbol == NULL) {
		arbol = new nodo;
		arbol->dato = dato;
	}
	else {
		if (dato <= arbol->dato) {
			insertar(dato, arbol->izquierda);
		}
		else
			insertar(dato, arbol->derecha);
	}
}

void imprimir(int cont, nodo* arbol) {
	if (arbol == NULL) {
		return;
	}
	else {
		imprimir(cont + 1, arbol->derecha);
		for (int i = 0; i <= cont; i++)
			cout << "    ";
		cout << arbol->dato << 
        endl;
		imprimir(cont + 1, arbol->izquierda);
	}
}

void buscar(int dato, nodo* arbol, int cont) {
	if (altura <= cont) {
		altura = cont;
	}
	if (arbol == NULL) {
		return;
	}
	else {
		if (dato == arbol->dato) {
			if (op34)
				cout << "Se encontró el dato " << dato << " en la altura: " << cont << endl;
			enc = true;
		}
		buscar(dato, arbol->derecha, cont + 1);
		buscar(dato, arbol->izquierda, cont + 1);
	}

}

void cambio(nodo *arbol){
	nodo *eliminar = NULL;
	nodo *PNULL = NULL;
	eliminar = arbol;
	if (arbol->padre == NULL){	
		if (eliminar->izquierda != NULL)
			eliminar = eliminar->izquierda;
		while (eliminar->derecha != NULL && arbol != NULL){
			eliminar = eliminar->derecha;
		}
		arbol->dato = eliminar->dato;
		if (eliminar->izquierda != NULL){
			eliminar->padre->derecha = eliminar->izquierda;
			eliminar->izquierda->padre = eliminar->padre;
		}
		else{
			eliminar->padre->derecha = NULL;
		}
		
	}
	else{
	if (eliminar->izquierda != NULL){
			eliminar = eliminar->izquierda;
		while (eliminar->derecha != NULL && arbol != NULL){
			eliminar = eliminar->derecha;
		}
		arbol->dato = eliminar->dato;
		if (eliminar->izquierda != NULL){
			arbol->izquierda = eliminar->izquierda;
			eliminar->izquierda->padre = arbol;
		}
		else{
			eliminar->padre->izquierda = NULL;
		}
	}
	else
	if (eliminar->derecha != NULL && arbol->padre == NULL){
		arbol = arbol->derecha;
	}
	else if (eliminar->derecha != NULL){
		arbol = arbol->derecha;
		eliminar->padre->derecha = arbol;
		arbol->padre = eliminar->padre;
	}
	}
	
	delete eliminar;
	eliminar = NULL;
}

// La función sirve para buscar el nodo a eliminar
bool borrar(int dato, nodo *arbol){
	bool encontrado = false;
	if (arbol->dato == dato){
		if (arbol->izquierda != NULL || arbol->derecha != NULL){
			cambio(arbol);
		}
		else{
			if (arbol->padre->derecha == arbol)
				arbol->padre->derecha = NULL;
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
	if (arbol->izquierda != NULL && arbol->derecha != NULL){	
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

int main() {
	setlocale(LC_ALL, "spanish");
	int op = 0;
	int dato;
	do {
		cout << "\tMenú\n";
		cout << "1. Insertar nodo \n2. Mostrar árbol\n3. Buscar si existe un número\n4. Altura de un nodo\n5. Altura del árbol\n";
		cout << "Opción: ";
		cin >> op;
		switch (op) {
		case 1:
			cout << "Dame el número a insertar: ";
			cin >> dato;
			insertar(dato, arbol);
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
		}
		system("CLS");
	} while (op != 10);

    cin.ignore();
    cin.get();
    return 0;
}