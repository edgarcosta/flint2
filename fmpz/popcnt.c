#include <mpir.h>
#include "flint.h"
#include "ulong_extras.h"
#include "fmpz.h"

#ifdef POPCNT_INTRINSICS
static __inline__ mp_bitcnt_t shortCount(const long long val)
{
        return __builtin_popcountll(val);
}
#else
/* A naive implementation if neither your processor nor your compiler want to
 * do the work. */
static __inline__ mp_bitcnt_t shortCount(const long long val)
{
        mp_bitcnt_t cnt;
        for(cnt=0; val; val >> 1) {
                cnt += val & 1
        }
        return cnt;
}
#endif

mp_bitcnt_t fmpz_popcnt(const fmpz_t c)
{
        fmpz c1;
        c1 = *c;
        if(!COEFF_IS_MPZ(c1))
        {
                return shortCount(*c);
        } else
        {
                __mpz_struct *t = COEFF_TO_PTR(c1);
                return mpz_popcount(t);
        }
}
