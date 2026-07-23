
Debian
====================
This directory contains files used to package bitqubed/bitqube-qt
for Debian-based Linux systems. If you compile bitqubed/bitqube-qt yourself, there are some useful files here.

## bitqube: URI support ##


bitqube-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bitqube-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bitqube-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitqube128.png` to `/usr/share/pixmaps`

bitqube-qt.protocol (KDE)

