
from constantes import commands
from constantes.ErrorMessage import *
from tabulate import tabulate

def gate(s, id_embalse, nivel_apertura,res):
    nivel_apertura = nivel_apertura.replace(".","")
    mensaje = commands.Command.Gate + id_embalse + nivel_apertura
    s.send(mensaje.encode("us-ascii"))
    buf = s.recv(1024)
    buf = buf.decode("us-ascii")


    if iserror(buf, res):
        pass
    else:
        buf = buf[3:]
        res.set("El nuevo nivel de apertura es de: {},{}% ".format(nivel_apertura[:2], nivel_apertura[2]))

def leve(s,id_embalse,res):
    mensaje = commands.Command.Level + id_embalse
    s.send(mensaje.encode("us-ascii"))
    buf = s.recv( 1024 )
    buf = buf.decode("us-ascii")
    if iserror(buf,res):
        pass
    else:
        buf = buf[3:]
        lista_niveles = []
        if not id_embalse:
            while buf:
                id_nivel = (buf[:5] , "{}.{}%".format(buf[5:7],buf[7]))
                lista_niveles.append(id_nivel)
                buf = buf[8:]
        else:
            id_nivel = (id_embalse, "{}.{}%".format(buf[5:7],buf[7]))
            lista_niveles.append(id_nivel)
        res.set(tabulate([[i[0],i[1]] for i in lista_niveles],["Id Embalse","Nivel %"],tablefmt ="fancy_grid"))

def stat(s,id_embalse,res):
    mensaje = commands.Command.State + id_embalse
    s.send(mensaje.encode("us-ascii"))
    buf = s.recv( 1024 )
    buf = buf.decode("us-ascii")
    if iserror(buf,res):
        pass
    else:
        buf = buf[3:]
        res.set("El nivel del embalse es de: {},{}% ".format(buf[:2],buf[2]))

def name(s,res):
    mensaje = commands.Command.Name
    s.send(mensaje.encode("us-ascii"))
    buf = s.recv(1024)
    buf = buf.decode("us-ascii")
    if iserror(buf, res):
        pass
    else:
        buf = buf[3:]
        buf = buf.split(":")

        res.set( tabulate([[embalse[:5],embalse[5:]] for embalse in buf],["Id Embalse ", "Nombre "],tablefmt="fancy_grid"))

def iserror(message, res):
    if (message.startswith("ER-")):
        if len(message) == 4:
            code = int(message[3])
            res.set(ER_MSG1[code])
        else:
            code = int(message[4])
            res.set(ER_MSG2[code])

        return True
    else:
        return False