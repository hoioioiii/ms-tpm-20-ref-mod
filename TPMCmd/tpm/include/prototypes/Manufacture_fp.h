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
 *  Date: Mar  4, 2020  Time: 02:36:44PM
 */

#ifndef _MANUFACTURE_FP_H_
#define _MANUFACTURE_FP_H_

//*** TPM_Manufacture()
// This function initializes the TPM values in preparation for the TPM's first
// use. This function will fail if previously called. The TPM can be re-manufactured
// by calling TPM_Teardown() first and then calling this function again.
//  Return Type: int
//      -1          failure
//      0           success
//      1           manufacturing process previously performed
LIB_EXPORT int TPM_Manufacture(
    int firstTime  // IN: indicates if this is the first call from
                   //     main()
);

//*** TPM_TearDown()
// This function prepares the TPM for re-manufacture. It should not be implemented
// in anything other than a simulated TPM.
//
// In this implementation, all that is needs is to stop the cryptographic units
// and set a flag to indicate that the TPM can be re-manufactured. This should
// be all that is necessary to start the manufacturing process again.
//  Return Type: int
//      0        success
//      1        TPM not previously manufactured
LIB_EXPORT int TPM_TearDown(void);

//*** TpmEndSimulation()
// This function is called at the end of the simulation run. It is used to provoke
// printing of any statistics that might be needed.
LIB_EXPORT void TpmEndSimulation(void);

#endif  // _MANUFACTURE_FP_H_
