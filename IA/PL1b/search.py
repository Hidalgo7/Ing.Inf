# search.py

"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""
import copy
from time import sleep
from tkinter import E
import util


class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return [s, s, w, s, w, w, s, w]


def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    """
    "*** YOUR CODE HERE ***"
    from game import Directions
    from util import Stack
    movements = {
        'South': Directions.SOUTH,
        'West': Directions.WEST,
        'East': Directions.EAST,
        'North': Directions.NORTH
    }

    path = [problem.getStartState()]
    checked = [problem.getStartState()]
    porExaminar = Stack()
    for successor in problem.getSuccessors(problem.getStartState()):
        porExaminar.push((problem.getStartState(), successor))
    reached = False

    while porExaminar and not reached:
        next = porExaminar.pop()
        while next[1][0] in checked and not porExaminar.isEmpty():
            next = porExaminar.pop()
        while path[-1] != next[0]:
            path.pop()
        path.append(next[1][0])
        checked.append(next[1][0])
        if problem.isGoalState(next[1][0]):
            reached = True
        else:
            for successor in problem.getSuccessors(next[1][0]):
                porExaminar.push((next[1][0], successor))

    result = []
    for i in range(0, len(path) - 1):
        origin = path[i]
        goal = path[i + 1]
        action = [x for x in problem.getSuccessors(origin) if x[0] == goal]
        result.append(action[0][1])

    return result


def breadthFirstSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    from game import Directions
    from util import Queue
    movements = {
        'South' : Directions.SOUTH,
        'West' : Directions.WEST,
        'East' : Directions.EAST,
        'North' : Directions.NORTH
    }

    checked = [problem.getStartState()]

    porExaminar = Queue()
    caminos = Queue()

    for successor,dir,_ in problem.getSuccessors(problem.getStartState()):
        porExaminar.push(successor)
        caminos.push([dir])
    
    while not porExaminar.isEmpty():
        next = porExaminar.pop()
        path = caminos.pop()
        if problem.isGoalState(next):
                return path
        elif next not in checked:
            checked.append(next)
            for successor,dir,_ in problem.getSuccessors(next):
                if successor not in checked:
                    thisPath = path + [dir]
                    porExaminar.push(successor)
                    caminos.push(thisPath)

def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    from game import Directions
    from util import PriorityQueue
    movements = {
        'South': Directions.SOUTH,
        'West': Directions.WEST,
        'East': Directions.EAST,
        'North': Directions.NORTH
    }

    paths = PriorityQueue()
    paths.push(([problem.getStartState], 0))
    checked = [problem.getStartState()]

    reached = False

    while not reached and not paths.isEmpty():
        next = paths.pop()
        for successor, _, cost in problem.getSuccessors(next[0]):
            new_path = (next[0].append(successor), next[1] + cost)
            paths.push(new_path, new_path[1])
        # while  in checked and not porExaminar.isEmpty():
        #     next = porExaminar.pop()
        # while path[-1] != next[0]:
        #     path.pop()
        # path.append(next[1][0])
        # checked.append(next[1][0])
        # if problem.isGoalState(next[1][0]):
        #     reached = True
        # else:
        #     for successor in problem.getSuccessors(next[1][0]):
        #         porExaminar.push((next[1][0],successor))

    # result = []
    # for i in range(0,len(path)-1):
    #     origin = path[i]
    #     goal = path[i+1]
    #     action = [x for x in problem.getSuccessors(origin) if x[0] == goal]
    #     result.append(action[0][1])

    # return result


def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0


def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"
    from game import Directions
    from util import Queue
    movements = {
        'South': Directions.SOUTH,
        'West': Directions.WEST,
        'East': Directions.EAST,
        'North': Directions.NORTH
    }

    # ESTRUCTURE OF GETSUCCESORS: [((X,Y) , DIRECTION, COST), ((X,Y) , DIRECTION, COST)]

    # ESTRUCTURE OF PARTIAL PATHS ELEMENTS: [ ([NODEA, NODEB, NODEC, ....], (INT) COST,  [DIR1, DIR2, DIR3, ...]) ,
    # ([NODEA, NODEB, NODED, ....], (INT) COST,  [DIR1, DIR2, DIR3, ...])]
    # --> MUST BE ORDERED BY COST

    partialPaths = []
    rootNode = problem.getStartState()
    alreadyExpanded = [rootNode]

    for successor, direction, cost in problem.getSuccessors(rootNode):
        partialPaths.append(([rootNode, successor], cost + heuristic(successor, problem),[direction]))

    partialPaths = orderPathsByCost(partialPaths)
    # print("\nCamino inicial: {}".format(partialPaths))

    caminoOptimo = False

    while (not caminoOptimo) and partialPaths:
        lowestCostPath = partialPaths.pop(0)
        # print("Lowest path: {}".format(lowestCostPath))

        actualNode = lowestCostPath[0][-1]

        # print("\nActual node {} and his successors {}:".format(actualNode,problem.getSuccessors(actualNode)))
        alreadyExpanded.append(actualNode)
        for successor, direction, cost in problem.getSuccessors(actualNode):
            if successor not in lowestCostPath[0] and successor not in alreadyExpanded:
                # ([NODEA, NODEB, NODEC, ....], (INT) COST, [DIR1, DIR2, DIR3, ...])
                newPath = copy.deepcopy(lowestCostPath[0])
                newPath.append(successor)
                newCost = lowestCostPath[1] + cost + heuristic(successor, problem)
                newPartialDir = copy.deepcopy(lowestCostPath[2])
                newPartialDir.append(direction)
                newPartialPath = (newPath, newCost, newPartialDir)
                add = caminosRepetidos(partialPaths, newPartialPath)
                if add:
                    partialPaths.insert(-1, newPartialPath)
        partialPaths = orderPathsByCost(partialPaths)
        # print("\nCamino despues de insertar sucesores: {}".format(partialPaths))

        # print((partialPaths[0][0][len(partialPaths[0][0])-1]))
        if problem.isGoalState(partialPaths[0][0][-1]):  # primer elemento ultimo nodo
            caminoOptimo = True

    if caminoOptimo:
        result = []
        caminoElegido = partialPaths[0][2]
        return caminoElegido
    else:
        return Exception("No hay camino posible al objetivo. ")


def orderPathsByCost(partialPaths):
    # ESTRUCTURE OF PARTIAL PATHS ELEMENTS: [ ([NODEA, NODEB, NODEC, ....], (INT) COST,  [DIR1, DIR2, DIR3, ...]) ,
    # ([NODEA, NODEB, NODED, ....], (INT) COST,  [DIR1, DIR2, DIR3, ...])]
    return sorted(partialPaths, key=lambda cost: cost[1])


def caminosRepetidos(partialPaths, newPartialPath):
    add = True
    for camino in partialPaths:
        if camino[0][-1] == newPartialPath[0][-1]:
            if camino[1] > newPartialPath[1]:
                partialPaths.remove(camino)
            else:
                add = False
            break
    return add


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
