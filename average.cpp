#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {

    if (argc == 1) {
        cout << "Please input numbers to find average." << endl;
        return 0;
    }

    double sum = 0;

    for (int i = 1; i < argc; i++) {
        sum += atof(argv[i]);
    }

    double avg = sum / (argc - 1);

    cout << "---------------------------------" << endl;
    cout << "Average of " << argc - 1 << " numbers = "
         << setprecision(6) << avg << endl;
    cout << "---------------------------------" << endl;

    return 0;
}

