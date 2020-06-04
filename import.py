# TODO
from cs50 import SQL
import csv
from sys import argv, exit

if len(argv) != 2:
    print("Error - usage: python import.py file.csv")
    exit(1)
    
db = SQL("sqlite:///students.db")

file = argv[1]
with open(file, "r") as read:
    reader = csv.DictReader(read)
    for row in reader:
        names = []
        for willbepart in row["name"].split(" "):
            names.append(willbepart)
            
        names.append(row["house"])
        names.append(row["birth"])
        if (len(names) > 4):
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", names[:5])

        if len(names) == 4:
            db.execute("INSERT INTO students (first, last, house, birth) VALUES(?, ?, ?, ?)", names[:4])
