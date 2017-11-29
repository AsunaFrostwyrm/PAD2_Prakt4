/* 
 * File:   read_file_main.cpp
 * Author: max
 *
 * Created on 22. November 2017, 17:08
 */

#include <cstdlib>
#include <map>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iterator>
#include <utility>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

void error(string s) {
    throw runtime_error{s};
}

int main() {
    try {
        high_resolution_clock::time_point t0 = high_resolution_clock::now();
        ifstream readin{"beispiel.txt"};
        ofstream outfile;
        int counter{0};
        if (!readin) {
            error("Failed opening file!");
        }
        string readword{};
        map<string, int> words{};
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        while ((readin >> readword)&& !readin.eof()) {
            ++words[readword];
            counter++;
        }
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        vector<pair<int, string >> sortvec
        {
        };
        pair<int, string> pushpair{};
        using citer = map<string, int>::const_iterator;
        for (citer p{words.cbegin()}; p != words.cend(); ++p) {
            pushpair.first = p->second;
            pushpair.second = p->first;
            sortvec.push_back(pushpair);
        }
        high_resolution_clock::time_point t3 = high_resolution_clock::now();
        sort(sortvec.begin(), sortvec.end());
        high_resolution_clock::time_point t4 = high_resolution_clock::now();
        outfile.open("P4A4.txt");
        for (int i {0}; i < sortvec.size(); i++) {
            outfile << sortvec[i].second << "\t" << sortvec[i].first << "\n";
            cout << sortvec[i].second << "\t" << sortvec[i].first << endl;
        }
        outfile.close();
        cout << "Anzahl Wörter: " << counter << endl;
        high_resolution_clock::time_point t5 = high_resolution_clock::now();
        double Time_complete{duration_cast<milliseconds>(t5 - t0).count()};
        double Time_readin{duration_cast<milliseconds>(t2 - t1).count()};
        double Time_PushToVec{duration_cast<milliseconds>(t3 - t2).count()};
        double Time_Sort{duration_cast<milliseconds>(t4 - t3).count()};
        double Time_Output{duration_cast<milliseconds>(t5 - t4).count()};

        cout << "Zeit fuer read: " << Time_readin << " ms" << endl;
        cout << "Zeit fuer Push to Vector: " << Time_PushToVec << " ms" << endl;
        cout << "Zeit fuer Sort: " << Time_Sort << " ms" << endl;
        cout << "Zeit fuer Output: " << Time_Output << " ms" << endl;
        cout << "Zeit Komplett: " << Time_complete << " ms" << endl;
        return 0;
    } catch (exception &e) {
        cerr << e.what() << endl;
        return -2;
    } catch (...) {
        cerr << "\nUnknown Exception!\n" << endl;
        return -1;
    }
}
