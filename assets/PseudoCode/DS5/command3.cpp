func search():
  sort(edges)
  dsu = new DSU()
  ans = []
  
  for e in edges:
    if dsu.join(e.u, e.v):
      ans.push(e)
      
  return ans