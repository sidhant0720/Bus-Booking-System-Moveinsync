#include "admin.h"

void Admin::adminLogin(std::vector<Bus>& buses) {
    std::string enteredUsername, enteredPassword;

    std::cout << "Enter Admin Username: ";
    std::cin >> enteredUsername;
    std::cout << "Enter Admin Password: ";
    std::cin >> enteredPassword;

    if (enteredUsername == adminUsername && enteredPassword == adminPassword) {
        std::cout << "Login successful!\n";
        manageBusDetails(buses);  // Call the existing admin menu function
    } else {
        std::cout << "Incorrect username or password. Access denied.\n";
    }
}

void Admin::manageBusDetails(std::vector<Bus>& buses) {
    int choice;

    do {
        std::cout << "\nManage Bus Details:\n";
        std::cout << "1. Add a new bus\n";
        std::cout << "2. Update bus information\n";
        std::cout << "3. Delete a bus\n";
        std::cout << "4. View all buses\n";
        std::cout << "5. Back to Admin Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addBus(buses);
                break;
            case 2:
                updateBus(buses);
                break;
            case 3:
                deleteBus(buses);
                break;
            case 4:
                displayAllBuses(buses);
                break;
            case 5:
                break; // Exit manage bus details menu
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);
}

void Admin::addBus(std::vector<Bus>& buses) {
    std::string busName, route, daysOfOperation;
    int totalSeats;
    double distance, estimatedTravelTime;

    std::cout << "Enter Bus Name: ";
    std::cin >> busName;
    std::cout << "Enter Total Seats: ";
    std::cin >> totalSeats;
    std::cout << "Enter Route: ";
    std::cin >> route;
    std::cout << "Enter Days of Operation: ";
    std::getline(std::cin >> std::ws, daysOfOperation);
    std::cout << "Enter Distance (in km): ";
    std::cin >> distance;
    std::cout << "Enter Estimated Travel Time (in hours): ";
    std::cin >> estimatedTravelTime;

    buses.push_back(Bus(busName, totalSeats, route, daysOfOperation, distance, estimatedTravelTime));
    std::cout << "Bus added successfully!\n";
}

void Admin::updateBus(std::vector<Bus>& buses) {
    int busIndex;

    std::cout << "Enter the index of the bus to update: ";
    std::cin >> busIndex;

    if (busIndex >= 1 && busIndex <= buses.size()) {
        // Prompt for updated information
        std::string busName, route, daysOfOperation;
        int totalSeats;
        double distance, estimatedTravelTime;

        std::cout << "Enter updated Bus Name: ";
        std::cin >> busName;
        std::cout << "Enter updated Total Seats: ";
        std::cin >> totalSeats;
        std::cout << "Enter updated Route: ";
        std::cin >> route;
        std::cout << "Enter updated Days of Operation: ";
        std::cin >> daysOfOperation;
        std::cout << "Enter updated Distance (in km): ";
        std::cin >> distance;
        std::cout << "Enter updated Estimated Travel Time (in hours): ";
        std::cin >> estimatedTravelTime;

        // Update bus information
        buses[busIndex - 1] = Bus(busName, totalSeats, route, daysOfOperation, distance, estimatedTravelTime);
        std::cout << "Bus updated successfully!\n";
    } else {
        std::cout << "Invalid bus index. No bus updated.\n";
    }
}

void Admin::deleteBus(std::vector<Bus>& buses) {
    int busIndex;

    std::cout << "Enter the index of the bus to delete: ";
    std::cin >> busIndex;

    if (busIndex >= 1 && busIndex <= buses.size()) {
        // Erase the bus at the specified index
        buses.erase(buses.begin() + busIndex - 1);
        std::cout << "Bus deleted successfully!\n";
    } else {
        std::cout << "Invalid bus index. No bus deleted.\n";
    }
}

void Admin::displayAllBuses(const std::vector<Bus>& buses) {
    std::cout << "\nAll Buses:\n";
    for (size_t i = 0; i < buses.size(); ++i) {
        const Bus& currentBus = buses[i];
        std::cout << "Bus " << i + 1 << " - " << currentBus.getBusName() << "\n";
        std::cout << "   Route: " << currentBus.getRoute() << "\n";
        std::cout << "   Days of Operation: " << currentBus.getDaysOfOperation() << "\n";
        std::cout << "   Total Seats: " << currentBus.getTotalSeats() << "\n";
        std::cout << "   Current Occupancy: " << currentBus.getCurrentOccupancy() << "\n";
        std::cout << "   Available Seats: " << currentBus.getTotalSeats() - currentBus.getCurrentOccupancy() << "\n";
        std::cout << "   Distance: " << currentBus.getDistance() << " km\n";
        std::cout << "   Estimated Travel Time: " << currentBus.getEstimatedTravelTime() << " hours\n";
        std::cout << "\n";
    }
}
