from itertools import permutations

# def permutaciones(l1):
#     return permutaciones_aux([],[],l1);
    
# def permutaciones_aux(r,s,t):
#     if t == []:
#         r.append(s)
#         s = []
#         return r
#     else:
#         copia_t = t.copy()
#         for i in t:
#             s.append(i)
#             copia_t.remove(i)
#             r = permutaciones_aux(r,s,copia_t)
#         return r
            

def Hamiltonian_circuit(g,l):
    salir = False
    i = 0
    while i < (len(l) - 1) and not salir:
        if g[l[i]][l[i+1]]:
            i += 1
        else:
            salir = True
    return not salir and g[l[i]][l[0]]

def graph_has_Hamiltonian_circuit(g):
    # g is a conected nondirected graph
    # decides whether g has a Hamiltonian circuit
    
    asignaciones = permutations(list(range(len(g))))
    for nodes in asignaciones:
        if Hamiltonian_circuit(g,nodes):
            return True
    return False
    
    #TODO


def test():

    
    g1 = [[1, 1, 1, 0, 0],
          [1, 1, 1, 1, 1],
          [1, 1, 1, 1, 1],
          [0, 1, 1, 1, 1],
          [0, 1, 1, 1, 1]]
    assert graph_has_Hamiltonian_circuit(g1)


    g2 = [[1, 1, 1, 0, 0, 0],
          [1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 0],
          [0, 1, 1, 1, 1, 1],
          [0, 1, 1, 1, 1, 1],
          [0, 0, 0, 1, 1, 1]]
    
    assert graph_has_Hamiltonian_circuit(g2)

    g3 = [[1, 1, 1, 0, 0, 0, 0, 0],
          [1, 1, 1, 1, 0, 1, 1, 1],
          [1, 1, 1, 0, 1, 1, 1, 1],
          [0, 1, 0, 1, 0, 1, 0, 0],
          [0, 0, 1, 0, 1, 0, 1, 0],
          [0, 1, 1, 1, 0, 1, 1, 1],
          [0, 1, 1, 0, 1, 1, 1, 1],
          [0, 1, 1, 0, 0, 1, 1, 1]]
    
    assert graph_has_Hamiltonian_circuit(g3)
    
    g4 = [[1, 1, 1, 0, 0, 0, 0, 0, 0, 0],
          [1, 1, 1, 1, 1, 1, 1, 0, 0, 0],
          [1, 1, 1, 0, 1, 1, 1, 0, 1, 0],
          [0, 1, 0, 1, 0, 1, 0, 0, 0, 0],
          [0, 1, 1, 0, 1, 1, 1, 0, 0, 0],
          [0, 1, 1, 1, 1, 1, 1, 1, 0, 0],
          [0, 1, 1, 0, 1, 1, 1, 1, 0, 1],
          [0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
          [0, 0, 1, 0, 0, 0, 0, 0, 1, 1],
          [0, 0, 0, 0, 0, 0, 1, 0, 1, 1]]
    
    assert not graph_has_Hamiltonian_circuit(g4)
    
    g5 = [[1, 1, 1, 0, 0, 0],
          [1, 1, 0, 1, 1, 0],
          [1, 0, 1, 1, 1, 1],
          [0, 1, 1, 1, 0, 1],
          [0, 1, 1, 0, 1, 0],
          [0, 0, 1, 1, 0, 1]]
    
    assert not graph_has_Hamiltonian_circuit(g5)
    
    g6 = [[1, 1, 0, 0],
          [1, 1, 1, 0],
          [0, 1, 1, 1],
          [0, 0, 1, 1]]
    
    assert not graph_has_Hamiltonian_circuit(g6)
    
    g7 = [[1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
          [0, 0, 0, 0, 0, 0, 0, 0, 1, 1]]
     
    
    assert not graph_has_Hamiltonian_circuit(g7)
    
    

test()

