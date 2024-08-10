#!/bin/bash

# Check if a file name is provided
if [ $# -eq 0 ]; then
    echo "No LaTeX file specified."
    echo "Usage: $0 filename.tex"
    exit 1
fi

# Get the file name without the extension
filename=$(basename -- "$1")
name="${filename%.*}"

# Run pdflatex, handling errors
pdflatex -interaction=nonstopmode -halt-on-error "$filename"

# Optionally run BibTeX if needed
# bibtex "$name"

# Run pdflatex again to resolve references
pdflatex -interaction=nonstopmode -halt-on-error "$filename"
pdflatex -interaction=nonstopmode -halt-on-error "$filename"

# Check if the PDF was successfully created
if [ -f "${name}.pdf" ]; then
    echo "Compilation successful: ${name}.pdf"
else
    echo "Compilation failed!"
    exit 1
fi
