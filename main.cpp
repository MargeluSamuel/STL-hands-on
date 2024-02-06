#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <fstream>
#include <map>

using namespace std;

string currentDepartment;
int currentDuration, currentPatientArrivalTime;

struct Patient {
    string problem, department;
    int arrivalTime, duration, priority;

    bool operator < (const Patient& other) const {
        if (arrivalTime == other.arrivalTime) {
            return priority < other.priority;
        }
        else {
            return arrivalTime > other.arrivalTime;
        }
    }
};

struct Doctor {
    string name;
    map<string, string> departments;
    int availability = 9;
    vector<string> patientsProblem;
};

//currentDepartment == doctor.department

bool departmentMatches(Doctor doctor) {
    if ((doctor.departments[currentDepartment] == "DA") && (currentDuration + doctor.availability <= 17) && (doctor.availability <= currentPatientArrivalTime)) {
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



    ifstream fin("C:\\Users\\User\\Desktop\\New folder (2)\\STL-hands-on\\HandsOn-Input.txt");

    fin >> numberOfPatients;

    for (int i = 0; i < numberOfPatients; i++) {
        string problem, department;
        int arrivalTime, priority, duration;

        fin >> problem >> department >> arrivalTime >> duration >> priority;

        patients.push({ problem, department, arrivalTime, duration, priority });
    }

    /* while (!patients.empty()) {
         Patient temp = patients.top();

         cout << temp.problem << " " << temp.department << " " << temp.arrivalTime << " " << temp.duration << " " << temp.priority << "\n";

         patients.pop();
     }*/

    fin >> numberOfDoctors;

    for (int i = 0; i < numberOfDoctors; i++) {

        Doctor docTemp;
        string name;
        int knowledge;

        fin >> name >> knowledge;

        docTemp.name = name;

        for (int i = 0; i < knowledge; i++) {
            string department;
            fin >> department;

            docTemp.departments[department] = "DA";
        }

        doctors.push_back(docTemp);
    }

    while (!patients.empty()) {
        Patient currentPatient = patients.top();

        currentDuration = currentPatient.duration;
        currentDepartment = currentPatient.department;
        currentPatientArrivalTime = currentPatient.arrivalTime;

        //patients.pop();

        auto doctor = find_if(doctors.begin(), doctors.end(), departmentMatches);

        if (doctor != doctors.end()) {
            doctor->availability += currentDuration;

            doctor->patientsProblem.push_back(currentPatient.problem);


            //sol.push_back(*doctor);
            patients.pop();
        }
        else {
            patients.pop();
        }
    }

    // for (auto i : patients) {
    //     cout << i.problem << " " << i.department << "\n";
    // }

    // for (auto i : doctors) {
    //     cout << i.name << "merge?" << i.department << "\n";
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