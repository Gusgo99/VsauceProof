# VsauceProof
Proof that the only numbers which can be writen as a sum of the factorial of its digits are 1, 2, 145 and 40585

It's about a tweet from the youtuber Vsauce which made an affirmation about the fact but presented no proofs, which made me a little currious. The tweet can be found on this link:
https://twitter.com/tweetsauce/status/965259567322943490

After some thinking, I came to the conclusion that it is possible to nail down the cases which this can happen to numbers with less than 8 digits.

To come to this conclusion, I considered what is the maximum value the sum of the factorial of the digits can be, which is: 9! * n, where n is the number of digits.

I also considered the minimum number which can be expressed with so many digits: 10^(n-1), also, where n is the number of digits.

Derivating both sides, we can calculate that the number will grow much faster than the sum of its digits factorial, which mean that the bigger a number is, past a certain point, the further it will be from the sum of it's factorials. Which means there is a upper limit to what numbers can have this propriety, which in base 10 is the solution to the equation:
9! * n = 10^(n - 1)

Solving the equation we get a number between 7 and 8, which can be rounded up in order to include even the unwanted cases. Now all we need to do is check if all the cases below 10^8 are the cases already presented. That is the function of the .cpp file presented in this repository.

After running the said program, the result presented in the screen is:

Starting to search possible cases in base 10 [/]

Searched from n = 1 to log(n) / log(10) = 8.

Values found:

1

2

145

40585

Which can be used to conclude that the cases presented by Vsauce are not the only known, but the only ones that exist, as stated on the tweet.

Sorry for any misspellings, english is not my main language.

Also, in case anyone disagree with my proof or think it can be presented in a cleaner manner, feel free to point out.
Corrections to the .cpp file are also be welcome and sorry if you don't like my C++ code, but I haven't writen in C++ for some time.
