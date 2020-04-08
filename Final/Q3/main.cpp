#include "Patient.h"

#include <iostream>
#include <utility>

#include <queue>
#include <stack>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

using namespace std;

// Describe any additional functions that are needed for part III

int main(int argc,char* argv[]) {
    if (argc < 2) {
        cerr << "Proper usage: " << argv[0] << " <patients_file>." << endl;
        return 1;
    }

    ifstream ifs(argv[1]);
    if (!ifs.is_open()) {
        cerr << "Error: Unable to open " << argv[1] << endl;
        return 1;
    }

    //??? intake_times;  // Part I, what data structure should be used here and why? (implement)
    set<pair<int, int>> intake_times;//O(1) bc its just initializing
    //??? patients; // Part II, what data structure should be used here and why? (implement)
    unordered_map<int, Patient*> patients;//O(1) bc its initializing
    //??? patient_urgencies; // Part III, what data structure should be used here and why? (comments only)

    //A set would be a good data structure to initialize patient urgency because it would organize the urgency by the number that corresponds to it.
    //the runtime would also be O(log(n)) when you insert due to the fact that sets use a red-black tree.
    //Just initaialize here with type being a pair of the int of the urgency and the patient pointer.
    // basically this is so we can identify and iterate through higher urgency by starting at the end of the set and going to the beginning since iis ordered form smallest to biggest.

    string first_name, last_name;
    int intake_time,urgency,id;

    // Overall runtime complexity: O(nlog(n))
    // Overall space complexity: O(n)
    while (ifs >> id) {// O(n)
        ifs >> first_name >> last_name >> intake_time >> urgency; // O(1)
        Patient *patient_record = new Patient(id,first_name + " "s + last_name); // O(1)
        patient_record->urgency(urgency); // O(1)

        intake_times.insert(make_pair(intake_time,id)); // O(log(n))
        patients.insert(make_pair(id,patient_record)); // O(1)
        // patient_urgencies.???(patient_record) // O(log(n))
    }
    // Output Patients sorted by oldest intake_time (smallest) to newest intake_time (largest) (Implement)
    cout << "Sorted by intake times: " << endl;
    for(set<pair<int, int>> :: iterator it = intake_times.begin(); it != intake_times.end(); ++it)
    {
      cout << *patients.at(it->second) << endl;
    }
    // Output Patients ID's sorted by most urgent to least urgent
    // In comment describe how this would work.
    //so basically we would iterate through the set starting from the end and going till you hit set.begin()
    // then call upon the second value in the set index since its a pair which would be th Patient pointer and print the Patient using the output operator in Patient.cpp(would be encapsulated into the iterator)
    return 0;
}
