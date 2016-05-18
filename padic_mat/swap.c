/*
    Copyright (C) 2011 Sebastian Pancratz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "fmpz_mat.h"
#include "padic_mat.h"

void padic_mat_swap(padic_mat_t A, padic_mat_t B)
{
    slong t;

    fmpz_mat_swap(padic_mat(A), padic_mat(B));

    t         = A->val;
    A->val = B->val;
    B->val = t;
}

