#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <random>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);

void find_goat(list<Goat> trip);
void clear_goats(list<Goat> &trip);
void shuffle_goats(list<Goat> &trip);
void replace_goat(list<Goat> &trip);
void reverse_goats(list<Goat> &trip);

int main_menu();

int main() {
    srand(time(0));
    bool again;
    cout << "test1" << endl;
    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                cout << "Finding goat.\n";
                find_goat(trip);
                break;
            case 5:
                cout << "Clearing goat data.\n";
                clear_goats(trip);
                break;
            case 6:
                cout << "Shuffling goat data.\n";
                shuffle_goats(trip);
                break;
            case 7:
                cout << "Replacing a goat.\n";
                replace_goat(trip);
                break;
            case 8:
                cout << "Reversing goat data.\n";
                reverse_goats(trip);
                break;
            case 9:
                cout << ".\n";
                clear_goats(trip);
                break;
            case 10:
                cout << ".\n";
                clear_goats(trip);
                break;
            case 11:
                cout << ".\n";
                clear_goats(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    
    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Find goat\n";
    cout << "[5] Clear goats\n";
    cout << "[6] Shuffle goats\n";
    cout << "[7] Replace goat\n";
    cout << "[8] Reverse goats\n";
    cout << "[9] \n";
    cout << "[10] \n";
    cout << "[11] \n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

//Checks if a goat exists in the list
void find_goat(list<Goat> trip) {
    string name;
    cout << "Name of goat to find: " << endl;
    cin >> name;
    Goat tempGoat(name);

    auto it = find(trip.begin(), trip.end(), tempGoat);
    if (it != trip.end()) {
        cout << name << " found!" << endl;
    } else {
        cout << name << " not found." << endl;
    }
}

//Clears all goats
void clear_goats(list<Goat> &trip) {
    trip.clear();
    cout << "Goats cleared" << endl;
}

//Shuffles the order of the goats
void shuffle_goats(list<Goat> &trip) {
    vector<Goat> trip2(trip.begin(), trip.end());
    shuffle(trip2.begin(), trip2.end(), default_random_engine());
    copy(trip2.begin(), trip2.end(), trip.begin());
    cout << "Goats shuffled" << endl;
}

//Replaces a specific goat
void replace_goat(list<Goat> &trip) {
    string name, color;
    int age, choice;

    choice = select_goat(trip);
    cout << "Replacement data:" << endl;
    cout << "Name: ";
    cin >> name;
    cout << "Age: ";
    cin >> age;
    while (age < 0) {
        cout << "Correct age please" << endl;
        cin >> age;
    }
    cout << "Color:";
    cin >> color;
    
    Goat tempGoat(name, age, color);

    auto it = trip.begin();
    advance(it, choice-1);
    trip.erase(it);
    trip.insert(it, tempGoat);
}

//Reverses goat list
void reverse_goats(list<Goat> &trip) {
    reverse(trip.begin(), trip.end());
}