#pragma once

class Algorithm {
    private:
        int size;
        int **array;
    public:
        explicit Algorithm(int size);
        ~Algorithm();
        void Set(int index1, int index2, int value);
        int Get(int index1, int index2);
        void PrintLength();
 
};