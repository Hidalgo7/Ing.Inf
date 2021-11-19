import copy

def actualizar_formula(num_variables,clauses,assignment):
    f = copy.deepcopy(clauses)
    for i in range(0,num_variables+1):
        if assignment[i] == 1:
            f = [clause for clause in f if i not in clause]
            for clause in f:
                while -i in clause:
                    clause.remove(-i)
        elif assignment[i] == 0:
            f = [clause for clause in f if -i not in clause]
            for clause in f:
                while i in clause:
                    clause.remove(i)
    return f

def variable_unica(num_variables, clauses, assignment):
    list = [clause[0] for clause in clauses if len(clause) == 1]
    if list:
        for x in list:
            if x > 0:
                assignment[x] = 1
            else:
                assignment[-x] = 0
        nueva_formula = actualizar_formula(num_variables,clauses, assignment)
        return True,nueva_formula
    else:
        return False,clauses

def una_aparicion(num_variables,clauses,assignment):
    lista_cont = [0] * (num_variables+1)
    for clause in clauses:
        for x in clause:
            lista_cont[abs(x)] += 1
    
    list = []
    for i in range(0,len(lista_cont)):
        if lista_cont[i] == 1:
            list.append(i)
    if list:
        for x in list:
            if any(x in sublist for sublist in clauses):
                assignment[x] = 1
            else:
                assignment[x] = 0
        nueva_formula = actualizar_formula(num_variables,clauses, assignment)
        return True, nueva_formula
    else:
        return False, clauses
        
            

def sat_preprocessing(num_variables, clauses, assignment):
    
    update = True
    while update:
        update = False   
        # TODO
        # usa funciones auxiliares         
        update1,clauses = variable_unica(num_variables,clauses,assignment)
        update2,clauses = una_aparicion(num_variables,clauses,assignment)
        
        update = update1 or update2
        if [] in clauses:
            return ([[1], [-1]], assignment)
        else:
            if (clauses == []) or (not update):
                     return (clauses, assignment)  

    

def test():
    assert ([], [None, 1]) == sat_preprocessing(1, [[1]], [None, None])
    
    
    assert ([[1],[-1]]) == sat_preprocessing(1, [[1], [-1]], [None,None])[0]
    
    
    ans = sat_preprocessing(4, [[4], [-3, -1], [3, -4, 2, 1], [1, -3, 4],
                                         [-1, -3, -4, 2], [4, 3, 1, 2], [4, 3],
                                         [1, 3, -4], [3, -4, 1], [-1]], [None, None, None, None, None])
    assert ans[0] == []
    assert ans[1][1] == 0
    assert ans[1][2] == 1
    assert ans[1][4] == 1
    
    
    ans = sat_preprocessing(5, [[4, -2], [-1, -2], [1], [-4],
                                [5, 1, 4, -2, 3], [-1, 2, 3, 5],
                                [-3, -1], [-4], [4, -1, 2]], 
                                  [None, None, None, None, None, None])
    assert ans[0] == [[1],[-1]]            
    
    
    ans = sat_preprocessing(6, [[-5, 3, 2, 6, 1], [5, 6, 2, 4],
                                [3, 5, 2, -1, 4], [1], [2, 1, 4, 3, 6],
                                [-1, -5, 2, 3], [-3, 2, -5, 6, -4]], 
                                   [None, None, None, None, None, None, None])
    assert ans[0] == [[5, 6, 2, 4], [3, 5, 2, 4], [-5, 2, 3], [-3, 2, -5, 6, -4]]
    assert ans[1][1] == 1
    
    
    ans = sat_preprocessing(7, [[-5, 3, 2, 6, 1], [5, 6, 2, 4],
                                [3, 5, 2, -1, 4], [1], [2, 1, 4, 3, 6],
                                [-1, -5, 2, 3], [-3, 2, -5, 6, -4, 7]], 
                                   [None, None, None, None, None, None, None, None] )
    assert ans[0] == []
    assert ans[1][1] == 1
    assert ans[1][4] == 1
    assert ans[1][6] == 1
    assert ans[1][7] == 1
    
   
    ans = sat_preprocessing(6, [[-6, -4, 5, -1, ], [1,2,3,6,-5],
                                [4,6], [-4, -3], [-1],
                                [1,6,-5,-4], [3,5,-6,-5,-1]],
                                   [None, None, None, None, None, None, None])
    assert ans[0] == []
    assert ans[1][1] == 0
    assert ans[1][2] == 1
    assert ans[1][3] == 0
    assert ans[1][5] == 0
    assert ans[1][6] == 1   
   
test()
