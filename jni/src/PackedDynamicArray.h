/*
	A good collection for when you need indices not to change when modifying the collection.
	Dynamically allocates when out of space.
	Values keep their indices after a remove.
	Values that are removed are quickly replaced before moved to the back of the collection.
	Trevor Berninger - Oct 18, 2015
*/

#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <sstream>

#define uint unsigned int
#define SSTR(x) dynamic_cast<std::ostringstream&>((std::ostringstream() << std::dec << x)).str()

#ifndef LOG
	#define LOG(message) std::cout << message;
#endif

template<typename T>
class PackedDynamicArray {
private:
	std::queue<uint> emptySlots;
	uint length, capacity;
	T* array;
public:
	uint Size() { return length; }
	uint Capacity() { return capacity; }
	T& operator[](uint i) { return array[i]; }
	// for(:) support:
	T* begin() const { return array; }
	T* end() const { return &(array[length]); }

	PackedDynamicArray(PackedDynamicArray<T> const& other) {
		SDL_Log("Oh my");
		array = new T[other.capacity];
		for(T i : other)
			Add(i);
		length = other.length;
		capacity = other.capacity;
		SDL_Log("I've been copied");
	}

	PackedDynamicArray(uint initCapacity = 30) { 
		SDL_Log("PDA constructing");
		array = new T[initCapacity];
		length = 0;
		capacity = initCapacity;
		SDL_Log("PDA constructed");
	}

	~PackedDynamicArray() { if(array != nullptr) delete [] array; }

	uint Add(T value) {
		SDL_Log("Adding value to PDA");
		if(!emptySlots.empty()) {
			uint pos = emptySlots.front();
			array[pos] = value;
			emptySlots.pop();
			return pos;
		}
		else {
			uint pos = length;
			if(length++ == capacity) {
				ReallocateWithSize(capacity + 20);
			}
			array[pos] = value;
			return pos;
		}
	}

	bool RemoveValue(T value) {
		T* i = std::find(array, array + capacity, value);
		if(i != array + capacity) {
			RemoveAt(i - array);
			return true;
		}
		return false;
	}

	void RemoveAt(uint index) {
		if(index > capacity) {
			LOG("PDA: Attempted remove at " + SSTR(index) + " with capacity of " + SSTR(capacity));
			return;
		}
		array[index] = T();
		emptySlots.push(index);
	}

	void Display() {
		for(uint i = 0; i < length; i++) {
			std::cout << i << '\t' << array[i] << '\n';
		}
	}

private:
	void ReallocateWithSize(uint size) {
		T* a = new T[size];
		std::copy(array, array + capacity, a);
		capacity = size;
		delete [] array;
		array = a;
	}
};