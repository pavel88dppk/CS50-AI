from cs50 import get_string
N = 0
s = get_string("Text: ")
count = 0
length = len(s)
for i in range(length):
    f = ord(s[N])
    if (f >= 65 and f <= 90) or (f >= 97 and f <= 122):
        count += 1
    N += 1
    f = 0
N = 0
wc = 0
for q in range(length):
    f = ord(s[N])
    if (f >= 65 and f <= 90) or (f >= 97 and f <= 122) or f == 39:
        wc += 0
    elif (f == 45):
        wc += 0
        f = ord(s[N - 1])
        if (f >= 65 and f <= 90) or (f >= 97 and f <= 122):
            wc += 0
        else:
            wc += 1
    else:    
        f = ord(s[N - 1])
        if (f >= 65 and f <= 90) or (f >= 97 and f <= 122):
            wc += 1
    if f == 32:
        f = ord(s[N - 1])
        if (f >= 97 and f <= 122) or (f >= 65 and f <= 90):
            wc += 1
    N += 1
sc = 0
N = 0
for x in range(length):
    f = ord(s[N])
    if f == 33 or f == 46 or f == 63:
        sc += 1
    N += 1
    f = 0
L = (count * (100 / wc))
S = (sc * (100 / wc))
index = round((0.0588 * L) - (0.296 * S) - 15.8)
if index <= 1.5:
    print("Before Grade 1")
elif index >= 15.5:
    print("Grade 16+")
else:
    print(f"Grade {index}")