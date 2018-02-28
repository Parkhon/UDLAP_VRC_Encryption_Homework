//This is the implementation of the Easy Bit Object:
#include "EBObj.h"
#include <string>
#include <iostream>
#include <climits>
#include <algorithm>

//This is the constructor of the Easy Bit Object
EBObj::EBObj(unsigned char* inputArray, unsigned int arraySize) : 
				bitString(inputArray),
				objectSize(arraySize)

{}

//Test before using or suffer the consequences of horrendous bugs!
/*EBObj::EBObj(EBObj* oldEBObj) :
				objectSize(oldEBObj->size())
{
				unsigned char* byteArray;
				byteArray = new unsigned char[oldEBObj->size()];
				for(unsigned int i = 0; i < oldEBObj->size(); i++)
				{
								byteArray[i] = oldEBObj->getByte(i);
				}
				bitString = byteArray;
}*/

//This is the destructor of the Easy Bit Object.
EBObj::~EBObj()
{
				//Deleting the dynamically allocated bitString constant.
				delete bitString;
}

EBObj EBObj::xorOp(EBObj* opIn) const
{
				//This is the XOR operation, it returns a new EBObj with the result of said operation.
				const unsigned char* largerArray;
				unsigned char* paddedSmallerArray;
				unsigned int newEBObjByteSize;
				//If operand is larger than operator, self larger than input
				if(objectSize > opIn->size())
				{
								newEBObjByteSize = objectSize;
								paddedSmallerArray = padArray(opIn->getByteArray(), opIn->size(), newEBObjByteSize);
								largerArray = bitString;
				}
				else //Else the operator is larger than the operand, input larger than self
				{
								newEBObjByteSize = opIn->size();
								paddedSmallerArray = padArray(bitString, objectSize, opIn->size());
								largerArray = opIn->getByteArray();
				}
				const unsigned int sizeOfResult = newEBObjByteSize;
				unsigned char* resultArray;
				resultArray = new unsigned char[sizeOfResult]; //Each EBObj must destroy their own arrays
			
				//Conducting the XOR proper, byte by byte
				for(unsigned int i = 0; i < sizeOfResult; i++)
				{
								resultArray[i] = largerArray[i] ^ paddedSmallerArray[i];
				}
				//After the XOR is applied, the dynamically allocated padded array is no longer needed
				//and should be deleted.
				delete paddedSmallerArray;

				//Creating the output EBObj.
				//BUG was here read random bits, used dynamic memory for resultArray, needs destructor!
				EBObj newEBObj(resultArray, sizeOfResult);
				return newEBObj;
}

EBObj EBObj::andOp(EBObj* opIn) const
{
				//This is the and logical operator, it returns a new EBObj with the result of the and operation.
				const unsigned char* largerArray;
				unsigned char* paddedSmallerArray;
          unsigned int newEBObjByteSize;
          //If operand is larger than operator, self larger than input
         if(objectSize > opIn->size())
          {
                  newEBObjByteSize = objectSize;
                 paddedSmallerArray = padArray(opIn->getByteArray(), opIn->size(), newEBObjByteSize);
                  largerArray = bitString;
          }
          else //Else the operator is larger than the operand, input larger than self
          {
                 newEBObjByteSize = opIn->size();
                  paddedSmallerArray = padArray(bitString, objectSize, opIn->size());
                  largerArray = opIn->getByteArray();
          }
          const unsigned int sizeOfResult = newEBObjByteSize;
          unsigned char* resultArray;
          resultArray = new unsigned char[sizeOfResult]; //Each EBObj must destroy their own arrays
  
          //Conducting the AND proper, byte by byte
          for(unsigned int i = 0; i < sizeOfResult; i++)
          { 
                  resultArray[i] = largerArray[i] & paddedSmallerArray[i];
          } 
          //After the AND is applied, the dynamically allocated padded array is no longer needed
          //and should be deleted.i
					delete paddedSmallerArray;
 
         //Creating the output EBObj.
         //BUG was here read random bits, used dynamic memory for resultArray, needs destructor!
         EBObj newEBObj(resultArray, sizeOfResult);
         return newEBObj;
}

unsigned int EBObj::size() const
{
				//This method returns the size of the underlying byte array, it is useful for many things, but it
				//does expose more information than ideal. Use with caution.
				unsigned int outSize = objectSize;
				return outSize;
}

const unsigned char* EBObj::getByteArray() const
{
				//This method delivers the underlying byte array, it exoposes more information than the get byte
				//method bellow, but it is necessary for certain operations. Still, preferably use the getByte op
				//when possible to simplify things.
				return bitString;
}

void EBObj::bits2String() const
{
				/*
				 * This machine generates a string which represents the binary values within a given arbitrarily 
				 * sized byte array.
				 */
				for(unsigned int i = 0; i < objectSize * CHAR_BIT; i++)
				{
								unsigned char singleBit = 1;
								unsigned int bitValue = (bitString[i / CHAR_BIT] >> (i % CHAR_BIT)) & singleBit;
								std::cout << bitValue << " ";
				}
				std::cout << "\n";
}

EBObj EBObj::swapBytes(unsigned int a, unsigned int b) const
{
				// This operation is used to create a new EBObj with a given pair of bytes swapped. It remains
				// untested, so it may have some bugs hidden inside.
				unsigned char* newEBObjArray;
				newEBObjArray = new unsigned char[objectSize];
				unsigned char temp;
				for(unsigned int i = 0; i < objectSize; i++)
				{
								if(i == a)
								{
												//Swapping
												temp = bitString[a];
												newEBObjArray[a] = bitString[b];
												newEBObjArray[b] = temp;
								} else if( i != b)
								{
												//Hard copying the bit string original value to the new EBObj.
												newEBObjArray[i] = bitString[i];
								}
				}
				//Creating the new EBObj
				EBObj newEBObj(newEBObjArray, objectSize);
				return newEBObj;
}

unsigned char EBObj::getByte(unsigned int target) const
{
				// This method retrieves a specific byte from this Easy Bit Object. Since the EBObj in the end represents a chain
				// of bits (in the form of a byte array), this method allows EBObj to be used similarly to an array without
				// exposing the underlying unsigned char (byte) array.
				unsigned char targetByte;
				if(target < objectSize)
				{
								targetByte = bitString[target];
				} else //Then an impossible operation was requested
				{
								//Error message
								std::cout << "In the EBObj swapBytes method, the index " << target << " is larger than the EBObj size of " 
												<< objectSize << std::endl;
								targetByte = 0;
				}
				return targetByte;
}

unsigned char* EBObj::padArray(const unsigned char* inputArray, unsigned int inputSize, unsigned int targetSize) const
{
				// This method creates a new array with the contents of its input plus a lot of zeroes once the input content
				// has run out. It fulfills a given target, given by targetSize. It is used to prepare arrays for binary operations
				// which require them to be of the same size.
			unsigned char* outputArray;
			outputArray = new unsigned char[targetSize]; //DESTROYED ON INVOCATOR
			for(unsigned int i = 0; i < targetSize; i++)
			{
							if(i < inputSize)
							{
												outputArray[i] = inputArray[i];
							} else
							{
												outputArray[i] = 0;				
							}
			}
			return outputArray;
}
