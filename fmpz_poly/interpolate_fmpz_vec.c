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

    Copyright (C) 2011 Fredrik Johansson

******************************************************************************/

#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_poly.h"
#include "fmpq_poly.h"

void
fmpz_poly_interpolate_fmpz_vec(fmpz_poly_t poly,
                                    const fmpz * xs, const fmpz * ys, long n)
{
    if (n == 0)
    {
        fmpz_poly_zero(poly);
        return;
    }
    else if (n == 1)
    {
        fmpz_poly_set_fmpz(poly, ys);
        return;
    }
    else
    {
        fmpz_t den;
        fmpz_init(den);
        fmpz_poly_fit_length(poly, n);
        _fmpq_poly_interpolate_fmpz_vec(poly->coeffs, den, xs, ys, n);
        _fmpz_vec_scalar_divexact_fmpz(poly->coeffs, poly->coeffs, n, den);
        _fmpz_poly_set_length(poly, n);
        _fmpz_poly_normalise(poly);
        fmpz_clear(den);
    }
}
