#include <iostream>
#include "HashTable.h"
#include <ctime>
#include <random>

using namespace std;


int main() {
    std::mt19937 rndGen(static_cast<unsigned>(time(nullptr))); // Generator Mersenne twister
    int testCount = 512; // Start test data
    for (int i = 0; i < 7; ++i) {
        int operCounter = 0; // Operation counter
        HashTable avrHT(testCount);

        clock_t clocks;
        float time = 0;
        float avrTime;
        avrHT.clear();
        //
        for (int j = 0; j < testCount; ++j) {
            int value = static_cast<int>(rndGen()); // Generating a value
            clocks = clock();
            operCounter += avrHT.insertElement(value);

            clocks = clock() - clocks;
            time += static_cast<float>(clocks) / CLOCKS_PER_SEC;
            }

        if(i == 1){
            avrHT.printAll();
        }
        avrTime = time / (float )testCount;
        operCounter /= testCount;
        std::cout << "Elements - " << testCount << " Average case insertion - " <<fixed<< avrTime << " sec " <<"Operation Counts - "<< operCounter << std::endl;
        time = 0;



        avrHT.clear();
        long long int base = 1;
        while (base <= testCount){
            base <<= 1;
        }
        operCounter = 0;
        for (int j = 0; j < testCount; ++j) {
            long long int key = (j+1)*base;
            clocks = clock();
            operCounter += avrHT.insertElement(key);
            clocks = clock() - clocks;
            time += static_cast<float>(clocks) / CLOCKS_PER_SEC;
        }



        avrTime = time / (float )testCount;
        operCounter /= testCount;
        std::cout << "Elements - " << testCount << " Bad case insertion - " <<fixed<< avrTime << " sec" <<" Average operation counts - "<< operCounter << std::endl << std::endl;
        testCount *= 2;

    }
    return 0;
}