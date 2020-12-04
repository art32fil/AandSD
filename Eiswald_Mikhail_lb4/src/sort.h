#ifndef SORT_H
#define SORT_H

#include <cassert>

#include <fstream>
#include <iostream>
#include <forward_list>
#include <utility>

#define llu long long unsigned

#define EMPTY_ARRAY 1
#define ALL_EQUAL 2

template <typename T>
int solomonSort(T* array, llu length, std::ofstream& out){
	if(!length) return EMPTY_ARRAY;
	T min = array[0];
	T max = array[0];
	for(llu i = 0; i < length; ++i){
		if(array[i] < min) min = array[i];
		if(array[i] > max) max = array[i];
	}
	std::cout << "Min: " << min << "\t";
	out << "Min: " << min << "\t";
	std::cout << "Max: " << max << "\n";
	out << "Max: " << max << "\n";

	double delta = (max - min)/(double)length;
	std::cout << "delta = " << delta << "\n";
	out << "delta = " << delta << "\n";

	if(delta < 0.00001) return ALL_EQUAL;

	std::forward_list<T>* cand = new std::forward_list<T>[length];

	llu index;
	for(llu i = 0; i < length; ++i){
		index = (array[i] - min)/delta;
		if(index == length) --index;
		std::cout<<"For "<<array[i]<<" estimated position is ("
			<<array[i]<<"-min)/delta = "<<index<<
			" of "<<length-1<<"\n";
		out<<"For "<<array[i]<<" estimated position is ("
                        <<array[i]<<"-min)/delta = "<<index<<
                        " of "<<length-1<<"\n";

		//if(cand[index].empty()) cand[index].push_front(array[i]);
		for(auto iter = cand[index].before_begin(); iter != cand[index].end(); ++iter){
			auto tmp = iter;
			++tmp;
			if(tmp == cand[index].end() || *(tmp) >= array[i]){
				cand[index].insert_after(iter, array[i]);
				break;
			}
			std::cout << array[i] << " > " << *(tmp) << "\n";
			out << array[i] << " > " << *(tmp) << "\n";
		}
	}

	llu i = 0;
	for(llu index = 0; index < length; ++index){
		for(auto iter = cand[index].begin(); iter != cand[index].end(); ++iter){
			array[i++] = *iter;
		}
	}

	delete[] cand;
	return 0;
}

#endif
