#include <iostream>
#include <fstream>
using namespace std;
const int MAX_CONTACTS = 100;
const string FILE_NAME = "contacts.txt";

struct Contact {
    string name;
    string email;
    string phoneNumber;
};

Contact contacts[MAX_CONTACTS];
int contactCount = 0;

void saveContactsToFile() {
    ofstream outFile(FILE_NAME);

    for (int i = 0; i < contactCount; ++i) {
        outFile << contacts[i].name << ',' << contacts[i].email << ',' << contacts[i].phoneNumber << '\n';
    }

    outFile.close();
}

void loadContactsFromFile() {
    ifstream inFile(FILE_NAME);

    if (!inFile.is_open()) {
        cout << "File not found. Creating a new file.\n";
        return;
    }

    while (!inFile.eof() && contactCount < MAX_CONTACTS) {
        getline(inFile, contacts[contactCount].name, ',');
       getline(inFile, contacts[contactCount].email, ',');
        getline(inFile, contacts[contactCount].phoneNumber, '\n');

        if (!contacts[contactCount].name.empty()) {
            ++contactCount;
        }
    }

    inFile.close();
}

void displayMainMenu() {
    cout << "Main Menu:\n"
                 "1. Add new contact\n"
                 "2. View existing contacts\n"
                 "3. Update contact information\n"
                 "4. Delete Contact\n"
                 "5. Managing File\n"
                 "6. Quit\n"
                 "Please select an option (1-6): ";
}

void addContact() {
    cin.ignore(); // Clear the newline character from the buffer
    if (contactCount < MAX_CONTACTS) {
        cout << "\nAdding a contact:\nEnter the following information:\n";
        cout << "Name: ";
        getline(std::cin, contacts[contactCount].name);
        cout << "Email: ";
        getline(cin, contacts[contactCount].email);
        cout << "Phone Number: ";
        getline(cin, contacts[contactCount].phoneNumber);

        ++contactCount;

        cout << "Contact added successfully!\n";
    } else {
        cout << "Contact list is full. Cannot add more contacts.\n";
    }
}

void viewContacts() {
    cout << "\nViewing contacts:\nContacts List:\n";

    for (int i = 0; i < contactCount; ++i) {
        cout << "Name: " << contacts[i].name << "\tPhone: " << contacts[i].phoneNumber
                  << "\tEmail: " << contacts[i].email << "\n";
    }

    cout << "\n1. Back to Main Menu\n";
}

void updateContact() {
    string searchName;
    cin.ignore(); // Clear the newline character from the buffer
    cout << "\nUpdating contact information:\nEnter the contact name to update: ";
    getline(cin, searchName);

    bool found = false;
    for (int i = 0; i < contactCount; ++i) {
        if (contacts[i].name == searchName) {
            cout << "Enter the new information:\n";
            cout << "Name: ";
            getline(std::cin, contacts[i].name);
            cout << "Email: ";
            getline(std::cin, contacts[i].email);
            cout << "Phone Number: ";
            getline(std::cin, contacts[i].phoneNumber);

            cout << "Contact updated successfully!\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Contact not found.\n";
    }
}

int main() {
    loadContactsFromFile();

    int choice;

    do {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                updateContact();
                break;
            // Add cases for other options (4. Save contacts to file, 5. Load contacts from file, 6. Quit)

            case 6:
                saveContactsToFile();
                cout << "Quitting the address book.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}
