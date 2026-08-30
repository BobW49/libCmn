#!/bin/bash
# vi:nu:et:sts=4 ts=4 sw=4

genMake libJson01.txt
mv Makefile_macos64_x86_64.txt libJson01_macos64_x86_64.txt

genMake libJson02.txt
mv Makefile_macos64_x86_64.txt libJson02_macos64_x86_64.txt

genMake pgmJson01.txt
mv Makefile_macos64_x86_64.txt pgmJson01_macos64_x86_64.txt


