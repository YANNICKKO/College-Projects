#!/bin/bash

fail() {
    echo "[ERROR] $1"
    exit 1
}

if [ ! -e Makefile ]; then
    fail "Makefile not found"
fi

make 1>/dev/null || exit 1

if [ ! -e checker ]; then
    fail "checker not found"
fi

if [ ! -e tests/in ]; then
    fail "tests/in not found"
fi

if [ ! -e tests/out ]; then
    mkdir tests/out
fi

if [ ! -e tests/ref ]; then
    fail "tests/ref not found"
fi

echo "====================== Task 3 ======================="

total=0
for i in 1 2 3 4 5; do
    ./checker < "tests/in/${i}.in" | xargs > "tests/out/${i}.out"
    out=$(diff "tests/ref/${i}.ref" "tests/out/${i}.out" 2>&1)

    if [ -z "$out" ]; then
        total=$(( total + 5 ))
        echo "Test ${i}					  5.00p/5.00p"
    else
        echo "Test ${i}					  0.00p/5.00p"
	echo "$out"
    fi
done

echo
printf "Total score:				%5.2fp/25.00p\n" ${total}

echo "task-3:${total}" >> ../../.results