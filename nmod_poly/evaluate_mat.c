/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2014 Ashish Kedia

******************************************************************************/

#include <gmp.h>
#include <stdlib.h>
#include <math.h>
#include "flint.h"
#include "ulong_extras.h"
#include "nmod_poly.h"
#include "flint.h"
#include "nmod_mat.h"

void
nmod_mat_one_addmul(nmod_mat_t dest, const nmod_mat_t mat, mp_limb_t c)
{
    slong i, j;

    if (dest == mat)
    {
        for (i = 0; i < mat->r; i++)
        {
            nmod_mat_entry(dest, i, i) =
                n_addmod(nmod_mat_entry(mat, i, i), c, mat->mod.n);
        }
        return;
    }
    for (i = 0; i < mat->r; i++)
        for (j = 0; j < mat->c; j++)
        {
            nmod_mat_entry(dest, i, j) = nmod_mat_entry(mat, i, j);
            if (i == j)
            {
                nmod_mat_entry(dest, i, i) =
                    n_addmod(nmod_mat_entry(dest, i, i), c, mat->mod.n);
            }
        }
}

void
nmod_mat_scaler_mul_add(nmod_mat_t dest, const nmod_mat_t X, const mp_limb_t b,
                        const nmod_mat_t Y)
{
    slong i, j;

    if (b == UWORD(0))
    {
        if (dest != X)
            nmod_mat_set(dest, X);
        return;
    }

    for (i = 0; i < X->r; i++)
    {
        for (j = 0; j < X->c; j++)
        {
            nmod_mat_entry(dest, i, j) =
                n_addmod(nmod_mat_entry(X, i, j),
                         n_mulmod2_preinv(nmod_mat_entry(Y, i, j), b, Y->mod.n,
                                          Y->mod.ninv), X->mod.n);
        }
    }
}

void
nmod_poly_evaluate_mat(nmod_mat_t dest, const nmod_poly_t poly,
                       const nmod_mat_t c)
{
    slong lim = sqrt(poly->length), i, j, rem, quo, curr;
    nmod_mat_t tmat, *temp;

    nmod_mat_zero(dest);

    if (poly->length == 0)
    {
        return;
    }

    if (poly->length == 1 || nmod_mat_is_zero(c))
    {
        nmod_mat_one_addmul(dest, dest, poly->coeffs[0]);
        return;
    }

    temp = malloc((lim + 1) * sizeof(nmod_mat_t));
    nmod_mat_init(temp[0], c->r, c->c, c->mod.n);
    nmod_mat_one(temp[0]);
    nmod_mat_init(tmat, c->r, c->c, c->mod.n);

    for (i = 1; i <= lim; i++)
    {
        nmod_mat_init(temp[i], c->r, c->c, c->mod.n);
        nmod_mat_mul(temp[i], temp[i - 1], c);
    }

    rem = (poly->length % lim);
    quo = poly->length / lim;
    curr = poly->length - rem - 1;

    for (i = 0; i < rem; i++)
    {
        nmod_mat_scaler_mul_add(dest, dest,
                                poly->coeffs[poly->length - rem + i], temp[i]);
    }

    for (i = 0; i < quo; i++)
    {
        nmod_mat_mul(tmat, dest, temp[lim]);
        nmod_mat_scaler_mul_add(dest, tmat, poly->coeffs[curr--],
                                temp[lim - 1]);
        for (j = 1; j < lim; j++)
        {
            nmod_mat_scaler_mul_add(dest, dest, poly->coeffs[curr--],
                                    temp[lim - 1 - j]);
        }
    }

    for (i = 0; i <= lim; i++)
    {
        nmod_mat_clear(temp[i]);
    }
    nmod_mat_clear(tmat);
}
