#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <bitset>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;



vector<vector<int>> leer_archivo_texto(string nombre_archivo) {
	ifstream archivo(nombre_archivo);
	vector<int> dimensiones(2, 0);


	if (archivo.is_open()) {
		vector<int> fila;
		string numero;
		string linea;

		getline(archivo, linea);
		stringstream stream(linea);
		while (getline(stream, numero, ' ')) {
			dimensiones.push_back(stoi(numero));
		}

		int filas = dimensiones[0];
		int columnas = dimensiones[1];

		vector<vector<int>> matriz(filas, vector<int>(columnas));


		while (getline(archivo, linea)) {
			stringstream stream(linea);
			while (getline(stream, numero, ' ')) {
				fila.push_back(stoi(numero));
			}
		matriz.push_back(fila);
		fila = {};
		}
		return matriz;
	}
	else {
		cout << "hubo un problema leyendo el archivo";
		return {{}};
	}
}



vector<int> leer_archivo_binario(string nombre_archivo) {

    ifstream archivo(nombre_archivo, ios::binary);
    vector<int> imagen;

    if (archivo.is_open()) {
        string nombre;
        string edad;
        string altura;
        string peso;
        string cedula;
        string diagnostico;

        vector<string> datos(6);
        vector<string> nombres_datos = {"nombre", "edad", "altura", "peso", "cedula", "diagnostico"};
        vector<int> longitudes_maximas = {30, 3, 3, 3, 10, 100};

        cout << "DATOS DEL PACIENTE: " << endl;
        for (int i = 0; i < longitudes_maximas.size(); i++) {
            int longitud = longitudes_maximas[i];
            string nombre_dato = nombres_datos[i];

            unsigned char buffer[longitud];
            archivo.read(reinterpret_cast<char*>(buffer), longitud);
            string dato_actual(reinterpret_cast<char*>(buffer), longitud);

            cout << nombre_dato << ": " << dato_actual << endl;
        }


        unsigned short binario_filas, binario_columnas;
        archivo.read(reinterpret_cast<char*>(&binario_filas), sizeof(binario_filas));
        archivo.read(reinterpret_cast<char*>(&binario_columnas), sizeof(binario_columnas));

        int filas = static_cast<int>(binario_filas);
        int columnas = static_cast<int>(binario_columnas);

        unsigned char binario_color;
        while (archivo.read(reinterpret_cast<char*>(&binario_color), sizeof(binario_color))) {
            imagen.push_back(static_cast<int>(static_cast<unsigned char>(binario_color)));
        }
       

        archivo.close();
    }

    return imagen;
}


vector<unsigned char> leer_imagen(string nombre_imagen) {

    cv::Mat imagen = cv::imread(nombre_imagen, cv::IMREAD_COLOR);

    if (imagen.empty()) {
        cout << "No se pudo cargar la imagen." << endl;
        return {};  
    }

    int filas = imagen.rows;
    int columnas = imagen.cols;
    int canales = imagen.channels();

    cout << "Dimensiones de la imagen: " << imagen.rows << "x" << imagen.cols << endl;
    cout << "Número de canales: " << imagen.channels() << endl;


    vector<unsigned char> imagen_leida;

    imagen_leida.push_back(static_cast<unsigned char>(filas >> 8));
    imagen_leida.push_back(static_cast<unsigned char>(filas & 0xFF));

    imagen_leida.push_back(static_cast<unsigned char>(columnas >> 8));
    imagen_leida.push_back(static_cast<unsigned char>(columnas & 0xFF));

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {

            unsigned char azul_actual = static_cast<unsigned char>(imagen.at<Vec3b>(i, j)[0]);
            unsigned char verde_actual = static_cast<unsigned char>(imagen.at<Vec3b>(i, j)[1]);
            unsigned char rojo_actual = static_cast<unsigned char>(imagen.at<Vec3b>(i, j)[2]);

            imagen_leida.push_back(azul_actual);
            imagen_leida.push_back(verde_actual);
            imagen_leida.push_back(rojo_actual);

        }
    }

    return imagen_leida;
}

void jpg_a_raw(vector<unsigned char> imagen_vector, string nombre_imagen_raw) {

    ofstream archivo_salida(nombre_imagen_raw, ios::out | ios::binary);
    if (!archivo_salida) {
        cerr << "No se pudo abrir el archivo RAW para escribir: " << nombre_imagen_raw << endl;
        return;
    }

    archivo_salida.write(reinterpret_cast<char*>(imagen_vector.data()), imagen_vector.size());
    archivo_salida.close();

}