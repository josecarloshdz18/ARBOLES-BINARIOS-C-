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