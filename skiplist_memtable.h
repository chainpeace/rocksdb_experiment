#include "memtable.h"

class SkiplistMemtable : public Memtable{
    
    public:
        int store() override;

};
