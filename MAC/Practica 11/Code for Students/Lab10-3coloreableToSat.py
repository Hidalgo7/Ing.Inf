import re, os
from time import time
from tools import list_minisat2list_our_sat
from colour_tools import fromAdjacencyToGX, visualizeGXGraph
from sat_solver import solve_SAT


def list2dimacs(my_list):
    print ('\n'.join(' '.join(map(str,sl)) for sl in my_list)) 
    return ('\n'.join(' '.join(map(str,sl)) for sl in my_list)) 


# colores [r, g, b]  ([red, green, blue])
# Cuando el grafo tiene m nodos tu formula tiene 3xm variables.
# Dada la variable i, (i-1)/3 corresponde al nodo del grafo y (i-1)%3 al color
def add_min_color_clauses(num_nodes,clauses):
    for i in range(0,num_nodes):
        clauses.append([i*3+1,i*3+2,i*3+3,0])

def add_max_color_clauses(num_nodes,clauses):
    for i in range(0,num_nodes):
        clauses.append([-(i*3+1),-(i*3+2),0])
        clauses.append([-(i*3+1),-(i*3+3),0])
        clauses.append([-(i*3+2),-(i*3+3),0])
    
def add_vertex_clauses(num_nodes,graph,clauses):
    for node1 in range(0,num_nodes):
        for node2 in range(0,num_nodes):
            if node1 != node2 and graph[node1][node2]:
                clauses.append([-(node1*3+1),-(node2*3+1),0])
                clauses.append([-(node1*3+2),-(node2*3+2),0])
                clauses.append([-(node1*3+3),-(node2*3+3),0])

def reduce_3colorable_to_SAT(graph):
   #TODO
   clauses = []
   clauses.append([])
   num_nodes = len(graph)
   
   add_min_color_clauses(num_nodes,clauses)
   add_max_color_clauses(num_nodes,clauses)
   add_vertex_clauses(num_nodes,graph,clauses)
   
   num_vars = 3*num_nodes
   num_clauses = len(clauses) - 1
   
   clauses[0] = ["p","cnf",num_vars,num_clauses]
   
   return clauses

         
def test():         
    g1 = [[1, 1, 1, 0],
          [1, 1, 1, 1],
          [1, 1, 1, 0],
          [0, 1, 0, 1]]
    
    f = open("g1.txt", "w")
    f.write(list2dimacs(reduce_3colorable_to_SAT(g1)))
    f.close()
    # SATISFIABLE
    
    graph = fromAdjacencyToGX(g1)
    print(graph)
    visualizeGXGraph(graph, "g1.txt")

    
    g2 = [[1, 1, 1, 1],
          [1, 1, 0, 1],
          [1, 0, 1, 1],
          [1, 1, 1, 1]]
    
    f = open("g2.txt", "w")
    f.write(list2dimacs(reduce_3colorable_to_SAT(g2)))
    f.close()
    # SATISFIABLE

    graph = fromAdjacencyToGX(g2)
    print(graph)
    visualizeGXGraph(graph, "g2.txt")
   

    g3 = [[1, 1, 1, 1],
          [1, 1, 1, 1],
          [1, 1, 1, 1],
          [1, 1, 1, 1]]
    
    f = open("g3.txt", "w")
    f.write(list2dimacs(reduce_3colorable_to_SAT(g3)))
    f.close()
    # UNSATISFIABLE
    
    graph = fromAdjacencyToGX(g3)
    print(graph)
    visualizeGXGraph(graph, "g3.txt")


    g4 = [[1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0],
          [1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0],
          [1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0],
          [0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0],
          [1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0],
          [1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0],
          [1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0],
          [1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0],
          [1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1],
          [1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1],
          [0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1],
          [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1]]
    
    f = open("g4.txt", "w")
    f.write(list2dimacs(reduce_3colorable_to_SAT(g4)))
    f.close()
    # UNSATISFIABLE
    
    graph = fromAdjacencyToGX(g4)
    print(graph)
    visualizeGXGraph(graph, "g4.txt")


    g5 = [[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
          [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1]]
    
    f = open("g5.txt", "w")
    f.write(list2dimacs(reduce_3colorable_to_SAT(g5)))
    f.close()
    # UNSATISFIABLE
     
    graph = fromAdjacencyToGX(g5)
    print(graph)
    visualizeGXGraph(graph, "g5.txt")

    g6 = [[1, 1, 1, 0],
          [1, 1, 0, 1],
          [1, 0, 1, 1],
          [0, 1, 1, 1]]
    
    f = open("g6.txt", "w")
    f.write(list2dimacs(reduce_3colorable_to_SAT(g6)))
    f.close()
    # SATISFIABLE
    
    graph = fromAdjacencyToGX(g6)
    print(graph)
    visualizeGXGraph(graph, "g6.txt")
    
def sat_test():
    directory = "/home/hidalgo/Ing.Inf/MAC/Practica 11/Code for Students/"
    pattern = re.compile("^g[0-9]*\.txt$")
    for filename in os.listdir(directory):
        if pattern.match(filename):
            print(filename)
            tupla = list_minisat2list_our_sat(filename)
            start_time = time()
            print(solve_SAT(tupla[0],tupla[1]))
            elapsed_time = time() - start_time
            print("Elapsed time: " + str(elapsed_time))
test()

sat_test()
    
   
  