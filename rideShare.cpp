#include <iostream>
#include <vector>
#include <string>

using namespace std;

// This is the base class which will be inherited by the derived classes or child classes
class Ride {
protected:
    int rideID;
    string pickupLocation;
    string dropoffLocation;
    double distanceCovered;

public:
    Ride(int id, string pickup, string dropoff, double dist)
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distanceCovered(dist) {}

    // This method will be overridden by the children classes and doing so will demo the
    // polymorphism. 
    virtual double fare() const = 0;
    virtual void rideDetails() const {
        cout << "Ride ID: " << rideID << ", From: " << pickupLocation
             << ", To: " << dropoffLocation << ", Distance: " << distanceCovered << " miles" << endl;
    }

    virtual ~Ride() {}
};

// StandardRide subclass which is a derived class based on Ride
class StandardRide : public Ride {
public:
    StandardRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    // Implementing the virtual function. 
    // This demonstrates polymorphism.     
    double fare() const override {
        return distanceCovered * 2.0;
    }

    void rideDetails() const override {
        Ride::rideDetails();
        cout << "Type: Standard, Fare: $" << fare() << endl;
    }
};

// PremiumRide subclass which is a dericed class based on Ride
class PremiumRide : public Ride {
public:
    PremiumRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    // As we can see, the functions are overridden and implementation is different
    // on each subclasses, hence polymorphism.    
    double fare() const override {
        return distanceCovered * 3.0;
    }

    void rideDetails() const override {
        Ride::rideDetails();
        cout << "Type: Premium, Fare: $" << fare() << endl;
    }
};

// Driver class which is the blueprint for driver objects
class Driver {
private:
    int driverID;
    string name;
    double rating;
    vector<Ride*> assignedRides;

public:
    Driver(int id, string n, double r) : driverID(id), name(n), rating(r) {}

    void addRide(Ride* ride) {
        assignedRides.push_back(ride);
    }

    void getDriverInfo() const {
        cout << "Driver: " << name << " (Rating: " << rating << ")" << endl;
        cout << "Rides Completed:" << endl;
        for (const auto& ride : assignedRides)
            ride->rideDetails();
    }
};

// Rider class which is the blueprint for rider objects
class Rider {
private:
    int riderID;
    string name;
    vector<Ride*> requestedRides;

public:
    Rider(int id, string n) : riderID(id), name(n) {}

    void requestRide(Ride* ride) {
        requestedRides.push_back(ride);
    }

    void viewRides() const {
        cout << "Rider: " << name << endl;
        cout << "Requested Rides:" << endl;
        for (const auto& ride : requestedRides)
            ride->rideDetails();
    }
};

// Main function
int main() {
    // Instantiating rides
    Ride* r1 = new StandardRide(101, "Boston Market", "Quincy Market", 12.5);
    Ride* r2 = new PremiumRide(102, "Everett City Hall", "MIT Building Cambridge", 8.0);

    // Calling the polymorphic functions (overridden with particular implementation) on each instances
    vector<Ride*> allRides = { r1, r2 };
    cout << "=== All Rides ===" << endl;
    for (Ride* ride : allRides) {
        ride->rideDetails();
    }

    // Instantiating drivers and assigning them rides
    Driver d1(1, "Peter Dury", 4.8);
    d1.addRide(r1);
    d1.addRide(r2);
    cout << "\n=== Driver Info ===" << endl;
    d1.getDriverInfo();

    // Instantiating riders and associating rides to them
    Rider rider1(1001, "Samuel");
    rider1.requestRide(r1);
    rider1.requestRide(r2);
    cout << "\n=== Rider Info ===" << endl;
    rider1.viewRides();

    // Freeing up the heap allocated memory
    for (Ride* ride : allRides)
        delete ride;

    return 0;
}