#!/usr/bin/env python3

import socket, os, signal, select

PORT = 50005
MAX_WAIT = 120

"""NOTA:
Los números de los comentarios (entre paréntesis) identifican distintos
ejercicios. Es necesario realizar los distintos ejercicios de uno en
uno, probando su correcto funcionamiento antes de pasar al siguiente.
"""

s = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )

s.bind( ('', PORT) )

"""A COMPLETAR POR EL ALUMNO:
(2) Evitar que procesos hijo queden como zombi.
Para ello habra que usar la funcion 'signal' para que trate
las señales tipo SIGCHLD.
"""
signal.signal(signal.SIGCHLD,signal.SIG_IGN)

while True:
    buf, dir_cli = s.recvfrom( 1024 )
    
    """A COMPLETAR POR EL ALUMNO:
    (1) Crear un nuevo proceso que atienda al cliente. Para ello:
    · Crear un nuevo socket.
    · Conectar con el socket del cliente.
    · Responder al cliente y seguir con la comunicación
      hasta recibir un mensaje vacío.
    """
    if not os.fork():
        s.close()
        dialogo = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )
        dialogo.connect(dir_cli)
        dialogo.send(buf)
        while True:
            rready, _, _ = select.select([dialogo],[],[],10)
            if not rready:
                break
            else:
                buf = dialogo.recv(1024)
                if not buf:
                    break
                dialogo.send(buf)
        print("Solicitud de cierre de conexion recibida.")
        dialogo.close()
        exit(0)
            
    """
    (3) Utilizar la funcion 'select' para comprobar que no
    llevamos mas de 2 minutos a la espera de recibir un
    mensaje. Si es así, acabar.
    """
s.close()