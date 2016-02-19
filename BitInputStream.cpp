#include "BitInputStream.hpp"
#include <iostream>
using namespace std;

int BitInputStream::readBit(){
		if(buf_index == 8){
			buf = in.get();
			buf_index=0;
		}
		char c = buf >> (buf_index) & 1;
		buf_index++;
		return (int) c;

}

int BitInputStream::readByte(){
		return in.get();
}

int BitInputStream::readInt(){
		int temp;
		in.read((char*)&temp, sizeof(int));
		return temp;
}
void BitInputStream::fill(){
		buf = in.get();
		buf_index = 0;
}
