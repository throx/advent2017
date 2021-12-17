f = open("input.txt", "r")

def diag(kp):
  nk = []
  for x in range(len(kp)):
    l = []
    for y in range(len(kp)):
      l.append(kp[y][x])
    nk.append("".join(l))
  return tuple(nk)

rules = {}
for line in f:
  k, v = line.strip().split(" => ")
  k = tuple(k.split("/"))
  v = v.split("/")
  rules[k] = v
  rules[diag(k)] = v

  k2 = tuple([s[::-1] for s in k])
  rules[k2] = v
  rules[diag(k2)] = v

  k3 = tuple(s for s in k[::-1])
  rules[k3] = v
  rules[diag(k3)] = v

  k4 = tuple([s[::-1] for s in k3])
  rules[k4] = v
  rules[diag(k4)] = v

grid = [
  ".#.",
  "..#",
  "###",
]

def num_on(g):
  return sum([sum([c == "#" for c in l]) for l in g])

for iter in range(5):
  newgrid = []
  if len(grid) % 2 == 0:
    for y in range(0, len(grid), 2):
      newlines = [[],[],[]]
      for x in range(0, len(grid), 2):
        k = tuple([grid[y][x:x+2], grid[y+1][x:x+2]])
        v = rules[k]
        for i, l in enumerate(v):
          newlines[i].extend(list(l))
      newgrid.extend(["".join(l) for l in newlines])
  elif len(grid) % 3 == 0:
    for y in range(0, len(grid), 3):
      newlines = [[],[],[],[]]
      for x in range(0, len(grid), 3):
        k = tuple([grid[y][x:x+3], grid[y+1][x:x+3], grid[y+2][x:x+3]])
        v = rules[k]
        for i, l in enumerate(v):
          newlines[i].extend(list(l))
      newgrid.extend(["".join(l) for l in newlines])
  else:
    raise "bad dimen"
  print (newgrid)
  grid = newgrid
  print (iter, num_on(grid))

print (num_on(grid))
