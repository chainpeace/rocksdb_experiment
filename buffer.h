#pragma once

#include <string>

class Buffer{
    public:
        Buffer();
        Buffer(int max_size);
        int writeToFile(int);
        int store();
        int getMaxSize(){return max_size_;}
        int getCurrentSize(){return contents_->size();}
        int getOffset(){return offset_;}
        std::string* getContents(){return contents_;}
        void clean();
        int copyToBuffer(std::string*);

    private:
        int max_size_;          // in MB
        int offset_;
        std::string* contents_;
};
