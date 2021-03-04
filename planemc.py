import numpy as np
 
class Passenger:
    walkspd = 0.5 # walking speed
    storespd = 30 # luggage storing speed
    swapspd = 15 # seat swapping speed
 
    def __init__(self, aislerow, seatrow, seatcol):
        self.x = 0 # at gate
        self.aislerow = int(aislerow)
        self.seatrow = int(seatrow)
        self.seatcol = int(seatcol)
        self.actiont = 0 # time of action (storing, swapping)
        self.atrow = False # reached row of own seat?
        self.stored = False # already stored luggage?
        self.swapped = False # swapped to seat?
        self.atseat = False # currently at seat?
 
    # printing
    def __repr__(self):
        longprint = False
        if (longprint):
            return "Passenger, seat (" + \
                str(self.seatrow) + " = " + str(self.aislerow) + ", " + \
                str(self.seatcol) + "), x: " + \
                str(self.x) + ", action t: " + \
                str(self.actiont) + ", at row: " + \
                str(self.atrow) + ", stored: " + \
                str(self.stored) + ", at seat: " + \
                str(self.atseat) + "\n"
        else:
            return str(4 * self.seatrow + self.seatcol + 1)
 
    # check whether aisle slot x empty
    def aislefree(aisle, x):
        if (x >= len(aisle)):
            return False
        if (aisle[x] == None):
            return True
        
        return False
 
    # check whether seat row is free
    def rowfree(row, aisleseats):
        for s in aisleseats:
            if (row[s] != None): # aisle seat not empty
                return False
            
        return True
 
    # walk forward in aisle
    def walk(self, aisle, aisledx, dt):
        dx = self.walkspd * dt / aisledx
 
        if (Passenger.aislefree(aisle, int(self.x) + 1)):
            aisle[int(self.x)] = None
            self.x += dx
            aisle[int(self.x)] = self
            
        self.atrow = int(self.x) >= self.aislerow
 
    # store luggage
    def store(self):
        self.actiont = -self.storespd
        self.stored = True
 
    # swap to get to window seat
    def swap(self, seats, aisleseats):
        self.swapped = True
        if (Passenger.rowfree(seats[self.seatrow], aisleseats)):
            self.actiont = -self.swapspd
 
class Plane: # Embraer E190
    rows = 25 # number of seat rows
    cols = 4 # seats per row
    aisledx = 0.5 # aisle separation
    seatdx = 1 # seat separation
    gatedist = 25 # distance from gate to first seat
    aisleseats = (1, 2) # seats that are next to aisle
 
    # assign passengers
    def assign(self, passengers):
        self.passengers = passengers
        self.aisle = np.full(int((self.gatedist + self.rows) / self.aisledx), None)
        self.seats = np.full((self.rows, self.cols), None)
 
    # printing
    def __repr__(self):
        return "\nAisle: \n" + str(self.aisle) + "\n Seats: \n" + str(self.seats)
 
    # run time step
    def tick(self, dt):
        for p in self.passengers:
            if (p.actiont >= 0 and not p.atseat): # if not performing action
                if (not p.atrow): # if not at row
                    p.walk(self.aisle, self.aisledx, dt)
                elif (not p.stored): # if luggage not stored
                    p.store()
                elif (not p.swapped): # swap to seat
                    p.swap(self.seats, self.aisleseats)
                else:
                    p.atseat = True
                    self.seats[p.seatrow, p.seatcol] = p
                    self.aisle[p.aislerow] = None
                    
            p.actiont += dt
 
# Performs plane boarding time Monte Carlo simulation
# for number of samples n with random seat distribution.
# Returns an array of boarding times.
def planemc(n):
    time = np.zeros(n) # boarding times
 
    plane = Plane()
    nseats = plane.rows * plane.cols
    npass = nseats
 
    tmax = 1e6
 
    printing = True # print state of plane
    singlestep = False # step one dt at a time by pressing enter
 
    for i in range(n):
        pseats = np.arange(nseats)
        np.random.shuffle(pseats) # randomly shuffle seats
        
        pvec = np.vectorize(Passenger)
        passengers = pvec(np.floor(pseats / plane.cols) * (plane.seatdx / plane.aisledx) + \
                          plane.gatedist / plane.aisledx, np.floor(pseats / plane.cols), \
                          pseats % plane.cols)
 
        if (printing):
            print("Passenger seats:", len(pseats), pseats)
            print("Passengers:", len(passengers), passengers)
        
        plane.assign(passengers)
 
        t = 0 # time (s)
        dt = 1
        boarded = False # fully boarded
        while not boarded and t < tmax:
            plane.tick(dt)
            
            boarded = True
            for p in passengers: # check if all passengers seated
                if (not p.atseat):
                    boarded = False
                    break
                
            if (printing):
                print("Plane:", plane)
 
            if (singlestep):
                input()
 
            t += dt
            
        time[i] = t
 
    return time
 
