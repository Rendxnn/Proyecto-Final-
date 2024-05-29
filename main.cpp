//g++ -o prueba main.cpp  -std=c++11 `pkg-config --cflags --libs opencv4`
#include "escribirArchivos.cpp"
#include "leerArchivos.cpp"
#include "LZW.cpp"
#include "vigenere.cpp"
using namespace std;


int main(int argc, char *argv[]) {
	if (argc != 3) {	
		cerr << "uso: " << argv[0] << "<nombre_imagen>" << "<clave_cifrado>";
		return 1;
	}

	string nombre_imagen = argv[1];
	string clave_cifrado = argv[2];
	string nombre_archivo_binario = nombre_imagen.substr(0, nombre_imagen.length() - 4) + ".bin";


	//LEER IMAGEN
	string imagen = leer_imagen(nombre_imagen);
	cout << "Imagen leida correctamente" << endl;


	//CIFRAR Y COMPRIMIR
	string imagen_cifrada = cifrar_vigenere(imagen, clave_cifrado);
	cout << "Imagen cifrada correctamente" << endl;

	vector<int> imagen_comprimida = comprimir_lzw(imagen_cifrada);
	cout << "imagen comprimida" << endl;


	//ESCRIBIR ARCHIVO BINARIO
	escribir_archivo_binario(nombre_archivo_binario, imagen_comprimida);


	//LEER ARCHIVO BINARIO
	vector<int> imagen_comprimida_leida = leer_archivo_binario(nombre_archivo_binario);


	//DESCOMPRIMIR Y DESCIFRAR
	string imagen_descomprimida = descomprimir_lzw(imagen_comprimida_leida);
	cout << "imagen descomprimida" << endl;

	string imagen_descifrada = descifrar_vigenere(imagen_descomprimida, clave_cifrado);
	cout << "Imagen descifrada correctamente" << endl;


	//RECONSTRUIR IMAGEN
	construir_imagen(imagen_descomprimida, nombre_imagen.substr(0, nombre_imagen.length() - 4) + "_salida_prueba.jpg");


	return 0;
}