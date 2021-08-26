#pragma once

#include <string>
#include "memtable.h"
#include "buffer.h"

class RandomMemtable : public Memtable{

    public :
        RandomMemtable();
        RandomMemtable(int);
        int store(Buffer*, int) override;
        std::string* getContents(){return contents_;}   
        int getOffset(){return offset_;}
    private :
        char pickRandomChar();
        void fillMemtable();
        std::string* contents_;
        int offset_;
};
