#!/usr/bin/env python3

import socket, sys

PORT = 50200

# Comprueba que se ha pasado un argumento.
if len( sys.argv ) != 2:
    print( "Uso: {} <servidor>".format( sys.argv[0] ) )
    sys.exit( 1 )

"""A COMPLETAR POR EL ALUMNO:
Crear un socket y enviar peticion de conexion al servidor.
"""

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect((sys.argv[1],PORT))

print( "Introduce el mensaje que quieres enviar (mensaje vacío para terminar):" )
while True:
    mensaje = input()
    if not mensaje:
        break
    """A COMPLETAR POR EL ALUMNO:
    Enviar mensaje y recibir 'eco'.
    Mostrar en pantalla lo recibido.
    ¡Cuidado! Recuerda que no hay garantías de recibir
    el mensaje completo en una única lectura.
    """
    print("Longitud mensaje en caracteres: " + str(len(mensaje)))
    print("Longitud mensaje en bytes: " + str(len(mensaje.encode())))
    s.send(mensaje.encode())
    respuesta = ""
    while True:
        buf = s.recv(10)
        respuesta += buf.decode()
        if respuesta == mensaje:
            break
    print("Respuesta: " + respuesta)
s.close()
