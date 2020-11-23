#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template < typename T >
void printVector(const vector<T>& array)
{
    int size = array.size();
    if(size == 0)
        cout << "No elements!";
    else
        for(int i=0; i<size; i++) cout << array[i] << "\t";
    cout << endl;
    return;
}

template < typename T >
void printQSortIterStep(const vector<T>& array, const vector<int>& highIndexVector, const vector<int>& lowIndexVector)
{
    cout << endl;
    cout << "Array:\t\t"; printVector(array);
	cout << "LowIndex:\t"; printVector(highIndexVector);
	cout << "HighIndex:\t"; printVector(lowIndexVector);
    return;
}

int popVector(vector<int>& array)
{
    int value = array[array.size()-1];
    array.pop_back();
    return value;
}

int error(const int n){
	cout << "Error!\t";
 	switch(n){
  		case 0: cout << "Empty file." << endl; break;
		case 1: cout << "Incorrect input arguments. Write file path or list for quick sort." << endl; break;
		case 2: cout << "File not found." << endl; break;
        case 3: cout << "Empty string." << endl; break;
 	};
	return 0;
}

template < typename T >
void qSortIter(vector<T>& array)
{
    const int size = array.size();

    int lowIndexCurr, highIndexCurr, i, j;
    vector<int> lowIndexVector, highIndexVector;
    T pivotElem;

    lowIndexVector.push_back(0);
    highIndexVector.push_back(size-1);

    while (lowIndexVector.size() > 0)
    {
        printQSortIterStep(array, lowIndexVector, highIndexVector);
        
        lowIndexCurr = popVector(lowIndexVector);
        highIndexCurr = popVector(highIndexVector);
        i = lowIndexCurr;
        j = highIndexCurr;
        pivotElem = array[(highIndexCurr + lowIndexCurr) / 2];
        cout << "Pivot VALUE:\t" << pivotElem << endl;
        do
        {
            while (array[i] < pivotElem)
                i++;
            while (array[j] > pivotElem)
                j--;
            if (i <= j)
            {
                if (array[i] > array[j]){
                    swap(array[i], array[j]);
                    cout << "Swap:\t\ti=" << i << "\tj=" << j << endl;
                    cout << "Array:\t\t";
                    printVector(array);
                }
                i++;
                if (j > 0)
                    j--;
            }
        } while (i <= j);
        if (i < highIndexCurr)
        {
            lowIndexVector.push_back(i);
            highIndexVector.push_back(highIndexCurr);
        }
        if (j > lowIndexCurr)
        {
            lowIndexVector.push_back(lowIndexCurr);
            highIndexVector.push_back(j);
        }
    }
    printQSortIterStep(array, lowIndexVector, highIndexVector);
    return;
}

void lineToIntVector(vector<int>& array, const string& line)
{
	istringstream lineStream(line);
	int num;
	while(lineStream >> num || !lineStream.eof())
    {
		if(lineStream.fail())
        {
			lineStream.clear();
			string temp;
			lineStream >> temp;
			continue;
		}
		array.push_back(num);
	}
	return;
}

int main(int argc, char *argv[]){
    string qSortString;
    vector<int> array;
    cout << "Write list for quick sort:" << endl;
    getline(cin, qSortString);
    lineToIntVector(array, qSortString);
    if (array.size() > 0)
		qSortIter(array);
    else
    	return error(3);
	return 0;
}
