#include "util.file.h"
#include "cmpt_error.h"

#include <fstream>
#include <sstream>
using namespace std;

vector<City> util::file::read_data(const string& filename)
{
    ifstream file(filename);
    if (!file) {
        cmpt::error("Error loading data from file " + filename);
    }

    vector<City> data;

    // TODO

    return data;
}

void util::file::write_data(const vector<City>& data, const string& filename)
{
    ofstream file(filename);
    if (!file) {
        cmpt::error("Error writing data to file " + filename);
    }

    // TODO

    // Remove this stub.
    string foo = data.front().name;

}
