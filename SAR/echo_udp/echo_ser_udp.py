#!/usr/bin/env python3

import socket

PORT = 60001

"""A COMPLETAR POR EL ALUMNO:
Crear un socket y asignarle su direccion.
"""

s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
s.bind(('',PORT))

while True:
    """A COMPLETAR POR EL ALUMNO:
    Recibir un mensaje y responder con el mismo.
    """
    mensaje,dir_cli = s.recvfrom(1024)
    print("Cliente\nDireccion IP: " + dir_cli[0] + "\nPuerto: " + str(dir_cli[1]))
    s.sendto(mensaje,dir_cli)
"""A COMPLETAR POR EL ALUMNO:
Cerrar socket.
"""

s.close()
