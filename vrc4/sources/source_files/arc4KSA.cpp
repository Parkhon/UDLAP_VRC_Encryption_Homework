//This is the implementation of the arc4 Key Scheduling Algorithm

#include "EBObj.h"
#include "arc4KSA.h"

//DEBUG
#include <iostream>

arc4KSA::arc4KSA()
{
				//Note that the state is always 256 elements long.
				//DELETE THIS POINTER IN THE CLASS WHICH SUMMONS IT!
				state = new unsigned int[256]; //Initializing the state with dynamic memory allocation.
}

void arc4KSA::loadKey(EBObj* inKey)
{
				//Loading the key for later usage. The idea is to make it super simple and explicit.
				//So when the source code is read, anybody can casually pick up what the algorithm is
				//doing.
			key = inKey;	//Using pointer since this object will quickly be eliminated anyway. DO NOT DESTROY POINTER
}

unsigned int* arc4KSA::generateState()
{
				//This method generates the original state for the reminder of the RC4 algorithm
				//Note that the two methods bellow modify the state of this object.
				fillState();
				keyBasedScrambler();
				//Finally returning the state for later usage.
				return state;
}

void arc4KSA::fillState()
{
				for(unsigned int i = 0 ; i < 256; i++)
				{
								state[i] = i;
				}
}

void arc4KSA::keyBasedScrambler()
{
				unsigned int j = 0;
				for(unsigned int i = 0; i < 256; i++)
				{
								j = (j + state[i] + key->getByte( i % key->size() ) ) % 256 ;
								//swapping
								unsigned int temp = state[i];
								state[i] = state[j];
								state[j] = temp;
								//std::cout << temp << ", " << state[i] << ", " << state[j]  << " -> " << j << " " << i << std::endl;
				}
}
