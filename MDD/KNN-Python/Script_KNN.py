import numpy as np
import pandas as pd
import statistics as st
import math
import csv
import matplotlib.pyplot as plt
import random
from sklearn.model_selection import KFold

def main():
    path_dataset = "mtcars.csv" # Escoged bien la ruta!!
    mtcars = pd.read_csv(path_dataset) # Leemos el csv
    # Discretizamos la variable clase para convertirlo en un problema de clasificacion
    ix_consumo_alto = mtcars.mpg >= 21
    mtcars.mpg[ix_consumo_alto] = 1
    mtcars.mpg[~ix_consumo_alto] = 0
    print("Este es el dataset sin normalizar")
    print(mtcars)
    print("\n\n")
    # Ahora normalizamos los datos
    mtcars_normalizado = mtcars.loc[:, mtcars.columns != 'mpg'].apply(normalize, axis=1)
    # Añadimos la clase a nuestro dataset normalizado
    mtcars_normalizado['mpg'] = mtcars['mpg']
    print("Este es el dataset normalizado")
    print(mtcars_normalizado)
    print("\n\n")
    # Hacemos un split en train y test con un porcentaje del 0.75 Train
    train,test = splitTrainTest(mtcars_normalizado,0.75)
    # Separamos las labels del Test. Es como si no nos las dieran!!
    labels = test.pop('mpg').tolist()
    print(labels)
    # Predecimos el conjunto de test

    # Mostramos por pantalla el Accuracy por ejemplo
    print("Accuracy conseguido:")
    print(accuracy(true_labels, predicted_labels))

    # Algun grafico? Libreria matplotlib.pyplot
    return(0)

# FUNCIONES de preprocesado
def normalize(x):
    return((x-min(x)) / (max(x) - min(x)))

def standardize(x):
    return((x-st.mean(x))/st.variance(x))

# FUNCIONES de evaluacion
def splitTrainTest(data, percentajeTrain):
    """
    Takes a pandas dataframe and a percentaje (0-1)
    Returns both train and test sets
    """
    v  = np.random.rand(len(data))
    mascara = v > 0.75
    
    train = data.loc[mascara]
    test = data.loc[~mascara]
    print("TRAIN: \n")
    print(train)
    print("TEST: \n")
    print(test)
    return(train,test)

def kFoldCV(data, K):
    """
    Takes a pandas dataframe and the number of folds of the CV
    YOU CAN USE THE sklearn KFold function here
    How to: https://scikit-learn.org/stable/modules/generated/sklearn.model_selection.KFold.html
    """

    return()

# FUNCION modelo prediccion
def knn(newx, data, K):
    """
    Receives two pandas dataframes. Newx consists on a single row df.
    Returns the prediction for newx
    """

    return(newlabel)

def euclideanDistance2points(x,y):
    """
    Takes 2 matrix - Not pandas dataframe!
    """
    

    return()

# FUNCION accuracy
def accuracy(true, pred):
    return()

if __name__ == '__main__':
    np.random.seed(25)
    main()
