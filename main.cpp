//g++ -o prueba main.cpp  -std=c++11 `pkg-config --cflags --libs opencv4`
#include "escribirArchivos.cpp"
#include "leerArchivos.cpp"
using namespace std;


void imprimir_matriz(vector<vector<int>> matriz) {
	for (auto const& fila: matriz) {
		for (auto const& numero: fila) {
			cout << numero << " ";
		}
		cout << endl;
	}
}


void imprimir_matriz_imagen(vector<vector<vector<int>>> matriz_imagen) {
	for (auto const& fila: matriz_imagen) {
		for (vector<int> pixel: fila) {
			cout << pixel[0] << " " << pixel[1] << " " << pixel[2] << endl;
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {	
		cerr << "uso: " << argv[0] << "<nombre_imagen>";
		return 1;
	}

	string nombre_imagen = argv[1];

	vector<vector<vector<int>>> matriz_imagen = leer_imagen();

	escribir_archivo_binario(matriz_imagen);

	vector<vector<vector<int>>> matriz_leida_binario = leer_archivo_binario("binario.bin");

	generar_imagen(matriz_leida_binario);

	return 0;
}