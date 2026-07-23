// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2017-2019 The BitQube Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITQUBE_AMOUNT_H
#define BITQUBE_AMOUNT_H

#include <stdint.h>

/** Amount in Bits, the smallest BitQube unit (1 BTQ = 100,000,000 Bits). Can be negative. */
typedef int64_t CAmount;

static const CAmount COIN = 100000000;
static const CAmount CENT = 1000000;

/** No amount larger than this (in satoshi) is valid.
 *
 * Note that this constant is *not* the total money supply, which in BitQube is
 * capped at 8,000,000 BTQ (7,358,400 BTQ mined across 8 phases = 91.98% + 641,600
 * BTQ Ecosystem Reserve premine = 8.02% of the cap), but rather a sanity check. As
 * this sanity check is used by consensus-critical validation code, the exact
 * value of the MAX_MONEY constant is consensus critical; in unusual
 * circumstances like a(nother) overflow bug that allowed for the creation of
 * coins out of thin air modification could lead to a fork.
 * */
static const CAmount MAX_MONEY = 8000000 * COIN;
inline bool MoneyRange(const CAmount& nValue) { return (nValue >= 0 && nValue <= MAX_MONEY); }

#endif //  BITQUBE_AMOUNT_H
