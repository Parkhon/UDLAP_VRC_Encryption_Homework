//Header file for the arc4 key scheduler algorithm:

//#include "EBObj.h"

class arc4KSA
{
				public:
								arc4KSA();
								void loadKey(EBObj* key);
								unsigned int* generateState();
				private:
								void fillState();
								void keyBasedScrambler();
								EBObj* key;
								unsigned int* state;
};
