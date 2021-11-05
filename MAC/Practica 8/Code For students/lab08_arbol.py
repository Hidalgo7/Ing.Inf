
  
def prim_algorithm(graph):
    # TODO
    marcados = [0]
    arbol = [[float('inf') for i in range(len(graph))]for j in range(len(graph))]
    while len(marcados) < len(graph):
        min = float('inf')
        act = -1
        sig = -1
        for i in marcados:
            for j in [x for x in range(len(graph)) if x != i]:
                if graph[i][j] < min and j not in marcados:
                    min = graph[i][j]
                    act = i
                    sig = j
        
        arbol[act][sig] = arbol[sig][act] = min
        marcados.append(sig)
    
    print(arbol)
    return arbol

def test():
    
    g1 =  [[float("inf"), 2.0],
           [2.0, float("inf")]]
    
    assert prim_algorithm(g1) == g1
    
    
       
    g2 = [[float("inf"), 5.0, 3.0],
          [5.0, float("inf"), float("inf")],
          [3.0, float("inf"), float("inf")]]
    
    assert prim_algorithm(g2) == g2
        
    
    
    g3 = [[float("inf"), 1.0, 2.0, 3.0, 4.0],
          [1.0, float("inf"), float("inf"), float("inf"), 8.0],
          [2.0, float("inf"), float("inf"), 2.0, 3.0],
          [3.0, float("inf"), 2.0, float("inf"), 5.0],
          [4.0, 8.0, 3.0, 5.0, float("inf")]]
    
    assert prim_algorithm(g3) == [[float("inf"), 1.0, 2.0, float("inf"), float("inf")], 
                                  [1.0, float("inf"), float("inf"), float("inf"), float("inf")], 
                                  [2.0, float("inf"), float("inf"), 2.0, 3.0], 
                                  [float("inf"), float("inf"), 2.0, float("inf"), float("inf")], 
                                  [float("inf"), float("inf"), 3.0, float("inf"), float("inf")]] 
    
    
        
    g4 = [[float("inf"), 6.0, 2.0, 5.0],
          [6.0, float("inf"), 4.0, float("inf")],
          [2.0, 4.0, float("inf"), 2.0],
          [5.0, float("inf"), 2.0, float("inf")]]
    
    assert prim_algorithm(g4) == [[float("inf"), float("inf"), 2.0, float("inf")], 
                                  [float("inf"), float("inf"), 4.0, float("inf")], 
                                  [2.0, 4.0, float("inf"), 2.0], 
                                  [float("inf"), float("inf"), 2.0, float("inf")]]
    
    
       
    g5 = [[float("inf"), 10.0, 1.0, float("inf"), float("inf"), float("inf")],
          [10.0, float("inf"), float("inf"), 5.0, 4.0, float("inf")],
          [1.0, float("inf"), float("inf"), 8.0, 2.0, 3.0],
          [float("inf"), 5.0, 8.0, float("inf"), float("inf"), 2.0],
          [float("inf"), 4.0, 2.0, float("inf"), float("inf"), float("inf")],
          [float("inf"), float("inf"), 3.0, 2.0, float("inf"), float("inf")]]
    
    assert prim_algorithm(g5) == [[float("inf"), float("inf"), 1.0, float("inf"), float("inf"), float("inf")], 
                                  [float("inf"), float("inf"),float("inf"), float("inf"), 4.0, float("inf")], 
                                  [1.0, float("inf"), float("inf"), float("inf"), 2.0, 3.0], 
                                  [float("inf"), float("inf"), float("inf"), float("inf"), float("inf"), 2.0], 
                                  [float("inf"), 4.0, 2.0, float("inf"), float("inf"), float("inf")], 
                                  [float("inf"), float("inf"), 3.0, 2.0, float("inf"), float("inf")]]
    
    
    
    g6 = [[float("inf"), 3.0, 1.0, float("inf"), float("inf"), float("inf"), float("inf")],
          [3.0, float("inf"), 8.0, 10.0, 5.0, float("inf"), float("inf")],
          [1.0, 8.0, float("inf"), float("inf"), float("inf"), float("inf"), float("inf")],
          [float("inf"), 10.0, float("inf"), float("inf"), 6.0, float("inf"), 9.0],
          [float("inf"), 5.0, float("inf"), 6.0, float("inf"), 1.0, 2.0],
          [float("inf"), float("inf"), float("inf"), float("inf"), 1.0, float("inf"), 4.0],
          [float("inf"),float("inf"),float("inf"), 9.0, 2.0, 4.0, float("inf")]]
    
    
    assert prim_algorithm(g6) == [[float("inf"), 3.0, 1.0, float("inf"), float("inf"), float("inf"), float("inf")], 
                                 [3.0, float("inf"), float("inf"), float("inf"), 5.0, float("inf"), float("inf")], 
                                 [1.0, float("inf"), float("inf"), float("inf"), float("inf"), float("inf"), float("inf")], 
                                 [float("inf"), float("inf"), float("inf"), float("inf"), 6.0, float("inf"), float("inf")], 
                                 [float("inf"), 5.0, float("inf"), 6.0, float("inf"), 1.0, 2.0], 
                                 [float("inf"), float("inf"), float("inf"), float("inf"), 1.0, float("inf"), float("inf")], 
                                 [float("inf"), float("inf"), float("inf"), float("inf"), 2.0, float("inf"), float("inf")]]

    

test()
