#include <cstdlib>
#include <string>
#include <iostream>

#include "random_memtable.h"
#include "buffer.h"

RandomMemtable::RandomMemtable(){
    RandomMemtable(64*1024*1024);
}
RandomMemtable::RandomMemtable(int max_size)
{
    max_size_ = max_size;
    offset_ = 0;
    contents_ = new std::string();
    fillMemtable();
}

int RandomMemtable::store(Buffer* buf, int len){
    if(offset_>=max_size_){
        return -1;
    }
    if(buf->getOffset()!=0){
        buf->clean();
    }
    len = std::min(len, buf->getMaxSize());
    buf->getContents()->assign(*contents_, offset_, len);
    
    offset_ += buf->getCurrentSize();
    return len;
}
//pick character in the range of 48~122(0~z)
char RandomMemtable::pickRandomChar(){
    return static_cast<char>((rand()%75)+48);
}
void RandomMemtable::fillMemtable(){
    for(int i=0;i<max_size_;i++){
        contents_->push_back(pickRandomChar());
    }
}
