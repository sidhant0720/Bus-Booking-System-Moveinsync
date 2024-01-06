#include <iostream>
#include <vector>
#include <string>

#include "user.cpp"
#include "admin.cpp"
#include "bus.cpp"
#include "seat.cpp"



// ANSI escape codes for text color
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"


void displayMainMenu() {
    std::cout<<BLUE;
    std::cout<<"-----------------------------------\n";
    std::cout << "1. Admin\n";
    std::cout << "2. User\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice: \n";
    std::cout<<"-----------------------------------";
    std::cout<<RESET;
}


void adminMenu(std::vector<Bus>& buses) {
    Admin admin;
    int choice;

    do {
        std::cout << "\nAdmin Menu:\n";
        std::cout << "1. Manage Bus Details\n";
        std::cout << "2. Back to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                admin.adminLogin(buses);
                //admin.manageBusDetails(buses);
                break;
            case 2:
                break; // Exit admin menu
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 2);
}

void performUserActions(std::vector<Bus>& buses, User& currentUser) {
    int choice;

    do {
        std::cout << "\nUser Menu:\n";
        std::cout << "1. Browse Available Buses\n";
        std::cout << "2. Check Seat Availability\n";
        std::cout << "3. Book a Seat\n";
        std::cout << "4. Cancel Seat Booking\n";
        std::cout << "5. Display booked seats\n";
        std::cout << "6. Back to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string source, destination;
                std::cout << "Enter source: ";
                std::cin >> source;
                std::cout << "Enter destination: ";
                std::cin >> destination;
                currentUser.browseAvailableBuses(buses, source, destination);
                break;
            }
            case 2: {
                int busIndex;
                std::cout << "Enter the index of the bus: ";
                std::cin >> busIndex;
                currentUser.checkSeatAvailability(buses[busIndex - 1]);
                break;
            }
            case 3: {
                int busIndex, seatNumber;
                std::cout << "Enter the index of the bus: ";
                std::cin >> busIndex;
                std::cout << "Enter the seat number: ";
                std::cin >> seatNumber;
                if (currentUser.bookSeat(buses[busIndex - 1], seatNumber)) {
                    std::cout << "Seat booked successfully!\n";
                } else {
                    std::cout << "Invalid seat number or seat already booked.\n";
                }
                break;
            }
            case 4: {
                int busIndex, seatNumber;
                std::cout << "Enter the index of the bus: ";
                std::cin >> busIndex;
                std::cout << "Enter the seat number to cancel: ";
                std::cin >> seatNumber;
                if (currentUser.cancelSeatBooking(buses[busIndex - 1], seatNumber)) {
                    std::cout << "Seat booking canceled successfully!\n";
                } else {
                    std::cout << "Invalid seat number or seat not booked.\n";
                }
                break;
            }
            case 5: {
                // New option to display booked seats by the current user
                std::cout << "Booked Seats by " << currentUser.getUsername() << ":\n";

                const std::vector<int>& bookedSeats = currentUser.getBookedSeats();

                if (bookedSeats.empty()) {
                    std::cout << "No seats booked by " << currentUser.getUsername() << ".\n";
                } else {
                    for (int seatNumber : bookedSeats) {
                        bool foundSeat = false;
                        // Find the bus that contains the booked seat
                        for (const Bus& bus : buses) {
                            const std::vector<Seat>& seats = bus.getSeats();

                            // Check if the seat is booked in the current bus
                            if (seatNumber >= 1 && seatNumber <= seats.size() && seats[seatNumber - 1].isSeatBooked()) {
                                foundSeat = true;
                                std::cout << "Seat " << seatNumber << " on Bus " << bus.getBusName() << ":\n";
                                std::cout << "   Route: " << bus.getRoute() << "\n";
                                std::cout << "   Days of Operation: " << bus.getDaysOfOperation() << "\n";
                                std::cout << "   Total Seats: " << bus.getTotalSeats() << "\n";
                                std::cout << "   Current Occupancy: " << bus.getCurrentOccupancy() << "\n";
                                std::cout << "   Available Seats: " << bus.getTotalSeats() - bus.getCurrentOccupancy() << "\n";
                                std::cout << "   Distance: " << bus.getDistance() << " km\n";
                                std::cout << "   Estimated Travel Time: " << bus.getEstimatedTravelTime() << " hours\n";
                                std::cout << "\n";
                                break; // Break once the bus is found
                            }
                        }

                        if (!foundSeat) {
                            std::cout << "No seat information available for Seat " << seatNumber << ".\n";
                        }
                    }
                }
                break;
            }
            case 6:
                break; // Exit user menu
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);
}

void userMenu(std::vector<Bus>& buses, std::vector<User>& users) {
    std::string enteredUsername, enteredPassword;
    User currentUser;

    // User login and registration menu
    bool foundUser = false;
    bool usernameTaken = false;

    do {
        std::cout << "1. Login\n";
        std::cout << "2. Register\n";
        std::cout << "3. Back to Main Menu\n";
        std::cout << "Enter your choice: ";
        int loginChoice;
        std::cin >> loginChoice;
        foundUser = false;
        usernameTaken = false;

        switch (loginChoice) {
            case 1: {
                std::cout << "Enter your username: ";
                std::cin >> enteredUsername;
                std::cout << "Enter your password: ";
                std::cin >> enteredPassword;

                // Find the user in the vector based on entered credentials
                for (User& user : users) {
                    if (user.authenticate(enteredUsername, enteredPassword)) {
                        std::cout << "Login successful!\n";
                        currentUser = user;  // Set the current user
                        foundUser = true;
                        performUserActions(buses, currentUser);  // Call the function for user options
                        break;
                    }
                }

                if (!foundUser) {
                    std::cout << "Invalid username or password. Try again.\n";
                }
                break;
            }
            case 2: {
                // Registration
                std::cout << "Enter a new username: ";
                std::cin >> enteredUsername;
                std::cout << "Enter a new password: ";
                std::cin >> enteredPassword;

                // Check if the username is already taken
                for (const User& user : users) {
                    if (user.getUsername() == enteredUsername) {
                        usernameTaken = true;
                        break;
                    }
                }

                if (usernameTaken) {
                    std::cout << "Username already taken. Try again.\n";
                } else {
                    // Create a new user and add it to the vector
                    users.push_back(User(enteredUsername, enteredPassword));
                    currentUser = users.back();  // Set the current user
                    std::cout << "Registration successful!\n";
                    performUserActions(buses, currentUser);  // Call the function for user options
                }
                break;
            }
            case 3:
                // Back to Main Menu
                return;  // Exit the userMenu function
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (true);
}



int main() {
    std::vector<Bus> buses;
    std::vector<User> users; 

    buses.push_back(Bus("Bus1", 30, "Route1", "Monday, Wednesday, Friday", 100.0, 2.5));
    buses.push_back(Bus("Bus2", 40, "Route2", "Tuesday, Thursday, Saturday", 150.0, 3.0));
    buses.push_back(Bus("Bus3", 30, "Delhi-Goa", "Tuesday", 150.0, 3.0));
    buses.push_back(Bus("Bus3", 10, "goa-kanpur", "Tuesday", 150.0, 3.0));

    int choice;

    do {
        displayMainMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                adminMenu(buses);
                break;
            case 2:
                userMenu(buses,users);
                break;
            case 3:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}