/* crypto/sms4/sms4.h */
/* ====================================================================
 * Copyright (c) 2014 - 2015 The GmSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the GmSSL Project.
 *    (http://gmssl.org/)"
 *
 * 4. The name "GmSSL Project" must not be used to endorse or promote
 *    products derived from this software without prior written
 *    permission. For written permission, please contact
 *    guanzhi1980@gmail.com.
 *
 * 5. Products derived from this software may not be called "GmSSL"
 *    nor may "GmSSL" appear in their names without prior written
 *    permission of the GmSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the GmSSL Project
 *    (http://gmssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE GmSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE GmSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 */

#include <stdio.h>

#ifndef OPENSSL_NO_SM3

#include <openssl/evp.h>
#include <openssl/objects.h>
#include <openssl/x509.h>
#include "sm3.h"


static int init(EVP_MD_CTX *ctx)
{
	return sm3_init(ctx->md_data);
}

static int update(EVP_MD_CTX *ctx, const void *in, size_t inlen)
{
	return sm3_update(ctx->md_data, in, inlen);
}

static int final(EVP_MD_CTX *ctx, unsigned char *md)
{
	return sm3_final(ctx->md_data, md);
}

static const EVP_MD sm3_md = {
  /* note: */
        NID_undef,                      /* TODO: undef??? works */
        NID_undef,
        SM3_DIGEST_LENGTH,
        0,
        init,
        update,
        final,
        NULL,
        NULL,
        /* note: https://wiki.openssl.org/index.php/Creating_an_OpenSSL_Engine_to_use_indigenous_ECDH_ECDSA_and_HASH_Algorithms#Digests */
        EVP_PKEY_NULL_method,/* {NID_undef, NID_undef, 0, 0, 0}, */
        SM3_BLOCK_SIZE,
        sizeof(sm3_ctx_t),
        NULL
        /* SM3_BLOCK_SIZE, */
        /* sizeof(EVP_MD *) + sizeof(sm3_ctx_t), */
};

const EVP_MD *EVP_sm3(void)
{
  return (&sm3_md);
}

#endif
