//g++ -o prueba main.cpp  -std=c++11 `pkg-config --cflags --libs opencv4`
#include "escribirArchivos.cpp"
#include "leerArchivos.cpp"
#include "LZW.cpp"
using namespace std;


int main(int argc, char *argv[]) {
	if (argc != 2) {	
		cerr << "uso: " << argv[0] << "<nombre_imagen>";
		return 1;
	}

	string nombre_imagen = argv[1];

	string imagen = leer_imagen(nombre_imagen);
	cout << "Imagen leida correctamente" << endl;
	
	vector<int> imagen_comprimida = comprimir_lzw(imagen);
	cout << "imagen comprimida" << endl;

	string imagen_descomprimida = descomprimir_lzw(imagen_comprimida);
	cout << "imagen descomprimida" << endl;

	construir_imagen(imagen_descomprimida, nombre_imagen.substr(0, nombre_imagen.length() - 4) + "_salida_prueba.jpg");
	

	return 0;
}