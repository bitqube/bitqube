// Copyright (c) 2011-2016 The Bitcoin Core developers
// Copyright (c) 2017-2019 The BitQube Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "bitqubeunits.h"

#include "primitives/transaction.h"

#include <QStringList>

BitQubeUnits::BitQubeUnits(QObject *parent):
        QAbstractListModel(parent),
        unitlist(availableUnits())
{
}

QList<BitQubeUnits::Unit> BitQubeUnits::availableUnits()
{
    QList<BitQubeUnits::Unit> unitlist;
    unitlist.append(BTQ);
    unitlist.append(mBTQ);
    unitlist.append(uBTQ);
    unitlist.append(Bit);
    return unitlist;
}

bool BitQubeUnits::valid(int unit)
{
    switch(unit)
    {
    case BTQ:
    case mBTQ:
    case uBTQ:
    case Bit:
        return true;
    default:
        return false;
    }
}

QString BitQubeUnits::name(int unit)
{
    switch(unit)
    {
    case BTQ: return QString("BTQ");
    case mBTQ: return QString("mBTQ");
    case uBTQ: return QString::fromUtf8("μBTQ");
    case Bit: return QString("Bit");
    default: return QString("???");
    }
}

QString BitQubeUnits::description(int unit)
{
    switch(unit)
    {
    case BTQ: return QString("BitQubes");
    case mBTQ: return QString("Milli-BitQubes (1 / 1" THIN_SP_UTF8 "000)");
    case uBTQ: return QString("Micro-BitQubes (1 / 1" THIN_SP_UTF8 "000" THIN_SP_UTF8 "000)");
    case Bit: return QString("Bits (1 / 100" THIN_SP_UTF8 "000" THIN_SP_UTF8 "000)");
    default: return QString("???");
    }
}

qint64 BitQubeUnits::factor(int unit)
{
    switch(unit)
    {
    case BTQ:  return 100000000;
    case mBTQ: return 100000;
    case uBTQ: return 100;
    case Bit:  return 1;
    default:   return 100000000;
    }
}

qint64 BitQubeUnits::factorAsset(int unit)
{
    switch(unit)
    {
        case 0:  return 1;
        case 1: return 10;
        case 2: return 100;
        case 3: return 1000;
        case 4: return 10000;
        case 5: return 100000;
        case 6: return 1000000;
        case 7: return 10000000;
        case 8: return 100000000;
        default:   return 100000000;
    }
}

int BitQubeUnits::decimals(int unit)
{
    switch(unit)
    {
    case BTQ: return 8;
    case mBTQ: return 5;
    case uBTQ: return 2;
    case Bit: return 0;
    default: return 0;
    }
}

QString BitQubeUnits::format(int unit, const CAmount& nIn, bool fPlus, SeparatorStyle separators, const int nAssetUnit)
{
    // Note: not using straight sprintf here because we do NOT want
    // localized number formatting.
    if((nAssetUnit < 0 || nAssetUnit > 8) && !valid(unit))
        return QString(); // Refuse to format invalid unit
    qint64 n = (qint64)nIn;
    qint64 coin = nAssetUnit >= 0 ? factorAsset(nAssetUnit) : factor(unit);
    int num_decimals = nAssetUnit >= 0 ? nAssetUnit : decimals(unit);
    qint64 n_abs = (n > 0 ? n : -n);
    qint64 quotient = n_abs / coin;
    qint64 remainder = n_abs % coin;
    QString quotient_str = QString::number(quotient);
    QString remainder_str = QString::number(remainder).rightJustified(num_decimals, '0');

    // Use SI-style thi
    // n space separators as these are locale independent and can't be
    // confused with the decimal marker.
    QChar thin_sp(THIN_SP_CP);
    int q_size = quotient_str.size();
    if (separators == separatorAlways || (separators == separatorStandard && q_size > 4))
        for (int i = 3; i < q_size; i += 3)
            quotient_str.insert(q_size - i, thin_sp);

    if (n < 0)
        quotient_str.insert(0, '-');
    else if (fPlus && n > 0)
        quotient_str.insert(0, '+');

    if (nAssetUnit == MIN_ASSET_UNITS)
        return quotient_str;


    return quotient_str + QString(".") + remainder_str;
}


// NOTE: Using formatWithUnit in an HTML context risks wrapping
// quantities at the thousands separator. More subtly, it also results
// in a standard space rather than a thin space, due to a bug in Qt's
// XML whitespace canonicalisation
//
// Please take care to use formatHtmlWithUnit instead, when
// appropriate.

QString BitQubeUnits::formatWithUnit(int unit, const CAmount& amount, bool plussign, SeparatorStyle separators)
{
    return format(unit, amount, plussign, separators) + QString(" ") + name(unit);
}

QString BitQubeUnits::formatWithCustomName(QString customName, const CAmount& amount, int unit, bool plussign, SeparatorStyle separators)
{
    return format(BTQ, amount / factorAsset(MAX_ASSET_UNITS - unit), plussign, separators, unit) + QString(" ") + customName;
}

QString BitQubeUnits::formatHtmlWithUnit(int unit, const CAmount& amount, bool plussign, SeparatorStyle separators)
{
    QString str(formatWithUnit(unit, amount, plussign, separators));
    str.replace(QChar(THIN_SP_CP), QString(THIN_SP_HTML));
    return QString("<span style='white-space: nowrap;'>%1</span>").arg(str);
}


bool BitQubeUnits::parse(int unit, const QString &value, CAmount *val_out)
{
    if(!valid(unit) || value.isEmpty())
        return false; // Refuse to parse invalid unit or empty string
    int num_decimals = decimals(unit);

    // Ignore spaces and thin spaces when parsing
    QStringList parts = removeSpaces(value).split(".");

    if(parts.size() > 2)
    {
        return false; // More than one dot
    }
    QString whole = parts[0];
    QString decimals;

    if(parts.size() > 1)
    {
        decimals = parts[1];
    }
    if(decimals.size() > num_decimals)
    {
        return false; // Exceeds max precision
    }
    bool ok = false;
    QString str = whole + decimals.leftJustified(num_decimals, '0');

    if(str.size() > 18)
    {
        return false; // Longer numbers will exceed 63 bits
    }
    CAmount retvalue(str.toLongLong(&ok));
    if(val_out)
    {
        *val_out = retvalue;
    }
    return ok;
}

bool BitQubeUnits::assetParse(int assetUnit, const QString &value, CAmount *val_out)
{
    if(!(assetUnit >= 0 && assetUnit <= 8) || value.isEmpty())
        return false; // Refuse to parse invalid unit or empty string
    int num_decimals = assetUnit;

    // Ignore spaces and thin spaces when parsing
    QStringList parts = removeSpaces(value).split(".");

    if(parts.size() > 2)
    {
        return false; // More than one dot
    }
    QString whole = parts[0];
    QString decimals;

    if(parts.size() > 1)
    {
        decimals = parts[1];
    }
    if(decimals.size() > num_decimals)
    {
        return false; // Exceeds max precision
    }
    bool ok = false;
    QString str = whole + decimals.leftJustified(num_decimals, '0');

    if(str.size() > 18)
    {
        return false; // Longer numbers will exceed 63 bits
    }
    CAmount retvalue(str.toLongLong(&ok));
    if(val_out)
    {
        *val_out = retvalue;
    }
    return ok;
}

QString BitQubeUnits::getAmountColumnTitle(int unit)
{
    QString amountTitle = QObject::tr("Amount");
    if (BitQubeUnits::valid(unit))
    {
        amountTitle += " ("+BitQubeUnits::name(unit) + ")";
    }
    return amountTitle;
}

int BitQubeUnits::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return unitlist.size();
}

QVariant BitQubeUnits::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row >= 0 && row < unitlist.size())
    {
        Unit unit = unitlist.at(row);
        switch(role)
        {
        case Qt::EditRole:
        case Qt::DisplayRole:
            return QVariant(name(unit));
        case Qt::ToolTipRole:
            return QVariant(description(unit));
        case UnitRole:
            return QVariant(static_cast<int>(unit));
        }
    }
    return QVariant();
}

CAmount BitQubeUnits::maxMoney()
{
    return MAX_MONEY;
}
