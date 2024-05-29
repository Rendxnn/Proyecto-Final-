#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <opencv2/opencv.hpp>

using namespace std; 
using namespace cv;


void escribir_archivo_binario(string nombre_archivo, vector<int> imagen_comprimida) {

    string nombre;
    string edad;
    string altura;
    string peso;
    string cedula;
    string diagnostico;

    vector<int> longitudes_maximas = {30, 3, 3, 3, 10, 100};

    ofstream archivo(nombre_archivo, ios::binary);

    if (archivo.is_open()) {
        
        cout << "Ingrese los siguientes datos: " << endl << "nombre" << endl << "edad" << endl << "altura" << endl << "peso" << endl << "cedula" << endl << "diagnostico" << endl << endl;

        getline(cin, nombre);
        cin >> edad;
        cin >> altura;
        cin >> peso;
        cin >> cedula;
        cin.ignore();
        getline(cin, diagnostico);

        vector<string> datos = {nombre, edad, altura, peso, cedula, diagnostico};

        for (int i = 0; i < datos.size(); i++) {
            string dato = datos[i];
            for (int j = 0; j < longitudes_maximas[i]; j++) {
                if (j >= dato.length()) {
                    unsigned char caracter = 0; 
                    archivo.write(reinterpret_cast<const char*>(&caracter), sizeof(caracter));
                }
                else {
                    unsigned char caracter = dato[j];
                    archivo.write(reinterpret_cast<const char*>(&caracter), sizeof(caracter));
                }
            }
        }


        for (int numero: imagen_comprimida) {
            archivo.write(reinterpret_cast<char*>(&numero), sizeof(numero)); 
        }
    }
}




int extraer_numero(const string &imagen_str, size_t &indice, int longitud) {
    int numero = stoi(imagen_str.substr(indice, longitud));
    indice += longitud;
    return numero;
}


void construir_imagen(const string &imagen_str, const string &nombre_archivo) {
    size_t indice = 0;

    // Extraer dimensiones de la imagen
    int filas = extraer_numero(imagen_str, indice, 3); // Asumiendo que 'formatear_numero' usa 4 dígitos
    int columnas = extraer_numero(imagen_str, indice, 3);

    Mat imagen(filas, columnas, CV_8UC3);

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            unsigned char azul_actual = extraer_numero(imagen_str, indice, 3); // Asumiendo que 'formatear_numero' usa 3 dígitos
            unsigned char verde_actual = extraer_numero(imagen_str, indice, 3);
            unsigned char rojo_actual = extraer_numero(imagen_str, indice, 3);

            imagen.at<Vec3b>(i, j)[0] = azul_actual;
            imagen.at<Vec3b>(i, j)[1] = verde_actual;
            imagen.at<Vec3b>(i, j)[2] = rojo_actual;
        }
    }

    // Guardar la imagen reconstruida
    imwrite(nombre_archivo, imagen);
}