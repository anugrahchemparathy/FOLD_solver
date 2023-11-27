#include <iostream>
#include <fstream>
#include <vector>
#include <string>


#include "storage_objects.h"
#include "parse_FOLD.h"


// main function
int main() {
    std::cout << "hello world" << std::endl;
    parsed_fold skeleton = load_fold_file();
    std::cout << "skeleton failed = " << skeleton.failed << std::endl;
    std::cout << "skeleton num_edges = " << skeleton.num_edges << " & num_vertices = " << skeleton.num_vertices << std::endl; 



    return 0;
}
