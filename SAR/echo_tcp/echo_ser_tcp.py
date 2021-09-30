#!/usr/bin/env python3

import socket

PORT = 50200
"""A COMPLETAR POR EL ALUMNO:
Crear un socket, asignarle su dirección y
convertirlo en socket de escucha.
"""

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind(('',PORT))
s.listen(5)
dialogo,_ = s.accept()
print("IP cliente: " + dialogo.getpeername()[0])
while True:
    """A COMPLETAR POR EL ALUMNO:
    Aceptar peticion de conexion.
    Mientras el cliente no cierre la conexion,
    recibir un mensaje y responder con el mismo.
    Cerrar conexión.
    """
    
    mensaje = dialogo.recv(1024)
    if not mensaje:
        dialogo.close()
        break
    else:
        dialogo.sendall(mensaje)
    
    
"""A COMPLETAR POR EL ALUMNO:
Cerrar socket de escucha.
"""
s.close()

