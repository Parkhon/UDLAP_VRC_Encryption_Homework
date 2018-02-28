#include <iostream>
#include "EBObj.h"
#include "arc4KSA.h"
#include "arc4PRGA.h"
#include "Vignere.h"

int main()
{
				//This main file is purely a sample to demonstrate the funcionality of the reusable Easy Bit Object.
				const unsigned int plaintext_size = 4;
				unsigned char plaintext [plaintext_size] = {'A','B','C','D'};
				EBObj bPlaintext(plaintext, plaintext_size);

				const unsigned int key_size = 4;	//Ineffectively handled
				unsigned char key [key_size] = {1,1,1,2};
				EBObj bKey(key, key_size);
				
				//Printing for preview purposes:
				std::cout << "The Plaintext is: ";
				bPlaintext.bits2String();
				
				std::cout << "The key is: ";
				bKey.bits2String();

				//Testing the arc4KSA: Key Scheduling
				arc4KSA ksa;
				ksa.loadKey(&bKey);
				unsigned int* state = ksa.generateState();
				std::cout << "\nThe initial state is: " << std::endl;
				for(unsigned int i = 0; i < 256; i++)
				{
								std::cout  << state[i] << "(" << i << ")" << " - ";
				}

				//Generating end key
				std::cout << std::endl;
				arc4PRGA prga;
				prga.loadState(state);
				EBObj rNum = prga.generateRandomNumbers(4);
				std::cout << "The Final Random Key is:" << std::endl;
				rNum.bits2String();
				std::cout << "So far so good" << std::endl; //The endl command is important to prevent c++ from holding useful data on its buffer.
				
				//Encrypting
				EBObj crypto = bPlaintext.xorOp(&rNum);
				std::cout << "The encrypted text with arc4 is: " << std::endl;
				crypto.bits2String();

				//Applying Vignere
				const unsigned int vigKey_size = 4;
				unsigned char vigKey[vigKey_size] = {1,2,3,4};
				EBObj bVigKey(vigKey, vigKey_size);
				std::cout << "\nFor the Vignere Cypher the key is " << std::endl;
				bVigKey.bits2String();
				std::cout << std::endl;
				std::cout << "The result of Vignere encryption is: " << std::endl;
				Vignere vig;
				vig.loadKey(&bVigKey);
				vig.loadPlainText(&crypto);
				EBObj cryptoVignere = vig.encrypt();
				cryptoVignere.bits2String();
				
				//Decrypting Vignere
				std::cout << "Decrypting with Vignere now: " << std::endl;
				vig.loadPlainText(&cryptoVignere);
				EBObj vigDec = vig.decrypt();
				vigDec.bits2String();
				std::cout << std::endl;

				//Decrypting with arc4
				std::cout << "The decrypted plaintext with arc4 is: " <<std::endl;
        EBObj decrypt = vigDec.xorOp(&rNum);
        decrypt.bits2String();
        std::cout << "" << std::endl;

}
