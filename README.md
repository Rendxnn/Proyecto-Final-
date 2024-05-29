# PROYECTO FINAL
## SISTEMAS OPERATIVOS
### Samuel García
### Sofía Mendieta
### Samuel Rendón

<hr>


## PREGUNTAS


### 1. ¿El orden entre encriptar y comprimir afecta el resultado?

Al utilizar el cifrado de Vigenere para el cifrado del mensaje (en este caso la imagen) es la misma que la del mensaje original. Sin emabrgo, si se encuentra un cambio de longitud para los mensajes al usar el método de compresión LZW. 

Si bien la estructura y contenido del mensaje varían para el orden de cifrado y compresión, su longitud puede ser variable al variar el orden de las operaciones al poder encontrar un mensaje más o menos propenso a compresión para LZW.

En resumen, sí, el orden de las operaciones puede afectar al resultado en su tamaño pero no en una medida significativa o facilmente predecible, ya que dependería qué mensaje es más compresible, el original o el cifrado.


<hr>

### 2. ¿Las imágenes médicas deben ser encriptadas o basta con encriptar el metadato?

El cifrado del mensaje para imágenes médicas puede no resultar en algo vital para la seguridad de la información, por lo cual, el cifrado de los metadatos puede resultar más que suficiente para la inmensa mayoría de los escenarios en los que se podría ver aplicada esta práctica.


<hr>

### 3. ¿Cuánto es el tamaño de los archivos?

Tras el proceso seguido para el programa desarrollado, trabajando las imágenes como cadenas para comprimirlas por medio de LZW, se evidencia una falencia de la compresión para las imágenes. 

Para el ejemplo de Lena:

Lena.png: 473,8 kB

Lena.raw: 786,4 kB

Lena.bin (cifrado y comprimido): 1,6 MB

Lena.jpg: 107,5 kB