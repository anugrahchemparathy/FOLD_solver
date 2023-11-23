# PLAN

Will start with Python, and convert chunks to CPP once high level structure is decided. One large benefit of this approach is ease of testing. It's easy to know what correct numbers look like for the CPP implementation if we have verifiably correct numbers on the slow Python prototype.

Visualization of final output will likely be done with tkinter (for now).

---

### JSON LOAD
save vertices
save edges


---
### Setup
create 
- A: new adjacency graph
- B: list of edges, one copy in each direction
    - we will remove edges as they are processed
- C: list of unique edges (one total per edge) storing a vector of polygons 


iterate over edges (B), creating polygons
- for every polygon we see, add it to the corresponding entries in (C) for every edge

---

### Math
convert (C) into a graph
- D: polygon adjacency list

OPTIONAL: check that (D) contains a single connected component

While reasonable:
- Select a random polygon P
    - DFS through (D) starting from P(or do a MST)
    - if max DFS depth is reasonable, continue, else repeat
   

DFS from P and while backtracking, flip polygons across edges