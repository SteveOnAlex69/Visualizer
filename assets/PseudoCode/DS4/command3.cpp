func search(s):
  cur = root
  for c in s:
    idx = c - '0'
    if cur is null:
      return null
    cur = cur.ch[idx]
  return cur