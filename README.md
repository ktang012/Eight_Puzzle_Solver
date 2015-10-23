# Eight Puzzle Solver
CS170 - Intro to Artificial Intelligence project.
Traces the path of various algorithms for solving a custom or default eight puzzle.
Assumes all operations have same weight.

## Uniform Cost Search
Given equal weights, g(n), and no heuristics, h(n) = 0, it performs breadth-first search.

## A\* with Misplaced Tile Heuristic
Misplaced tile heuristic is calculated by the number of tiles not in the final position.

## A\* with Manhattan Distance Heuristic
Manhattan distance heuristic is calculated by each distance of a current tile's initial
position and it's goal position.



