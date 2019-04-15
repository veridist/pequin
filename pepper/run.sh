#!/bin/bash

if [ $# -eq 2 ]
then
    file_name=$1
    compile=1
elif [ $# -eq 1 ]
then
    file_name=$1
    compile=0
else
    file_name=""
    echo "Usage : ./run.sh <file_name> [compile]"
fi

if [ "$file_name" != "" ]
then
    if [ $compile -eq 1 ]
    then
         echo "################# Compiling verifier ############################"
         ./pepper_compile_and_setup_V.sh $file_name $file_name.vkey $file_name.pkey

        echo "################# Compiling prover############################"
        ./pepper_compile_and_setup_P.sh $file_name
    fi

     #echo "################# Generating inputs ############################"
     #./bin/pepper_verifier_$file_name gen_input $file_name.inputs

     #echo "################# Running partial prover ############################"
     #./bin/pepper_partial_prover_$file_name ./bin/$file_name.params ./bin/$file_name.pws ./prover_verifier_shared/$file_name.inputs ./prover_verifier_shared/$file_name.partial

     echo "################# Running prover ############################"
     ./bin/pepper_prover_$file_name prove $file_name.pkey $file_name.inputs $file_name.outputs $file_name.proof

     echo "################# Running verifier ############################"
     ./bin/pepper_verifier_$file_name verify $file_name.vkey $file_name.inputs $file_name.outputs  $file_name.proof
fi
