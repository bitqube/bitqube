 #!/usr/bin/env bash

 # Execute this file to install the bitqube cli tools into your path on OS X

 CURRENT_LOC="$( cd "$(dirname "$0")" ; pwd -P )"
 LOCATION=${CURRENT_LOC%BitQube-Qt.app*}

 # Ensure that the directory to symlink to exists
 sudo mkdir -p /usr/local/bin

 # Create symlinks to the cli tools
 sudo ln -s ${LOCATION}/BitQube-Qt.app/Contents/MacOS/bitqubed /usr/local/bin/bitqubed
 sudo ln -s ${LOCATION}/BitQube-Qt.app/Contents/MacOS/bitqube-cli /usr/local/bin/bitqube-cli
