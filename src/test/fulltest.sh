#!/bin/bash
set -e
echo "=== Running mfind automated tests ==="

# Create temporary directory for testing
TMPDIR=$(mktemp -d)
echo "Using temp folder: $TMPDIR"

# Create test files and subdirectories
touch "$TMPDIR/file1.txt"
touch "$TMPDIR/file2.log"
touch "$TMPDIR/file3.TXT"
mkdir -p "$TMPDIR/subdir"
touch "$TMPDIR/subdir/file4.txt"

# Create some larger file for size testing
dd if=/dev/zero of="$TMPDIR/largefile.bin" bs=1024 count=5 2>/dev/null
dd if=/dev/zero of="$TMPDIR/fargefile.bin" bs=1024 count=2 2>/dev/null

# Start timer
start_time=$(date +%s%3N)

# ------------------- Test 1: Name filter only -------------------
echo "Test 1: name_filter (-n) for files starting with 'f'"
../../build/mfind "$TMPDIR" -n "f*" > output1.txt 2> error1.txt

# Check results
for file in file1.txt file2.log file3.TXT; do
    if grep -q "$file" output1.txt; then
        echo "✓ Found $file"
    else
        echo "✗ Missing $file"
    fi
done

# ------------------- Test 2: Size filter only -------------------
echo "Test 2: size_filter (-s) files > 4000 bytes"
../../build/mfind "$TMPDIR" -s ">4k" > output2.txt 2> error2.txt

if grep -q "largefile.bin" output2.txt; then
    echo "✓ largefile.bin found (correct size filter)"
else
    echo "✗ largefile.bin missing"
fi

# ------------------- Test 3: Sequential filters (-sn) -------------------
echo "Test 3: size_filter then name_filter"
../../build/mfind "$TMPDIR" -sn ">1k" "f*" > output3.txt 2> error3.txt

# Expected: largefile.bin (size) + files starting with f
if grep -q "fargefile.bin" output3.txt; then
    echo "✓ fargefile.bin found (correct size filter)"
else
    echo "✗ fargefile.bin missing"
fi
for file in file1.txt file2.log file3.TXT largefile.bin; do
    if grep -q "$file" output3.txt; then
        echo "✗ $file found"
    else
        echo "✓ $file missing"
    fi
done

# End timer
end_time=$(date +%s%3N)
elapsed=$((end_time - start_time))

echo "--------------------------------"
echo "All tests executed"
echo "Elapsed time: ${elapsed} ms"
echo "--------------------------------"

# Cleanup
rm -rf "$TMPDIR" output*.txt error*.txt
echo "✓ Test environment cleaned"