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
#include "FlushContext_fp.h"

#if CC_FlushContext  // Conditional expansion of this file

/*(See part 3 specification)
// Flush a specific object or session
*/
//  Return Type: TPM_RC
//      TPM_RC_HANDLE      'flushHandle' does not reference a loaded object or session
TPM_RC
TPM2_FlushContext(FlushContext_In* in  // IN: input parameter list
)
{
    // Internal Data Update

    // Call object or session specific routine to flush
    switch(HandleGetType(in->flushHandle))
    {
        case TPM_HT_TRANSIENT:
            if(!IsObjectPresent(in->flushHandle))
                return TPM_RCS_HANDLE + RC_FlushContext_flushHandle;
            // Flush object
            FlushObject(in->flushHandle);
            break;
        case TPM_HT_HMAC_SESSION:
        case TPM_HT_POLICY_SESSION:
            if(!SessionIsLoaded(in->flushHandle) && !SessionIsSaved(in->flushHandle))
                return TPM_RCS_HANDLE + RC_FlushContext_flushHandle;

            // If the session to be flushed is the exclusive audit session, then
            // indicate that there is no exclusive audit session any longer.
            if(in->flushHandle == g_exclusiveAuditSession)
                g_exclusiveAuditSession = TPM_RH_UNASSIGNED;

            // Flush session
            SessionFlush(in->flushHandle);
            break;
        default:
            // This command only takes object or session handle.  Other handles
            // should be filtered out at handle unmarshal
            FAIL(FATAL_ERROR_INTERNAL);
            break;
    }

    return TPM_RC_SUCCESS;
}

#endif  // CC_FlushContext