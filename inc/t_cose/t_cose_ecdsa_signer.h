//
//  t_cose_ecdsa_signer.h
//  t_cose_test
//
//  Created by Laurence Lundblade on 5/23/22.
//  Copyright © 2022 Laurence Lundblade. All rights reserved.
//

#ifndef t_cose_ecdsa_signer_h
#define t_cose_ecdsa_signer_h

#include "t_cose/t_cose_signer.h"
#include "t_cose/t_cose_common.h"
#include "t_cose/t_cose_parameters.h"
#include "t_cose_crypto.h"


struct t_cose_ecdsa_signer {
    /* Private data structure */

    /* t_cose_signer must be the first item for the polymorphism to work.
     * This structure, t_cose_ecdsa_signer, will sometimes be uses as a t_cose_signer.
     */
    struct t_cose_signer s;

    /* The rest of this is mostly specific to ECDSA signing */
    int32_t               cose_algorithm_id;
    struct t_cose_key     signing_key;
    uint32_t              option_flags;
    struct q_useful_buf_c kid;
    const struct t_cose_header_param  *added_signer_params;
};


void
t_cose_ecdsa_signer_init(struct t_cose_ecdsa_signer *context,
                         int32_t                     cose_algorithm_id);


/*
 * Set the signing key for the particular signer
 */
static void
t_cose_ecdsa_signer_set_signing_key(struct t_cose_ecdsa_signer *context,
                                    struct t_cose_key             signing_key,
                                    struct q_useful_buf_c         kid);

/* The header parameter for the algorithm ID is generated automatically.
   and should not be added in this list.  The kid will be generated
   automatically if it not NULL when set_signing_key is called.
 */
static void
t_cose_ecdsa_signer_set_header_parameter(struct t_cose_ecdsa_signer *context,
                                    const struct t_cose_header_param * header_parameters);


/* This is how you get the general interface / instance for a signer,
 * a t_cose_signer, from the specific and concrete instance of a
 * signer. Because the t_cose_signer is the first member in a
 * t_cose_ecdsa_signer, the implementation for this is in essence just a
 * cast and in the end no code is generated.
 */
static struct t_cose_signer *
t_cose_signer_from_ecdsa_signer(struct t_cose_ecdsa_signer *me);



/* =========================================================================
 BEGINNING OF PRIVATE INLINE IMPLEMENTATION
 ========================================================================= */

static inline void
t_cose_ecdsa_signer_set_signing_key(struct t_cose_ecdsa_signer *context,
                                    struct t_cose_key             signing_key,
                                    struct q_useful_buf_c         kid)
{
    context->signing_key = signing_key;
    context->kid         = kid;

}



static inline struct t_cose_signer *
t_cose_signer_from_ecdsa_signer(struct t_cose_ecdsa_signer *me)
{
    /* Because s is the first item in the t_cose_ecdsa_signer, this function should
     * compile to nothing. It is here to keep the type checking safe.
     */
    return &(me->s);
}

static void
t_cose_ecdsa_signer_set_header_parameter(struct t_cose_ecdsa_signer *me,
                                    const struct t_cose_header_param * header_parameters)
{
    me->added_signer_params = header_parameters;
}

#endif /* t_cose_ecdsa_signer_h */
