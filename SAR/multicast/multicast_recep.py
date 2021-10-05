#!/usr/bin/env python3

import socket

PORT = 50006

s = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )

s.bind( ('', PORT) )

"""A COMPLETAR POR EL ALUMNO:
Asociar el socket a la dirección multicast.
"""
s.setsockopt(socket.IPPROTO_IP,socket.IP_ADD_MEMBERSHIP,socket.inet_aton("224.0.0.11")+socket.inet_aton("0.0.0.0"))

"""A COMPLETAR POR EL ALUMNO:
Eliminar bucle.
"""
buf, dir_cli = s.recvfrom( 1024 )

"""A COMPLETAR POR EL ALUMNO:
Responder al emisor con el código seguido del nombre del alumno.
Recibir respuesta e informar al usuario.
"""
buf += b"Iker Hidalgo|G10" 
s.sendto( buf, dir_cli)

"""A COMPLETAR POR EL ALUMNO:
Desasociar dirección multicast.
"""
s.setsockopt(socket.IPPROTO_IP,socket.IP_DROP_MEMBERSHIP,socket.inet_aton("224.0.0.11")+socket.inet_aton("0.0.0.0"))

s.close()
