#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <bitset>
#include <opencv2/opencv.hpp>
#include <iomanip> // Para std::setw y std::setfill

using namespace cv;
using namespace std;

string formatear_numero(int numero) {
    std::ostringstream oss;
    oss << std::setw(3) << std::setfill('0') << numero;
    return oss.str();
}

string leer_imagen(string nombre_imagen) {

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


    string imagen_leida = "";

    imagen_leida += formatear_numero(filas);
    imagen_leida += formatear_numero(columnas); 

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {

            unsigned char azul_actual = imagen.at<Vec3b>(i, j)[0];
            unsigned char verde_actual = imagen.at<Vec3b>(i, j)[1];
            unsigned char rojo_actual = imagen.at<Vec3b>(i, j)[2];

            imagen_leida += formatear_numero(azul_actual);
            imagen_leida += formatear_numero(verde_actual);
            imagen_leida += formatear_numero(rojo_actual);
        }
    }

    return imagen_leida;
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

        int valor_actual;
        while (archivo.read(reinterpret_cast<char*>(&valor_actual), sizeof(int))) {
            imagen.push_back(valor_actual);
        }
       
        archivo.close();
    }

    return imagen;
}




void generar_raw(const std::string &nombre_imagen, const std::string &nombre_raw) {
    cv::Mat imagen = cv::imread(nombre_imagen, cv::IMREAD_UNCHANGED);

    if (imagen.empty()) {
        std::cerr << "Error: No se pudo abrir la imagen " << nombre_imagen << std::endl;
        return;
    }

    std::ofstream rawFile(nombre_raw, std::ios::out | std::ios::binary);
    if (!rawFile) {
        std::cerr << "Error: No se pudo crear el archivo " << nombre_raw << std::endl;
        return;
    }

    rawFile.write(reinterpret_cast<const char*>(imagen.data), imagen.total() * imagen.elemSize());

    rawFile.close();

    std::cout << "Imagen guardada exitosamente en formato RAW en " << nombre_raw << std::endl;
}

