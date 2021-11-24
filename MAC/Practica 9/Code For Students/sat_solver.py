import os
from time import time
from copy import deepcopy
from tools import list_minisat2list_our_sat
from pre_processing import sat_preprocessing
      
def check_SAT(num_variables,clauses,assignment):
    for clause in clauses:
        sat = False
        i = 0
        while not sat and i < len(clause):
            if clause[i] is not None:
                if clause[i] > 0:
                    if assignment[clause[i]] == 1:
                        sat = True
                else:
                    if assignment[-clause[i]] == 0:
                        sat = True
            i +=1
        if not sat:
            return "UNSATISFIABLE"
    return True

def solve_SAT_aux(num_variables,clauses,assignment):
    print(assignment)
    if clauses == [[1],[-1]]:
        return "UNSATISFIABLE"
    elif check_SAT(num_variables,clauses,assignment) == True:
        return assignment
    else:
        found = False
        i = 0
        while i < len(clauses) and not found:
            clause = clauses[i]
            for literal in clause:
                if assignment[abs(literal)] is None:
                    valor_literal = abs(literal)
                    found = True
            
            i += 1
        if found:
            copy = list(assignment)
            copy[valor_literal] = 0
            sol = solve_SAT_aux(num_variables,clauses,copy)
            if sol == "UNSATISFIABLE":
                copy[valor_literal] = 1
                sol = solve_SAT_aux(num_variables,clauses,copy)
            return sol
        else:
            return "UNSATISFIABLE"
    
def solve_SAT(num_variables, clauses):
   #TODO
   assignment = [None] * (num_variables+1)
   clauses,assignment = sat_preprocessing(num_variables,clauses,assignment)
   return solve_SAT_aux(num_variables,clauses,assignment)
   
    
def test():
    clauses = [[-2, -3, -1], [3, -2, 1], [-3, 2, 1],
               [2, -3, -1], [3, -2, 1], [3, -2, 1]]
    solutions = [[0, 0, 0, 0],
                 [0, 0, 1, 1],
                 [0, 1, 0, 0],
                 [0, 1, 1, 0],
                 [1, 0, 0, 0],
                 [1, 0, 1, 1],
                 [1, 1, 0, 0],
                 [1, 1, 1, 0],
                 [None, 0, 0, 0],
                 [None, 0, 1, 1],
                 [None, 1, 0, 0],
                 [None, 1, 1, 0]]
    
    assert solve_SAT(3,clauses) in solutions
    print("-"*40)
    
    clauses = [[1, -2, -3], [2, -3, 1], [3, -2, 1],
               [2, 3, 1]]
    solutions = [[0, 1, 0, 0], 
                 [0, 1, 0, 1], 
                 [0, 1, 1, 0], 
                 [0, 1, 1, 1], 
                 [1, 1, 0, 0], 
                 [1, 1, 0, 1], 
                 [1, 1, 1, 0], 
                 [1, 1, 1, 1],
                 [None, 1, 0, 0], 
                 [None, 1, 0, 1], 
                 [None, 1, 1, 0], 
                 [None, 1, 1, 1],
                 [None, 1, None, None],
                 [1, 1, None, None]]
    assert solve_SAT(3,clauses) in solutions
    print(solve_SAT(3,clauses))
    print("-"*40)

    clauses = [[2, 1, 3], [-2, -1, 3], [-2, 3, -1], [-2, -1, 3],
               [2, 3, 1], [-1, 3, -2], [-3, 2, 1], [1, -3, -2],
               [-2, -1, 3], [1, -2, -3], [-2, -1, 3], [-1, -2, -3],
               [3, -2, 1], [2, 1, 3], [-3, -1, 2], [-3, -2, 1],
               [-1, 3, -2], [1, 2, -3], [-3, -1, 2], [2, -1, 3]]
    assert solve_SAT(3,clauses) == "UNSATISFIABLE"
    print(solve_SAT(3,clauses))
    print("-"*40)
     
    clauses = [[4, -18, 19],[3, 18, -5],[-5, -8, -15],[-20, 7, -16],[10, -13, -7],
               [-12, -9, 17],[17, 19, 5],[-16, 9, 15], [11, -5, -14],[18, -10, 13],
               [-3, 11, 12],[-6, -17, -8],[-18, 14, 1],[-19, -15, 10],[12, 18, -19],
               [-8, 4, 7],[-8, -9, 4],[7, 17, -15],[12, -7, -14],[-10, -11, 8],
               [2, -15, -11],[9, 6, 1],[-11, 20, -17],[9, -15, 13],[12, -7, -17],
               [-18, -2, 20],[20, 12, 4],[19, 11, 14],[-16, 18, -4],[-1, -17, -19],
               [-13, 15, 10],[-12, -14, -13],[12, -14, -7],[-7, 16, 10],[6, 10, 7],
               [20, 14, -16],[-19, 17, 11],[-7, 1, -20],[-5, 12, 15],[-4, -9, -13],
               [12, -11, -7],[-5, 19, -8],[-16],[20, -14, -15],[13, -4, 10],
               [14, 7, 10],[-5, 9, 20],[10, 1, -19],[-16, -15, -1],[16, 3, -11],
               [-15, -10, 4],[4, -15, -3],[-10, -16, 11],[-8, 12, -5],[14, -6, 12],
               [1, 6, 11],[-13, -5, -1],[-12],[1, -20, 19],[-2, -13, -8],
               [18],[-11, 14, 9],[-6, -15, -2],[-5],[-6, 17, 5],
               [-13, 5, -19],[20, -1, 14],[9, -17, 15],[-5, 19, -18],[-12, 8, -10],
               [-18, 14, -4],[15, -9, 13],[9, -5, -1],[10, -19, -14],[20, 9, 4],
               [-9, -2, 19],[-5, 13, -17],[2, -10, -18],[-18, 3, 11],[7, -9, 17],
               [-15, -6, -3],[-2, 3, -13],[12, 3, -2],[2, -2, -3, 17],[20, -15, -16],
               [-5, -17, -19],[-20, -18, 11],[-9, 1, -5],[-19, 9, 17],[17],[1],
               [4, -16, -5]]
    assert solve_SAT(20, clauses) == "UNSATISFIABLE" 
    print(solve_SAT(20,clauses))
    print("-"*40)
    print("Tests passed") 
   
    clauses = [[-6, -4, -2, 6], [-5], [7], [1, -3], 
               [1, -4, -1, -7], [-6, -1], [1], [-7]]
    
    assert solve_SAT(7, clauses) == "UNSATISFIABLE" 
    print(solve_SAT(7,clauses))

    ## Para probar el juego de pruebas
    
    
    
def SAT_solver_time_test():
    directory = "/home/hidalgo/Ing.Inf/MAC/Practica 9/Code For Students/instancias"
    for filename in os.listdir(directory):
        print(filename)
        tupla = list_minisat2list_our_sat("instancias/" + filename)
        start_time = time()
        print(solve_SAT(tupla[0],tupla[1]))
        elapsed_time = time() - start_time
        print("Elapsed time: " + str(elapsed_time))
        
# tupla = list_minisat2list_our_sat ('instancias/8-unsat.cnf')
# print(solve_SAT(tupla[0], tupla[1]))

SAT_solver_time_test()


# start_time = time()
# test()
# elapsed_time = time() - start_time   
# print("Elapsed time: %0.10f seconds." % elapsed_time) 
