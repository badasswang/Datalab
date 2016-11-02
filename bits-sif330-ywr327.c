/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
/* uses demorgan's laws */

  return ( ~x)&(~y);
}
/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
//masks above highbit
int mhigh = ~ 0 << highbit;
//masks below lowbit
int mlow = ~(~0 << lowbit);
//masks all but most significant bit
int msig = ~(1 << highbit);
mhigh = mhigh & msig; //ensures highbit is higher than lowbit
return ~(mhigh | mlow);//translates masks into results


}
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  //return 1 when all 0
  //shift half to right, OR gets 1's
  x = (x >> 16) | x;
  x = (x >> 8) | x;
  x = (x >> 4) | x;
  x = (x >> 2) | x;
  x = (x >> 1) | x;
  // if x has any 1's, OR would've accumulates 1's, 
  // ~ => 0, 0&1 => 0
  return ~x & 1;
}
/* 
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void) {
int byte = 0xaa; //8 of the right bits
int word = (byte | (byte << 8)); //16 correct bits
    return (word | (word << 16)); //first and second "halfs" of bits are returned
}
/* 
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) {
	/*takes advantage of this logical equivalence, both are only false when x is true and y is false */ 
    return ( (!x)|y);
}
/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {
  int y= x >> 1;
  int result, a; 
  //if bit isn't in greatest spot
  y = (y >> 1) | y;
  y = (y >> 2) | y;
  y = (y >> 4) | y;
  y = (y >> 8) | y;
  y = (y >> 16) | y;//y is a mask of 1s up to thebit before greatest bit
result = x & (~ y); //returns mask with 1 at most significant bit
//use multiplexer as an if statement 
a = x & (1 << 31); //masks most singificant bit
return (a | ((~a) & result));


}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
 return (!(x & (x + (~1 + 1)))) & (!!x)& ((x >>31)^1);
 //checks if x is 0, if not, checks whether only 1 bit is 1
 //if there is only one 1 in x, then the first two part  will give you 0 (negated to 1)
 //the second part checks if x is 0 (which should return 0)
 //the third part is a special check for the left most bit
 //all three must return 1 for the function to return 1
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
int diff = (~y+1) + x; //equivalent to x-y 
int samesign = x ^ y;//checks if x and y are different signs
int diffsign = diff ^ x; //checks if x and diff have differnt signs
//if x and x-y will have different signs when x and y have different signs
//there is overflow
//all of signs are marked in left most bit, hence the 31 bit shift
return !((samesign & diffsign) >> 31);  

}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
/* !x is true if x isn't 0, shifting the first digit down becomes -1 if negative, 0 if positive */ 
 return (!x ^  !(x >> 31));
}
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
/* Creates a number with all 1's except the initial (negative) bit  */  
return  (~0) ^ (1 << 31);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /* method 1, p96 in book*/
  return ~x+1;

}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
  return (!!x) | (x >> 31); //if positive, returns 1, if zero, both parts are 0, and if negative, it is nonzero, and all of the bits are 1 from the second part (-1)
}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
 unsigned m = 0x7FFFFFFF;
 unsigned abs = m & uf; //takes absolute value
 unsigned nan = 0x7F800001; //smallest NaN
 if (abs >= nan) {return uf;} //if abs is bigger than NaN, it is a NaN
 return abs; //else return abs 
 
}

/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
  unsigned x = uf; //store uf to use for shifting
  unsigned sign = uf & (0x80000000); //sign bit
  unsigned exp = ((x << 1) >> 24) & 0xFF ; //last 8 bits are exponents
  unsigned fracmask = 0x7fffff;
  unsigned frac = uf & fracmask; //frac part of float
  unsigned rne = (uf & 2) && (uf & 1) ;//round to nearest even (when last two digits are 11)
  if (!(~(exp)& 0xFF)) {return uf;} //sorts out NaN/infinity
  if (exp == 1) { //special case when exp is 1
  return sign + (0x400000) + (frac >> 1) + rne; //cross between normal and denorm, shift fraction and add rne but also needs the special 1 placement
  } 
  if (exp) {
     exp = ( exp + 0xFF) & 0xff;//decrements exp
  return sign + (exp << 23) + frac;
  } //else we have a denormalized number
  //sign and exp are unchanged
  return sign + (frac >> 1) + rne; //exp is 0
  }
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  int x = uf; //to check if uf is negative when a signed int
  int exp = (uf >> 23) & 0xFF; //last 8 bits are exp
  int frac = uf & 0x7FFFFF; //takes frac part of float
    
  if (exp < 127) {return 0;} //underflow
  if (exp > 157) {return 0x80000000u;} // overflow/NaN/inf
  frac = frac | 0x800000; //adds the leading 1 (because it's normalized) 
  if (exp >=150)
  {frac = frac << (exp - 150);} //effect of multiplying by 2^e
  else {
  frac = frac >> (150 - exp);} //effect of multiplying by 2^e, really only the leading 1 due to rounding
if (x < 0) { //negate as needed
    return (-1) * frac; 
  }
return frac;
}
