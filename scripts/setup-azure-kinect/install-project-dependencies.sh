#!/usr/bin/env bash

# dependencies-installer.sh:
#     Install necessary dependencies iff not available.
#
# author: Everett
# created: 2020-11-06 13:53
# Github: https://github.com/antiqueeverett/

xargs -a <(awk '! /^ *(#|$)/' "dependencies.txt") -r -- sudo apt-get -y install
sudo update-ca-certificates
sudo apt update
