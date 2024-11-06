Corrector Ortográfico.

Breve descripción.

    El programa recibe un archivo de texto el cual puede contener errores ortográficos.
    Si el programa detecta errores, imprime las sugerencias en un archivo de texto de
    salida pasado por consola. Estas sugerencias se basan en un archivo diccionario 
    solicitado.

Construcción:

    $ make program

Corrección sin chequear duplicados:

    $ ./main archivoTexto.txt archivoSalida.txt

Corrección chequeando duplicados:

    $ ./main archivoTexto.txt archivoSalida.txt -cd

Eliminación de archivos generados:

    $ make clean