#include <iostream>
#include <vector>

using namespace std;

const int coach_seat = 80;
const int coaches = 6;
const int price = 25;
const int free_ticket_hold = 10;

struct TrainJourney {
    string departureTime;
    string returnTime;
    vector<int> availableSeats;
    int totalPassengers;
    int totalRevenue;
};

void displayHeader() {
    cout << "********" << endl;
    cout << "* Welcome to the Railway Ticket Management System *" << endl;
    cout << "********" << endl;
}

void displayMenu() {
    cout << "\nOptions:\n";
    cout << "1. View Train Schedule\n";
    cout << "2. Purchase Tickets\n";
    cout << "3. Display Day Summary\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

void displayTrainSchedule(const vector<TrainJourney>& trainSchedule) {
    cout << "\nTrain Schedule:\n";
    for (int i = 0; i < trainSchedule.size(); i++) {
        const TrainJourney& journey = trainSchedule[i];
        cout << "Train " << (i + 1) << ": " << journey.departureTime << " to " << journey.returnTime << " - Seats: ";
        if (journey.availableSeats[0] == 0) {
            cout << "Closed\n";
        } else {
            cout << journey.availableSeats[0] << " remaining\n";
        }
    }
}

void purchaseTickets(vector<TrainJourney>& trainSchedule) {
    displayTrainSchedule(trainSchedule);

    int choice;
    cout << "\nEnter train number for booking the tickets (0 to exit): ";
    cin >> choice;

    if (choice == 0) {
        cout << "Thank you for using the Ticket Management System. Goodbye!\n";
        return;
    } else if (choice >= 1 && choice <= 4) {
        TrainJourney& selectedJourney = trainSchedule[choice - 1];
        int passengers;
        cout << "Enter the number of passengers: ";
        cin >> passengers;

        if (passengers < 1) {
            cout << "Enter more than one passenger. Please try again.\n";
            return;
        }

        int totalCost = price * passengers;
        int freeTickets = passengers / free_ticket_hold;

        if (freeTickets > 0) {
            totalCost -= freeTickets * price;
        }

        if (totalCost < 0) {
            totalCost = 0;
        }

        if (selectedJourney.availableSeats[0] < passengers) {
            cout << "Not enough seats available. Please choose another train.\n";
            return;
        } else {
            selectedJourney.availableSeats[0] -= passengers;
            selectedJourney.totalPassengers += passengers;
            selectedJourney.totalRevenue += totalCost;

            cout << "\nTickets purchased successfully!\n";
            cout << "Total Cost: $" << totalCost << endl;
            cout << "Tickets booked for Train " << choice << ".\n";
        }
    } else {
        cout << "Invalid choice. Please enter a number between 1 and 4 or 0 to exit.\n";
    }
}

void displayDaySummary(const vector<TrainJourney>& trainSchedule) {
    int totalPassengersForDay = 0;
    int totalRevenueForDay = 0;
    TrainJourney mostPassengersJourney = trainSchedule[0];

    cout << "\nEnd of the Day Summary:\n";
    for (int i = 0; i < trainSchedule.size(); i++) {
        const TrainJourney& journey = trainSchedule[i];
        cout << "Train " << (i + 1) << ": " << journey.departureTime << " to " << journey.returnTime << "\n";
        cout << "Total Passengers: " << journey.totalPassengers << "\n";
        cout << "Total Revenue: $" << journey.totalRevenue << "\n";

        totalPassengersForDay += journey.totalPassengers;
        totalRevenueForDay += journey.totalRevenue;

        if (journey.totalPassengers > mostPassengersJourney.totalPassengers) {
            mostPassengersJourney = journey;
        }
    }

    cout << "Total Passengers for the Day: " << totalPassengersForDay << "\n";
    cout << "Total Revenue for the Day: $" << totalRevenueForDay << "\n";
    cout << "Train Journey with the Most Passengers: Train " << (mostPassengersJourney.departureTime) << " to " << mostPassengersJourney.returnTime << "\n";
}

int main() {
    displayHeader();
    vector<TrainJourney> trainSchedule = {
        {"09:00", "10:00", vector<int>(coaches, coach_seat), 0, 0},
        {"11:00", "12:00", vector<int>(coaches, coach_seat), 0, 0},
        {"13:00", "14:00", vector<int>(coaches, coach_seat), 0, 0},
        {"15:00", "16:00", vector<int>(coaches, coach_seat), 0, 0}
    };

    cout << "Electric Mountain Railway - Start of the Day\n";

    while (true) {
        displayMenu();

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                displayTrainSchedule(trainSchedule);
                break;
            case 2:
                purchaseTickets(trainSchedule);
                break;
            case 3:
                displayDaySummary(trainSchedule);
                break;
            case 0:
                cout << "Thank you for using the Ticket Management System. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }
    }

    return 0;
}
