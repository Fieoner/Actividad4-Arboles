/*
 * Arbol.cpp
 *
 *  Created on: 21/12/2014
 *      Author: pmartin
 */

#include "Arbol.h"
#include <fstream>
#include <queue>

Arbol::Arbol () {
	raiz = NULL;
}
Arbol::Arbol (int dato) {
	raiz = new NodoArbol (dato);
}
void destruir (pNodoArbol &nodo) {
	if (nodo != NULL) {
		destruir (nodo->iz);
		destruir (nodo->de);
		delete nodo;
		nodo = NULL;
	}
}
Arbol::~Arbol () {
	pNodoArbol nodo = raiz;
	destruir (nodo);
	raiz = NULL;
}

void auxPreOrden (pNodoArbol nodo) {
	if (nodo != NULL) {
		cout << nodo->clave << " "; 	// Nodo
		auxPreOrden (nodo->iz);	 		// Izquierda
		auxPreOrden (nodo->de);			// Derecha
	}
}

void Arbol::preOrden () {
	auxPreOrden (raiz);
	cout << "FIN" << endl;
}

void auxOrdenCentral (pNodoArbol nodo) {
	if (nodo != NULL) {
		auxOrdenCentral (nodo->iz);	 	// Izquierda
		cout << nodo->clave << " "; 	// Nodo
		auxOrdenCentral (nodo->de);		// Derecha
	}
}

void Arbol::ordenCentral () {
	auxOrdenCentral (raiz);
	cout << "FIN" << endl;
}

void auxPostOrden (pNodoArbol nodo) {
	if (nodo != NULL) {
		auxPostOrden (nodo->iz);	 	// Izquierda
		auxPostOrden (nodo->de);		// Derecha
		cout << nodo->clave << " "; 	// Nodo
	}
}

void Arbol::postOrden () {
	auxPostOrden (raiz);
	cout << "FIN" << endl;
}

void Arbol::amplitud () {
	pNodoArbol p;
	queue <pNodoArbol> c;

	p = raiz;
	if (p != NULL)
		c.push (p);
	while (!c.empty ()) {
		p = c.front ();
		c.pop ();
		cout << p->clave << " ";
		if (p->iz != NULL)
			c.push (p->iz);
		if (p->de != NULL)
			c.push (p->de);
	}
	cout << "FIN" << endl;
}

void inserta (pNodoArbol &nodo, int valor) {

	if (nodo == NULL)
		nodo = new NodoArbol (valor);
	else if (valor != nodo->clave) {
		if (valor < nodo->clave)
			inserta (nodo->iz, valor);
		else inserta (nodo->de, valor);
	}
	else cout << "Error, la clave ya existe" << endl;
}

void Arbol::insertar (int x) {
	inserta (raiz, x);
}
void quitarSucesor (pNodoArbol nodoQuitar, pNodoArbol &sucesor) {
	pNodoArbol hijo;

	if (sucesor->de == NULL) {
		hijo = sucesor->iz;
		nodoQuitar->clave = sucesor->clave;
		delete sucesor;
		sucesor = hijo;
	}
	else quitarSucesor (nodoQuitar, sucesor->de);
}

void elimina (pNodoArbol &nodo, int valor) {
	pNodoArbol hijo;

	if (nodo != NULL) {
		if (valor == nodo->clave)
			if ((nodo->iz == NULL) || (nodo->de == NULL)) {
				if (nodo->iz == NULL)
					hijo = nodo->de;
				else hijo = nodo->iz;
				delete nodo;
				nodo = hijo;
			}
			else quitarSucesor (nodo, nodo->iz);
		else if (valor < nodo->clave)
			elimina (nodo->iz, valor);
		else elimina (nodo->de, valor);
	}
	else cout << "la clave buscada no existe" << endl;
}

void Arbol::eliminar (int x) {
	elimina (raiz, x);
}

void Arbol::rellenarArbol (string f) {
	ifstream s;
	int num;
	s.open(f.c_str());
	while (!s.eof()) {
		s >> num;
		insertar(num);
	}
}


int Arbol::sumaClavesImparesDosHijos (pNodoArbol p) {
	int resul = 0;
	if (p == NULL){
		if (raiz != NULL){
			p = raiz;
		}
		else {
			return 0;
		}
	}
	if (p->iz != NULL)
		resul += sumaClavesImparesDosHijos(p->iz);
	if (p->de != NULL)
		resul += sumaClavesImparesDosHijos(p->de);
	if (p->clave % 2 == 1 && p->iz != NULL && p->de != NULL)
		resul += p->clave;
	return resul;
}


void Arbol::mostrarClavesUnHijo (pNodoArbol p) {
	int hijos = 0;
	if (p == NULL){
		if (raiz != NULL){
			p = raiz;
		}
		else {
			return;
		}
	}
	if (p->de != NULL){
		mostrarClavesUnHijo(p->de);
	}
	if (p->de != NULL)
		hijos++;
	if (p->iz != NULL)
		hijos++;
	if (hijos == 1){
		cout << p->clave << endl;
	}
	if (p->iz != NULL){
		mostrarClavesUnHijo(p->iz);
	}
}
