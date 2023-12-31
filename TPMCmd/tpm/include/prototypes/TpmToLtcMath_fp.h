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

#ifndef _TPM_TO_LTC_MATH_FP_H_
#define _TPM_TO_LTC_MATH_FP_H_

#ifdef MATH_LIB_LTC

//*** BnModMult()
// Does multiply and divide returning the remainder of the divide.
LIB_EXPORT BOOL BnModMult(
    bigNum result, bigConst op1, bigConst op2, bigConst modulus);

//*** BnMult()
// Multiplies two numbers
LIB_EXPORT BOOL BnMult(bigNum result, bigConst multiplicand, bigConst multiplier);

//*** BnDiv()
// This function divides two BIGNUM values. The function always returns TRUE.
LIB_EXPORT BOOL BnDiv(
    bigNum quotient, bigNum remainder, bigConst dividend, bigConst divisor);

#  ifdef TPM_ALG_RSA
//*** BnGcd()
// Get the greatest common divisor of two numbers
LIB_EXPORT BOOL BnGcd(bigNum   gcd,      // OUT: the common divisor
                      bigConst number1,  // IN:
                      bigConst number2   // IN:
);

//***BnModExp()
// Do modular exponentiation using BIGNUM values. The conversion from a bignum_t
// to a BIGNUM is trivial as they are based on the same structure
LIB_EXPORT BOOL BnModExp(bigNum   result,    // OUT: the result
                         bigConst number,    // IN: number to exponentiate
                         bigConst exponent,  // IN:
                         bigConst modulus    // IN:
);

//*** BnModInverse()
// Modular multiplicative inverse
LIB_EXPORT BOOL BnModInverse(bigNum result, bigConst number, bigConst modulus);
#  endif  // TPM_ALG_RSA
#  ifdef TPM_ALG_ECC

//*** BnEccModMult()
// This function does a point multiply of the form R = [d]S
// return type: BOOL
//  FALSE       failure in operation; treat as result being point at infinity
LIB_EXPORT BOOL BnEccModMult(bigPoint   R,  // OUT: computed point
                             pointConst S,  // IN: point to multiply by 'd'
                             bigConst   d,  // IN: scalar for [d]S
                             bigCurve   E);

//*** BnEccModMult2()
// This function does a point multiply of the form R = [d]S + [u]Q
// return type: BOOL
//  FALSE       failure in operation; treat as result being point at infinity
LIB_EXPORT BOOL BnEccModMult2(bigPoint   R,  // OUT: computed point
                              pointConst S,  // IN: first point (optional)
                              bigConst   d,  // IN: scalar for [d]S or [d]G
                              pointConst Q,  // IN: second point
                              bigConst   u,  // IN: second scalar
                              bigCurve   E   // IN: curve
);

//*** BnEccAdd()
// This function does addition of two points. Since this is not implemented
// in LibTomCrypt() will try to trick it by doing multiply with scalar of 1.
// I have no idea if this will work and it's not needed unless MQV or the SM2
// variant is enabled.
// return type: BOOL
//  FALSE       failure in operation; treat as result being point at infinity
LIB_EXPORT BOOL BnEccAdd(bigPoint   R,  // OUT: computed point
                         pointConst S,  // IN: point to multiply by 'd'
                         pointConst Q,  // IN: second point
                         bigCurve   E   // IN: curve
);
#  endif  // TPM_ALG_ECC
#endif    // MATH_LIB_LTC

#endif  // _TPM_TO_LTC_MATH_FP_H_
