#include <iostream>
#include <string>

using namespace std;

std::string cifrar_vigenere(const std::string &texto, const std::string &clave) {
    std::string texto_cifrado;
    int clave_len = clave.length();
    
    for (size_t i = 0; i < texto.length(); ++i) {
        char texto_letra = texto[i];
        char clave_letra = clave[i % clave_len];
        
        if (std::isdigit(texto_letra) && std::isdigit(clave_letra)) {
            // Cifrar la letra del texto
            char letra_cifrada = ((texto_letra - '0') + (clave_letra - '0')) % 10 + '0';
            texto_cifrado += letra_cifrada;
        } else {
            // En caso de encontrar caracteres no numéricos, simplemente los agregamos sin cambios
            texto_cifrado += texto_letra;
        }
    }
    
    return texto_cifrado;
}

// Función para descifrar el texto cifrado usando el cifrado de Vigenère adaptado a números
std::string descifrar_vigenere(const std::string &texto_cifrado, const std::string &clave) {
    std::string texto_descifrado;
    int clave_len = clave.length();
    
    for (size_t i = 0; i < texto_cifrado.length(); ++i) {
        char texto_letra = texto_cifrado[i];
        char clave_letra = clave[i % clave_len];
        
        if (std::isdigit(texto_letra) && std::isdigit(clave_letra)) {
            // Descifrar la letra del texto cifrado
            char letra_descifrada = ((texto_letra - clave_letra + 10) % 10) + '0';
            texto_descifrado += letra_descifrada;
        } else {
            // En caso de encontrar caracteres no numéricos, simplemente los agregamos sin cambios
            texto_descifrado += texto_letra;
        }
    }
    
    return texto_descifrado;
}

