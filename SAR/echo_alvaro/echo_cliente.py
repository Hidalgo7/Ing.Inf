import select
import socket, sys

PORT = 8001
TIMER = 1
MAX_INTENTOS = 3

"""NOTA:
Los números de los comentarios (entre paréntesis) identifican distintos
ejercicios. Es necesario realizar los distintos ejercicios de uno en
uno, probando su correcto funcionamiento antes de pasar al siguiente.
"""

if len(sys.argv) != 2:
    print("Uso: {} <servidor>".format(sys.argv[0]))
    exit(1)

"""A COMPLETAR POR EL ALUMNO:
(1) Usar la función gethostbyname para obtener la dirección IP del servidor y mostrarla en pantalla.
"""

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
hostname = socket.gethostname()
local_ip = socket.gethostbyname(hostname)

dir_serv = (sys.argv[1], PORT)

print("IP local: ", local_ip, "\n")

"""A COMPLETAR POR EL ALUMNO:
(2) "Conectar" el socket.
"""

s.connect(dir_serv)

print("Introduce el mensaje que quieres enviar (mensaje vacío para terminar):")
while True:
    mensaje = input()
    if not mensaje:
        break

    enviado = []
    i = 0
    while not enviado and i < MAX_INTENTOS:
        s.send(mensaje.encode())
        enviado, _, _ = select.select([s], [], [], TIMER)
        print(enviado)
        i += 1

    if enviado:
        buf = s.recv(1024)
        print("Mensaje enviado: ", buf.decode())

    else:
        print("Mensaje no enviado.")
        break
s.close()