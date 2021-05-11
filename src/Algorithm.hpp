#pragma once

class Algorithm {
    private:
        int size;
        unsigned short **array;
    public:
        explicit Algorithm(int size);
        ~Algorithm();
        void Set(int index1, int index2, unsigned short value);
        unsigned short Get(int index1, int index2);
        //void PrintLength();
 
};