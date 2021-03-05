#just a place where I paste code, I already coded, however, I will not use it. It mght come handy in the future
"Administrative": int(row["Administrative"])
"Administrative_Duration": float(row["Administrative_Duration"])
"Informational": int(row["Informational"])
"Informational_Duration": float(row["Informational_Duration"])
"ProductRelated": int(row["ProductRelated"])
"ProductRelated_Duration": float(row["ProductRelated_Duration"])
"BounceRates": float(row["BounceRates"])
"ExitRates": float(row["ExitRates"])
"PageValues": float(row["PageValues"])
"SpecialDay": float(row["SpecialDay"])
"Month": {x for x in range(12)}
"OperatingSystems": int(row["OperatingSystems"])
"Browser": int(row["Browser"])
"Region": int(row["Region"])
"TrafficType": int(row["TrafficType"])
"VisitorType": bool(row["VisitorType"])
"Weekend": bool(row["Weekend"])



tfcounter = 0
pfcounter = 0
ptcounter = 0
ttcounter = 0
for label in labels:
    if labels[label] == 1:
        ttcounter += 1

for label in predictions:
    if predictions[label] == 1:
        ptcounter += 1


sensitivity = ptcounter / ttcounter

for label in labels:
    if labels[label] == 0:
        tfcounter += 1
for label in predictions:
    if predictions[label] == 0:
        pfcounter += 1

specificity = pfcounter / tfcounter
