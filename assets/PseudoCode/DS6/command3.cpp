func search(u, v):
  dis = array(INF)
  dis[u] = 0
  
  while true:
    minD = INF
    nxt = null
    
    for e in edges:
      if dis[e.v] != INF:
        continue
      d = dis[e.u] + e.w
      if d < minD:
        minD = d
        nxt = e.v
        
    if minD == INF:
      break
    if nxt == v:
      return minD
      
    dis[nxt] = minD
    
  return INF