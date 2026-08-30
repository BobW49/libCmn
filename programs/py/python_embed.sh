#!/bin/sh

# This is how to get everything needed to embed python
# in one of my programs.

# get version
python --version

# get cflags
python3.13-config --cflags

# get ldflags
python3.13-config --ldflags --embed
