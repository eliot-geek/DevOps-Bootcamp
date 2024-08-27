#!/bin/bash

scp ../src/cat/s21_cat runner@172.24.116.8:/usr/local/bin/
if [ $? -ne 0 ]; then
    echo "Errors while copying s21_cat."
    exit 1
fi

scp ../src/grep/s21_grep runner@172.24.116.8:/usr/local/bin/
if [ $? -ne 0 ]; then
    echo "Errors while copying s21_grep."
    exit 1
fi
echo "Deployment successful. Here are the contents of /usr/local/bin:"
ssh runner@172.24.116.8 ls -lh /usr/local/bin