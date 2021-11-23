#!/usr/bin/env python3

import socket

from funciones.Comandos import *
from tkinter import *
from funciones.tkinter_custom_button import TkinterCustomButton


SERVER = 'localhost'
PORT = 60013


def gui(s):
    
    def clear():
        list = root.pack_slaves() + root.place_slaves()
        for l in list:
            l.destroy()
        
    def winGate():
        lblAviso = Label(root,text ="NOTA: el nivel de apertura del embalse se especifica en porcentaje, con dos numeros en la parte entera y uno en la parte fraccional, separados por un punto.",
                         bg="#121212",fg="#FFFFFF",wraplengt =390,justify= LEFT)
        lblAviso.pack(pady = 20)

        frame = LabelFrame(root,text = "Modificar nivel de apertura",font = 30,bg='#121212',fg="white",labelanchor="n",padx = 50,pady=30)
        frame.place(relx=0.5, rely=0.4, anchor=CENTER)

        lbl1 = Label(frame,text ="Id del embalse:",bg="#121212",fg="#FFFFFF")
        lbl1.grid(row=0, column=0,padx = 10,pady=10)
        id_embalse = Entry(frame,width=7)
        id_embalse.grid(row=0,column=1)

        lbl2 = Label(frame,text ="Nivel de apertura:",bg="#121212",fg="#FFFFFF")
        lbl2.grid(row=1, column=0,padx = 10,pady=10)
        apertura = Entry(frame,width=4)
        apertura.grid(row=1,column=1)

        res = StringVar()

        lblResultado = Label(root, textvariable=res, bg="#121212", fg="#FFFFFF")
        lblResultado.place(relx=0.5, rely=0.8, anchor=CENTER)

        botonSubmit = TkinterCustomButton(master=root,text="OK",fg_color="#3d3d3d",hover_color = "#aaaaaa",
                                        width=100,corner_radius=20,command = lambda:[gate(s, id_embalse.get(), apertura.get(),res)])
        botonSubmit.place(relx=0.5, rely=0.6,anchor = CENTER)


        botonAtras = TkinterCustomButton(master=root,text="<",fg_color="#3d3d3d",hover_color = "#aaaaaa",
                                        width=40,corner_radius=20,command = lambda:[clear(),inicio()])
        botonAtras.place(relx=0.5,rely=0.9,anchor=CENTER)

    def winStat():

        frame = LabelFrame(root,text = "Consultar apertura de embalse",font = 30,bg='#121212',fg="white",labelanchor="n",padx = 50,pady=30)
        frame.place(relx=0.5, rely=0.4, anchor=CENTER)

        lbl1 = Label(frame,text ="Id del embalse:",bg="#121212",fg="#FFFFFF")
        lbl1.grid(row=0, column=0,padx = 10,pady=10)
        id_embalse = Entry(frame,width=7)
        id_embalse.grid(row=0,column=1)

        res = StringVar()

        lblResultado = Label(root,textvariable = res,bg="#121212",fg="#FFFFFF")
        lblResultado.place(relx=0.5,rely=0.8,anchor=CENTER)

        botonSubmit = TkinterCustomButton(master=root,text="OK",fg_color="#3d3d3d",hover_color = "#aaaaaa",
                                        width=100,corner_radius=20,command = lambda:stat(s,id_embalse.get(),res))
        botonSubmit.place(relx=0.5, rely=0.6,anchor = CENTER)

        botonAtras = TkinterCustomButton(master=root,text="<",fg_color="#3d3d3d",hover_color = "#aaaaaa",
                                        width=40,corner_radius=20,command = lambda:[clear(),inicio()])
        botonAtras.place(relx=0.5,rely=0.9,anchor=CENTER)

    def winName():
        res = StringVar()
        frame = LabelFrame(root, text="Consultar LISTADO de embalses", font=30, bg='#121212', fg="white",
                           labelanchor="n", padx=50, pady=30)
        frame.place(relx=0.5, rely=0.4, anchor=CENTER)

        lblResultado = Label(frame, textvariable=res, bg="#121212", fg="#FFFFFF")
        lblResultado.grid(row=0, column=0)

        botonAtras = TkinterCustomButton(master=root, text="<", fg_color="#3d3d3d", hover_color="#aaaaaa",
                                         width=40, corner_radius=20, command=lambda: [clear(), inicio()])
        botonAtras.place(relx=0.5, rely=0.9, anchor=CENTER)

        botonSubmit = TkinterCustomButton(master=root, text="Get list", fg_color="#3d3d3d", hover_color="#aaaaaa",
                                          width=100, corner_radius=20, command=lambda: name(s,res))
        botonSubmit.place(relx=0.5, rely=0.7, anchor=CENTER)
    def winLeve():
        lblAviso = Label(root,text ="NOTA: Si se quiere consultar el estado de todos los embalses dejar el campo \"Id del embalse\" vacio.",
                         bg="#121212",fg="#FFFFFF",wraplengt =395,justify= LEFT)
        lblAviso.pack(pady = 20)

        frame = LabelFrame(root,text = "Consultar llenado de embalses",font = 30,bg='#121212',fg="white",labelanchor="n",padx = 50,pady=30)
        frame.place(relx=0.5, rely=0.3, anchor=CENTER)

        lbl1 = Label(frame,text ="Id del embalse:",bg="#121212",fg="#FFFFFF")
        lbl1.grid(row=0, column=0,padx = 10,pady=10)

        id_embalse = Entry(frame,width=7)
        id_embalse.grid(row=0,column=1)

        res = StringVar()

        lblResultado = Label(root,textvariable = res,bg="#121212",fg="#FFFFFF")
        lblResultado.place(relx=0.5,rely=0.7,anchor=CENTER)

        botonSubmit = TkinterCustomButton(master=root,text="OK",fg_color="#3d3d3d",hover_color = "#aaaaaa",
                                        width=100,corner_radius=20,command = lambda: leve(s,id_embalse.get(),res))
        botonSubmit.place(relx=0.5, rely=0.4,anchor = CENTER)

        botonAtras = TkinterCustomButton(master=root,text="<",fg_color="#3d3d3d",hover_color = "#aaaaaa",
                                        width=40,corner_radius=20,command = lambda:[clear(),inicio()])
        botonAtras.place(relx=0.5,rely=0.9,anchor=CENTER)

    def inicio():
        root.title("Gestion de Embalses")

        frame = LabelFrame(root,text = "MENU",font = 30,fg="white",labelanchor="n",padx = 50,pady=30)
        frame.configure(background='#121212')
        frame.pack(padx = 20, pady = 50)


        botonGate = TkinterCustomButton(master=frame,text="Modificar nivel de apertura",fg_color="#3d3d3d",hover_color = "#aaaaaa",
                                        width=230,corner_radius=10,command = lambda:[clear(),winGate()])
        botonGate.pack(pady = 20)

        botonStat = TkinterCustomButton(master=frame,text="Consultar apertura de embalse",fg_color="#3d3d3d",hover_color = "#aaaaaa",
                                        width=230,corner_radius=10,command = lambda:[clear(),winStat()])
        botonStat.pack(pady = 20)

        botonName = TkinterCustomButton(master=frame,text="Listado de embalses",fg_color="#3d3d3d",hover_color = "#aaaaaa",
                                        width=230,corner_radius=10,command = lambda:[clear(),winName()])
        botonName.pack(pady = 20)
        
        botonLeve = TkinterCustomButton(master=frame,text="Consultar llenado de embalses",fg_color="#3d3d3d",hover_color = "#aaaaaa",
                                        width=230,corner_radius=10,command = lambda:[clear(),winLeve()])
        botonLeve.pack(pady = 20)

        botonSalir = TkinterCustomButton(master=frame,text="Salir",fg_color="#3d3d3d",hover_color = "#aaaaaa",
                                        width=230,corner_radius=10,command = root.destroy)
        botonSalir.pack(pady = 20)

    root = Tk()
    root.geometry("400x600")
    root.configure(background='#121212')
    inicio()
    root.mainloop()



if __name__ == "__main__":
    if len( sys.argv ) > 3:
        print( "Uso: {} [<servidor> [<puerto>]]".format( sys.argv[0] ) )
        exit( 2 )

    if len( sys.argv ) >= 2:
        SERVER = sys.argv[1]
    if len( sys.argv ) == 3:
        PORT = int( sys.argv[2])

    s = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )
    s.connect( (SERVER, PORT) )

    gui(s)

    s.close()