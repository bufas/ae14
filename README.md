MASTER PLAN
===========

Implement a correctness checker which runs through the input linearly.

Implement different implicit binary search layouts
    Inorder
    BFS
    DFS

Try to build the tree in different ways
    Balanced
    Skewed with varying skew factors

Tests
    Different tree sizes
    Random queries that exist in the input
    Random queries that do not exist in the input (recursion bottoms out)
    Queries that give many branch mispredictions (recurse right and left alternating)

Measurements
    Cachefaults
        Create queries that take the left path often (DFS should be good)
        Create queries that take the right path often (DFS should be bad)
    
    Branch mispredictions
        Create queries that take left branch followed by right branch over and over.



TODO
Extend benchmark to measure cachefaults
Extend benchmark to measure branch mispredictions

Implement vEB layout

Research mmap usage
Implement explicit inorder layout
Implement explicit BFS layout
Implement explicit DFS layout
Implement explicit vEB layout

Write the tests and measurements
Plot tests and measurements

Write report

