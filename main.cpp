//g++ -o prueba main.cpp  -std=c++11 `pkg-config --cflags --libs opencv4`
#include "escribirArchivos.cpp"
#include "leerArchivos.cpp"
#include "LZW.cpp"
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

	vector<unsigned char> imagen = leer_imagen(nombre_imagen);

	vector<int> imagen_comprimida = comprimir_lzw(imagen);

	cout << imagen.size() << " " << imagen_comprimida.size();

	escribir_archivo_binario(nombre_imagen.substr(0, nombre_imagen.size() - 4) + ".bin", imagen_comprimida);

	generar_imagen(imagen, nombre_imagen.substr(0, nombre_imagen.size() - 4) + "_salida.jpg");

	return 0;
}