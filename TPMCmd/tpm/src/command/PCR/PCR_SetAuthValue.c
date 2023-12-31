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
#include "Tpm.h"
#include "PCR_SetAuthValue_fp.h"

#if CC_PCR_SetAuthValue  // Conditional expansion of this file

/*(See part 3 specification)
// Set authValue to a group of PCR
*/
//  Return Type: TPM_RC
//      TPM_RC_VALUE                PCR referenced by 'pcrHandle' is not a member
//                                  of a PCR authorization group
TPM_RC
TPM2_PCR_SetAuthValue(PCR_SetAuthValue_In* in  // IN: input parameter list
)
{
    UINT32 groupIndex;
    // Input Validation:

    // If PCR does not belong to an auth group, return TPM_RC_VALUE
    if(!PCRBelongsAuthGroup(in->pcrHandle, &groupIndex))
        return TPM_RC_VALUE;

    // The command may cause the orderlyState to be cleared due to the update of
    // state clear data.  If this is the case, Check if NV is available.
    // A TPM_RC_NV_UNAVAILABLE or TPM_RC_NV_RATE error may be returned at
    // this point
    RETURN_IF_ORDERLY;

    // Internal Data Update

    // Set PCR authValue
    MemoryRemoveTrailingZeros(&in->auth);
    gc.pcrAuthValues.auth[groupIndex] = in->auth;

    return TPM_RC_SUCCESS;
}

#endif  // CC_PCR_SetAuthValue