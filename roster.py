# TODO
from sys import argv, exit
from cs50 import SQL

if len(argv) != 2:
    print("Error - Usage: python roster.py {name of house}")
    exit(1)
    
housename = argv[1].lower()

houses = ["slytherin", "gryffindor", "ravenclaw", "hufflepuff"]
if housename.lower() not in houses:
    print("Bad house provided. Include: Gryffindor, Hufflepuff, Slytherin or Ravenclaw.")
    exit(1)
    
db = SQL("sqlite:///students.db")
data = db.execute(f"SELECT first, middle, last, birth FROM students WHERE lower(house) = ? ORDER BY last, first;", housename)


for row in data:
    first = row["first"].strip()
    last = row["last"].strip()
    birth = str(row["birth"]).strip()
    
    if not row["middle"]:
        print(f"{first} {last}, born {birth}")
    else:
        middle = row["middle"].strip()
        print(f"{first} {middle} {last}, born {birth}")

