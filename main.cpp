#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <random>
#include <unordered_map>

using namespace std;

class Player {


public:

    string name;
    double ppg;
    double steals;
    double blocks;
    double assists;
    double rebounds;

public:

    Player() {

        name = "";
        ppg = 0;
        steals = 0;
        blocks = 0;
        assists = 0;
        rebounds = 0;
    }

    Player(string name, double ppg, double steals, double blocks, double assists, double rebounds) {

        this->name = name;
        this->ppg = ppg;
        this->steals = steals;
        this->blocks = blocks;
        this->assists = assists;
        this->rebounds = rebounds;
    }

    string randomName() {

        return name;
    }

    void generateData() {

        name = randomName();
    }

    void printStats() {

        cout << name << ", " << fixed << setprecision(2) << ppg << ", " << steals << ", " << blocks << ", " << assists << ", " << rebounds << endl;
    }

    vector<double> getStats() {

        vector<double> stats;

        stats.push_back(ppg);
        stats.push_back(steals);
        stats.push_back(blocks);
        stats.push_back(assists);
        stats.push_back(rebounds);
        return stats;
    }

};

double getRandom(double min, double max) {

    return (max - min) * ((double)rand() / (double)RAND_MAX) + min;
}

void generateStats(vector<Player>& players, string name) {

    double ppg = getRandom(0.0, 50.4);
    double steals = getRandom(0.0, 3.5);
    double blocks = getRandom(0.0, 4.3);
    double assists = getRandom(0.0, 11.2);
    double rebounds = getRandom(0.0, 22.9);

    Player temp(name, ppg, steals, blocks, assists, rebounds);
    players.push_back(temp);
}

void searchDatabase(string findName, unordered_map<string, vector<double>>& player_stats)
{

    if (player_stats.find(findName) == player_stats.end()) {
        cout << "Player not found in Database, try another search" << endl;
    }
    else {
        cout << findName;
        for (int i = 0; i < player_stats[findName].size(); i++) {
            cout << ", " << fixed << setprecision(2) << player_stats[findName].at(i);
        }
    }
}

void readFile(vector<string>& names, string filename) {

    ifstream file;
    string currentRow;
    int counter = 0;

    file.open(filename);

    if (file.is_open()) {

        //Removes Top Line (Header) from File
        //string currentRow;
        //getline(file, currentRow);

        while (getline(file, currentRow)) {

            //string playername;

            istringstream ss(currentRow);


            getline(ss, currentRow, '\n');
            counter++;
            names.push_back(currentRow);
        }
    }
    file.close();
}

int main()
{
    vector<string> names; // For reading Names from file
    vector<Player> players; // For Sorting Algorithms
    unordered_map<string, vector<double>> player_stats; // For instant Access during Search
    vector<double> stats;

    string selection;

    readFile(names, "randomNames.txt");

    for (int i = 0; i < names.size(); i++) {

        generateStats(players, names[i]);
        player_stats[names[i]] = players[i].getStats();
    }


    //* ===== Main User Interface ===== *//

    cout << "|| Welcome to the Best Basketball Player [Men & Women] Database Software!!! ||" << endl;
    cout << "|| ***Copyright Pending*** The Reference Referees LLC, Best Basketball Player Software ||" << endl;
    cout << endl << "Here are your database search options, please select an option to proceed" << endl;
    cout << "- [A] Print All Player Stats" << endl;
    cout << "- [B] Search for a player by name" << endl;
    cout << "- [C] Sort and Print Top 100 players by Position" << endl;
    cout << "- [Q] Quit Program" << endl;
    getline(cin, selection);

    while (selection != "Q") {

        string option;

        if (selection != "A" && selection != "B" && selection != "C") {
            cout << "Sorry can't process that input, please try again with a proper selection" << endl;
        }
        else if (selection == "A") {
            for (int i = 0; i < names.size(); i++) {
                players[i].printStats();
            }
        }
        else if (selection == "B") {

            string input;
            cout << "Please enter a player name to search..." << endl;

            getline(cin, input);
            searchDatabase(input, player_stats);
        }
        else if (selection == "C") {

        }

        getline(cin, option);
        selection = option;
    }


    return 0;