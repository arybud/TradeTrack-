
#  TradeTrack Journal - A Trading Journal Software

## Overview

TradeTrack Journal is a C++ console application crafted to create and manage trading journal entries. It offers functionalities for adding, viewing, editing, deleting journal entries, and changing passwords for secure access.

## Features

- **Password Protection**: Secure login with encrypted password storage.
- **Journal Management**:
  - **Add new journal entries**: Allows users to add new journal entries.
  - **View and edit existing entries**: Users can view and make changes to their previous journal entries.
  - **Delete specific entries**: Remove unwanted journal entries.
  - **Display all journal entries**: View a list of all journal entries.
- **Password Management**: Change the password securely.

## Functions

- **CheckPassword**: Verifies the entered password against the stored password.
- **SetNewPassword**: Prompts and sets a new password.
- **isValidDate**: Validates the date format (DD-MM-YYYY).
- **AddNewJournal**: Adds a new journal entry.
- **ViewEditOldJournal**: Views or edits an existing journal entry.
- **DeleteJournal**: Deletes a journal entry.
- **DisplayAllJournals**: Displays all journal entries.
- **ChangePassword**: Changes the existing password.

## Installation

Open bash and follow these steps :-

1. Clone the repository:
   ```sh
   git clone https://github.com/your-username/TradeTrack_Journal.git

2. Navigate to the project directory:
   ```sh
   cd TradeTrack_Journal

3. Compile the source code:
   ```sh
   g++ main.cpp -o TradeTrack_Journal


## Usage

1. Run the application in Bash:
   ```sh
   ./TradeTrack_Journal

2. Follow the prompts to set a password if not already set, and log in.
## Contributing

Contributions are always welcome! Please submit issues or fork the repository and create pull requests.




## License

This project is licensed under the MIT License.

