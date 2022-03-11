#!/bin/bash

DIFF=$(diff std_out ft_out)
if [ "$DIFF" == "" ]
then
    echo "\033[32mDIFF OK\033[0m"
else
    echo "\033[0;31mDIFF KO\033[0m"
    echo $DIFF > diff
fi