#!/usr/bin/env python3

import socket, random

PORT = 60013

"""A COMPLETAR POR EL ALUMNO:
Crear un socket y asignarle su direccion.
"""
embalses = [["GI317", "776", "Iker"], ["NA071", "129", "Hidlago"]]

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(('', PORT))
print("Puerto:" + str(PORT))

while True:
    """A COMPLETAR POR EL ALUMNO:
    Recibir un mensaje y responder con el mismo.
    """
    buf, dir_cli = s.recvfrom(1024)
    mensaje = buf.decode()
    respuesta = ""
    if mensaje.startswith("GATE"):
        mensaje = mensaje[4:]
        if not mensaje or len(mensaje) != 8:
            respuesta += "ER-3"
        else:
            for embalse in embalses:
                if embalse[0] == mensaje[:5]:
                    embalse[1] = mensaje[5:8];

            respuesta += "OK+"


    elif mensaje.startswith("STAT"):
        mensaje = mensaje[4:]
        if not mensaje:
            respuesta += "ER-3"
        else:

            for embalse in embalses:
                if embalse[0] == mensaje:
                    respuesta += embalse[1]
            if respuesta:
                respuesta = "OK+" + respuesta
            else:
                respuesta += "ER-12"

    elif mensaje.startswith("LEVE"):
        mensaje = mensaje[4:]
        if not mensaje:
            respuesta += "OK+"
            for embalse in embalses:
                respuesta += embalse[0]
                respuesta += embalse[1]
        else:
            embalse = next((x for x in embalses if x[0] == mensaje), None)
            if embalse is not None:
                respuesta += "OK+"
                respuesta += embalse[0]
                respuesta += embalse[1]
            else:
                respuesta += "ER-14"

    elif mensaje.startswith("NAME"):
        respuesta += "OK+"
        for embalse in embalses:
            #print("\n"+respuesta)
            if len(respuesta) != 3:
                respuesta += ":" + embalse[0] + embalse[2]
            else:
                respuesta += embalse[0] + embalse[2]
    s.sendto(respuesta.encode("us-ascii"), dir_cli)

s.close()