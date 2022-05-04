# multiAgents.py
# --------------


import sys
from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]
        newGhostPositions = [ghostState.getPosition() for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"

        foodList = newFood.asList()
        minFood = sys.maxsize
        for food in foodList:
            distanceToFood = abs(newPos[0] - food[0]) + abs(newPos[1] - food[1])
            if distanceToFood < minFood:
                minFood = distanceToFood
        
        minGhost = sys.maxsize
        for ghost in newGhostPositions:
            distanceToGhost = abs(newPos[0] - ghost[0]) + abs(newPos[1] - ghost[1])
            if distanceToGhost < minGhost:
                minGhost = distanceToGhost
        
        
        score = 0
        if minFood == 0:
            score += 10
        else:
            score += 10/minFood
        
        if minGhost == 0:
            score -= 15
        else:
            score -= 20/minGhost

        return score + successorGameState.getScore()

def scoreEvaluationFunction(currentGameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"
        
        legalActions = gameState.getLegalActions(0)
        successors = [gameState.generateSuccessor(0,action) for action in legalActions]

        values = []
        for successor in successors:
            values.append(self.value(successor,0,self.depth,1))

        actionIndex = values.index(max(values))

        return legalActions[actionIndex]
    

    def value(self,gameState,depth,maxDepth,agent):
        if gameState.isWin() or gameState.isLose() or maxDepth == depth:
            return scoreEvaluationFunction(gameState)
        if agent == 0:
            return self.maxValue(gameState,depth,maxDepth,agent)
        else:
            return self.minValue(gameState,depth,maxDepth,agent)
        
    def maxValue(self, gameState, depth, maxDepth, agent):
        legalActions = gameState.getLegalActions(agent)
        successors = [gameState.generateSuccessor(agent,action) for action in legalActions]

        agent += 1
        if agent == gameState.getNumAgents():
            agent = 0
            depth +=1

        values = []
        for successor in successors:
            values.append(self.value(successor,depth,maxDepth,agent))

        return max(values)

    def minValue(self, gameState, depth, maxDepth, agent):
        legalActions = gameState.getLegalActions(agent)
        successors = [gameState.generateSuccessor(agent,action) for action in legalActions]

        agent += 1
        if agent == gameState.getNumAgents():
            agent = 0
            depth +=1

        values = []
        for successor in successors:
            values.append(self.value(successor,depth,maxDepth,agent))

        return min(values)
        

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        legalActions = gameState.getLegalActions(0)

        values =[]
        alpha = -sys.maxsize
        beta = sys.maxsize
        for action in legalActions:
            successor = gameState.generateSuccessor(0,action)
            v = self.value(successor,0,self.depth,1,alpha,beta)
            if v > beta:
                return v
            values.append(v)
            alpha = max([v,alpha])

        actionIndex = values.index(max(values))

        return legalActions[actionIndex]

    def value(self,gameState,depth,maxDepth,agent,alpha,beta):
        if gameState.isWin() or gameState.isLose() or maxDepth == depth:
            return scoreEvaluationFunction(gameState)
        if agent == 0:
            return self.maxValue(gameState,depth,maxDepth,agent,alpha,beta)
        else:
            return self.minValue(gameState,depth,maxDepth,agent,alpha,beta)
    
    def maxValue(self, gameState, depth, maxDepth, agent, alpha, beta):
        legalActions = gameState.getLegalActions(agent)
        
        newAgent = agent + 1
        if newAgent == gameState.getNumAgents():
            newAgent = 0
            depth += 1

        values = []
        for action in legalActions:
            successor = gameState.generateSuccessor(agent,action)
            v = self.value(successor,depth,maxDepth,newAgent,alpha,beta)
            if v > beta:
                return v
            values.append(v)
            alpha = max([v,alpha])
        
        return max(values)

    def minValue(self, gameState, depth, maxDepth, agent, alpha, beta):
        legalActions = gameState.getLegalActions(agent)
        
        newAgent = agent + 1
        if newAgent == gameState.getNumAgents():
            newAgent = 0
            depth += 1

        values = []
        for action in legalActions:
            successor = gameState.generateSuccessor(agent,action)
            v = self.value(successor,depth,maxDepth,newAgent,alpha,beta)
            if v < alpha:
                return v
            values.append(v)
            beta = min([v,beta])
        
        return min(values)


class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"
        util.raiseNotDefined()

def betterEvaluationFunction(currentGameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

# Abbreviation
better = betterEvaluationFunction
