/*************************************************************************
 *                                                                       *
 * Open Dynamics Engine, Copyright (C) 2001,2002 Russell L. Smith.       *
 * All rights reserved.  Email: russ@q12.org   Web: www.q12.org          *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of EITHER:                                  *
 *   (1) The GNU Lesser General Public License as published by the Free  *
 *       Software Foundation; either version 2.1 of the License, or (at  *
 *       your option) any later version. The text of the GNU Lesser      *
 *       General Public License is included with this library in the     *
 *       file LICENSE.TXT.                                               *
 *   (2) The BSD-style license that is included with this library in     *
 *       the file LICENSE-BSD.TXT.                                       *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files    *
 * LICENSE.TXT and LICENSE-BSD.TXT for more details.                     *
 *                                                                       *
 *************************************************************************/

/* 
 * optimized and unoptimized vector and matrix functions 
 * (inlined private versions)
 */

#ifndef _ODE__PRIVATE_MATRIX_H_
#define _ODE__PRIVATE_MATRIX_H_


#include "ode_matrix.hpp"


#ifdef __cplusplus

template <unsigned a_stride, typename element_type>
ODE_INLINE
void dxtSetZero (element_type *a, sizeint n)
{
    element_type *const aend = a + n * a_stride;
    for (element_type *acurr = a; acurr != aend; acurr += a_stride) {
        *acurr = (element_type)0;
    }
}

template <typename element_type>
ODE_INLINE
void dxSetZero (element_type *a, sizeint n)
{
    dxtSetZero<1>(a, n);
}

template <typename element_type>
ODE_INLINE
void dxSetValue (element_type *a, sizeint n, element_type value)
{
    element_type *const aend = a + n;
    for (element_type *acurr = a; acurr != aend; ++acurr) {
        *acurr = value;
    }
}


#else // #ifndef __cplusplus

ODE_PURE_INLINE
void dxSetZero (dReal *a, sizeint n)
{
    dReal *const aend = a + n;
    dReal *acurr;
    for (acurr = a; acurr != aend; ++acurr) {
        *acurr = 0;
    }
}

ODE_PURE_INLINE
void dxSetValue (dReal *a, sizeint n, dReal value)
{
    dReal *const aend = a + n;
    dReal *acurr;
    for (acurr = a; acurr != aend; ++acurr) {
        *acurr = value;
    }
}


#endif // #ifdef __cplusplus


ODE_PURE_INLINE
dReal dxCalculateModuloMaximum(const dReal *valueStorage, sizeint valueCount)
{
    dIASSERT(valueCount != 0);

    dReal moduleMaximum = dFabs(*valueStorage);

    const dReal *const storageEnd = valueStorage + valueCount;
    for (const dReal *currentValue = valueStorage + 1; currentValue != storageEnd; ++currentValue) {
        moduleMaximum = dMax(moduleMaximum, dFabs(*currentValue));
    }

    return moduleMaximum;
}


dReal dxDot (const dReal *a, const dReal *b, unsigned n);
void dxMultiply0 (dReal *A, const dReal *B, const dReal *C, unsigned p, unsigned q, unsigned r);
void dxMultiply1 (dReal *A, const dReal *B, const dReal *C, unsigned p, unsigned q, unsigned r);
void dxMultiply2 (dReal *A, const dReal *B, const dReal *C, unsigned p, unsigned q, unsigned r);
int dxFactorCholesky (dReal *A, unsigned n, void *tmpbuf);
void dxSolveCholesky (const dReal *L, dReal *b, unsigned n, void *tmpbuf);
int dxInvertPDMatrix (const dReal *A, dReal *Ainv, unsigned n, void *tmpbuf);
int dxIsPositiveDefinite (const dReal *A, unsigned n, void *tmpbuf);
void dxLDLTAddTL (dReal *L, dReal *d, const dReal *a, unsigned n, unsigned nskip, void *tmpbuf);
void dxLDLTRemove (dReal **A, const unsigned *p, dReal *L, dReal *d, unsigned n1, unsigned n2, unsigned r, unsigned nskip, void *tmpbuf);
void dxRemoveRowCol (dReal *A, unsigned n, unsigned nskip, unsigned r);

ODE_PURE_INLINE sizeint dxEstimateFactorCholeskyTmpbufSize(unsigned n)
{
    return dPAD(n) * sizeof(dReal);
}

ODE_PURE_INLINE sizeint dxEstimateSolveCholeskyTmpbufSize(unsigned n)
{
    return dPAD(n) * sizeof(dReal);
}

ODE_PURE_INLINE sizeint dxEstimateInvertPDMatrixTmpbufSize(unsigned n)
{
    sizeint FactorCholesky_size = dxEstimateFactorCholeskyTmpbufSize(n);
    sizeint SolveCholesky_size = dxEstimateSolveCholeskyTmpbufSize(n);
    sizeint MaxCholesky_size = FactorCholesky_size > SolveCholesky_size ? FactorCholesky_size : SolveCholesky_size;
    return (sizeint)dPAD(n) * (n + 1) * sizeof(dReal) + MaxCholesky_size;
}

ODE_PURE_INLINE sizeint dxEstimateIsPositiveDefiniteTmpbufSize(unsigned n)
{
    return (sizeint)dPAD(n) * n * sizeof(dReal) + dxEstimateFactorCholeskyTmpbufSize(n);
}

ODE_PURE_INLINE sizeint dxEstimateLDLTAddTLTmpbufSize(unsigned nskip)
{
    return nskip * (2 * sizeof(dReal));
}

ODE_PURE_INLINE sizeint dxEstimateLDLTRemoveTmpbufSize(unsigned n2, unsigned nskip)
{
    return n2 * sizeof(dReal) + dxEstimateLDLTAddTLTmpbufSize(nskip);
}

/* For internal use */
#define dSetZero(a, n) dxSetZero(a, n)
#define dSetValue(a, n, value) dxSetValue(a, n, value)
#define dDot(a, b, n) dxDot(a, b, n)
#define dMultiply0(A, B, C, p, q, r) dxMultiply0(A, B, C, p, q, r)
#define dMultiply1(A, B, C, p, q, r) dxMultiply1(A, B, C, p, q, r)
#define dMultiply2(A, B, C, p, q, r) dxMultiply2(A, B, C, p, q, r)
#define dFactorCholesky(A, n, tmpbuf) dxFactorCholesky(A, n, tmpbuf)
#define dSolveCholesky(L, b, n, tmpbuf) dxSolveCholesky(L, b, n, tmpbuf)
#define dInvertPDMatrix(A, Ainv, n, tmpbuf) dxInvertPDMatrix(A, Ainv, n, tmpbuf)
#define dIsPositiveDefinite(A, n, tmpbuf) dxIsPositiveDefinite(A, n, tmpbuf)
#define dLDLTAddTL(L, d, a, n, nskip, tmpbuf) dxLDLTAddTL(L, d, a, n, nskip, tmpbuf)
#define dLDLTRemove(A, p, L, d, n1, n2, r, nskip, tmpbuf) dxLDLTRemove(A, p, L, d, n1, n2, r, nskip, tmpbuf)
#define dRemoveRowCol(A, n, nskip, r) dxRemoveRowCol(A, n, nskip, r)


#define dEstimateFactorCholeskyTmpbufSize(n) dxEstimateFactorCholeskyTmpbufSize(n)
#define dEstimateSolveCholeskyTmpbufSize(n) dxEstimateSolveCholeskyTmpbufSize(n)
#define dEstimateInvertPDMatrixTmpbufSize(n) dxEstimateInvertPDMatrixTmpbufSize(n)
#define dEstimateIsPositiveDefiniteTmpbufSize(n) dxEstimateIsPositiveDefiniteTmpbufSize(n)
#define dEstimateLDLTAddTLTmpbufSize(nskip) dxEstimateLDLTAddTLTmpbufSize(nskip)
#define dEstimateLDLTRemoveTmpbufSize(n2, nskip) dxEstimateLDLTRemoveTmpbufSize(n2, nskip)


#endif // #ifndef _ODE__PRIVATE_MATRIX_H_
