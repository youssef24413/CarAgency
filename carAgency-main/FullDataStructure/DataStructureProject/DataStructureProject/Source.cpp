#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <unordered_map>

using namespace std;

const string RESET_COLOR = "\033[0m";
const string RED_COLOR = "\033[31m";
const string GREEN_COLOR = "\033[32m";
const string YELLOW_COLOR = "\033[33m";
const string BLUE_COLOR = "\033[34m";

class Car {
public:
    string brand;
    string model;
    int year;
    double price;

    Car(const string& brand, const string& model, int year, double price) :
        brand(brand), model(model), year(year), price(price) {}
};

class CarPart {
public:
    string name;
    string type;
    double price;

    CarPart(const string& name, const string& type, double price) :
        name(name), type(type), price(price) {}
};

class UserManager {
private:
    unordered_map<string, string> users;

public:
    UserManager() {}

    bool authenticate(const string& username, const string& password) {
        if (users.find(username) != users.end() && users[username] == password) {
            return true;
        }
        return false;
    }

    void registerUser(const string& username, const string& password) {
        if (users.find(username) == users.end()) {
            users[username] = password;
            cout << GREEN_COLOR << "User registration successful." << RESET_COLOR << "\n";
        }
        else {
            cout << RED_COLOR << "Username already exists. Please choose a different username." << RESET_COLOR << "\n";
        }
    }
};

class CarAgencyManagementSystem {
private:
    stack<Car> carInventory;
    stack<CarPart> carPartsInventory;
    const int MAX_STACK_SIZE = 5;

public:
    void addCar(const string& brand, const string& model, int year, double price) {
        if (carInventory.size() < MAX_STACK_SIZE) {
            Car newCar(brand, model, year, price);
            carInventory.push(newCar);
            cout << GREEN_COLOR << "Car added to inventory successfully." << RESET_COLOR << "\n";
        }
        else {
            cout << YELLOW_COLOR << "Warning: Car inventory is full. Cannot add more cars." << RESET_COLOR << "\n";
        }
    }

    void addCarPart(const string& name, const string& type, double price) {
        if (carPartsInventory.size() < MAX_STACK_SIZE) {
            CarPart newPart(name, type, price);
            carPartsInventory.push(newPart);
            cout << GREEN_COLOR << "Car part added to inventory successfully." << RESET_COLOR << "\n";
        }
        else {
            cout << YELLOW_COLOR << "Warning: Car part inventory is full. Cannot add more car parts." << RESET_COLOR << "\n";
        }
    }

    void viewLatestCarDetails() {
        if (carInventory.empty()) {
            cout << YELLOW_COLOR << "No cars in the inventory." << RESET_COLOR << "\n";
        }
        else {
            Car latestCar = carInventory.top();
            cout << "Latest Car Details:\n";
            cout << GREEN_COLOR << "Brand: " << latestCar.brand << RESET_COLOR << "\n";
            cout << GREEN_COLOR << "Model: " << latestCar.model << RESET_COLOR << "\n";
            cout << GREEN_COLOR << "Year: " << latestCar.year << RESET_COLOR << "\n";
            cout << GREEN_COLOR << "Price: $" << latestCar.price << RESET_COLOR << "\n";
        }
    }

    void viewAllCars() {
        if (carInventory.empty()) {
            cout << YELLOW_COLOR << "No cars in the inventory." << RESET_COLOR << "\n";
        }
        else {
            cout << "All Cars in Inventory:\n";
            stack<Car> tempStack = carInventory;

            while (!tempStack.empty()) {
                Car currentCar = tempStack.top();
                tempStack.pop();

                cout << GREEN_COLOR << "Brand: " << currentCar.brand << RESET_COLOR << "\n";
                cout << GREEN_COLOR << "Model: " << currentCar.model << RESET_COLOR << "\n";
                cout << GREEN_COLOR << "Year: " << currentCar.year << RESET_COLOR << "\n";
                cout << GREEN_COLOR << "Price: $" << currentCar.price << RESET_COLOR << "\n";
                cout << "---------------------------\n";
            }
        }
    }

    void viewAllCarParts() {
        if (carPartsInventory.empty()) {
            cout << YELLOW_COLOR << "No car parts in the inventory." << RESET_COLOR << "\n";
        }
        else {
            cout << "All Car Parts in Inventory:\n";
            stack<CarPart> tempStack = carPartsInventory;

            while (!tempStack.empty()) {
                CarPart currentPart = tempStack.top();
                tempStack.pop();

                cout << GREEN_COLOR << "Name: " << currentPart.name << RESET_COLOR << "\n";
                cout << GREEN_COLOR << "Type: " << currentPart.type << RESET_COLOR << "\n";
                cout << GREEN_COLOR << "Price: $" << currentPart.price << RESET_COLOR << "\n";
                cout << "---------------------------\n";
            }
        }
    }

    void removeCarPart(const string& name, const string& type) {
        if (carPartsInventory.empty()) {
            cout << YELLOW_COLOR << "No car parts in the inventory." << RESET_COLOR << "\n";
        }
        else {
            stack<CarPart> tempStack;
            bool partFound = false;

            while (!carPartsInventory.empty()) {
                CarPart currentPart = carPartsInventory.top();
                carPartsInventory.pop();

                if (currentPart.name == name && currentPart.type == type) {
                    partFound = true;
                    cout << GREEN_COLOR << "Car part removed from inventory." << RESET_COLOR << "\n";
                }
                else {
                    tempStack.push(currentPart);
                }
            }

            if (!partFound) {
                cout << YELLOW_COLOR << "Car part not found in the inventory." << RESET_COLOR << "\n";
            }

            while (!tempStack.empty()) {
                carPartsInventory.push(tempStack.top());
                tempStack.pop();
            }
        }
    }

    void removeCar(const string& brand, const string& model) {
        if (carInventory.empty()) {
            cout << YELLOW_COLOR << "No cars in the inventory." << RESET_COLOR << "\n";
        }
        else {
            stack<Car> tempStack;
            bool carFound = false;

            while (!carInventory.empty()) {
                Car currentCar = carInventory.top();
                carInventory.pop();

                if (currentCar.brand == brand && currentCar.model == model) {
                    carFound = true;
                    cout << GREEN_COLOR << "Car removed from inventory." << RESET_COLOR << "\n";
                }
                else {
                    tempStack.push(currentCar);
                }
            }

            if (!carFound) {
                cout << YELLOW_COLOR << "Car not found in the inventory." << RESET_COLOR << "\n";
            }

            while (!tempStack.empty()) {
                carInventory.push(tempStack.top());
                tempStack.pop();
            }
        }
    }

    bool searchCar(const string& brand, const string& model) {
        stack<Car> tempStack = carInventory;

        while (!tempStack.empty()) {
            Car currentCar = tempStack.top();
            tempStack.pop();

            if (currentCar.brand == brand && currentCar.model == model) {
                return true;
            }
        }
        return false;
    }

    bool searchCarPart(const string& name, const string& type) {
        stack<CarPart> tempStack = carPartsInventory;

        while (!tempStack.empty()) {
            CarPart currentPart = tempStack.top();
            tempStack.pop();

            if (currentPart.name == name && currentPart.type == type) {
                return true;
            }
        }
        return false;
    }
};

class MaintenanceCenter {
private:
    struct CarCompare {
        bool operator()(const pair<int, Car>& a, const pair<int, Car>& b) const {
            return a.first < b.first;
        }
    };

    priority_queue<pair<int, Car>, vector<pair<int, Car>>, CarCompare> maintenanceQueue;

public:
    void enqueueCarToMaintenance(const Car& car, int levelOfDestruction) {
        maintenanceQueue.push({ levelOfDestruction, car });
        cout << GREEN_COLOR << "Car added to maintenance queue successfully." << RESET_COLOR << "\n";
    }

    void dequeueCarFromMaintenance(const Car& car) {
        bool carFound = false;
        priority_queue<pair<int, Car>, vector<pair<int, Car>>, CarCompare> tempQueue;

        while (!maintenanceQueue.empty()) {
            if (maintenanceQueue.top().second.brand == car.brand && maintenanceQueue.top().second.model == car.model) {
                carFound = true;
                cout << GREEN_COLOR << "Car removed from maintenance queue." << RESET_COLOR << "\n";
                maintenanceQueue.pop();
                break;
            }
            tempQueue.push(maintenanceQueue.top());
            maintenanceQueue.pop();
        }

        while (!tempQueue.empty()) {
            maintenanceQueue.push(tempQueue.top());
            tempQueue.pop();
        }

        if (!carFound) {
            cout << YELLOW_COLOR << "Car not found in maintenance queue." << RESET_COLOR << "\n";
        }
    }

    void viewFrontCar() {
        if (maintenanceQueue.empty()) {
            cout << YELLOW_COLOR << "Maintenance queue is empty." << RESET_COLOR << "\n";
        }
        else {
            Car frontCar = maintenanceQueue.top().second;
            cout << "Front Car in Maintenance Queue:\n";
            cout << GREEN_COLOR << "Brand: " << frontCar.brand << RESET_COLOR << "\n";
            cout << GREEN_COLOR << "Model: " << frontCar.model << RESET_COLOR << "\n";
            cout << GREEN_COLOR << "Year: " << frontCar.year << RESET_COLOR << "\n";
            //cout << GREEN_COLOR << "Price: $" << frontCar.price << RESET_COLOR << "\n";
            cout << GREEN_COLOR << "Level of Destruction: " << maintenanceQueue.top().first << RESET_COLOR << "\n";
        }
    }

    void viewAllCars() {
        if (maintenanceQueue.empty()) {
            cout << YELLOW_COLOR << "Maintenance queue is empty." << RESET_COLOR << "\n";
        }
        else {
            priority_queue<pair<int, Car>, vector<pair<int, Car>>, CarCompare> tempQueue = maintenanceQueue;

            cout << "All Cars in Maintenance Queue:\n";
            while (!tempQueue.empty()) {
                Car currentCar = tempQueue.top().second;
                cout << GREEN_COLOR << "Brand: " << currentCar.brand << RESET_COLOR << "\n";
                cout << GREEN_COLOR << "Model: " << currentCar.model << RESET_COLOR << "\n";
                cout << GREEN_COLOR << "Year: " << currentCar.year << RESET_COLOR << "\n";
                //cout << GREEN_COLOR << "Price: $" << currentCar.price << RESET_COLOR << "\n";
                cout << GREEN_COLOR << "Level of Destruction: " << tempQueue.top().first << RESET_COLOR << "\n";
                cout << "---------------------------\n";
                tempQueue.pop();
            }
        }
    }

    bool searchCar(const Car& car) {
        priority_queue<pair<int, Car>, vector<pair<int, Car>>, CarCompare> tempQueue = maintenanceQueue;

        while (!tempQueue.empty()) {
            if (tempQueue.top().second.brand == car.brand && tempQueue.top().second.model == car.model) {
                return true;
            }
            tempQueue.pop();
        }
        return false;
    }
};

struct CarNode {
    string brand;
    string model;
    int year;
    double price;
    CarNode* next;

    CarNode(string brand, string model, int year, double price) :
        brand(brand), model(model), year(year), price(price), next(nullptr) {}
};

class UsedCarList {
private:
    CarNode* head;

public:
    UsedCarList() {
        head = nullptr;
    }

    ~UsedCarList() {
        CarNode* current = head;
        while (current != nullptr) {
            CarNode* next = current->next;
            delete current;
            current = next;
        }
    }

    void addCar(string brand, string model, int year, double price) {
        CarNode* newCar = new CarNode(brand, model, year, price);
        if (head == nullptr) {
            head = newCar;
        }
        else {
            CarNode* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newCar;
        }
    }

    void removeCar(string brand, string model) {
        if (head == nullptr) {
            cout << "No cars in the list." << endl;
            return;
        }

        if (head->brand == brand && head->model == model) {
            CarNode* temp = head;
            head = head->next;
            delete temp;
            cout << "Car removed successfully." << endl;
            return;
        }

        CarNode* current = head;
        CarNode* prev = nullptr;
        while (current != nullptr && (current->brand != brand || current->model != model)) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Car not found." << endl;
        }
        else {
            prev->next = current->next;
            delete current;
            cout << "Car removed successfully." << endl;
        }
    }

    void searchCar(string brand, string model) {
        CarNode* current = head;
        while (current != nullptr && (current->brand != brand || current->model != model)) {
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Car not found." << endl;
        }
        else {
            cout << "Car found: " << current->brand << " " << current->model << " " << current->year << " " << current->price << endl;
        }
    }

    bool viewCars() {
        if (head == nullptr) {
            cout << "No cars in the list." << endl;
            return false;
        }

        CarNode* current = head;
        while (current->next != nullptr) {
            cout << "Brand: " << current->brand << endl;
            cout << "Model: " << current->model << endl;
            cout << "Year: " << current->year << endl;
            cout << "Price: " << current->price << endl << endl;
            current = current->next;
        }

        cout << "Last entered car: " << endl;
        cout << "Brand: " << current->brand << endl;
        cout << "Model: " << current->model << endl;
        cout << "Year: " << current->year << endl;
        cout << "Price: " << current->price << endl;
        return true;
    }
};

int main() {
    UserManager userManager;
    string username, password;

    cout << BLUE_COLOR << "Car Management System" << RESET_COLOR << "\n";

    while (true) {
        cout << "Create a username: ";
        cin >> username;

        cout << "Create a password: ";
        cin >> password;

        userManager.registerUser(username, password);

        cout << "Would you like to register another user? (" << GREEN_COLOR << "yes" << RESET_COLOR << "/" << RED_COLOR << "no" << RESET_COLOR << "): ";
        string choice;
        cin >> choice;

        if (choice != "yes") {
            break;
        }
    }

    while (true) {
        cout << "Enter username: ";
        cin >> username;

        cout << "Enter password: ";
        cin >> password;

        if (userManager.authenticate(username, password)) {
            cout << GREEN_COLOR << "Authentication successful. Welcome, " << username << "!" << RESET_COLOR << "\n";
            break;
        }
        else {
            cout << RED_COLOR << "Authentication failed. Please try again." << RESET_COLOR << "\n";
        }
    }

    CarAgencyManagementSystem carAgency;
    MaintenanceCenter maintenanceCenter;
    UsedCarList usedCarList;
    int choice;
    int itemType;

    do {
        cout << "Choose item type:\n";
        cout << "1. Car\n";
        cout << "2. Car Part\n";
        cout << "3. Maintenance Center\n";
        cout << "4. Used Car List\n";
        cout << "Enter your choice: ";
        cin >> itemType;

        switch (itemType) {
        case 1:
            cout << "Car Operations:\n";
            cout << "1. Add Car\n";
            cout << "2. Remove Car\n";
            cout << "3. View Latest Car Details\n";
            cout << "4. View All Cars\n";
            cout << "5. Search Car\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                string brand, model;
                int year;
                double price;

                cout << "Enter car brand: ";
                cin >> brand;

                cout << "Enter car model: ";
                cin >> model;

                cout << "Enter car year: ";
                cin >> year;

                cout << "Enter car price: $";
                cin >> price;

                carAgency.addCar(brand, model, year, price);
                break;
            }
            case 2: {
                string brand, model;
                cout << "Enter car brand: ";
                cin >> brand;

                cout << "Enter car model: ";
                cin >> model;

                carAgency.removeCar(brand, model);
                break;
            }
            case 3: {
                carAgency.viewLatestCarDetails();
                break;
            }
            case 4: {
                carAgency.viewAllCars();
                break;
            }
            case 5: {
                string brand, model;
                cout << "Enter car brand: ";
                cin >> brand;

                cout << "Enter car model: ";
                cin >> model;

                if (carAgency.searchCar(brand, model)) {
                    cout << GREEN_COLOR << "Car found in inventory." << RESET_COLOR << "\n";
                }
                else {
                    cout << YELLOW_COLOR << "Car not found in inventory." << RESET_COLOR << "\n";
                }
                break;
            }
            default:
                cout << RED_COLOR << "Invalid choice. Please enter a valid option." << RESET_COLOR << "\n";
            }
            break;
        case 2:
            cout << "Car Part Operations:\n";
            cout << "1. Add Car Part\n";
            cout << "2. Remove Car Part\n";
            cout << "3. View All Car Parts\n";
            cout << "4. Search Car Part\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                string name, type;
                double price;

                cout << "Enter part name: ";
                cin >> name;

                cout << "Enter part type: ";
                cin >> type;

                cout << "Enter part price: $";
                cin >> price;

                carAgency.addCarPart(name, type, price);
                break;
            }
            case 2: {
                string name, type;
                cout << "Enter part name: ";
                cin >> name;

                cout << "Enter part type: ";
                cin >> type;

                carAgency.removeCarPart(name, type);
                break;
            }
            case 3: {
                carAgency.viewAllCarParts();
                break;
            }
            case 4: {
                string name, type;
                cout << "Enter part name: ";
                cin >> name;

                cout << "Enter part type: ";
                cin >> type;

                if (carAgency.searchCarPart(name, type)) {
                    cout << GREEN_COLOR << "Car part found in inventory." << RESET_COLOR << "\n";
                }
                else {
                    cout << YELLOW_COLOR << "Car part not found in inventory." << RESET_COLOR << "\n";
                }
                break;
            }
            default:
                cout << RED_COLOR << "Invalid choice. Please enter a valid option." << RESET_COLOR << "\n";
            }
            break;
        case 3:
            cout << "Maintenance Center Operations:\n";
            cout << "1. Enqueue Car to Maintenance\n";
            cout << "2. Dequeue Car from Maintenance\n";
            cout << "3. View Front Car in Maintenance Queue\n";
            cout << "4. View All Cars in Maintenance Queue\n";
            cout << "5. Search Car in Maintenance\n"; // Added
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                string brand, model;
                int year, levelOfDestruction;

                cout << "Enter car brand: ";
                cin >> brand;

                cout << "Enter car model: ";
                cin >> model;

                cout << "Enter car year: ";
                cin >> year;

                cout << "Enter level of destruction: ";
                cin >> levelOfDestruction;

                Car newCar(brand, model, year, 0);
                maintenanceCenter.enqueueCarToMaintenance(newCar, levelOfDestruction);
                break;
            }
            case 2: {
                string brand, model;

                cout << "Enter car brand: ";
                cin >> brand;

                cout << "Enter car model: ";
                cin >> model;

                Car carToDequeue(brand, model, 0, 0);
                maintenanceCenter.dequeueCarFromMaintenance(carToDequeue);
                break;
            }
            case 3: {
                maintenanceCenter.viewFrontCar();
                break;
            }
            case 4: {
                maintenanceCenter.viewAllCars();
                break;
            }
            case 5: {
                string brand, model;
                cout << "Enter car brand: ";
                cin >> brand;

                cout << "Enter car model: ";
                cin >> model;

                Car carToSearch(brand, model, 0, 0);
                if (maintenanceCenter.searchCar(carToSearch)) {
                    cout << GREEN_COLOR << "Car found in maintenance queue." << RESET_COLOR << "\n";
                }
                else {
                    cout << YELLOW_COLOR << "Car not found in maintenance queue." << RESET_COLOR << "\n";
                }
                break;
            }
            default:
                cout << RED_COLOR << "Invalid choice. Please enter a valid option." << RESET_COLOR << "\n";
            }
            break;
        case 4:
            cout << "Used Car List Operations:\n";
            cout << "1. Add Car\n";
            cout << "2. Remove Car\n";
            cout << "3. View Cars\n";
            cout << "4. Search Car\n"; // Added
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                string brand, model;
                int year;
                double price;

                cout << "Enter car brand: ";
                cin >> brand;

                cout << "Enter car model: ";
                cin >> model;

                cout << "Enter car year: ";
                cin >> year;

                cout << "Enter car price: $";
                cin >> price;

                usedCarList.addCar(brand, model, year, price);
                break;
            }
            case 2: {
                string brand, model;
                cout << "Enter car brand: ";
                cin >> brand;

                cout << "Enter car model: ";
                cin >> model;

                usedCarList.removeCar(brand, model);
                break;
            }
            case 3: {
                usedCarList.viewCars();
                break;
            }
            case 4: {
                string brand, model;
                cout << "Enter car brand: ";
                cin >> brand;

                cout << "Enter car model: ";
                cin >> model;

                usedCarList.searchCar(brand, model);
                break;
            }
            default:
                cout << RED_COLOR << "Invalid choice. Please enter a valid option." << RESET_COLOR << "\n";
            }
            break;
        default:
            cout << RED_COLOR << "Invalid choice. Please enter a valid option." << RESET_COLOR << "\n";
        }

        cout << "Do you want to continue? (" << GREEN_COLOR << "yes" << RESET_COLOR << "/" << RED_COLOR << "no" << RESET_COLOR << "): ";
        string continueChoice;
        cin >> continueChoice;

        if (continueChoice == "no") {
            break;
        }
    } while (true);

    cout << "Exiting program. Goodbye!" << endl;

    return 0;
}