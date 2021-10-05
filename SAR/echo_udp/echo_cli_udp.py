#!/usr/bin/env python3

import socket, sys

PORT = 60001

# Comprueba que se ha pasado un argumento.
if len( sys.argv ) != 2:
    print( "Uso: {} <servidor>".format( sys.argv[0] ) )
    sys.exit( 1 )

"""A COMPLETAR POR EL ALUMNO:
Crear el socket.
"""
dir_ser = ( sys.argv[1],PORT )
s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
s.bind(('',0))
print("Socket creado.\nDireccion IP:" + s.getsockname()[0] + "\nPuerto: " + str(s.getsockname()[1]))

print( "Introduce el mensaje que quieres enviar (mensaje vacío para terminar):" )
while True:
    mensaje = input()
    if not mensaje:
        break
    """A COMPLETAR POR EL ALUMNO:
    Enviar mensaje y recibir 'eco'.
    Mostrar en pantalla lo recibido.
    """
    s.sendto(mensaje.encode(),dir_ser)
    print("Longitud del mensaje enviado:\n" + str(len(mensaje.encode())) + " bytes\n" + str(len(mensaje)) + " caracteres")
    eco = s.recv(1024)
    print("Echo: " + eco.decode())
"""A COMPLETAR POR EL ALUMNO:
Cerrar socket.
"""

s.close()

