#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

BITQUBED=${BITQUBED:-$SRCDIR/bitqubed}
BITQUBECLI=${BITQUBECLI:-$SRCDIR/bitqube-cli}
BITQUBETX=${BITQUBETX:-$SRCDIR/bitqube-tx}
BITQUBEQT=${BITQUBEQT:-$SRCDIR/qt/bitqube-qt}

[ ! -x $BITQUBED ] && echo "$BITQUBED not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
BTQVER=($($BITQUBECLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for bitqubed if --version-string is not set,
# but has different outcomes for bitqube-qt and bitqube-cli.
echo "[COPYRIGHT]" > footer.h2m
$BITQUBED --version | sed -n '1!p' >> footer.h2m

for cmd in $BITQUBED $BITQUBECLI $BITQUBETX $BITQUBEQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${BTQVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${BTQVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
