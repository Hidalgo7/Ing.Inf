#!/usr/bin/env python3

import socket, sys

PORT = 50005

if len( sys.argv ) != 2:
    print( "Uso: {} <servidor>".format( sys.argv[0] ) )
    exit( 1 )

dir_serv = (sys.argv[1], PORT)

s = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )

"""A COMPLETAR POR EL ALUMNO:
Enviar primer mensaje y recibir respuesta.
"""
print( "Introduce el mensaje que quieres enviar (mensaje vacío para terminar):" )
mensaje = input()
s.sendto(mensaje.encode(),dir_serv)
buf, dir_serv = s.recvfrom(1024)
print(buf.decode())

"""A TENER EN CUENTA POR EL ALUMNO:
Verificar que el 'connect' se hace con el socket adecuado.
"""
s.connect( dir_serv )


while True:
    
    mensaje = input()
    if not mensaje:
        break
    s.send( mensaje.encode() )
    buf = s.recv( 1024 )
    print( buf.decode() )
"""A COMPLETAR POR EL ALUMNO:
Enviar un mensaje vacío para que acabe el proceso servidor.
"""
s.send(b"")
s.close()
