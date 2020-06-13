import csv
from sys import argv, exit

def countmax(s, sub):
    res = [0 for k in range(len(s))]
    for j in range(len(s) - len(sub), -1, -1):
        if s[j: j + len(sub)] == sub:
            if j + len(sub) > len(s)-1:
                res[j] = 1
            else:
                res[j] = 1 + res[j + len(sub)]
    for z in range(len(s)):
        temp = res[z]
        if z == 0:
            maximum = res[z]
        elif(res[z] > maximum):
            maximum = res[z]
    return(maximum)
            

def matcher(reader, real):
    for row in reader:
        person = row[0]
        values = [int(n) for n in row[1:]]
        if values == real:
            print(person)
            exit(1)
    print("no match")
    
if len(argv) != 3:
    exit("Usage: python dna.py database.csv sequence.txt")

with open(argv[1]) as csvfile:
    reader = csv.reader(csvfile)
    allsequences = next(reader)[1:]
    
    with open(argv[2]) as dnasqnc:
        s = dnasqnc.read()
        real = [countmax(s, f) for f in allsequences]
    matcher(reader,real)