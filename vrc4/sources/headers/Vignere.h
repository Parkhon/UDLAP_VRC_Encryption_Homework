//This is the header file for the vignere cypher:
#pragma once
#include "EBObj.h"

class Vignere
{
				public:
								Vignere();
								~Vignere();
								void loadKey(EBObj* inKey);
								void loadPlainText(EBObj* inPlain);
								EBObj encrypt();
								EBObj decrypt();
				private:
								unsigned char vignereOp(bool decrypt);
								void initializeIndexes();
								EBObj* key;
								EBObj* plainText;
								unsigned int i;


};
