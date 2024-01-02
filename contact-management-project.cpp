#include <iostream>
#include <fstream>
using namespace std;
const int MAXCONTACTS = 100;
const string FILENAME = "contacts.txt";

struct Contact {
    string name;
    string email;
    string phoneNumber;
};

Contact contacts[MAXCONTACTS];
int contactCount = 0;

void saveContactsToFile() {
    ofstream outFile(FILENAME);

    for (int i = 0; i < contactCount; ++i) {
        outFile << contacts[i].name << ',' << contacts[i].email << ',' << contacts[i].phoneNumber << '\n';
    }

    outFile.close();
}

void loadContactsFromFile() {
    ifstream inFile(FILENAME);

    if (!inFile.is_open()) {
        cout << "File not found. Creating a new file.\n";
        return;
    }

    while (!inFile.eof() && contactCount < MAXCONTACTS) {
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
         << "1. Add new contact\n"
         << "2. View existing contacts\n"
         << "3. Update contact information\n"
         << "4. Delete Contact\n"
         << "5. Managing File\n"
         << "6. Quit\n"
         << "Please select an option (1-6): ";
}

void addContact() {
    cin.ignore(); // Clear the newline character from the buffer
    if (contactCount < MAXCONTACTS) {
        cout << "\nAdding a contact:\nEnter the following information:\n";
        cout << "Name: ";
        getline(cin, contacts[contactCount].name);
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
            getline(cin, contacts[i].name);
            cout << "Email: ";
            getline(cin, contacts[i].email);
            cout << "Phone Number: ";
            getline(cin, contacts[i].phoneNumber);

            cout << "Contact updated successfully!\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Contact not found.\n";
    }
}

void deleteContact() {
    string searchName;
    cin.ignore(); // Clear the newline character from the buffer
    cout << "\nDeleting a contact:\nEnter the contact name to delete: ";
    getline(cin, searchName);

    bool found = false;
    for (int i = 0; i < contactCount; ++i) {
        if (contacts[i].name == searchName) {
            // Shift elements to fill the gap
            for (int j = i; j < contactCount - 1; ++j) {
                contacts[j] = contacts[j + 1];
            }
            --contactCount;

            cout << "Contact deleted successfully!\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Contact not found.\n";
    }
}

void manageFile() {
    int fileOption;
    cout << "\nManaging File:\n"
         << "1. Save contacts to file\n"
         << "2. Load contacts from file\n"
         << "Please select an option (1-2): ";
    cin >> fileOption;

    switch (fileOption) {
        case 1:
            saveContactsToFile();
            cout << "Contacts saved to file.\n";
            break;
        case 2:
            loadContactsFromFile();
            cout << "Contacts loaded from file.\n";
            break;
        default:
            cout << "Invalid option.\n";
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
            case 4:
                deleteContact();
                break;
            case 5:
                manageFile();
                break;
            case 6:
                saveContactsToFile();
                cout << "Quitting the address book.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice>=1&&choice<=5);

    return 0;
}

