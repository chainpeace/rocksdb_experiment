
#include <iostream>

#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#include "cxxopts.hpp"
#include "test.h"
#include "buffer.h"
#include "memtable.h"
#include "random_memtable.h"
#include "mytime.h"

// TO DO : mytime.h -> c++ style


#define MB (1024*1024)

unsigned long long my_write_time = 0, my_write_count = 0;
unsigned long long sync_time = 0, sync_count = 0;

int main(int argc, char * argv[]){
    
    int memtable_size = 64;
    int buffer_size = 1;
    int ds = 0;

    struct timespec local_time[2];

    cxxopts::Options options("Memtable write experiment",
            "Program for evalutaing memtable to disk perfomance");
    options.add_options()
        ("m, memtable_size", "memtable size in MB", 
         cxxopts::value<int>()->default_value("64"))
        ("b, buffer_size", "buffer size in MB",
         cxxopts::value<int>()->default_value("1"))
        ("d, data_struct", "data structure for memtable"
         "\n(0: random)\n", 
         cxxopts::value<int>()->default_value("0"))
        ;
    try{

        auto result = options.parse(argc, argv);
        memtable_size = result["memtable_size"].as<int>() * MB;
        buffer_size = result["buffer_size"].as<int>() * MB;
        ds = result["data_struct"].as<int>();
        
    } catch(const cxxopts::OptionException& e){
        std::cout<<options.help()<<std::endl;
        return 0;
    }
        //cout<<"main test : "<<memtable_size<<endl;
    Memtable *mt;
    switch(ds){
        case 0:
            mt = new RandomMemtable(memtable_size); 
            break;
        default:
            exit(0);
    }

    Buffer *buf = new Buffer(buffer_size);
    //mt->store(buf, buffer_size);
    //std::cout<<buf->getCurrentSize()<<std::endl;

    int fd = open("/mnt/sdb/test.tmp", O_CREAT | O_RDWR | O_TRUNC);
    if(fd<0){
        std::cout<<"open error"<<std::endl;
        exit(-1);
    }
    
    std::cout<<"file open"<<std::endl;
    int done = 1; 
    
    for(int i=0;i<memtable_size;i+=buffer_size){
        mt->store(buf, buffer_size);
        
        clock_gettime(CLOCK_MONOTONIC, &local_time[0]);
        
        buf->writeToFile(fd);
        
        clock_gettime(CLOCK_MONOTONIC, &local_time[1]);
        calclock(local_time, &my_write_time, &my_write_count);
    }

    close(fd);

    clock_gettime(CLOCK_MONOTONIC, &local_time[0]);
    
    fdatasync(fd);
    
    clock_gettime(CLOCK_MONOTONIC, &local_time[1]);
    calclock(local_time, &sync_time, &sync_count);

    printf("[%s::%s::%d] my_write_time { %llu } my_write_count { %llu } \n",
            __FILE__, __func__, __LINE__, my_write_time, my_write_count);
    printf("[%s::%s::%d] sync_time { %llu } sync_count { %llu } \n",
            __FILE__, __func__, __LINE__, sync_time, sync_count);

    return 0;
  
}
