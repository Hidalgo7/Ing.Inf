#!/usr/bin/env python3

import socket, sys, select

PORT = 60001
TIMER = 1
MAX_INTENTOS = 3

"""NOTA:
Los números de los comentarios (entre paréntesis) identifican distintos
ejercicios. Es necesario realizar los distintos ejercicios de uno en
uno, probando su correcto funcionamiento antes de pasar al siguiente.
"""

if len( sys.argv ) != 2:
    print( "Uso: {} <servidor>".format( sys.argv[0] ) )
    sys.exit( 1 )

"""A COMPLETAR POR EL ALUMNO:
(1) Usar la función gethostbyname para obtener la dirección IP del servidor y mostrarla en pantalla.
"""

print("IP servidor: " + socket.gethostbyname(sys.argv[1]))
dir_serv = (sys.argv[1], PORT)

s = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )

"""A COMPLETAR POR EL ALUMNO:
(2) "Conectar" el socket.
"""
s.connect(dir_serv)
print( "Introduce el mensaje que quieres enviar (mensaje vacío para terminar):" )
while True:
    mensaje = input()
    if not mensaje:
        break
    """A COMPLETAR POR EL ALUMNO:
    (2) Puesto que el socket es "conectado", sustituir 'sendto' por la función 'send'.
    (3) Usar la funcion 'select' para esperar el "eco" del mensaje
        'TIMER' segundos como máximo. Si no se recibe, retransmitirlo.
        Añadir un nuevo bucle para poder hacer varias retransmisiones.
        Avisar al usuario por cada retransmisión realizada.
    (4) Controlar el numero máximo de transmisiones de un mensaje dado.
        Avisar al usuario cuando se dé este hecho y terminar la ejecución.
    """
    rready = []
    cont = 0
    
    while not rready and cont < MAX_INTENTOS:
        s.send( mensaje.encode())
        print("Paquete enviado")
        rready, _, _ = select.select([s],[],[],TIMER)
        cont += 1
    
    if cont == MAX_INTENTOS:
        print("Numero maximo de intentos alcanzado. Cerrando conexion.")
        break
    else:
        buf = s.recv( 1024 )
        print("Respuesta: " + buf.decode() )
s.close()
