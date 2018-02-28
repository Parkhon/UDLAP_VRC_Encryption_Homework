//This is the implementation of the Vignere Cypher
#include "Vignere.h"
//#include "EBObj.h"

Vignere::Vignere()
{

}

Vignere::~Vignere()
{

}

void Vignere::loadKey(EBObj* inKey)
{
				//Loading the key for the Vignere Cypher
				key = inKey;	
}

void Vignere::loadPlainText(EBObj* inPlain)
{
				//Loading the plaintext for the Vignere Cypher
				plainText = inPlain;
}

EBObj Vignere::encrypt()
{
				//Preparing output array
				unsigned char* outputArray;
				outputArray = new unsigned char[plainText->size()]; //DYNAMIC MEMORY ALLOCATION, HANDLED BY EBObject destructor
				//Vignere Cypher Main Algorithm
				initializeIndexes();
				while( i < plainText->size() )
				{
								outputArray[i] = vignereOp(false);
								i++;
				}
				//Building and delivering EBObject
				EBObj result( outputArray, plainText->size() );
				return result;
}

EBObj Vignere::decrypt()
{
				//Preparing output array
        unsigned char* outputArray;
        outputArray = new unsigned char[plainText->size()]; //DYNAMIC MEMORY ALLOCATION, HANDLED BY EBObject destructor
        //Vignere Cypher Main Algorithm
        initializeIndexes();
        while( i < plainText->size() ) 
        { 
                outputArray[i] = vignereOp(true);
                i++;
        } 
        //Building and delivering EBObject
         EBObj result( outputArray, plainText->size() );
        return result;
}

unsigned char Vignere::vignereOp(bool decrypt)
{
				//The main operation carried out by the vignere cypher, with a 256 bit capacity instead of just the alphabet.
				if(decrypt)
				{
								unsigned char output = ( -key->getByte( i % key->size() ) + plainText->getByte(i) ) % 256;
                return output;

				}else {
								unsigned char output = ( key->getByte( i % key->size() ) + plainText->getByte(i) ) % 256;
								return output;
				}
}

void Vignere::initializeIndexes()
{
				//Initializing the index for Vignere encryption
				i = 0;
}
