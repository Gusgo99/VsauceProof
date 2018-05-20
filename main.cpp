/* 
 * File:   main.cpp
 * Author: Gustavo Pacola Gonçalves (@Gusgo99)
 *
 * Created on 19 de Fevereiro de 2018, 09:04
 */

#include <iostream>
#include <ctime>
#include <fstream>

#define MAXDIGITS 8                                                             // The maximum number of digits it will test
#define BASEUSED 10                                                             // The numerical base being used

using namespace std;

unsigned int factorial[BASEUSED];                                               // Array stores all the values from 0! to 9!, to prevent calculating during runtime
unsigned int digits[MAXDIGITS];                                                 // Array used to store the value of each digit
unsigned int powers[MAXDIGITS];                                                 // The value of 10 to the power of the the index accessed
unsigned long long int number;                                                  // The number being tested
unsigned long long int sum;                                                     // The sum of the factorial of each number

char loading[] = {'/', '-', '\\', '|'};                                         // Just the loading "animation?"

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
    cout << "Creating tables to speed up the verifications" << endl;
    cout << "Creating table of powers of " << BASEUSED << endl;
    powers[0] = 1;                                                              // Set x^0 = 1
    digits[0] = 1;
    for(int i = 1; i != MAXDIGITS; i++) {
        digits[i] = 0;                                                          // Set all digits of the number as 0 to begin the testing
        powers[i] = powers[i - 1] * BASEUSED;                                   // Calculate the powers of the base used from 1 to the maximum number of digits
        
    }
    
    cout << "Creating table of factorials" << endl;
    factorial[0] = 1;
    for(int i = 1; i != BASEUSED; i++) {
        factorial[i] = factorial[i - 1] * i;                                    // Calculate n factorial from n = 1 to the maximum number a digit can assume
        
    }
    
    cout << endl;
    
    while(digits[MAXDIGITS - 1] != (BASEUSED)) {                                // Keep calculating if the conditions are met until it reaches the maximum defined number
        static time_t currentT, lastT;
        time(&currentT);
        if(currentT != lastT) {
            lastT = currentT;
            static int load;
            cout << "\r" << "Starting to search possible cases in base ";
            cout << BASEUSED << " [" << loading[load++ % 4] << "]";
            
            
        }
        
        digits[0]++;                                                            // Increment the rightmost digit
        for(int i = 0; i != (MAXDIGITS - 1); i++) {                             // Check if any digit is bigger than the maximum value allowed by the base
            if(digits[i] == BASEUSED) {                                         // If it is,
                digits[i] = 0;                                                  // set the digit to zero
                digits[i + 1]++;                                                // and increment the digit to its left
                
            }
        }
        sum = 0;                                                                // Variable which sum the factorials of the digits
        number = 0;                                                             // The number which is being tested
        for(int i = 0; i != MAXDIGITS; i++) {                                   // Recon the number based on its digits
            number += digits[i] * powers[i];
            
        }
        for(int i = 0; i != MAXDIGITS; i++) {                                   // Recon the sum of its digits factorial
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
    
    ofstream result;
    
    result.open("resultado.txt");
    
    if(!result.is_open()) {
        return 0x0001;
        
    }
    
    current = &first;                                                           // Set the first element of the list as the current
    cout << endl << "Searched from n = 1 to n = " << BASEUSED << "^";
    cout << MAXDIGITS << endl;
    cout << "Values found: " << endl;
    result << "Searched from n = 1 to n = " << BASEUSED << "^";
    result << MAXDIGITS << endl;
    result << "Values found: " << endl;
    
    while(true) {                                                               // Prints all the elements on the list
        result << current -> value << endl;
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
    
    result << endl;
    result << "Look up tables used:" << endl;
    result << "Powers of " << BASEUSED << " (" << BASEUSED << "^n): " << endl;
    
    for(int i = 0; i != MAXDIGITS; i++) {
        result << "n = " << i << ": " << powers[i] << endl;
        
    }
    
    result << endl;
    
    result << "Factorial of n (n!):"<< endl;
    
    for(int i = 0; i != BASEUSED; i++) {
        result << "n = " << i << ": " << factorial[i] << endl;
        
    }
    
    result.close();

    return 0;
}