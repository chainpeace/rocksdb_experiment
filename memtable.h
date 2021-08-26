#pragma once
#include "buffer.h"
class Memtable{

    public:
        virtual int store(Buffer*, int) = 0;
        int getMaxSize(){return max_size_;}
    
    protected:
        int max_size_;

};

