import math


def readint():
    return int(raw_input())


def readarray(f):
    return map(f, raw_input().split())


def largest_two(array, Plates):
    largest = 0
    second_largest = 0

    for i in range(Plates):
        if array[i] > largest:
            second_largest = largest
            largest = array[i]
        elif array[i] > second_largest:
            second_largest = array[i]

    return largest, second_largest


def count_p(array, max, Plates):
    count = 0
    base = math.ceil(float(max)/2)

    for i in range(Plates):
        if array[i] > base:
            count += 1

    return count

Count = readint()
Plates = 0

Time = 0
X = 0  # largest
W = 0  # second largest
Count_P = 0  # number of P's in the array


for CASE in range(Count):

    Plates = readint()
    array = readarray(int)
    X, W = largest_two(array, Plates)
    Count_P = count_p(array, X, Plates)

    while True:
        if Count_P < (X - math.ceil(float(X)/2)):
           # if (X-W) >= Count_P and Plates != 1:
            #    array.remove(X)
             #   array.append(X-W)
             #   array.append(W)

            Time += Count_P + math.ceil(float(X)/2)
            break
        else:
            Time += X
            break

        X, W = largest_two(array, Plates)
        Count_P = count_p(array, X, Plates)
    print "Case #" + str(CASE + 1) + ": " + str(int(Time))
    Time = 0

exit(0)