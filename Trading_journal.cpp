#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdio>

using namespace std;
string EncryptDecrypt(const string& str, const string& key) {
    string result = str;
    for (size_t i = 0; i < str.size(); ++i) {
        result[i] ^= key[i % key.size()];
    }
    return result;
}

bool CheckPassword(const string& password, const string& key) {
    string storedPassword;
    ifstream file("password.txt");
    if (file.is_open()) {
        getline(file, storedPassword);
        file.close();
    } else {
        return false;
    }

    string decryptedPassword = EncryptDecrypt(storedPassword, key);
    return (password == decryptedPassword);
}


void SetNewPassword(const string& key) {
    string newpassword, confirmPassword;
    cout << "No password found. Set a new password: ";
    cin >> newpassword;
    cout << "Confirm the new password: ";
    cin >> confirmPassword;

    if (newpassword == confirmPassword) {
        string encryptedPassword = EncryptDecrypt(newpassword, key);
        ofstream passwordfile("password.txt");
        if (passwordfile.is_open()) {
            passwordfile << encryptedPassword;
            passwordfile.close();
            cout << "Password set successfully" << endl;
        } else {
            cerr << "Error: Failed to open password file for writing" << endl;
            exit(1);
        }
    } else {
        cerr << "Passwords do not match. Please restart the program and try again." << endl;
        exit(1);
    }
}


bool isValidDate(const string& date) {
    if (date.size() != 10) {
        return false;
    }

    for (char c : date) {
        if (!isdigit(c) && c != '-') {
            return false;
        }
    }

    if (date[2] != '-' || date[5] != '-') {
        return false;
    }

    int day, month, year;
    char dash1, dash2;
    stringstream ss(date);
    ss >> day >> dash1 >> month >> dash2 >> year;

    if (ss.fail() || dash1 != '-' || dash2 != '-') {
        return false;
    }

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900) {
        return false;
    }

    return true;
}

void DisplayMainMenu() {
    cout << "\tMain Menu:" << endl;
    cout << "1. Add New Journal" << endl;
    cout << "2. View/Edit an Old Journal" << endl;
    cout << "3. Delete a Journal" << endl;
    cout << "4. Display all Journals" << endl;
    cout << "5. Change Password" << endl;
    cout << "0. Exit" << endl;
}

void AddNewJournal() {
    string date;
    string journal;
    string line;

    while (true) {
        cout << "Enter the date (DD-MM-YYYY): ";
        cin >> date;
        cin.ignore();

        if (!isValidDate(date)) {
            cout << "Invalid date format. Please try again." << endl;
        } else {
            break;
        }
    }

    cout << "Enter your journal (Type 'Finished Writing' in a new line to finish):" << endl;

    ofstream myfile("Journals.txt", ios::app);

    if (myfile.is_open()) {
        while (getline(cin, line) && line != "Finished Writing") {
            journal += line + " ";
        }

        myfile << "Trading Journal " << date << endl;
        myfile << journal << endl;
        myfile << " -------------------------------------------------------" << endl;

        myfile.close();

        cout << "Journal entry added successfully!" << endl;
    } else {
        cout << "Error opening the file." << endl;
    }
      cout<<"Press enter key to return to Main menu.";
    getchar();
    cout<<endl;
}

void ViewEditOldJournal() {
    string date;
    string line;
    bool found = false;

    while(true){
    cout << "Enter the date of the journal you want to view/edit (DD-MM-YYYY): ";
    cin >> date;
    cin.ignore();
     
    if (!isValidDate(date)) {
    cout << "Invalid date format. Please try again." << endl;
    } else {
      break;
     }
    }

    ifstream inputFile("Journals.txt");
    ofstream tempFile("temp_edit.txt");

    if (inputFile.is_open() && tempFile.is_open()) {
        while (getline(inputFile, line)) {
            if (line == "Trading Journal " + date) {
                found = true;
                cout << line << endl;
                while (getline(inputFile, line) && line != "-------------------------------------------------------") {
                    cout << line << endl;
                }

                cout << "You can edit the content above. Type 'Finished Editing' when done." << endl;

                string editLine;
                while (getline(cin, editLine) && editLine != "Finished Editing") {
                    tempFile << editLine << endl;
                }
            } else {
                tempFile << line << endl;
            }
        }

        inputFile.close();
        tempFile.close();

        remove("Journals.txt");
        rename("temp_edit.txt", "Journals.txt");

        if (!found) {
            cout << "Journal entry not found for the given date." << endl;
        } else {
            cout << "Journal entry edited successfully!" << endl;
        }
    } else {
        cout << "Error opening files." << endl;
    }
      cout<<"Press enter key to return to Main menu.";
    getchar();
    cout<<endl;
}

void DeleteJournal() {
    string date;
    string line;
    bool found = false;

    cout << "Enter the date of the journal you want to delete (DD-MM-YYYY): ";
    cin >> date;
    cin.ignore();

    if (!isValidDate(date)) {
        cout << "Invalid date format." << endl;
        cout<<"Press enter key to return to Main menu.";
    getchar();
    cout<<endl;
        return;
    }

    ifstream inputFile("Journals.txt");
    ofstream tempFile("temp.txt");

    if (inputFile.is_open() && tempFile.is_open()) {
        while (getline(inputFile, line)) {
            if (line == "Date: " + date) {
                found = true;
                cout << line << endl;

                while (getline(inputFile, line) && line != "-------------------------------------------------------") {
                    cout << line << endl;
                }

                cout << "Are you sure you want to delete this Journal? (yes/no): ";
                string choice;
                cin >> choice;

                if (choice == "yes") {
                    while (getline(inputFile, line) && line != "-------------------------------------------------------") {
                        // Skip journal content to delete
                    }
                } else {
                    tempFile << line << endl;
                }
            } else {
                tempFile << line << endl;
            }
        }

        inputFile.close();
        tempFile.close();

        remove("Journals.txt");
        rename("temp.txt", "Journals.txt");

        if (found) {
            cout << "Journal entry deleted successfully!" << endl;
        } else {
            cout << "Journal entry not found for the given date." << endl;
        }
    } else {
        cout << "Error opening files." <<endl;
    }
      cout<<"Press enter key to return to Main menu.";
    getchar();
    cout<<endl;
}

void DisplayAllJournals() {
    string line;

    ifstream myfile("Journals.txt");

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            cout << line << endl;
        }

        myfile.close();
    } else {
        cout << "Error opening the journal file." << endl;
    }
    cout<<"Press enter key to return to Main menu.";
    getchar();
    cout<<endl;
}

void ChangePassword(const string& key) {
    string oldpassword, newpassword, confirmPassword;
    cout << "Enter the old password: ";
    cin >> oldpassword;

    if (CheckPassword(oldpassword, key)) {
        cout << "Enter the new password: ";
        cin >> newpassword;

        cout << "Confirm the new password: ";
        cin >> confirmPassword;

        if (newpassword == confirmPassword) {
            string encryptedPassword = EncryptDecrypt(newpassword, key);
            ofstream passwordfile("password.txt");
            if (passwordfile.is_open()) {
                passwordfile << encryptedPassword;
                passwordfile.close();
                cout << "Password changed successfully" << endl;
            } else {
                cerr << "Error: Failed to open password file for writing" << endl;
                exit(1);
            }
        } else {
            cerr << "New password and confirmed passwords do not match." << endl;
        }
    } else {
        cerr << "Incorrect password." << endl;
    }
    cout << "Press enter key to return to Main menu.";
    getchar();
    cout << endl;
}

int main() {
    const string key = "my_secret_key"; 
    int maxAttempts = 3;
    int attempts = 0;
    bool isAuthenticated = false;
    char option;

    cout << "\t\t\t\tTrading Journal" << endl;

    if (FILE *file = fopen("password.txt", "r")) {
        fclose(file);
    } else {
        SetNewPassword(key);
    }

    while (attempts < maxAttempts && !isAuthenticated) {
        string password;
        cout << "Enter the password: ";
        getline(cin, password);

        if (CheckPassword(password, key)) {
            isAuthenticated = true;
            cout << "\n\t\t\t\tWelcome to your Trading Journal" << endl;
            break;
        } else {
            cout << "Incorrect password. Access denied." << endl;
            attempts++;
            if (attempts < maxAttempts) {
                cout << "You have " << maxAttempts - attempts << " attempts remaining." << endl;
            }
        }
    }

    if (isAuthenticated) {
        int choice;

        while (1) {
            DisplayMainMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    AddNewJournal();
                    break;
                case 2:
                    ViewEditOldJournal();
                    break;
                case 3:
                    DeleteJournal();
                    break;
                case 4:
                    DisplayAllJournals();
                    break;
                case 5:
                    ChangePassword(key);
                    break;
                case 0:
                    while (1) {
                        cout << "Are you sure you want to exit ?(y/n): ";
                        cin >> option;
                        if (option == 'y' || option == 'Y')
                            exit(0);
                        else if (option == 'n' || option == 'N') {
                            cout << endl;
                            continue;
                        } else {
                            cout << "Invalid choice\n";
                            cout << "Press enter to return to main menu.\n";
                            getchar();
                            break;
                        }
                    }
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        }
    } else {
        cout << "Maximum login attempts exceeded. Exiting the program." << endl;
    }

    return 0;
}
