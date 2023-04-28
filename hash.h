#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        HASH_INDEX_T hashVal = 0;
 
				std::string kval{k};
				while (kval.size() < 30){
					kval = 'a' + kval;
				}

				HASH_INDEX_T w[5] = { 0 };

				for (int i = 4; i >= 0; i--){
					unsigned long start = kval.size() - 6 * (5 - i);
					if (start >= 0 && start < kval.size()) { // Add this check
							std::string substr = kval.substr(start, 6);
							HASH_INDEX_T curr = 0;

							for (unsigned int j = 0; j < substr.size(); j++){
									curr += (HASH_INDEX_T)(letterDigitToNumber(substr[j]) * pow(36, substr.size() - 1 - j));
							}

							w[i] = curr;
					}
				}

				for (int i = 0; i < 5; i++){
					hashVal += rValues[i] * w[i];
				}
				return hashVal;


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				if (letter >= '0' && letter <= '9'){
						return (HASH_INDEX_T)(letter - '0' + 26);
				}
				else{
					char temp = (char)std::tolower(letter);
					return (HASH_INDEX_T)(temp - 'a');
				}
				

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
