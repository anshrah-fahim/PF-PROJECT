#include <iostream>
#include <windows.h> // For SetConsoleTextAttribute for coloured text
#include <limits> // For numeric limits (clearing the buffer)
using namespace std;

struct Appointment {
    string patientName;
    string address;
    int phoneNumber;
    int age;
    string gender;
    string doctorName;      // Doctor name
    string appointmentDay;  // Appointment day
};

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int bookAppointment(Appointment appointments[], int appointmentCount);
void viewAppointments(Appointment appointments[], int appointmentCount);
void updateAppointment(Appointment appointments[], int appointmentCount);
void deleteAppointment(Appointment appointments[], int& appointmentCount);

int main() {
    int setPassword = 1290;
    int password;
    int attempts = 0;
    int maxAttempts = 3;
    setColor(10); // 10 is for green colour
    cout << "                              ---------------------------------------------------------------" << endl;
    cout << "                                   WELCOME TO ONLINE APPOINTMENT SYSTEM OF THE HOSPITAL " << endl;
    cout << "                         **************************************************************************" << endl;
    setColor(15); // 15 is for white colour
    cout << "Use 1290 for the password inorder to login here." << endl;
    do {
        cout << "Enter password: ";
        cin >> password;
        if (password == setPassword) {
            cout << "Login successful!\n";
            break; // Exit the loop if the password is correct
        }
        else {
            attempts++;
            if (attempts < maxAttempts) {
                cout << "Incorrect password! Please try again. " << attempts << " of " << maxAttempts << " attempts are left.\n";
            }
            if (attempts == maxAttempts && password != setPassword) {
                cout << "Maximum attempts reached. Now you can retry after an hour.\n";
            }
        }
    } while (attempts < maxAttempts);

    Appointment appointments[10];
    int appointmentCount = 0;
    int choice;
    cout << "We have the following DOCTORS in our Hospital" << endl;
    cout << "Dr.Sara(Cardiologist), Dr.Ali(Dermatologist), Dr.Rizwan(Orthopedic), Dr.Tyaba(Skin specialist), Dr.Hassan(Physician)\n";

    do {
        setColor(6); // 6 is for yellow colour
        cout << "\n--- Hospital Management System ---\n";
        cout << "1. Book Appointment\n";
        cout << "2. View Appointments\n";
        cout << "3. Update Appointment\n";
        cout << "4. Delete Appointment\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Input validation for menu choice
        if (cin.fail()) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid choice! Please enter a number between 1 and 5.\n";
            continue; // Skip the rest of the loop and prompt the user again
        }

        switch (choice) {
            case 1:
                appointmentCount = bookAppointment(appointments, appointmentCount);
                break;
            case 2:
                viewAppointments(appointments, appointmentCount);
                break;
            case 3:
                updateAppointment(appointments, appointmentCount);
                break;
            case 4:
                deleteAppointment(appointments, appointmentCount);
                break;
            case 5:
                setColor(15);
                cout << "Exiting the system. Thank you!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 5); // Exit the loop when option 5 is selected
    return 0;
}

int bookAppointment(Appointment appointments[], int appointmentCount) {
    if (appointmentCount >= 10) {
        setColor(15);
        cout << "Cannot book more appointments. Limit reached.\n";
        return appointmentCount;
    }

    Appointment patient; // struct Appointment named patient
    setColor(9); // 9 is for blue
    cin.ignore(); // Clear the input buffer before using getline()
    cout << "\nPlease provide the following details:\n";
    cout << "Enter your name: ";
    getline(cin, patient.patientName); // Use getline() for full name input
    cout << "Enter your phone number: ";
    cin >> patient.phoneNumber;
    cin.ignore(); // Clear the buffer before next getline
    cout << "Enter your address: ";
    getline(cin, patient.address); // Use getline() for full address input
    cout << "Enter your age: ";
    cin >> patient.age;
    cin.ignore(); // Clear the buffer before next getline
    cout << "Enter your gender: ";
    getline(cin, patient.gender); // Use getline() for gender input

    // doctor availability
    string doctors[] = { "Dr.Sara(Cardiologist)", "Dr.Ali(Dermatologist)", "Dr.Rizwan(Orthopedic)", "Dr.Tyaba(Skin specialist)", "Dr.Hassan(Physician)" };
    string days[] = { "monday", "tuesday", "wednesday", "thursday", "friday" };
    string inputDay;
    setColor(15); // white
    cout << "AVAILABILITY OF DOCTORS\n";
    cout << "Enter the day and we will tell you about the specific doctor availability: ";
    cin >> inputDay;
    bool found = false;
    for (int i = 0; i < 5; i++) { // matches the day with all the doctors
        if (days[i] == inputDay) {
            patient.doctorName = doctors[i];
            patient.appointmentDay = inputDay;
            setColor(6); // 6 is for yellow
            cout << "\nDoctors available on " << inputDay << ": ---------" << doctors[i];
            found = true;
            break;
        }
    }

    if (!found) { // !found means "not found"
        cout << "No Doctor is available on this day.\n";
        return appointmentCount;
    }

    // record details
    setColor(6);
    cout << "\nThank you, " << patient.patientName << "!" << endl;
    cout << "Your details are recorded as:\n";
    cout << "Name: " << patient.patientName << "\n";
    cout << "Phone Number: " << patient.phoneNumber << "\n";
    cout << "Address: " << patient.address << "\n";
    cout << "Age: " << patient.age << "\n";
    cout << "Gender: " << patient.gender << "\n";

    // Save the appointment
    appointments[appointmentCount] = patient;
    appointmentCount++;
    setColor(12); // 12 is for red
    cout << "\nAppointment booked successfully with " << patient.doctorName << " on " << patient.appointmentDay << ".\n";
    return appointmentCount;
}

void viewAppointments(Appointment appointments[], int appointmentCount) {
    if (appointmentCount == 0) {
        cout << "No appointments found.\n";
        return;
    }
    setColor(15); // 15 is for white
    cout << "\n--- Appointment List ---\n";
    for (int i = 0; i < appointmentCount; i++) {
        setColor(7); // 7 is for grey
        cout << "--- Patient Name: " << appointments[i].patientName << endl;
        cout << "--- Doctor: " << appointments[i].doctorName << endl;
        cout << "--- Day: " << appointments[i].appointmentDay << endl;
        cout << "--- Address: " << appointments[i].address << endl;
        cout << "--- Phone: " << appointments[i].phoneNumber << endl;
        cout << "--- Age: " << appointments[i].age << endl;
        cout << "--- Gender: " << appointments[i].gender << "\n" << endl;
    }
}

void updateAppointment(Appointment appointments[], int appointmentCount) {
    if (appointmentCount == 0) {
        cout << "No appointments to update.\n";
        return;
    }

    int appointmentIndex;
    cout << "Enter the index of the appointment you want to update (0 to " << appointmentCount - 1 << "): ";
    cin >> appointmentIndex;

    if (appointmentIndex < 0 || appointmentIndex >= appointmentCount) {
        cout << "Invalid index.\n";
        return;
    }

    // Ask for the new day and update the doctor accordingly
    string newDay;
    cout << "Enter new appointment day: ";
    cin >> newDay;

    // Check if the new day is valid and assign the doctor accordingly
    string doctors[] = { "Dr.Sara(Cardiologist)", "Dr.Ali(Dermatologist)", "Dr.Rizwan(Orthopedic)", "Dr.Tyaba(Skin specialist)", "Dr.Hassan(Physician)" };
    string days[] = { "monday", "tuesday", "wednesday", "thursday", "friday" };
    bool found = false;

    for (int i = 0; i < 5; i++) {
        if (days[i] == newDay) {
            appointments[appointmentIndex].appointmentDay = newDay;
            appointments[appointmentIndex].doctorName = doctors[i];
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Invalid day! No doctor available on this day.\n";
        return;
    }

    cout << "Appointment updated to " << appointments[appointmentIndex].appointmentDay << " with " << appointments[appointmentIndex].doctorName << ".\n";
}

void deleteAppointment(Appointment appointments[], int& appointmentCount) {
    if (appointmentCount == 0) {
        cout << "No appointments to delete.\n";
        return;
    }

    int appointmentIndex;
    cout << "Enter the index of the appointment you want to delete (0 to " << appointmentCount - 1 << "): ";
    cin >> appointmentIndex;

    if (appointmentIndex < 0 || appointmentIndex >= appointmentCount) {
        cout << "Invalid index.\n";
        return;
    }

    for (int i = appointmentIndex; i < appointmentCount - 1; i++) {
        appointments[i] = appointments[i + 1];
    }

    appointmentCount--;
    cout << "Appointment deleted successfully.\n";
}
