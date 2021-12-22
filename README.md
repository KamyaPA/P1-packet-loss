# P1-packet-loss
A P1 software program from AAU

Does not run on Windows, more stable on Linux and Mac
Requires the ncurses libery

Run by giving the program paramiters
./a.out <configfile> <outputfile> <nuber of ticks> <outputrate> <delay>

configfile
    commands:
        addr: add a router
            addr <name> <legth of queue> <speed>
        addh: add a host
            addh <name> <speed> 
        conr: connect routers
            conr <name-r1> <name-r2> <length>
        conh: connect host to router
            conh <name-host> <name-router> <length>
        #: comment

Example of a configfile

#adding routers
addr R1 1000 2
addr R2 1000 5
conr R1 R2 10
#adding hosts
addh H1 10
addh H2 10
conh H1 R1 5
conh H2 R2 8

Output file
    where the data will be stored
    it stores in two collumns 
    Tick and packetloss pr. outputrate

Nuber of ticks
    The total amounts of ticks the program should run

Outputrate
    How often should the program write data to the
    outputfile

Delay
    How long between each tick in milliseconds
    rounds down to nerest 1000.

