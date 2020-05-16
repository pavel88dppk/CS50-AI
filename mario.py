from cs50 import get_int
while True:
    n = get_int("height: ")
    if n > 0 and n < 9:
        break

for s in range(n):
    for u in range (n):
        if n - (s + u) > 1:
            print (" ", end = "") 
        else:
            print ("#", end = "")
    print ("  ", end = "")
    for t in range (n):
        if n - (s + t) <= 1:
            print ("#", end = "")
    print()