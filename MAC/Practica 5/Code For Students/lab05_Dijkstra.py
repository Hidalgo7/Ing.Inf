from time import time
from math import inf




# algoritmo voraz de Dijkstra
def Dijkstra (graph, initial):
    #TODO
    pesos = [0.0] * len(graph)
    restantes = list(range(len(graph)))
    for i in range(0,len(pesos)):
        pesos[i] = graph[initial][i]
        
    restantes.remove(initial)
    
    while restantes:
        actual = restantes[0]
        for i in restantes:
            if pesos[actual] > pesos[i]:
                actual = i
        for i in range(0,len(pesos)):
            if pesos[i] > pesos[actual] + graph[actual][i]:
                pesos[i] = pesos[actual] + graph[actual][i]
        
        restantes.remove(actual)
        
    return pesos
        

def test():
    
    g0 =  [[0.0, 5.0, 1.0, inf],
          [5.0, 0.0, 1.0, 2.0],
          [1.0, 1.0, 0.0, 10.0],
          [inf, 2.0, 10.0, 0.0]]
    
    assert Dijkstra(g0, 3) == [4.0, 2.0, 3.0, 0.0]
    
    g1 =  [[0.0, 2.0],
           [2.0, 0.0]]
    
    assert Dijkstra(g1,0) == [0.0,2.0]
    
    g2 = [[0.0, 5.0, 3.0],
          [5.0, 0.0, inf],
          [3.0, inf, 0.0]]
    
    assert Dijkstra(g2, 1) == [5.0, 0.0, 8.0]
        
     
    g3 = [[0.0, 1.0, 2.0, 3.0, 4.0],
          [1.0, 0.0, inf, inf, 8.0],
          [2.0, inf, 0.0, 2.0, 2.0],
          [3.0, inf, 2.0, 0.0, 5.0],
          [4.0, 8.0, 2.0, 5.0, 0.0]]
    
    assert Dijkstra(g3, 3) == [3.0, 4.0, 2.0, 0.0, 4.0]
        
    g4 = [[0.0, 6.0, 2.0, 5.0],
          [6.0, 0.0, 4.0, inf],
          [2.0, 4.0, 0.0, 2.0],
          [5.0, inf, 2.0, 0.0]]
    
    assert Dijkstra(g4, 3) == [4.0, 6.0, 2.0, 0.0]
    
    g5 = [[0.0, 10.0, 1.0, inf, inf, inf],
          [10.0, 0.0, inf, 5.0, 4.0, inf],
          [1.0, inf, 0.0, 8.0, 2.0, 3.0],
          [inf, 5.0, 8.0, 0.0, inf, 2.0],
          [inf, 4.0, 2.0, inf, 0.0, inf],
          [inf, inf, 3.0, 2.0, inf, 0.0]]
    
    assert Dijkstra(g5, 0) == [0.0, 7.0, 1.0, 6.0, 3.0, 4.0]
    
    
    g6 = [[0.0, 3.0, 1.0, inf, inf, inf, inf],
          [3.0, 0.0, 8.0, 10.0, 5.0, inf, inf],
          [1.0, 8.0, 0.0, inf, inf, inf, inf],
          [inf, 10.0, inf, 0.0, 6.0, inf, 9.0],
          [inf, 5.0, inf, 6.0, 0.0, 1.0, 2.0],
          [inf, inf, inf, inf, 1.0, 0.0, 4.0],
          [inf,inf,inf, 9.0, 2.0, 4.0, 0.0]]
    
    assert Dijkstra(g6, 3)  == [13.0, 10.0, 14.0, 0.0, 6.0, 7.0, 8.0]

start_time = time()
test()
elapsed_time = time() - start_time   
print("Elapsed time: %0.10f seconds." % elapsed_time)       