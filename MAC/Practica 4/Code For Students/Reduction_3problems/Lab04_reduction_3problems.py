from vertex_cover import solve_vc
import copy


def multisolve(graph, problem):    
    #TODO
    if problem == "VERTEX COVER":
        vertex_cover = solve_vc(graph)
        return vertex_cover
    elif problem == "CLIQUE":
        copia = copy.deepcopy(graph)
        for i in range(0,len(copia)):
            for j in range(0,len(copia[i])):
                copia[i][j] = 1 - copia[i][j]
        clique = solve_vc(copia)
        for i in range(0,len(clique)):
            clique[i] = 1 - clique[i]
        return clique;
    else:
        vertex_cover = solve_vc(graph)
        independence_set = []
        for i in range(0,len(vertex_cover)):
            x = 1 - vertex_cover[i]
            independence_set.append(x)
        return independence_set
        
    

def test():
   graph = [[1, 0, 1, 0], [0, 1, 0, 1], [1, 0, 1, 1], [0, 1, 1, 1]]
   
   sol_vertex = multisolve(graph, "VERTEX COVER")
   sol_clique = multisolve(graph, "CLIQUE")
   sol_independent_set =  multisolve(graph, "INDEPENDENT SET")
   
   assert sol_vertex in [[0,0,1,1], [1,0,0,1], [0,1,1,0]]
   assert sol_independent_set in [[1,0,0,1],[1,1,0,0],[0,1,1,0]]
   assert sol_clique in [[1,0,1,0],[0,0,1,1],[0,1,0,1]]
   
   graph = [[0,1,1],[1,0,1],[1,1,0]]
   
   sol_vertex = multisolve(graph, "VERTEX COVER")
   sol_clique = multisolve(graph, "CLIQUE")
   sol_independent_set =  multisolve(graph, "INDEPENDENT SET")
     
   assert sol_vertex in [[0,1,1], [1,0,1], [1,1,0]]
   assert sol_independent_set in [[1,0,0],[0,1,0],[0,0,1]]
   assert sol_clique in [[1,1,1]]


test()
