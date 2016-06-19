import math

def readarray(f):
    return map(f, raw_input().split())

for case in range(int(raw_input())):
        
        D = raw_input().split()
        items = raw_input().split()
        items = map(int, items)
        #print "D: " + str(D)
        #print "P: "
        #print P
        time = 0


        X = max(items)
        ceilXhalf = math.ceil(float(X)/2.0)
        numberOfPs = 0

        Plist = []
        nextPlist = []
        for i in items:
            if i > ceilXhalf:
                Plist.append(i)

        while len(Plist) < (int(X) - ceilXhalf):
            time = time + len(Plist)
            for p in Plist:
                nextPlist.append(math.floor(float(p)/2.0))
                nextPlist.append(math.ceil(float(p)/2.0))

            Plist = nextPlist
            nextPlist = []
            
            
            X = max(Plist)
            ceilXhalf = math.ceil(float(X)/2.0)

        time = time + int(X)
        case = case + 1
        print "Case #" + str(case) + ": " +  str(time)
