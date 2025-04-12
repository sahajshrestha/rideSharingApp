#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Base Ride class
class Ride {
protected:
    int rideID;
    string pickupLocation;
    string dropoffLocation;
    double distanceCovered;

public:
    Ride(int id, string pickup, string dropoff, double dist)
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distanceCovered(dist) {}

    virtual double fare() const = 0; // Polymorphic method
    virtual void rideDetails() const {
        cout << "Ride ID: " << rideID << ", From: " << pickupLocation
             << ", To: " << dropoffLocation << ", Distance: " << distanceCovered << " miles" << endl;
    }

    virtual ~Ride() {}
};

// StandardRide subclass
class StandardRide : public Ride {
public:
    StandardRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double fare() const override {
        return distanceCovered * 1.5;
    }

    void rideDetails() const override {
        Ride::rideDetails();
        cout << "Type: Standard, Fare: $" << fare() << endl;
    }
};

// PremiumRide subclass
class PremiumRide : public Ride {
public:
    PremiumRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double fare() const override {
        return distanceCovered * 3.0;
    }

    void rideDetails() const override {
        Ride::rideDetails();
        cout << "Type: Premium, Fare: $" << fare() << endl;
    }
};

// Driver class
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

// Rider class
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

// Main function to demonstrate functionality
int main() {
    // Create rides
    Ride* r1 = new StandardRide(101, "Downtown", "Airport", 12.5);
    Ride* r2 = new PremiumRide(102, "University", "Mall", 8.0);

    // Demonstrate polymorphism
    vector<Ride*> allRides = { r1, r2 };
    cout << "=== All Rides ===" << endl;
    for (Ride* ride : allRides) {
        ride->rideDetails();
    }

    // Create driver and assign rides
    Driver d1(1, "Alice", 4.8);
    d1.addRide(r1);
    d1.addRide(r2);
    cout << "\n=== Driver Info ===" << endl;
    d1.getDriverInfo();

    // Create rider and request rides
    Rider rider1(1001, "Bob");
    rider1.requestRide(r1);
    rider1.requestRide(r2);
    cout << "\n=== Rider Info ===" << endl;
    rider1.viewRides();

    // Clean up
    for (Ride* ride : allRides)
        delete ride;

    return 0;
}