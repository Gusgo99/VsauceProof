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

unsigned int factorial[_baseUsed] =                                             // Array stores all the values from 0! to 9!, to prevent calculating during the execution of the program
    {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
unsigned int digits[_maxDigits];                                                // Array used to store the value of each digit
unsigned int powers[_maxDigits];                                                // The value of 10 to the power of the the index accessed
unsigned int number;                                                            // The number being tested
unsigned int sum;                                                               // The sum of the factorial of each number

char loading[] = {'/', '-', '\\', '-'};                                         // Just the loading "animation?"

typedef struct cases {                                                          // An element of the list of found cases
    unsigned int value;                                                         // Stores the value founded
    cases *next;                                                                // Stores the next element of the list
    
};

int main() {
    cases first;                                                                // First element of the list of cases found
    cases *current = &first;                                                    // Pointer to the element being used on the list
    first.value = 0;                                                            // Clear the first value of the list
    first.next = NULL;                                                          // Make sure the pointer is not pointing to anywhere it souldn't be
    
    /* I was expecting it would take some time to run, so I thought it would be
     * better to use a lookup table instead of doing the arithmethic every time,
     * but after running I don't think this was necessary considering the times
     * it takes to run.*/
    powers[0] = 1;                                                              // Set 10^0 = 1
    for(int i = 0; i != _maxDigits; i++) {
        digits[i] = 0;                                                          // Set all digits of the number as 0 to begin the testing
        if(i != 0) {
            powers[i] = powers[i - 1] * 10;                                     // Calculate the powers of 10 from 1 to the maximum number of digits
            
        }
    }
    
    while(digits[_maxDigits - 1] != (_baseUsed)) {                              // Keep calculating if the conditions are met until it reaches the maximum defined number
        for(int i = 0; i != 6; i++) {                                           // Just keep a bar rotating to show the program is running
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
        for(int i = 0; i != (_maxDigits - 1); i++) {                            // Check if any digit is bigger than 9,
            if(digits[i] == _baseUsed) {                                        // if it is, increment the digit to its left
                digits[i] = 0;
                digits[i + 1]++;
                
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
            if(current -> value != 0) {                                         // Verify if the current element of the list has been writen
                current -> next = new cases;                                    // If yes, create a new elemento to the list
                current = current -> next;                                      // Set the new elemente as the current
                current -> value = number;                                      // Write the value to the list
                current -> next = NULL;                                         // Mark this as the last element
                
            }
            else {                                                              // If not, add the element to the list
                current -> value = number;
                
            }
        }
    }
    
    current = &first;                                                           // Set the first element of the list as the current
    cout << endl << "Searched from n = 1 to log(n) / log(10) = ";
    cout << _maxDigits << "." << endl;
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

