#! /bin/bash

echo "Hi $USER"

case $1 in
    sim)
        cd bin/simulation
        rm -r *
        cmake -DSIM=on ../..
        make
    ;;
    arduino)
        cd bin/arduino
        rm -r *
        cmake -DSIM=off ../..
        make
    ;;
    *)
echo Need correct input
;;
esac
