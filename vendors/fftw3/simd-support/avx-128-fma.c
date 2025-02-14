/*
 * Copyright (c) 2003, 2007-14 Matteo Frigo
 * Copyright (c) 2003, 2007-14 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 */

#include "kernel/ifftw.h"

#if HAVE_AVX_128_FMA

#if defined(__x86_64__) || defined(_M_X64) || defined(_M_AMD64)
#include "amd64-cpuid.h"
#else
#include "x86-cpuid.h"
#endif

int X(have_simd_avx_128_fma)(void) {
  static int init = 0, res = 0;
  int eax, ebx, ecx, edx;

  if (!init) {
    /* Check if this is an AMD CPU */
    cpuid_all(0, 0, &eax, &ebx, &ecx, &edx);

    /* 0x68747541: "Auth"  , 0x444d4163: "enti"  , 0x69746e65: "cAMD" */
    if (ebx == 0x68747541 && ecx == 0x444d4163 && edx == 0x69746e65) {
      /* OK, this is an AMD CPU. Check if we support FMA4 */
      cpuid_all(0x80000001, 0, &eax, &ebx, &ecx, &edx);
      if (ecx & (1 << 16)) {
        res = 1;
      }
    }
    init = 1;
  }
  return res;
}

#endif
