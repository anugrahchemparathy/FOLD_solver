#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "storage_objects.h"

using json = nlohmann::json;
using namespace std;


// main function
int main() {
    std::cout << "hello world" << std::endl;

    point_t mypoint = {1,2};
    std::cout << point_2_string(mypoint) << endl;

    return 0;
}
