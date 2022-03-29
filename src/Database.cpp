#include "Database.h"
#include "util.file.h"

#include <algorithm>
#include <iostream>
using namespace std;

Database::Database(const string& db_filename)
    : _db_filename(db_filename)
    , _cities(util::file::read_data(db_filename))
{ }

Database::~Database() // Destructor must never let exception escape.
{
    if (_db_filename.empty())
        return;

    try {
        util::file::write_data(_cities, _db_filename);
    } catch (const exception& e) {
        cerr << e.what() << "\n";
    }
}

void Database::open(const std::string& target_filename)
{
    if (!_db_filename.empty()) {
        util::file::write_data(_cities, _db_filename);
    } else {
        _cities = util::file::read_data(target_filename);
        _db_filename = target_filename;
    }
}

// TODO
