#include "HCTree.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char** argv){
	ifstream ifile;
	ofstream ofile;
	vector<int> freq(256,0);
	byte readByte;

	if(argc != 3){
		cout<< "This program need one input file and one out file" << endl;
		return 0;
	}
	//now open both files
	ifile.open(argv[1],ios::binary);
	if(!ifile.is_open()){
			ifile.clear();
			ifile.close();
			return 0;
	}
	BitInputStream input(ifile);

	ofile.open(argv[2],ios::binary);
	if(!ofile.is_open()){
			ofile.clear();
			ofile.close();
			return 0;
	}

	BitOutputStream output(ofile);

	if(!ifile.good()){
		cout<< "Bad file(s)!"<<endl;
		return 0;
	}

	ifile.seekg(0, ios_base::end);
	if(ifile.tellg()==0){
		cout<< "Empty Input File!"<<endl;
		return 0;
	}
	ifile.seekg(0, ios_base::beg);

	int i=0;
	int sum=0;
	int total = input.readInt();
	sum=input.readInt();
	HCTree HCT;
	HCT.rebuild(sum,input);
  int j;
	for(j=0;j<total;j++){
		int temp = HCT.decode(input);
		output.writeByte(temp);
	}

	ifile.close();
	ofile.close();
}
