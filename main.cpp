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

	vector<unsigned char> imagen = leer_imagen(nombre_imagen);
	cout << "Imagen leida correctamente" << endl;

	jpg_a_raw(imagen, nombre_imagen.substr(0, nombre_imagen.length() - 4) + ".raw");
	cout << "Imagen RAW generada correctamente" << endl;


	vector<int> imagen_comprimida = comprimir_lzw(imagen);
	cout << "Imagen original comprimida correctamente" << endl;

	for (int num: imagen_comprimida) {
		cout << num << " "; 
	}


	escribir_archivo_binario(nombre_imagen.substr(0, nombre_imagen.length() - 4) + ".comp", imagen_comprimida);
	cout << "Archivo de imagen comprimida generado" << endl;


	cout << endl << endl;

	cout << "INICIO DE DESCOMPRESIÓN" << endl;


	vector<int> imagen_comprimida_leida = leer_archivo_binario(nombre_imagen.substr(0, nombre_imagen.length() - 4) + ".comp");
	cout << "Imagen comprimida leida" << endl;

	for (int num: imagen_comprimida_leida) {
		cout << num << " ";
	}

	vector<unsigned char> imagen_descomprimida_leida = descomprimir_lzw(imagen_comprimida_leida);
	cout << "Imagen descomprimida" << endl;
	

	generar_imagen(imagen_descomprimida_leida, nombre_imagen.substr(0, nombre_imagen.length() - 4) + "_descomp.jpg");
	cout << "Imagen leida generada" << endl;

	return 0;
}