//This is the header file for the ARC4 pseudo random generation algorithm
//WIP header includes, delete in release
//#include "EBObj.h"

class arc4PRGA
{
				public:
								arc4PRGA();
								~arc4PRGA();
								void loadState(unsigned int* inState);
								EBObj generateRandomNumbers(unsigned int quantity);
				private:
								void initializeIndexes();
								void onTheGoStateMutation();
								unsigned char randomGeneration();
								//Attributes
								unsigned int i;
								unsigned int j;
								unsigned int* state;
};
