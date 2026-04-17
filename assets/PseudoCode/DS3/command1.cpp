func insert(rt, x):
  if rt is null:
    rt = new Node(x)
    return
  if x < rt.val:
    insert(rt.L, x)
  else:
    insert(rt.R, x)
  if unbalanced(rt):
    rotate(rt)