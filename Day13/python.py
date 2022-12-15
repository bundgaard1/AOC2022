LineList = []
with open("input.txt", "r") as data:
    for t in data:
        Line = t.strip()
        if Line != "":
            LineList.append(Line.replace("10", "A"))

NumLines = len(LineList)

Part1Answer = 0
PairNum = 1
CorrectPairs = []
for t in range(NumLines//2):
    L = LineList[t*2]
    R = LineList[t*2+1]
    for n, u in enumerate(L):
        v = R[n]
        if u == v:
            continue
        elif u == "]":
            Limit = n
            LeftDefault = True
            break
        elif v == "]":
            Limit = n
            LeftDefault = False
            break
    LeftQueue = []
    RightQueue = []
    for i in range(n+1):
        u = L[i]
        v = R[i]
        if u.isdigit() or u == "A":
            LeftQueue.append(u)
        if v.isdigit() or v == "A":
            RightQueue.append(v)
    if not(LeftQueue) and RightQueue:
        LeftDefault = True
        Index = L.index("]")
        for i in range(Index+1):
            u = L[i]
            if u.isdigit() or u == "A":
                LeftQueue.append(u)
    elif not(RightQueue) and LeftQueue:
        LeftDefault = False
        Index = R.index("]")
        for i in range(Index+1):
            v = R[i]
            if v.isdigit() or v == "A":
                RightQueue.append(v)
    while LeftQueue and RightQueue:
        u = LeftQueue.pop(0)
        v = RightQueue.pop(0)
        if u == v:
            continue
        elif u > v:
            LeftDefault = False
            break
        elif u < v:
            LeftDefault = True
            break
    if LeftDefault:
        Part1Answer += PairNum
        CorrectPairs.append(PairNum)
    PairNum += 1


BeforeTwo = 0
AfterSix = 0

Two = "[[2]]"
Six = "[[6]]"

for v, s in enumerate(LineList):
    CloseIndex = s.index("]")
    NumberIndex = 100 
    for n, u in enumerate(s):
        if u == "A" or u.isdigit():
            NumberIndex = n
            Number = u
            break
    Lower = False
    if CloseIndex < NumberIndex:
        Lower = True
    elif Number < "2":
        Lower = True
    if Lower:
        BeforeTwo += 1
        LineList[v] = "Void"

for t in reversed(range(len(LineList))):
    if LineList[t] == "Void":
        del LineList[t]

for v, s in enumerate(LineList):
    for n, u in enumerate(s):
        if u == "A" or u.isdigit():
            Number = u
            break
    Higher = False
    if Number < "6":
        Lower = True
    else:
        Higher = True
    if Higher:
        AfterSix += 1
        LineList[v] = "Void"

for t in reversed(range(len(LineList))):
    if LineList[t] == "Void":
        del LineList[t]

TwoIndex = BeforeTwo + 1
SixIndex = TwoIndex + len(LineList) + 1

Part2Answer = TwoIndex*SixIndex
print(TwoIndex, SixIndex)
print(BeforeTwo, len(LineList), AfterSix)        

print(f"{Part1Answer = }")
print(f"{Part2Answer = }")