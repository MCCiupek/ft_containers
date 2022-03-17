#!/bin/bash

mkfile="Makefile"
search="main"
SEED=42
HEAD="test\t\t\tcompil\tft\tstd\tdiff"

get_compil () {
    make 2> _logs
    if [ -s _logs ]; then
        printf "\033[0;31mKO\033[0m\t"
    else
        printf "\033[32mOK\033[0m\t"
    fi
}

get_time () {
    T="$(date +%s)"
    ./$1 $SEED > $2
    T="$(($(date +%s)-T))"
    printf "$T\t"
}

get_diff () {
    diff $1 $2 > _diff
    if [ -s _diff ]; then
        printf "\033[0;31mKO\033[0m\n"
    else
        printf "\033[32mOK\033[0m\n"
    fi
    rm _diff
}

run_test () {
    sed -i "" s/$search/$1/g $mkfile
    get_compil
    [ -s _logs ] && printf "x\t" || get_time test_ft ft_out
    [ -s _logs ] && printf "x\t" || get_time test_std std_out
    [ -s _logs ] && printf "x\n" || get_diff std_out ft_out
    # rm _logs
    sed -i "" s/$1/$search/g $mkfile
}

all () {

    cd srcs

    echo $HEAD

    for FILE in *.cpp; do 
        printf "%-10s\t\t" "${FILE%.*}"
        cd ..
        run_test ${FILE%.*}
        cd srcs
    done

    for REPO in */; do
        cd $REPO;
        
        echo "\n$REPO" | sed 's/.$//'
        echo $HEAD

        sed -i "#" "s#./srcs/#./srcs/$REPO#g" ../../$mkfile

        for FILE in *.cpp; do
            printf "%-10s\t\t" "${FILE%.*}"
            cd ../..
            run_test ${FILE%.*}
            cd srcs/$REPO
        done
        
        sed -i "#" "s#./srcs/$REPO#./srcs/#g" ../../$mkfile

        cd ..
    done

    cd ..

}

container () {

    cd srcs

    for REPO in */; do
        if [ $1/ = $REPO ]; then
            cd $REPO;
            
            echo "$REPO" | sed 's/.$//'
            echo $HEAD

            sed -i "#" "s#./srcs/#./srcs/$REPO#g" ../../$mkfile

            for FILE in *.cpp;
                do printf "%-10s\t\t" "${FILE%.*}"
                cd ../..
                run_test ${FILE%.*}
                cd srcs/$REPO
                done
            
            sed -i "#" "s#./srcs/$REPO#./srcs/#g" ../../$mkfile

        fi
    done

    cd ..

}

make fclean

if [ -z "$1" ]; then
    all
else
    for CONT in $@; do
        container $CONT
    done
fi

rm -rf "$mkfile#"
