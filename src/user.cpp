#include "user.h"
#include <algorithm>

User::User() : username(""), password("") {}

User::User(const std::string& uname, const std::string& pwd) : username(uname), password(pwd) {}

const std::string& User::getUsername() const {
    return username;
}

const std::string& User::getPassword() const {
    return password;
}

const std::vector<int>& User::getBookedSeats() const {
    return bookedSeats;
}

bool User::authenticate(const std::string& enteredUsername, const std::string& enteredPassword) const {
    return (username == enteredUsername && password == enteredPassword);
}

void User::browseAvailableBuses(const std::vector<Bus>& buses, const std::string& source, const std::string& destination) {
    std::cout << "\nAvailable Buses from " << source << " to " << destination << ":\n";

    for (size_t i = 0; i < buses.size(); ++i) {
        const Bus& currentBus = buses[i];

        int percentOccupancy = (currentBus.getCurrentOccupancy() * 100 / currentBus.getTotalSeats());

        if (percentOccupancy < 60) {
            std::cout << "\033[32m";  // Set text color to green
        } else if (percentOccupancy < 90) {
            std::cout << "\033[33m";  // Set text color to yellow
        } else {
            std::cout << "\033[31m";  // Set text color to red
        }
        // Check if the bus follows the specified route
        if (currentBus.getRoute() == source + "-" + destination) {
            std::cout << "Bus " << i + 1 << " - " << currentBus.getBusName() << "\n";
            std::cout << "   Route: " << currentBus.getRoute() << "\n";
            std::cout << "   Days of Operation: " << currentBus.getDaysOfOperation() << "\n";
            std::cout << "   Total Seats: " << currentBus.getTotalSeats() << "\n";
            std::cout << "   Current Occupancy: " << currentBus.getCurrentOccupancy() << "\n";
            std::cout << "   Available Seats: " << currentBus.getTotalSeats() - currentBus.getCurrentOccupancy()
                      << "\n";
            std::cout << "   Distance: " << currentBus.getDistance() << " km\n";
            std::cout << "   Estimated Travel Time: " << currentBus.getEstimatedTravelTime() << " hours\n";
            std::cout << "\n";
        }
        std::cout << "\033[0m";
    }
}

void User::checkSeatAvailability(const Bus& bus) {
    std::cout << "\nSeat Availability for " << bus.getBusName() << ":\n";

    const std::vector<Seat>& seats = bus.getSeats();
    for (const Seat& seat : seats) {
        if (seat.isSeatBooked()) {
            std::cout << "\033[31m";
            std::cout << "Seat " << seat.getSeatNumber() << ": ";
            std::cout << "Booked\n";
            std::cout << "\033[0m";
        } else {
            std::cout << "\033[32m";
            std::cout << "Seat " << seat.getSeatNumber() << ": ";
            std::cout << "Available\n";
            std::cout << "\033[0m";
        }
    }
}

bool User::bookSeat(Bus& bus, int seatNumber) {
    if (seatNumber >= 1 && seatNumber <= bus.getTotalSeats()) {
        if (!bus.getSeats()[seatNumber - 1].isSeatBooked()) {
            bus.bookSeat(seatNumber);
            bookedSeats.push_back(seatNumber);  // Associate the booked seat with the user
            std::cout << "Seat " << seatNumber << " booked successfully!\n";
            return true;
        } else {
            std::cout << "Seat " << seatNumber << " is already booked. Choose another seat.\n";
        }
    } else {
        std::cout << "Invalid seat number. Please enter a valid seat number.\n";
    }
    return false;
}

bool User::cancelSeatBooking(Bus& bus, int seatNumber) {
    if (seatNumber >= 1 && seatNumber <= bus.getTotalSeats()) {
        auto it = std::find(bookedSeats.begin(), bookedSeats.end(), seatNumber);
        if (it != bookedSeats.end()) {
            bus.cancelSeatBooking(seatNumber);
            bookedSeats.erase(it);
            std::cout << "Seat " << seatNumber << " booking canceled successfully!\n";
            return true;
        } else {
            std::cout << "Seat " << seatNumber << " is not booked by you. No booking to cancel.\n";
        }
    } else {
        std::cout << "Invalid seat number. Please enter a valid seat number.\n";
    }
    return false;
}
