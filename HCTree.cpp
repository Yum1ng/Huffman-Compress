#include "HCTree.hpp"
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

HCTree::~HCTree(){
    deleteAll(root);
}

void HCTree::build(const vector<int>& freqs){
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pque;
    for (int i = 0; i < freqs.size(); i++){
        if (freqs[i] != 0){
            HCNode* newNode = new HCNode(freqs[i],i,0,0,0);
            pque.push(newNode);
            leaves[i] = newNode;
        }
    }

    while(!pque.empty()){
        //if there are two more elements, pick the two highest priority
        if(pque.size() >= 2){
            HCNode* newPop1 = pque.top();
            pque.pop();
            HCNode* newPop2 = pque.top();
            pque.pop();

            int newcount = newPop1->count + newPop2->count;
            HCNode* mergeNode = new HCNode(newcount, 0,newPop1,newPop2,0);
            newPop1 -> p = mergeNode;
            newPop2 -> p = mergeNode;

            pque.push(mergeNode);
        }

        else{
            this->root = pque.top();
            pque.pop();
            return;
        }
    }
}

void HCTree::encode (byte symbol, BitOutputStream& out)const{
    if(root==0){
        cout<<"Root is null"<<endl;
        return;
    }
    int s = symbol;
    HCNode* encodebyte = this->leaves[s];
    stack<int> code;

    if(encodebyte == root){
        out.writeBit(1);
        return;
    }

    while(encodebyte->p != 0){
        if(encodebyte -> p -> c0 == encodebyte){
            code.push(1);
        }
        else if(encodebyte -> p -> c1 == encodebyte){
            code.push(0);
        }
        encodebyte = encodebyte -> p;
    }

    //flip the string to get the final encode
    for (int i = code.size(); i > 0; i--){
        out.writeBit(code.top());
        code.pop();
    }
}

int HCTree::decode (BitInputStream& inTree)const{
    if(root!=0&&root->c0==0)
        return (int)root->symbol;
    HCNode* curr = root;
    while(curr -> c0 != 0 && curr -> c1 != 0){
        int readbit = inTree.readBit();
        if (readbit == 0) {
            curr = curr -> c1;
        }
        else {
            curr = curr -> c0;
        }
    }
    return curr -> symbol;
}

void HCTree::preorder(HCNode* curr, BitOutputStream& out)const{
    if(curr==0) return;
    if(curr->c0!=0){
        out.writeBit(0);
    }
    else if(curr->c0==0){
        out.writeBit(1);
        out.flush();
        out.writeByte(curr->symbol);
        return;
    }
    preorder(curr->c0,out);
    preorder(curr->c1,out);

    return;
}

void HCTree::rebuild(int sum, BitInputStream& input){
    HCNode* curr = new HCNode(0,0,0,0,0);
    root = curr;
    byte newbyte;
    int newbit;
    int time=0;
    HCNode* p =0;
    HCNode* cc0 = 0;
    HCNode* cc1 = 0;
    while(time<sum){
          newbit = input.readBit();
          if(newbit==1){
                newbyte = input.readByte();
	        input.fill();
          curr->symbol=newbyte;
	        time++;
              if(time==sum) break;

              if(curr->p!=0){

                  if(curr->p->c0==curr){
                      HCNode* newNode = new HCNode(0,0,0,0,curr->p);
                      curr->p->c1=newNode;
                      curr=curr->p->c1;
                  }
                  else{

                      curr=curr->p;
                      while(curr->p->c1!=0){
                          curr=curr->p;
                      }
		                  curr = curr ->p;
                      HCNode* newNode = new HCNode(0,0,0,0,curr);
                      curr->c1=newNode;
                      curr=curr->c1;
                    }
	           }
            else return;
	      }
        else if(newbit==0){
            HCNode* newNode = new HCNode(0,0,0,0,curr);
            curr->c0=newNode;
            curr=curr->c0;
        }
    }
}
