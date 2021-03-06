/*
    Copyright (C) 2013 Mike Hansen

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#ifdef T

#include "templates.h"

void
TEMPLATE(T, mat_mul) (TEMPLATE(T, mat_t) C,
                      const TEMPLATE(T, mat_t) A,
                      const TEMPLATE(T, mat_t) B, const TEMPLATE(T, ctx_t) ctx)
{
    if (TEMPLATE(CAP_T, MAT_MUL_KS_CUTOFF) (A->r, B->c, ctx))
        TEMPLATE(T, mat_mul_KS) (C, A, B, ctx);
    else
        TEMPLATE(T, mat_mul_classical) (C, A, B, ctx);
}


#endif
