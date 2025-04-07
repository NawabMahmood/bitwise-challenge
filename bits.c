/* 
 * < Nawab Mahmood Nm3749>
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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    /** 
     * This implementation computes x & ~y and ~x & y, then adds
     * the two together. Note that the addition is equivalent to
     * the bitwise or operator, which can be re-written in terms 
     * of the & and ~ operators. 
     */ 
    int left = x & (~y);
    int right = (~x) & y; 
    return ~(~left & ~right); 
}

/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    /** 
     * assuming this is a 32-bit integer, the minimum two's 
     * complement is just the sign bit and zeroes everywhere else. 
     */ 
    return 1 << 31;
}

//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 2
 */
int isTmax(int x) {
    /** 
     * Maximum:     011.....1
     * ~Maximum:    100.....0
     * If x is not all ones, x + 1 zeroes out all of the rightmost
     * consecutive ones. We therefore want ~x to equal x + 1, as 
     * long as ~x is not zero. 
     */ 
    int allOnes = ~x; 
    int isMax = !(~x ^ (x + 1)); 
    return (!(!allOnes)) & isMax; 
}

/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    /** 
     * First, compute x & (x >> 16); the odd bits in the last sixteen
     * positions should be ones. Then repeat with x & (x >> 8), and so
     * on and so forth, until the last bit should just be a 1. 
     */ 
    x &= x >> 16; 
    x &= x >> 8; 
    x &= x >> 4; 
    x &= x >> 2; 

    // now x is ...1* if all odd bits are ones, and ...0* otherwise.
    return 1 & (x >> 1); 
}

/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    /** 
     * It's just ~x + 1. 
     */ 
    return ~x + 1; 
}

//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    /** 
     * Compute x - 0x30 and 0x39 - x. Neither should be negative.
     */ 
     int sign = 1 << 31;
     int low = x + ~0x30 + 1; 
     int high = 0x39 + ~x + 1; 
     int lowNeg = sign & low >> 31; 
     int highNeg = sign & high >> 31; 
     return !(lowNeg | highNeg); 
}

/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    /** 
     * Create a mask that's zero if x is zero and all ones if x is
     * nonzero. Then, return (mask & y) + (~mask & z). This will 
     * produce y if x is nonzero and z if x is zero. 
     */ 

    // start by making mask = 1 if x is zero, mask = 0 otherwise.
    // then, make 32 copies of that bit.
    int mask = !x; 
    mask += mask << 1; // 2 copies
    mask += mask << 2; // 4
    mask += mask << 4; // 8 
    mask += mask << 8; // 16 
    mask += mask << 16; // 32

    // mask is inverted from our first comment. 
    return ((~mask) & y) + (mask & z); 
}

/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    /** 
     * Compute y - x, as well as the signs of x and y. This may 
     * overflow if the signs do not match, otherwise we're okay. 
     * Therefore, we only care about the following two possibilities:
     * 1. x is negative but y is nonnegative. 
     * 2. both signs are equal and y-x is not negative
     * Note case 1 doesn't depend on the value stored in y-x. 
     */ 
    int diff = y + (~x) + 1; 
    int signDiff = (diff >> 31) & 1; 

    int caseOne = (x >> 31) & (~y >> 31) & 1; 
    int caseTwo = (~((x >> 31) ^ (y >> 31))) & 1 & !signDiff; 
    return caseOne | caseTwo; 
}

//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
    /** 
     * If x is zero, then x = ~x + 1 = 0. Otherwise, x | (~x + 1)
     * has a nonzero sign bit. Flip the sign bit and return it. 
     */ 
    x = x | (~x + 1);
    return (~x >> 31) & 1; 
}

/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    /** 
     * The number of bits needed in positive x is the index of the
     * leftmost one bit. The number of bits needed in negative x is 
     * the index of the leftmost zero bit. zero always takes 1 bit.
     * So, if x is negative, then x needs as many bits as ~x. 
     * Once that's done, apply binary search to see how many bits 
     * x needs to have. 
     */ 

    int signMask = (x >> 31) & 1; 
    int bits = 1; 
    int temp; 

    signMask += signMask << 1; 
    signMask += signMask << 2; 
    signMask += signMask << 4; 
    signMask += signMask << 8; 
    signMask += signMask << 16; 

    // signMask is all ones if x is negative, all zeroes otherwise. 
    // now invert x is signMask is all ones. 
    x = (signMask & ~x) | (~signMask & x); 

    // first, check if x needs more than 16 bits. This happens if 
    // x >> 16 is nonzero, or !!(x >> 16) << 4 is 16. Afterwards,
    // lop off the last 16 bits if x needs more than 16 bits, and 
    // don't touch x otherwise. 
    temp = (!!(x >> 16)) << 4; 
    bits += temp; 
    x = x >> temp; 

    // repeat for 8, 4, 2, and 1. 
    temp = (!!(x >> 8)) << 3; 
    bits += temp; 
    x = x >> temp; 

    temp = (!!(x >> 4)) << 2; 
    bits += temp; 
    x = x >> temp; 

    temp = (!!(x >> 2)) << 1; 
    bits += temp; 
    x = x >> temp; 

    temp = (!!(x >> 1)); 
    bits += temp; 
    x = x >> temp; 

    // at the very end, x is either zero or one, depending on if
    // x still needs one more bit or not. This corresponds to a 
    // leading bit of 1. 
    return bits + x; 
}

//float
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
    // decompose into sign, exponent, and fraction. 
    int sign = uf & (1 << 31); 
    int exp = uf & (0xFF << 23); 
    int frac = uf ^ exp ^ sign; 

    // checking for NaN 
    if(exp == (0xFF << 23))
        return uf; 

    // for subnormals floats, we can just shift the entire float by
    // one and keep the sign. 
    if(exp == 0) 
        return (uf << 1) + sign; 

    // for the rest of the numbers, increment the exponent by one. 
    // if the exponent is 0xFF << 23, then we have an infinite result,
    // and we need to zero out the fractional part. 
    else {
        exp += 1 << 23; 
        if(exp == (0xFF << 23)) 
            frac = 0; 
    }

    return sign + exp + frac; 
}

/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
    int sign = x & (1 << 31); 
    int exp = 31 + 127; 
    int frac = 0; 

    // if x is zero, return zero.
    if(x == 0) 
        return 0; 

    // if x was negative, negate it. If x was the minimum value, 
    // i.e. if x == sign, then we know that x is just -2^31. 
    if(x == sign) return 0xcf000000; 
    else if(sign) x = ~x + 1; 

    // compute the exponent by shifting x until its leading bit
    // overlaps with the sign bit. 
    while(!(x & (1 << 31))) {
        x = x << 1; 
        exp -= 1; 
    } 

    // take off the leading bit, then move x down another 8 bits 
    // for the fractional part. 
    frac = (x & (~(1 << 31))) >> 8; 

    // Two cases to round up: 
    // * frac has a trailing one bit and the last 8 bits of x are 
    //   at least 0x80. 
    // * frac has a trailing zero bit and the last 8 bits of x 
    //   are strictly greater than 0x80. 
    if((frac & 1) && ( (x & 0xFF) >= 0x80 )) frac++; 
    else if(!(frac & 1) && ( (x & 0xFF) > 0x80 )) frac++; 

    // use + instead of | to let the rounded fraction increase the
    // exponent. 
    return sign + (exp << 23) + frac; 
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
    // start by taking the sign, exp, and frac of uf.
    int sign = (uf >> 31) & 1; 
    int exp = ((uf >> 23) & 0xFF) - 127; 
    int frac = uf & 0x7FFFFF; 

    // if the exponent is >= 31, then uf >= 2^31. 
    // this includes both out of range numbers and infinites.
    if(exp >= 31) return 0x80000000u; 

    // check for zero. 
    if(exp == -127 && frac == 0) return 0; 

    // if the exponent is < 0, then it's smaller than 1. return 0. 
    if(exp < 0) return 0; 

    // add the leading bit to the fraction. 
    frac += 1 << 23; 

    // if the exponent is less than 23, we need to shift to the right
    // and remove any excess bits. 
    if(exp < 23) frac = frac >> (23 - exp); 

    // if the exponent is greater than 23, just shift to the left.
    else frac = frac << (exp - 23); 

    // negate the fraction, if necessary. 
    if(sign) frac = ~frac + 1; 
    return frac; 
}
