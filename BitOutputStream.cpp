#include "BitOutputStream.hpp"
#include <iostream>
using namespace std;

void BitOutputStream::writeBit(int bit){
	if(out.good()){
		if(buf_index == 8){
			flush();
		}
		if(bit==1){
			buf=buf|(bit)<<buf_index;
		}
		else
			buf=buf& ~(1<<buf_index);

		buf_index++;
	}
	else{
		cout<<"Output File is not good!"<<endl;
		return;
	}
}

void BitOutputStream::writeByte(int i){
	if(out.good()){
		out.put(i);
	}
	else{
		cout<<"Output File is not good!"<<endl;
		return;
	}
}

void BitOutputStream::writeInt(int i){
	if(out.good()){
		out.write((char*)&i, sizeof(int));
	}
	else{
		cout<<"Output File is not good!"<<endl;
		return;
	}

}

void BitOutputStream::flush(){
	if(!out.good()){
		cout<<"Output File is not good!"<<endl;
		return;
	}
	out.put(buf);
	buf=buf_index=0;
}
