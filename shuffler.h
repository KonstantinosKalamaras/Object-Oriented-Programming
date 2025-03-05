#include<iostream>

using namespace std;

template <class X> void shuffle(X** myArray, int myArraySize){
    // TODO: Implement here the shuffle algorithm
    int i , j;
    X* tmp;
    for(i = 0; i < myArraySize; i++){
        j = rand() % (i + 1);
        tmp = myArray[i];
        myArray[i] = myArray[j];
        myArray[j] = tmp;
    }
}
