#include <iostream>
#include "cxxopts.hpp"
#include "test.h"

using namespace std;

int main(int argc, char * argv[]){
    cxxopts::Options options("Memtable write experiment",
            "Program for evalutaing memtable to disk perfomance");
    options.add_options()
        ("m, memtable_size", "memtable size", cxxopts::value<int>())
        ;
    auto result = options.parse(argc, argv);

    cout<<"main test : "<<argc<<endl;
    printHeader();
    return 0;
  
}
