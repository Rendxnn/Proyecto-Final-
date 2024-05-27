#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <opencv2/opencv.hpp>

using namespace std; 


void escribir_archivo_plano(vector<vector<vector<int>>> matriz) {
	ofstream archivo("plano.txt");

	if (archivo.is_open()) {
		archivo << matriz.size() << " " << matriz[0].size() << endl;
		for (vector<vector<int>> fila: matriz) {
			for (vector<int> pixel: fila) {
                for (int color: pixel) {
                    archivo << color << " ";
                }
			}
			archivo << endl;
		}
		archivo.close();
	}
	else {
		cout << "error al escribir el archivo plano";
	}
}


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
            unsigned char binario = static_cast<unsigned char>(numero);
            archivo.write(reinterpret_cast<const char*>(&binario), sizeof(binario)); 
        }
    }
}




void generar_imagen(vector<unsigned char> imagen_vector, string nombre_imagen_salida) {
    int filas = (imagen_vector[0] << 8) + imagen_vector[1];
    int columnas = (imagen_vector[2] << 8) + imagen_vector[3];

    cout << "Filas: " << filas << ", Columnas: " << columnas << endl;

    // Crear un objeto Mat para manipular la imagen si es necesario
    cv::Mat imagen(filas, columnas, CV_8UC3);

    int indice = 4; // Empezamos después de las dimensiones
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cv::Vec3b &pixel = imagen.at<cv::Vec3b>(i, j);
            pixel[0] = imagen_vector[indice++]; // azul
            pixel[1] = imagen_vector[indice++]; // verde
            pixel[2] = imagen_vector[indice++]; // rojo
        }
    }

    // Mostrar la imagen en una ventana
    cv::imshow("imagen leida", imagen);
    cv::waitKey(0);

    // Guardar los datos en formato RAW
    ofstream archivo_salida(nombre_imagen_salida, ios::out | ios::binary);
    if (!archivo_salida) {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
        return;
    }

    // Escribir los datos de píxeles en el archivo
    archivo_salida.write(reinterpret_cast<char*>(&imagen_vector[4]), filas * columnas * 3);

    archivo_salida.close();
}