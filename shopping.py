import csv
import sys

from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier


TEST_SIZE = 0.4


def main():

    # Check command-line arguments
    if len(sys.argv) != 2:
        sys.exit("Usage: python shopping.py data")

    # Load data from spreadsheet and split into train and test sets
    evidence, labels = load_data(sys.argv[1])
    X_train, X_test, y_train, y_test = train_test_split(
        evidence, labels, test_size=TEST_SIZE
    )

    # Train model and make predictions
    model = train_model(X_train, y_train)
    predictions = model.predict(X_test)
    sensitivity, specificity = evaluate(y_test, predictions)

    # Print results
    print(f"Correct: {(y_test == predictions).sum()}")
    print(f"Incorrect: {(y_test != predictions).sum()}")
    print(f"True Positive Rate: {100 * sensitivity:.2f}%")
    print(f"True Negative Rate: {100 * specificity:.2f}%")


def load_data(filename):
    """
    Load shopping data from a CSV file `filename` and convert into a list of
    evidence lists and a list of labels. Return a tuple (evidence, labels).

    evidence should be a list of lists, where each list contains the
    following values, in order:
        - Administrative, an integer
        - Administrative_Duration, a floating point number
        - Informational, an integer
        - Informational_Duration, a floating point number
        - ProductRelated, an integer
        - ProductRelated_Duration, a floating point number
        - BounceRates, a floating point number
        - ExitRates, a floating point number
        - PageValues, a floating point number
        - SpecialDay, a floating point number
        - Month, an index from 0 (January) to 11 (December)
        - OperatingSystems, an integer
        - Browser, an integer
        - Region, an integer
        - TrafficType, an integer
        - VisitorType, an integer 0 (not returning) or 1 (returning)
        - Weekend, an integer 0 (if false) or 1 (if true)

    labels should be the corresponding list of labels, where each label
    is 1 if Revenue is true, and 0 otherwise.
    """
    data = dict()
    with open(filename) as f:
        reader = csv.DictReader(f)
        evidence = []
        labels = []
        for row in reader:
            if row["Month"] == "Jan":
                month = 0
            elif row["Month"] == "Feb":
                month = 1
            elif row["Month"] == "Mar":
                month = 2
            elif row["Month"] == "Apr":
                month = 3
            elif row["Month"] == "May":
                month = 4
            elif row["Month"] == "Jun":
                month = 5
            elif row["Month"] == "Jul":
                month = 6
            elif row["Month"] == "Aug":
                month = 7
            elif row["Month"] == "Sep":
                month = 8
            elif row["Month"] == "Oct":
                month = 9
            elif row["Month"] == "Nov":
                month = 10
            elif row["Month"] == "Dec":
                month = 11
            if row["Weekend"] == "true":
                weekend = 1
            else:
                weekend = 0
            if row["VisitorType"].lower() == "returning_visitor":
                visitor = 1
            else:
                visitor = 0
            row_evidence = [
                int(row["Administrative"]),
                float(row["Administrative_Duration"]),
                int(row["Informational"]),
                float(row["Informational_Duration"]),
                int(row["ProductRelated"]),
                float(row["ProductRelated_Duration"]),
                float(row["BounceRates"]),
                float(row["ExitRates"]),
                float(row["PageValues"]),
                float(row["SpecialDay"]),
                int(month),
                int(row["OperatingSystems"]),
                int(row["Browser"]),
                int(row["Region"]),
                int(row["TrafficType"]),
                visitor,
                weekend
            ]
            evidence.append(row_evidence)
            if row["Revenue"].lower() == "true":
                revenue = 1
            elif row["Revenue"].lower() == "false":
                revenue = 0
            labels.append(revenue)

    return (evidence, labels)


def train_model(evidence, labels):
    """
    Given a list of evidence lists and a list of labels, return a
    fitted k-nearest neighbor model (k=1) trained on the data.
    """
    neigh = KNeighborsClassifier(n_neighbors=1)
    return neigh.fit(evidence, labels)


def evaluate(labels, predictions):
    """
    Given a list of actual labels and a list of predicted labels,
    return a tuple (sensitivity, specificty).

    Assume each label is either a 1 (positive) or 0 (negative).

    `sensitivity` should be a floating-point value from 0 to 1
    representing the "true positive rate": the proportion of
    actual positive labels that were accurately identified.

    `specificity` should be a floating-point value from 0 to 1
    representing the "true negative rate": the proportion of
    actual negative labels that were accurately identified.
    """
    tt = 0
    tf = 0

    ft = 0
    ff = 0

    for x in range(len(predictions)):
        if predictions[x] == 1:
            if labels[x] == predictions[x]:
                tt += 1
            else:
                ft += 1
        if predictions[x] == 0:
            if labels[x] == predictions[x]:
                tf += 1
            else:
                ff += 1
    sensitivity = tt / (tt + ff)
    specificity = tf / (tf + ft)

    return (sensitivity, specificity)


if __name__ == "__main__":
    main()
