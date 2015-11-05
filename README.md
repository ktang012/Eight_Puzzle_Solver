# Eight Puzzle Solver
CS170 - Intro to Artificial Intelligence project.

The program traces the path of various algorithms for solving an eight puzzle.
It assumes all operations have the same cost.

## Uniform Cost Search
Given equal weights, g(n), and no heuristics, h(n) = 0, it performs breadth-first search.

## A\* with Misplaced Tile Heuristic
Misplaced tile heuristic is calculated by the number of tiles not in the goal state position.

## A\* with Manhattan Distance Heuristic
Manhattan distance heuristic is calculated by each distance of a current tile's current
position and it's goal state position.

## Bugs
- Solves puzzle but fails to return linked list of optimal path
