#include <string>
#include <fcntl.h>
#include <unistd.h>

#include "buffer.h"


Buffer::Buffer(){
    Buffer(1024*1024);
}

Buffer::Buffer(int max_size)
    :max_size_(max_size){

    offset_ = 0;
    contents_ = new std::string();

}
int Buffer::writeToFile(int fd){
    const char* buf = contents_->data();
    size_t left = Buffer::getCurrentSize();
    int done = 0;
    while(left>0){
        int written = write(fd, buf, left);
        left -= written;
        buf += written;
        done += written;
    }
    return done;

}
int Buffer::store(){
    return 0;
}
void Buffer::clean(){
    offset_ = 0;
    contents_ = new std::string();
}
