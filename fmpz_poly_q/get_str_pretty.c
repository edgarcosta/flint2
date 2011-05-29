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

    Copyright (C) 2010, 2011 Sebastian Pancratz
   
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fmpz_poly_q.h"

/**
 * \ingroup  StringConversions
 * 
 * Returns the pretty string representation of \c op.
 * 
 * Returns the pretty string representation of the rational function \c op, 
 * using the string \c x as the variable name.
 */
char * fmpz_poly_q_get_str_pretty(const fmpz_poly_q_t op, const char *x)
{
    int i, j;
    char * str;
    char * numstr;
    char * denstr;
    
    if (fmpz_poly_is_one(op->den))
    {
        return fmpz_poly_get_str_pretty(op->num, x);
    }
    
    numstr = fmpz_poly_get_str_pretty(op->num, x);
    denstr = fmpz_poly_get_str_pretty(op->den, x);
    
    str = malloc(strlen(numstr) + strlen(denstr) + 6);
    if (!str)
    {
        printf("ERROR (fmpz_poly_q_get_str_pretty).  Memory allocation failed.\n");
        abort();
    }
    
    i = 0;
    if (fmpz_poly_degree(op->num) > 0)
    {
        str[i++] = '(';
        for (j = 0; j < strlen(numstr); j++)
            str[i++] = numstr[j];
        str[i++] = ')';
    }
    else
    {
        for (j = 0; j < strlen(numstr); j++)
            str[i++] = numstr[j];
    }
    str[i++] = '/';
    if (fmpz_poly_degree(op->den) > 0)
    {
        str[i++] = '(';
        for (j = 0; j < strlen(denstr); j++)
            str[i++] = denstr[j];
        str[i++] = ')';
    }
    else
    {
        for (j = 0; j < strlen(denstr); j++)
            str[i++] = denstr[j];
    }
    str[i] = '\0';
    
    free(numstr);
    free(denstr);
    
    return str;
}
