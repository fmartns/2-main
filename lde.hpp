#ifndef LDE_HPP
#define LDE_HPP
#include <string>

using namespace std;

template<typename T>
struct No {
	No <T> *eloA;
	T info;
	No <T> *eloP;
};

template<typename T>
struct LDE {
	No <T> *comeco;
	No <T> *fim;
};

template<typename T>
void inicializarLDE (LDE <T> &lista) {
	lista.comeco = NULL;
	lista.fim = NULL;
}

template<typename T>
bool inserirFinalLDE(LDE <T> &lista, T info) {
	No <T> *novo = new No <T>;

	if(novo == NULL) return false;
	novo->eloA = NULL;
	novo->info = info;
	novo->eloP = NULL;

	if(lista.comeco == NULL) {
		lista.comeco = novo;
		lista.fim = novo;
	} else {
		lista.fim->eloP = novo;
		novo->eloA = lista.fim;
		lista.fim = novo;
	}
	return true;
}

template<typename T>
bool inserirLDE(LDE<T> &lista, T info) {
    No<T> *novo = new No<T>;

    if(novo == NULL) return false;
    novo->eloA = NULL;
    novo->info = info;
    novo->eloP = NULL;

    if(lista.comeco == NULL) {
        lista.comeco = novo;
        lista.fim = novo;
    } else if(lista.comeco->info > novo->info) {
        lista.comeco->eloA = novo;
        novo->eloP = lista.comeco;
        lista.comeco = novo;
    } else if(lista.fim->info < novo->info) {
        lista.fim->eloP = novo;
        novo->eloA = lista.fim;
        lista.fim = novo;
    } else {
        No<T> *ant = lista.comeco;
        while(ant != NULL) {
            if(ant->info < novo->info && ant->eloP->info > novo->info) {
                novo->eloA = ant;
                novo->eloP = ant->eloP;
                ant->eloP->eloA = novo;
                ant->eloP = novo;
                break;
            }
            ant = ant->eloP;
        }
    }
    return true;
}

template<typename T>
void liberarLDE(LDE <T> &lista) {
	No <T> *aux = lista.comeco;
	No <T> *aux2;
	while( aux != NULL ) {
		aux2 = aux;
		aux = aux->eloP;
		delete aux2;
	}
}

template <typename T>
bool retirarLDE( LDE <T> &lista, T valor ) {
	No <T> *aux = pesquisarLDE(lista, valor);
	if( aux == NULL ) return false;

	if( aux == lista.comeco ) {
		if( aux == lista.fim ) { // Caso a
			lista.comeco = NULL;
			lista.fim = NULL;
		} else {  // Caso b
			lista.comeco = aux->eloP;
			lista.comeco->eloA = NULL;
		}
	}
	else if( aux == lista.fim ) { // Caso c
		lista.fim = aux->eloA;
		lista.fim->eloP = NULL;
	}
	else { // Caso d
		No <T> *ant = aux->eloA;
		No <T> *prox = aux->eloP;
		ant->eloP = prox;
		prox->eloA = ant;
	}
	delete aux;
	return true;
}

template<typename T>
No <T> *procurarLDE(LDE <T> &lista, int info) {
	No <T> *aux = lista.comeco;
	while(aux != NULL) {
		if(aux->info.info == info) {
			return aux;
		}
		aux = aux->eloP;
	}
	return NULL;
}

template <typename T>
bool removerLDE( LDE <T> &lista, int valor ) {
	No <T> *aux = procurarLDE(lista, valor);
	if( aux == NULL ) return false;

	if( aux == lista.comeco ) {
		if( aux == lista.fim ) { // Caso a
			lista.comeco = NULL;
			lista.fim = NULL;
		} else {  // Caso b
			lista.comeco = aux->eloP;
			lista.comeco->eloA = NULL;
		}
	}
	else if( aux == lista.fim ) { // Caso c
		lista.fim = aux->eloA;
		lista.fim->eloP = NULL;
	}
	else { // Caso d
		No <T> *ant = aux->eloA;
		No <T> *prox = aux->eloP;
		ant->eloP = prox;
		prox->eloA = ant;
	}
	delete aux;
	return true;
}
#endif