#include "HCTree.hpp"
#include "HCNode.hpp"
#include <vector>
#include "BitOutputStream.hpp"
#include "BitInputStream.hpp"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc,char** argv){
    ifstream inputfile;
    ofstream outputfile;
    vector<int> freq(256,0);
    int read;
    HCTree Huff;

    if(argc != 3){
        cout << "this program needs two input and output files" <<endl;
        return 0;
    }
    //now open both files
    inputfile.open(argv[1],ios::binary);
    BitInputStream input(inputfile);
    if(!inputfile.is_open()){
        inputfile.clear();
        inputfile.close();
        return 0;
    }

    //check the good flag. If false, throw
    if(!inputfile.good()){
        cout << "bad file!" << endl;
        return 0;
    }

    //TODO
    inputfile.seekg(0, ios_base::end);
    if(inputfile.tellg()==0){
        cout<< "Empty Input File!"<<endl;
        return 0;
    }
    inputfile.seekg(0, ios_base::beg);

    int index;
    int sum;
    int numelement=0;

    while(inputfile.good()){
        if(inputfile.eof())
          break;

        //the data to save
        if((index = input.readByte())==EOF)
          break;
        //the freqency of that char should +1
        freq[index]++;
        sum++;
    }
    for(int i=0; i<freq.size();i++){
        if(freq[i]!=0)
            numelement++;
    }
    //Build the tree!!!
    Huff.build(freq);

    outputfile.open(argv[2],ios::binary);
    BitOutputStream output(outputfile);
    if(!outputfile.is_open()){
        outputfile.clear();
        outputfile.close();
        return 0;
    }

    output.writeInt(sum);
    output.writeInt(numelement);

    Huff.preorder(Huff.root,output);

    inputfile.clear();
    inputfile.seekg(0,ios_base::beg);


    while(inputfile.good()){
      if((read = input.readByte()) == EOF)
          break;
      Huff.encode(read, output);
    }


    if(numelement!=1)
        output.flush();
    
    inputfile.clear();
    inputfile.close();
    outputfile.clear();
    outputfile.close();

    return 0;
}
