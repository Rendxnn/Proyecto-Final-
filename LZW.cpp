#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> comprimir_lzw(const vector<unsigned char>& entrada) {
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


vector<unsigned char> descomprimir_lzw(const vector<int>& comprimido) {
    vector<unsigned char> salida;
    unordered_map<int, string> diccionario;

    for (int i = 0; i < 256; i++) {
        diccionario[i] = string(1, char(i));
    }

    string actual = diccionario[comprimido[0]];
    salida.insert(salida.end(), actual.begin(), actual.end());
    string previo = actual;

    for (size_t i = 1; i < comprimido.size(); ++i) {
        int codigo = comprimido[i];
        string entrada;
        
        if (diccionario.find(codigo) != diccionario.end()) {
            entrada = diccionario[codigo];
        } else if (codigo == diccionario.size()) {
            entrada = previo + previo[0];
        } else {
            throw runtime_error("Código de compresión LZW inválido.");
        }

        salida.insert(salida.end(), entrada.begin(), entrada.end());

        diccionario[diccionario.size()] = previo + entrada[0];
        previo = entrada;
    }

    return salida;
}