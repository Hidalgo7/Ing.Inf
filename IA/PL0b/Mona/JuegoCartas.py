from Cartas import Carta,Mazo,LaMona,Mano,ManoPersona
import random

class JuegoCartas:

    manos = []
    def __init__(self):
        self.mazo = Mazo()
        self.mazo.barajar()

        
    def inicializar_partida(self,n_jugadores=2):

        #el primer jugador siempre sera la maquina
        self.manos.append(LaMona('Ordenador'))
        for idxJug in range(1,n_jugadores+1):
            nombreJugador = input("Cual es el nombre del  jugador {0}?".format(idxJug))
            self.manos.append(ManoPersona(nombreJugador))

        
    def primera_ronda(self):
        self.manos[0].imprimir()
        contOut = self.manos[0].eliminar_parejas()
        print('Se han eliminado {0}'.format(contOut))
        self.manos[0].imprimir()
        for idxJug in range(1,n_jugadores+1):
            contOut = self.manos[idxJug].eliminar_parejas()
    
    def robar_carta(self,turno):
        carta = self.manos[turno-1].pop_carta(random.randint(0,self.manos[turno-1].cont_cartas()-1))
        self.manos[turno].anadir_carta(carta)
        print("Se ha robado la carta:")
        print(str(carta))
        print("del jugador " + self.manos[turno-1].jugador)
    
    def descartar(self,turno):
        contOut = self.manos[turno].eliminar_parejas()
        print('Se han eliminado {0}'.format(contOut))
        
    def partida_finalizada(self):
        terminada = False
        cont = sum(map(lambda x : x.esta_vacio(), juego.manos))
        print("{} jugadores han terminado la partida".format(cont))
        return terminada
        

if __name__ == "__main__":
    print('Ejecutando como programa principal')
    juego = JuegoCartas()
    n_jugadores = int(input("Cuantos jugadores tiene el juego (sin contar las maquina)? "))
    print(n_jugadores)
    manos = juego.inicializar_partida(n_jugadores)
    juego.mazo.repartir_cartas(juego.manos,40)
    juego.primera_ronda()
    numCartas = [mano.cont_cartas() for mano in juego.manos]
    turno = numCartas.index(max(numCartas))
    
    salir = juego.partida_finalizada()
    while not salir:
        turno += 1
        if turno == len(juego.manos):
            turno = 0
        juego.robar_carta(turno)
        juego.descartar(turno)
        
        salir = juego.partida_finalizada()

    #########################################################
    #TODO opcional si queréis podeis implementar el juego
    # tal que un jugador pueda decidir
    # a quien le roba una carta y luego se ha de comprobar si forma
    # nueva pareja con la robada
    # la maquina podra almacenar las que le ha robado cada cual
    # de forma que si precisa una carta que le han robado anteriormente pueda
    # recuperarla
    # el juego acabara cuando alguien se quede sin cartas
    # o haya una ronda completa en la que nadie haga parejas
    # en ese caso el que tenga mas cartas en la mano pierde
    ######################################################
    
    
