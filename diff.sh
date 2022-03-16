#!/bin/bash

DIFF=$(diff std_out ft_out)
if ["$DIFF" == ""]
then
    echo "\033[32mOK\033[0m"
else
    echo "\033[0;31mKO\033[0m"
    # echo $DIFF > diff
fi