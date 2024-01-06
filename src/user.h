#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include <string>
#include "bus.h"

class User {
private:
    std::string username;
    std::string password;
    std::vector<int> bookedSeats;

public:
    User();
    User(const std::string& uname, const std::string& pwd);

    const std::string& getUsername() const;
    const std::string& getPassword() const;
    const std::vector<int>& getBookedSeats() const;

    bool authenticate(const std::string& enteredUsername, const std::string& enteredPassword) const;

    void browseAvailableBuses(const std::vector<Bus>& buses, const std::string& source, const std::string& destination);
    void checkSeatAvailability(const Bus& bus);
    bool bookSeat(Bus& bus, int seatNumber);
    bool cancelSeatBooking(Bus& bus, int seatNumber);
};

#endif // USER_H
