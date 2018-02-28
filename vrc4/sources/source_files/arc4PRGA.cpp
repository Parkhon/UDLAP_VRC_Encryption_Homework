//This is the implementation of the RC4 pseudo random generation algorithm
#include "EBObj.h"
#include "arc4PRGA.h"

arc4PRGA::arc4PRGA()
{
				state = new unsigned int[255];	//DYNAMICALLY ALLOCATED, DELETED ON DESTRUCTOR
}

arc4PRGA::~arc4PRGA()
{
				//Destructor
				delete state;
}

void arc4PRGA::loadState(unsigned int* inState)
{
				//Be mindful, the array that is incoming might hop out of scope. Copying it manually instead
			//Cloning the state, hard copy
			for(unsigned int c = 0; c < 256; c++)
			{
								state[c] = inState[c];
			}
}

EBObj arc4PRGA::generateRandomNumbers(unsigned int quantity)
{
				//This method generates the random number byte string which is the output to the RC4 Key Gen algorithm.
				initializeIndexes();
				//Preparing output EBObj
				unsigned char* outArray;
				outArray = new unsigned char[quantity];
				for(unsigned int c = 0; c < quantity; c++)
				{
								//While work remains to be done:
								onTheGoStateMutation();	//Mutating the state on the go
								unsigned char randNum = randomGeneration(); //Getting the next random number
								outArray[c] = randNum; //Adding the random number to the output creation array
				}
				//Generating output EBObj
				EBObj output(outArray, quantity);
				return output;		//Delivering output of the key gen algorithm
}


void arc4PRGA::initializeIndexes()
{
				//This method initializes the i and j indexes used by the algorithm
				i = 0;
				j = 0;
}

void arc4PRGA::onTheGoStateMutation()
{
				//This algorithm mutates the state on the go according to the i and j indexes, modifies the state while the algorithm
				//does its work, meaning that the key changes mid execution, very clever.
				i = (++i) % 256;
				j = (j + state[i]) % 256;
				//Swapping: this is the end product of this method
				unsigned int temp = state[i];
				state[i] = state[j];
				state[j] = temp;
}

unsigned char arc4PRGA::randomGeneration()
{
				unsigned int k = state[ (state[i] + state[j]) % 256 ];
				return k;
}
