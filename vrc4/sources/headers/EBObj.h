#pragma once
// This is the header file for the Easy Bit Object -> EBObj
#include <string>

class EBObj
{
				public:
								EBObj(unsigned char* inputArray, unsigned int arraySize); //Constructor
								EBObj(EBObj* oldEBObj); //Copy Constructor
								~EBObj(); //Destructor
								EBObj xorOp(EBObj* opIn) const;
								EBObj andOp(EBObj* opIn) const;
								EBObj transformOp() const;
								unsigned int size() const;
								const unsigned char* getByteArray() const;
								void bits2String() const;
								EBObj swapBytes(unsigned int a, unsigned int b) const;
								unsigned char getByte(unsigned int target) const;
				private:
								unsigned char* padArray(const unsigned char* inputArray, unsigned int inputSize,
																unsigned int targetSize) const;
								const unsigned char* bitString; 
								const unsigned int objectSize;
};
