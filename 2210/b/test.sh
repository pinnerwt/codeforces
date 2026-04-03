#!/usr/bin/env bash
# Usage:
#   ./test.sh           - compile and test the .cpp file in current directory
#   ./test.sh next      - cd to next problem directory
#   ./test.sh a/b/c1/d2 - cd to that problem directory

set -e

# --- Navigation ---
if [ $# -ge 1 ]; then
    arg="${1,,}"  # lowercase

    # Find contest dir (parent of current problem dir)
    contest_dir="$(dirname "$(pwd)")"

    if [ "$arg" = "next" ]; then
        order_file="$contest_dir/order.txt"
        if [ ! -f "$order_file" ]; then
            echo "Error: order.txt not found in $contest_dir"
            exit 1
        fi
        current="$(basename "$(pwd)")"
        found=0
        next=""
        while IFS= read -r line; do
            if [ "$found" -eq 1 ]; then
                next="$line"
                break
            fi
            if [ "$line" = "$current" ]; then
                found=1
            fi
        done < "$order_file"
        if [ -z "$next" ]; then
            echo "No next problem after '$current'"
            exit 0
        fi
        target="$contest_dir/$next"
    else
        target="$contest_dir/$arg"
    fi

    if [ ! -d "$target" ]; then
        echo "Error: directory $target not found"
        exit 1
    fi

    echo ">> Entering $(basename "$contest_dir")/$( basename "$target")"
    cd "$target" && exec "$SHELL"
fi

# --- Test in current directory ---
# Find the single .cpp file, or default to sol.cpp
cpp_files=(*.cpp)
if [ ${#cpp_files[@]} -eq 1 ] && [ -f "${cpp_files[0]}" ]; then
    SRC="${cpp_files[0]}"
else
    SRC="sol.cpp"
fi
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
