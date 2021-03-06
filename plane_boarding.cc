#include "deque.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

Deque<int> dq;
int numFirstClass;
std::vector<int> init;

int main(int argc, char *argv[]) {
        if (argc<=2){
            std::cerr<<"'Usage: ./plane_boarding <input_file> <fclass_cap>'";
            exit(1);
        }
        else if (atoi(argv[2])<=0){
            std::cerr<<"'Error: invalid first class capacity'";
            exit(1);
        }
        std::ifstream f;
        f.open(argv[1]);
        if (!f.is_open()){
            std::cerr<<"'Error: cannot open file "<<argv[1]<<"'";
            exit(1);
        }
        int num;
        while (f >> num) {
            init.push_back(num);
        }

        numFirstClass = atoi(argv[2]);
        for (unsigned int i = 0; i < init.size(); i++) {
            if (init[i] <= numFirstClass) {
                dq.PushFront(init[i]);
            } else {
                dq.PushBack(init[i]);
            }
        }
        for (unsigned int n = 0; n < dq.Size(); n++) {
            printf("%d ", dq[n]);
        }
        return 1;
}
