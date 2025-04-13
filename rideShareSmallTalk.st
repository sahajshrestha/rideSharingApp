"This is the base class which will be inherited by the derived classes or child classes"
Object subclass: Ride [
    | rideID pickupLocation dropoffLocation distance |

    Ride class >> newWithID: id pickup: pickup dropoff: dropoff distance: dist [
        ^ self new initializeWithID: id pickup: pickup dropoff: dropoff distance: dist
    ]

    initializeWithID: id pickup: pickup dropoff: dropoff distance: dist [
        rideID := id.
        pickupLocation := pickup.
        dropoffLocation := dropoff.
        distance := dist.
        ^ self
    ]

    fare [
        self subclassResponsibility
    ]

    rideDetails [
        ^ 'Ride ID: ', rideID printString, ' from ', pickupLocation, ' to ', dropoffLocation, ', Distance: ', distance printString
    ]
]

"StandardRide subclass which is a derived class based on Ride"
Ride subclass: StandardRide [
    fare [
        ^ distance * 1.5
    ]

    rideDetails [
        ^ super rideDetails, ' Type: Standard, Fare: $', self fare printString
    ]
]

"PremiumRide subclass which is a dericed class based on Ride"
Ride subclass: PremiumRide [
    fare [
        ^ distance * 3
    ]

    rideDetails [
        ^ super rideDetails, ' Type: Premium, Fare: $', self fare printString
    ]
]

"Driver class which is the blueprint for driver objects"
Object subclass: Driver [
    | driverID name rating assignedRides |

    Driver class >> newWithID: id name: n rating: r [
        ^ self new initializeWithID: id name: n rating: r
    ]

    initializeWithID: id name: n rating: r [
        driverID := id.
        name := n.
        rating := r.
        assignedRides := OrderedCollection new.
        ^ self
    ]

    addRide: aRide [
        assignedRides add: aRide
    ]
    
    getDriverInfo [
    ('Driver: ', name) displayNl.
    'Rides Completed:' displayNl.
    assignedRides do: [:ride | ride rideDetails displayNl]
]
]

"Rider class which is the blueprint for rider objects"
Object subclass: Rider [
    | riderID name requestedRides |

    Rider class >> newWithID: id name: n [
        ^ self new initializeWithID: id name: n
    ]

    initializeWithID: id name: n [
        riderID := id.
        name := n.
        requestedRides := OrderedCollection new.
        ^ self
    ]

    requestRide: aRide [
        requestedRides add: aRide
    ]

    viewRides [
        ('Rider: ', name) displayNl.
        'Requested Rides:' displayNl.
        requestedRides do: [:ride | ride rideDetails displayNl]
    ]
]

"Main program"
| ride1 ride2 allRides driver rider |

ride1 := StandardRide newWithID: 101 pickup: 'Downtown' dropoff: 'Airport' distance: 12.0.
ride2 := PremiumRide newWithID: 102 pickup: 'University' dropoff: 'Mall' distance: 8.0.

allRides := OrderedCollection with: ride1 with: ride2.

'=== All Rides ===' displayNl.
allRides do: [:r | r rideDetails displayNl].

driver := Driver newWithID: 1 name: 'Alice' rating: 4.8.
driver addRide: ride1.
driver addRide: ride2.

'=== Driver Info ===' displayNl.
driver getDriverInfo.

rider := Rider newWithID: 1001 name: 'Bob'.
rider requestRide: ride1.
rider requestRide: ride2.

'=== Rider Info ===' displayNl.
rider viewRides.

'