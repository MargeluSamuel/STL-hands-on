#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <fstream>

using namespace std;

string currentDepartment;
int currentDuration;

struct Patient {
    string problem, department;
    int duration, priority;

    bool operator < (const Patient& other) const {
        return priority < other.priority;
    }
};

struct Doctor {
    string name, department;
    int availability = 0;
    vector<string> patientsProblem;
};


bool departmentMatches(Doctor doctor) {
    if ((currentDepartment == doctor.department) && (currentDuration + doctor.availability <= 8)) {
        return true;
    }
    else {
        return false;
    }
}


int main() {

    int numberOfDoctors, numberOfPatients;
    vector<Doctor> doctors; vector<Doctor> sol;
    priority_queue<Patient> patients;



    ifstream fin("db.txt");

    fin >> numberOfPatients;

    for (int i = 0; i < numberOfPatients; i++) {
        string problem, department;
        int priority, duration;

        fin >> problem >> department >> duration >> priority;

        patients.push({ problem, department, duration, priority });
    }

    /* while (!patients.empty()) {
         Patient temp = patients.top();

         cout << temp.priority;

         patients.pop();
     }*/

    fin >> numberOfDoctors;

    for (int i = 0; i < numberOfDoctors; i++) {

        string name, department;

        fin >> name >> department;

        doctors.push_back({ name, department });
    }

    while (!patients.empty()) {
        Patient currentPatient = patients.top();

        currentDuration = currentPatient.duration;
        currentDepartment = currentPatient.department;

        patients.pop();

        auto doctor = find_if(doctors.begin(), doctors.end(), departmentMatches);

        if (doctor != doctors.end()) {
            doctor->availability += currentDuration;

            doctor->patientsProblem.push_back(currentPatient.problem);


            sol.push_back(*doctor);
        }
    }

    // for (auto i : patients) {
    //     cout << i.problem << " " << i.department << "\n";
    // }

    // for (auto i : doctors) {
    //     cout << i.name << " " << i.department << "\n";
    // }



    for (vector<Doctor>::iterator it = doctors.begin(); it < doctors.end(); it++) {
        if (it->patientsProblem.size() > 0) {
            cout << it->name << " ";
            for (auto i : it->patientsProblem) {
                cout << i << " ";
            }

            cout << "\n";
        }
    }


}