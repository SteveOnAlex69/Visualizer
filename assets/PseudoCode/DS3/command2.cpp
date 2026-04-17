func erase(rt, x):
  if rt is null: return
  if x < rt.val:
    erase(rt.L, x)
  elif x > rt.val:
    erase(rt.R, x)
  elif rt.R:
    val = getMin(rt.R)
    rt.val = val.val
    erase(rt.R, val.val)
  else:
    tmp = rt
    rt = rt.L
    free(tmp)