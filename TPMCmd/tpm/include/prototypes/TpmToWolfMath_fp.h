/* Microsoft Reference Implementation for TPM 2.0
 *
 *  The copyright in this software is being made available under the BSD License,
 *  included below. This software may be subject to other third party and
 *  contributor rights, including patent rights, and no such rights are granted
 *  under this license.
 *
 *  Copyright (c) Microsoft Corporation
 *
 *  All rights reserved.
 *
 *  BSD License
 *
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *
 *  Redistributions of source code must retain the above copyright notice, this list
 *  of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright notice, this
 *  list of conditions and the following disclaimer in the documentation and/or
 *  other materials provided with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ""AS IS""
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*(Auto-generated)
 *  Created by TpmPrototypes; Version 3.0 July 18, 2017
 *  Date: Aug 30, 2019  Time: 02:11:54PM
 */

#ifndef _TPM_TO_WOLF_MATH_FP_H_
#define _TPM_TO_WOLF_MATH_FP_H_

#ifdef MATH_LIB_WOLF

//*** BnFromWolf()
// This function converts a wolfcrypt mp_int to a TPM bignum. In this implementation
// it is assumed that wolfcrypt used the same format for a big number as does the
// TPM -- an array of native-endian words in little-endian order.
void BnFromWolf(bigNum bn, mp_int* wolfBn);

//*** BnToWolf()
// This function converts a TPM bignum to a wolfcrypt mp_init, and has the same
// assumptions as made by BnFromWolf()
void BnToWolf(mp_int* toInit, bigConst initializer);

//*** MpInitialize()
// This function initializes an wolfcrypt mp_int.
mp_int* MpInitialize(mp_int* toInit);

#  if LIBRARY_COMPATIBILITY_CHECK
//** MathLibraryCompatibililtyCheck()
// This function is only used during development to make sure that the library
// that is being referenced is using the same size of data structures as the TPM.
BOOL MathLibraryCompatibilityCheck(void);
#  endif

//*** BnModMult()
// Does multiply and divide returning the remainder of the divide.
LIB_EXPORT BOOL BnModMult(
    bigNum result, bigConst op1, bigConst op2, bigConst modulus);

//*** BnMult()
// Multiplies two numbers
LIB_EXPORT BOOL BnMult(bigNum result, bigConst multiplicand, bigConst multiplier);

//*** BnDiv()
// This function divides two bigNum values. The function returns FALSE if
// there is an error in the operation.
LIB_EXPORT BOOL BnDiv(
    bigNum quotient, bigNum remainder, bigConst dividend, bigConst divisor);

#  if ALG_RSA
//*** BnGcd()
// Get the greatest common divisor of two numbers
LIB_EXPORT BOOL BnGcd(bigNum   gcd,      // OUT: the common divisor
                      bigConst number1,  // IN:
                      bigConst number2   // IN:
);

//***BnModExp()
// Do modular exponentiation using bigNum values. The conversion from a mp_int to
// a bigNum is trivial as they are based on the same structure
LIB_EXPORT BOOL BnModExp(bigNum   result,    // OUT: the result
                         bigConst number,    // IN: number to exponentiate
                         bigConst exponent,  // IN:
                         bigConst modulus    // IN:
);

//*** BnModInverse()
// Modular multiplicative inverse
LIB_EXPORT BOOL BnModInverse(bigNum result, bigConst number, bigConst modulus);
#  endif  // TPM_ALG_RSA
#  if ALG_ECC

//*** PointFromWolf()
// Function to copy the point result from a wolf ecc_point to a bigNum
void PointFromWolf(bigPoint   pOut,  // OUT: resulting point
                   ecc_point* pIn    // IN: the point to return
);

//*** PointToWolf()
// Function to copy the point result from a bigNum to a wolf ecc_point
void PointToWolf(ecc_point* pOut,  // OUT: resulting point
                 pointConst pIn    // IN: the point to return
);

//*** BnEccModMult()
// This function does a point multiply of the form R = [d]S
// return type: BOOL
//  FALSE       failure in operation; treat as result being point at infinity
LIB_EXPORT BOOL BnEccModMult(bigPoint   R,  // OUT: computed point
                             pointConst S,  // IN: point to multiply by 'd' (optional)
                             bigConst   d,  // IN: scalar for [d]S
                             bigCurve   E);

//*** BnEccModMult2()
// This function does a point multiply of the form R = [d]G + [u]Q
// return type: BOOL
//  FALSE       failure in operation; treat as result being point at infinity
LIB_EXPORT BOOL BnEccModMult2(bigPoint   R,  // OUT: computed point
                              pointConst S,  // IN: optional point
                              bigConst   d,  // IN: scalar for [d]S or [d]G
                              pointConst Q,  // IN: second point
                              bigConst   u,  // IN: second scalar
                              bigCurve   E   // IN: curve
);

//** BnEccAdd()
// This function does addition of two points.
// return type: BOOL
//  FALSE       failure in operation; treat as result being point at infinity
LIB_EXPORT BOOL BnEccAdd(bigPoint   R,  // OUT: computed point
                         pointConst S,  // IN: point to multiply by 'd'
                         pointConst Q,  // IN: second point
                         bigCurve   E   // IN: curve
);
#  endif  // TPM_ALG_ECC
#endif    // MATH_LIB_WOLF

#endif  // _TPM_TO_WOLF_MATH_FP_H_
