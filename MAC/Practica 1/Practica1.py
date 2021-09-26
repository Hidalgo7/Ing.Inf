#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Sep 10 12:52:01 2021

@author: 953429
"""
import math
import random

#Ejercicio 1

def absoluto(n):
    print("El valor absoluto de %d es %d" %(n,abs(n)));
    
absoluto(-3);

#Ejercicio 2

print("\n")

def suma(a,b):
    print("La suma de %d y %d es %d" % (a,b,a+b));
    
suma(8,6);

#Ejercicio 3

print("\n")

def celsius_a_farenheit(t):
    print("%dº son %d F" %(t,9*t/5 +32));
    
celsius_a_farenheit(23);

#Ejercicio 4

print("\n")

def area_esfera(r):
    print("El area de la esfera con radio %d es %d" % (r,4*math.pi*r**2))
    
area_esfera(3);

#Ejercicio 5

print("\n")

def asserts(a,b,c):
    assert a == b;
    assert b < c;
    assert c > a;
    

asserts(2,2,4); #caso correcto
#asserts(5,2,7); #caso incorrecto (AssertionError)

#Ejercicio 6

print("\n")

def distancia_euclidea(A,B):
    print("La distancia euclidea entre (%d,%d) y (%d,%d) es %f" % (A[0],A[1],B[0],B[1],math.sqrt((A[0]-B[0])**2 + (A[1]-B[1])**2)));

distancia_euclidea([2,3],[1,0]);

#Ejercicio 7

print("\n")

def ecuacion(x,y):
    resultado = 5 * x**3 + math.sqrt(x**2+y**2) + math.e**math.log(x,math.e);
    print("El resultado para la ecuacion con los parametros %d y %d es %f" %(x,y,resultado));
    
ecuacion(2,6);

#Ejercicio 8

print("\n")

def inicializar_lista():
    lista = [1,2,3,4,5];
    print(lista);
    print(type(lista));
    
inicializar_lista();

#Ejercicio 9

print("\n")

def sustituir4():
    lista = [2,6,3,4,7,1,4,4,2,5,4,7]
    print(lista)
    lista = [10 if x == 4 else x for x in lista]    
    print(lista)
    
sustituir4();

#Ejercicio 10

print("\n")

def iteraciones_collatz():
    lista=[6, 11, 27, 32, 33]
    iteraciones = [0 for i in range(5)]
    for i in range(len(lista)):
        x = lista[i]
        while x > 1:
            if x % 2 == 0:
                x /= 2
            else:
                x = x*3+1
            iteraciones[i] += 1
    print("Lista: " + str(lista))
    print("Iteraciones: " + str(iteraciones))

iteraciones_collatz()

#Ejercicio 11

print("\n")

def inicializar_matriz():
    matriz = [[random.randint(-5,5) for i in range(6)] for j in range(3)]
    print(matriz)
    
inicializar_matriz()

#Ejercicio 12

print("\n")

def num_apariciones_matriz(m,x):
    cont = 0
    for i in m:
        for j in i:
            if j == x: 
                cont += 1
    
    print("El numero %d aparece %d veces en la matriz " %(x,cont) + str(m))

x = 1
m = [[random.randint(0,1) for i in range(3)] for j in range(3)]
num_apariciones_matriz(m,x)

#Ejercicio 13

print("\n")

def esta_en_matriz(m):
    esta = False
    i = 0
    while not esta and i < len(m):
        j = 0;
        while not esta and j < len(m[i]):
            if m[i][j] > 4 and m[i][j] < 7:
                esta = True
            else:
                j += 1
        if not esta:
            i += 1
    
    if esta:
        print("Hay un numero entre 4 y 7 en la matriz " + str(m) + " en la posicion [%d,%d]" %(i,j))
    else:
        print("No hay ningun numero entre 4 y 7 en la matriz " + str(m))
        
m = [[random.randint(0,1) for i in range(3)] for j in range(3)]

esta_en_matriz(m)

m = [[random.randint(2,8) for i in range(3)] for j in range(3)]

esta_en_matriz(m)

#Ejercicio 14

print("\n")

def numeros_booleanos():
    a = [random.randint(-5,5) for i in range(6)]
    b = [bool(random.getrandbits(1)) for i in range(6)]
    
    pos = neg = 0
    
    for i in range(len(a)):
        if a[i] > 0 and b[i]:
            pos += 1
        elif a[i] < 0 and not b[i]:
            neg += 1
        
    print(a)
    print(b)
    
    print("La correlacion Positivo/True y Negativo/False es (%d,%d)" %(pos,neg))
    
numeros_booleanos()
