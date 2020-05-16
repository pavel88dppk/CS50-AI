from cs50 import get_int

while True:
    input = get_int("Number: ")
    if input > 0:
        break
sumn1 = 0
sumproducts = 0
numtest = input
numtest2 = input

while numtest > 1:
    n1 = numtest % 10
    sumn1 += n1
    numtest -= n1
    numtest /= 10
    n2 = numtest % 10
    n22 = n2 * 2
    if n22 > 9:
        sumproducts += n22 % 10
        sumproducts += (n22 - (n22 % 10)) / 10
    else:
        sumproducts += n22
    numtest -= n2
    numtest /= 10
if (sumn1 + sumproducts) % 10 == 0:
    amex = (numtest2 >= 34e13 and numtest2 < 35e13) or (numtest2 >= 37e13 and numtest2 < 38e13)
    master_card = (numtest2 >= 51e14 and numtest2 < 56e14)
    visa = (numtest2 >= 4e12 and numtest2 < 5e12) or (numtest2 >= 4e15 and numtest2 < 5e15)
    if amex:
        print("AMEX")
        
    elif master_card:
        print("MASTERCARD")
    elif visa:
        print("VISA")
    else:
        print("invalid car")
else:
    print("INVALID")

