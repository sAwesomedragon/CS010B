#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Distance.cpp"

using namespace std;

void readData(const string &, vector<double> &, vector<double> &);
double interpolation(double, const vector<double> &, const vector<double> &);
bool isOrdered(const vector<double> &);
void reorder(vector<double> &, vector<double> &);

int main (int argc, char* argv[]){
    ostringstream outSS;
    string fileName;
    double userAngle;
    vector<double> angle;
    vector<double> lift;

    fileName = argv[1];

    readData(fileName, angle, lift);
    isOrdered(angle);

    reorder(angle, lift);
    //     for (unsigned int i = 0; i < angle.size(); i++) {
    //     cout << angle.at(i) << " " << lift.at(i) << endl; 
    // }

    cin >> userAngle;
    cout << interpolation(userAngle, angle, lift);
    
    cout << "yuh" << endl;
    return 0;
}


void readData(const string &fileName, vector<double> &angle, vector<double> &lift) {
    ifstream inFS;
    double inputFile;

   inFS.open(fileName);
   if (!inFS.is_open()) {
      cout << "Error opening " << fileName << endl;
      exit(1);
   }

    while (inFS >> inputFile) {
        angle.push_back(inputFile);
        inFS >> inputFile;
        lift.push_back(inputFile);
    }
    inFS.close();
}

double interpolation(double userAngle, const vector<double> &angle, const vector<double> &lift){
    //user input is 15.3
    unsigned int i = 0;
    double desiredlift;
    double parta;
    double partb;
    double partc;

    for (unsigned int i = 0; i < angle.size(); i++){
        if (userAngle == angle.at(i)) {
            return lift.at(i);
        } 
    }

        while(userAngle > angle.at(i) && i < angle.size() - 1){
        i++;
        }

        parta = lift.at(i - 1);

        partb = (userAngle - angle.at(i - 1)) / (angle.at(i) - angle.at(i - 1)); 

        partc = lift.at(i) - lift.at(i - 1);

        desiredlift = parta + (partb * partc);
    //f(b) = f(a) + ((b - a)/(c - a))(f(c) - f(a))
    //f(a) = lift of a
    //f(b) = lift of b
    //f(c) = lift of c
    //a = angle of a
    //b = angle of b
    //c = angle of c
    return desiredlift;
}

bool isOrdered(const vector<double> &angle) { // pass in the angles and see if they are in ASCENDING order
 for (unsigned int i = 0; i < angle.size() - 1; i++) {
  if (angle.at(i) <= angle.at(i + 1)) {
   //continue the loop  
  }
  else {
   //exit the loop and say that its false
   return false;
  }
 }
 return true;
}

void reorder(vector<double> &angle, vector<double> &lift) {
    unsigned int min_holder;
    double swap_holder;

    for (unsigned int i = 0; i < angle.size() - 1; i++) {
        min_holder = i;
        for (unsigned int n = i+1; n < angle.size(); n++) {
            if (angle.at(n) < angle.at(i) && angle.at(n) < angle.at(min_holder)) {
                min_holder = n;
            }
        }

        if(min_holder != i) {
            swap_holder = angle.at(i);
            angle.at(i) = angle.at(min_holder);
            angle.at(min_holder) = swap_holder;
            swap_holder = lift.at(i);
            lift.at(i) = lift.at(min_holder);
            lift.at(min_holder) = swap_holder;
            }
    }
}
