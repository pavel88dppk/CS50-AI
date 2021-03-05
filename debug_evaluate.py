tt = 0
ft = 0
tf = 0
ff = 0

list1 = [1,1,0,0]
list2 = [1,0,0,0]

for x in range(len(list1)):
    if list2[x] == 1:
        if list2[x] == list1[x]:
            tt += 1
        else:
            ft += 1
    elif list2[x] == 0:
        if list2[x] == list1[x]:
            tf += 1
        else:
            ff += 1

print(tt, ft, tf, ff)
sensitivity = tt / (tt + ft)
specificity = tf / (tf + ff)

print(f"sensitivity: {sensitivity}, specificity: {specificity}")
