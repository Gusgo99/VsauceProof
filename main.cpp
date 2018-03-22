/* 
 * File:   main.cpp
 * Author: Gustavo Pacola Gonçalves (@Gusgo99)
 *
 * Created on 19 de Fevereiro de 2018, 09:04
 */

#define _maxDigits 8                                                            // The maximum number of digits it will test
#define _baseUsed 10                                                            // The numerical base being used

#include <iostream>

using namespace std;

unsigned int factorial[_baseUsed];                                              // Array stores all the values from 0! to 9!, to prevent calculating during runtime
unsigned int digits[_maxDigits];                                                // Array used to store the value of each digit
unsigned int powers[_maxDigits];                                                // The value of 10 to the power of the the index accessed
unsigned int number;                                                            // The number being tested
unsigned int sum;                                                               // The sum of the factorial of each number

char loading[] = {'/', '-', '\\', '-'};                                         // Just the loading "animation?"

struct cases {                                                                  // An element of the list of found cases
    unsigned int value;                                                         // Stores the value founded
    cases *next;                                                                // Pointer to the next element of the list
    
};

int main() {
    cases first;                                                                // First element of the list of cases found
    cases *current = &first;                                                    // Pointer to the element being used on the list
    first.value = 1;                                                            // Clear the first value of the list
    first.next = NULL;                                                          // Make sure the pointer is not pointing to anywhere it souldn't be
    
    /* I was expecting it would take some time to run, so I thought it would be
     * better to use a lookup table instead of doing the arithmethic every time,
     * but after running it I don't think this was necessary considering the
     * time it takes to run, at least in base 10.*/
    cout << "Creating table to speed up the verifications" << endl;
    cout << "Creating table of powers of " << _baseUsed << endl;
    powers[0] = 1;                                                              // Set x^0 = 1
    digits[0] = 0;
    for(int i = 1; i != _maxDigits; i++) {
        digits[i] = 0;                                                          // Set all digits of the number as 0 to begin the testing
        powers[i] = powers[i - 1] * _baseUsed;                                  // Calculate the powers of the base used from 1 to the maximum number of digits
        
    }
    
    cout << "Creating table of factorials" << endl;
    factorial[0] = 1;
    for(int i = 1; i != _baseUsed; i++) {
        factorial[i] = factorial[i - 1] * i;                                    // Calculate n factorial from n = 1 to the maximum number a digit can assume
        
    }
    
    cout << endl;
    
    while(digits[_maxDigits - 1] != (_baseUsed)) {                              // Keep calculating if the conditions are met until it reaches the maximum defined number
        for(int i = 0; i != 6; i++) {                                           // Just keep a bar rotating to show the program is still running
            if(digits[i] != 0) {
                break;
                
            }
            if(i == 5) {
                static int load;
                cout << "\r" << "Starting to search possible cases in base ";
                cout << _baseUsed << " [" << loading[load++ % 4] << "]";
                
            }
            
        }
        
        digits[0]++;                                                            // Increment the rightmost digit
        for(int i = 0; i != (_maxDigits - 1); i++) {                            // Check if any digit is bigger than the maximum value allowed by the base
            if(digits[i] == _baseUsed) {                                        // If it is,
                digits[i] = 0;                                                  // set the digit to zero
                digits[i + 1]++;                                                // and increment the digit to its left
                
            }
        }
        sum = 0;                                                                // Variable which sum the factorials of the digits
        number = 0;                                                             // The number which is being tested
        for(int i = 0; i != _maxDigits; i++) {                                  // Recon the number based on its digits
            number += digits[i] * powers[i];
            
        }
        for(int i = 0; i != _maxDigits; i++) {                                  // Recon the sum of its digits factorial
            if((number / powers[i]) != 0) {
                sum += factorial[digits[i]];

            }
        }
        if(sum == number) {                                                     // Verify if there is a match
            current -> next = new cases;                                        // If yes, create a new elemento to the list
            current = current -> next;                                          // Set the new elemente as the current
            current -> value = number;                                          // Write the value to the list
            current -> next = NULL;                                             // Mark this as the last element
        }
    }
    
    current = &first;                                                           // Set the first element of the list as the current
    cout << endl << "Searched from n = 1 to n = " << _baseUsed << "^";
    cout << _maxDigits << endl;
    cout << "Values found: " << endl;
    
    while(true) {                                                               // Prints all the elements on the list
        cout << current -> value << endl;
        if(current -> next != NULL) {
            current = current -> next;
            
        }
        else {                                                                  // At the end of the list, delete all the elements
            break;
            
        }
    }
    
    while(first.next != NULL) {                                                 // Libera memoria alocada
        current = first.next -> next;
        delete first.next;
        first.next = current;
        
    }

    return 0;
}
