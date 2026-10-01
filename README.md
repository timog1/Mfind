# =======================================================
# mfind – Multithreaded File Finder with Filters
# =======================================================
# mfind is a lightweight, multithreaded file search tool
# written in C. It allows searching files in a directory
# with multiple filters applied sequentially. Files must
# pass all filters to appear in the final output.
# =======================================================

# ------------------------------
# Get the Repository
# ------------------------------

# Clone via Git:
# git clone https://git.fiw.fhws.de/k69662/c_project_systemnah.git
# cd c_project_systemnah
# git branch -M main
# git push -uf origin main

# Or download as ZIP:
# - Download and extract the repository.
# - Navigate to the source folder.

# ------------------------------
# Build
# ------------------------------

# From the source folder, run:
# make

# This will build the `mfind` executable.

# ------------------------------
# Usage
# ------------------------------

# ./mfind <directory> <number_of_threads> <filters> <filter_options...>

# ------------------------------
# Filters
# ------------------------------

# Filters are applied in sequence; a file must pass all
# filters to be included in the final output.

# -n <pattern>   : Name filter (supports wildcards, e.g., "S*" for files starting with S)
# -s <size>      : Size filter (supports bytes, KB, MB, GB)
#                 Examples:
#                 >3000B  → file size greater than 3000 bytes
#                 <5M     → file size smaller than 5 megabytes
#                 =10K    → file size exactly 10 kilobytes

# ------------------------------
# Filter Example
# ------------------------------

# ./mfind . -sn ">3000B" "S*"

# Explanation:
# 1. -s >3000B : only files larger than 3000 bytes
# 2. -n "S*"   : only files starting with an uppercase S
# Files must satisfy both filters to appear.

# ------------------------------
# More Examples
# ------------------------------

# Search all files larger than 10 KB and starting with "log"
# ./mfind ./logs -sn ">10K" "log*"

# Search all files smaller than 1 MB
# ./mfind . -s "<1M"

# Search all files starting with "A" or "B"
# ./mfind . -n "A*" -n "B*"

# ------------------------------
# Notes
# ------------------------------

# - Filters are applied in order.
# - All filters must pass for a file to appear.
# - Supports b/k/m/g units for sizes.
# - Supports wildcards for file names:
#     * → matches any sequence of characters (including none)
#     ? → matches exactly one character
# - Specify <number_of_threads> for multithreaded performance.

# ------------------------------
# Testing
# ------------------------------

# Two test suites are provided in src/test:

# 1. Full automated Bash test:
#    src/test/fulltest.sh
#    - Run this script to test mfind on multiple files and filters
#    - Includes timing and checks expected outputs
#    - Usage:
#      cd src/test
#      bash fulltest.sh

# 2. Unit tests in C:
#    src/test/mymathtest.c
#    - Contains unittest functions for individual filters
#    - Compile and run:
#      gcc -o mymathtest mymatchtest.c ../mfind.c -I../include
#      ./mymathtest

# Only files passing both size and name filters will appear.