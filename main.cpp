#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

string currentDepartment;

struct Patient {
    string problem, department;
};

struct Doctor {
    string name, department, patientsProblem = "";
};


bool departmentMatches(Doctor doctor) {
    if ((doctor.patientsProblem == "") && (currentDepartment == doctor.department)) {
        return true;
    }
    else {
        return false;
    }
}


int main() {

    int numberOfDoctors, numberOfPatients;
    vector<Patient> patients; vector<Doctor> doctors; vector<Doctor> sol;



    ifstream fin("D:\\Exercitii\\Facultate\\netrom\\Repos\\Fork-STL-hands-on.git\\HandsOn-Input.txt");

    fin >> numberOfPatients;

    for (int i = 0; i < numberOfPatients; i++) {
        string problem, department;

        fin >> problem >> department;

        patients.push_back({ problem, department });
    }

    fin >> numberOfDoctors;

    for (int i = 0; i < numberOfPatients; i++) {
        string name, department;

        fin >> name >> department;

        doctors.push_back({ name, department });
    }

    // for (auto i : patients) {
    //     cout << i.problem << " " << i.department << "\n";
    // }

    // for (auto i : doctors) {
    //     cout << i.name << "salut" << i.department << "\n";
    // }

    for (vector<Patient>::iterator pIt = patients.begin(); pIt < patients.end(); pIt++) {

        currentDepartment = pIt->department;
        vector<Doctor>::iterator dIt = find_if(doctors.begin(), doctors.end(), departmentMatches);

        if (dIt != doctors.end()) {
            dIt->patientsProblem = pIt->problem;
            sol.push_back(*dIt);
        }
    }

    for (vector<Doctor>::iterator it = sol.begin(); it < sol.end(); it++) {
        cout << it->name << " " << it->patientsProblem << "\n";
    }


}