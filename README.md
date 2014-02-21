# MASTER PLAN

## TODO
- Write the tests and measurements
- Plot tests and measurements
- Write report

### Tests
- ~~Different tree sizes~~
- Random queries that exist in the input
- Random queries that do not exist in the input (recursion bottoms out)
- Queries that give many branch mispredictions (recurse right and left alternating)
- ~~Varying skew factors~~

### Measurements
- Cachefaults
  - Create queries that take the left path often (DFS should be good)
  - Create queries that take the right path often (DFS should be bad)
- Branch mispredictions
  - Create queries that take left branch followed by right branch over and over.



