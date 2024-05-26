#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> comprimir_lzw(const string& entrada) {
	vector<int> comprimido;
	unordered_map<string, int> diccionario;

	for (int i = 0; i < 256; i++) {
		string caracter(1, char(i));
		diccionario[caracter] = i;
	}

	string actual;
	for (char caracter: entrada) {
		string temporal = actual + caracter;
		if (diccionario.find(temporal) != diccionario.end()) {
			actual = temporal;
		}
		else {
			comprimido.push_back(diccionario[actual]);
			diccionario[temporal] = diccionario.size();
			actual = string(1, caracter);
		}
	}

	if (!actual.empty()) {
		comprimido.push_back(diccionario[actual]);
	}

	return comprimido;
}


string descomprimir_lzw(const vector<int>& comprimido) {
	unordered_map<int, string> diccionario;
	string descomprimido;

	for (int i = 0; i < 256; i++) {
		string caracter(1, char(i));
		diccionario[i] = caracter;
	}

	string previo(1, char(comprimido[0]));
	string actual;
	actual += previo;
	descomprimido += previo;

	for (size_t i = 1; i < comprimido.size(); i++) {
		int valor = comprimido[i];

		if (diccionario.find(valor) == diccionario.end()) {
			actual = previo + previo[0];
		}
		else {
			actual = diccionario[valor];
		}

		descomprimido += actual;
		diccionario[diccionario.size()] = previo + actual[0];
		previo = actual;
	}

	return descomprimido;
}