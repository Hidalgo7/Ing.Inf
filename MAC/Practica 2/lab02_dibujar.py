import para_dibujar as dib

def test():
    g  = [[1, 1, 1, 0, 0, 0],
          [1, 1, 1, 0, 1, 1],
          [1, 1, 1, 1, 1, 0],
          [0, 0, 1, 1, 1, 1],
          [0, 1, 1, 1, 1, 1],
          [0, 1, 0, 1, 1, 1]]
          
    dib.dibujar(g)
    
    g = [[1,0,1,0],
         [0,1,1,1],
         [1,1,1,0],
         [0,1,0,1]]
    
    dib.dibujar(g)
    G = dib.nuevo_formato(g)
    print(G)
    
test()