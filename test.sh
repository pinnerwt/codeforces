#!/usr/bin/env bash
# Usage: ./test.sh [source_file]
# Run from a problem directory (e.g. 2050/a/).
# Compiles sol.cpp (or specified file), runs against all inX.txt,
# and diffs output with ansX.txt.

set -e

SRC="${1:-sol.cpp}"
BIN="./sol"

if [ ! -f "$SRC" ]; then
    echo "Error: $SRC not found in $(pwd)"
    exit 1
fi

echo "Compiling $SRC ..."
g++ -std=c++17 -O2 -o "$BIN" "$SRC"

passed=0
failed=0
total=0

for inf in in*.txt; do
    [ -f "$inf" ] || continue
    num="${inf#in}"
    num="${num%.txt}"
    ansf="ans${num}.txt"

    if [ ! -f "$ansf" ]; then
        echo "Warning: $ansf not found, skipping test $num"
        continue
    fi

    total=$((total + 1))
    outf="out${num}.txt"

    if ! timeout 5 "$BIN" < "$inf" > "$outf" 2>&1; then
        echo "Test $num: RUNTIME ERROR"
        failed=$((failed + 1))
        continue
    fi

    if diff -q --strip-trailing-cr "$outf" "$ansf" > /dev/null 2>&1; then
        echo "Test $num: PASSED"
        passed=$((passed + 1))
    else
        echo "Test $num: FAILED"
        diff --strip-trailing-cr "$outf" "$ansf" | head -20
        echo "---"
        failed=$((failed + 1))
    fi
done

echo ""
echo "Results: $passed/$total passed, $failed failed"

if [ "$failed" -gt 0 ]; then
    exit 1
fi
