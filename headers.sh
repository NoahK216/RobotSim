#!/bin/bash

# this code is by Kyle Rosenberg augmenting code by Neil Kirby
# augmented once more by Noah Klein

readonly AUTHOR_NAME="Noah Klein"
readonly SRC_DIR=""
readonly HEADER_DEST="include/"
readonly CPP_MODE=true # Set to true for C++ mode, false for C mode

# Define an array of filenames to exclude from automatic header generation
declare -a EXCLUDE_FILES=("Robot.nvs" "RobotWidget.nvs")

file_extension="c"
header_extension="h"
if [ "$CPP_MODE" = true ]; then
    file_extension="cpp"
    header_extension="hpp"
fi

# Ensure include directory exists
echo "Ensuring directory $HEADER_DEST exists..."
mkdir -p "$HEADER_DEST"

# Create header files
echo "Creating header files..."
echo "new visible symbols..."
ctags -x --c-kinds=f --extras=-F "$SRC_DIR"*."$file_extension" | awk -f headers.awk
echo "updating changed visible symbols"

# Iterate over .nvs files in the source directory
for f in "$SRC_DIR"*.nvs ; do
    [ -f "$f" ] || break

    # Check if the filename is in the exclusion list
    if [[ " ${EXCLUDE_FILES[@]} " =~ " $(basename $f) " ]]; then
        echo "Skipping excluded file: $f"
        rm "$f"
        continue
    fi

    echo $f
    # Get the .vs filename from the .nvs filename
    filename="$(basename $f .nvs).vs"
    # echo "...checking $filename"
    diff $filename $f >/dev/null 2>&1
    # What did diff return?
    error=$?
    if [ $error -eq 0 ]; then
        # echo "    no change to $filename"
        rm "$f"
    else
        echo "   need to update $filename"
    fi
done

echo "creating headers from changed visible symbols"
# Create header files from the visible symbols in the source directory
for nf in "$SRC_DIR"*.nvs; do
    [ -f "$nf" ] || break

    # Get the name of the file with the .hpp and .vs extension
    dest_filename="$HEADER_DEST$(basename $nf .nvs).$header_extension"
    source_filename="$(basename $nf .nvs).vs"

    # echo "    Moving $nf to $f"
    mv "$nf" "$source_filename"

    # Notify the user we are crafting them a delicious header file
    echo -e "\tcreating $dest_filename from $source_filename"

    # Clear the file and write the author comment string
    echo -e "/* $AUTHOR_NAME */\n" > "$dest_filename"
    
    # Append everything in the visible symbol files
    cat "$source_filename" >> "$dest_filename"
done

date > headers
echo "Done creating headers."
