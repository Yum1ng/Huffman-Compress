#include "HCNode.hpp"
using namespace std;

bool HCNode::operator < (const HCNode& other){
    if (count == other.count)
    	return symbol < other.symbol;
    else
    	return count > other.count;
}

bool comp(HCNode* one, HCNode* other){
    return *one < *other;
}
