# BIG INTEGER CALCULATOR
## DESCRIPTION

This program is used to calculate big integers with over 19 digits. The larger the number is, the more memory and time it takes to process.

## DATA STRUCTURE

The program uses mainly Struct and Array (String).
<br />&nbsp;&nbsp;struct **BigInt**
<br />&nbsp;&nbsp;{
<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**bool** *pos*; //The number is positive or not?
<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**string** *num*; //Carry the entered number.
<br />&nbsp;&nbsp;};

## FUNCTIONS

* Convert integer to **BigInt** and vice versa
* Comparision
* Addition
* Subtraction
* Multiplication
* Division
* Modular
* Factorial
* Square Root
* Square
* Exponentiation (Power)
* Power and mod (a^b % c)
* Absolute Value (abs)
* Sin, cos, tan, cot
* Greatest Common Divisor (gcd)
* Lowest Common Multiple (lcm)
* Prime Check

## REFERENCE DOCUMENTS

[Multiplication](https://en.wikipedia.org/wiki/Multiplication_algorithm#Long_multiplication)
<br /> [Square Root](https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Decimal_(base_10))
<br /> [Greatest Common Divisor](https://en.wikipedia.org/wiki/Euclidean_algorithm#Implementations)
<br /> [Prime Check - Simple Method](https://en.wikipedia.org/wiki/Primality_test#C#)
<br /> [Prime Check - Miller Rabin](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test)

## NOTES

Most of functions mentioned above return **BigInt** even **Division** and **Square Root**.
