#!/bin/bash

# Configuration (change these as needed)
WIDTH=340
SCENE_ID=1

# define base names
CSV_FOLDER_NAME="image_${WIDTH}_scene${SCENE_ID}"
CSV_OUTPUT_DIR="csv/${CSV_FOLDER_NAME}"

# Create output directories
mkdir -p produced_images
mkdir -p csv
mkdir -p "$CSV_OUTPUT_DIR"

# Run the renderer 10 times
for i in {1..10}; do
    echo "Starting run $i..."

    # Run and time the render, output image with run-specific name
    IMAGE_NAME="image_${WIDTH}_${SCENE_ID}_run${i}.ppm"
    time build/Debug/inOneWeekend > "produced_images/${IMAGE_NAME}"

    # The camera generates this base CSV name
    GENERATED_CSV="image_${WIDTH}_scene${SCENE_ID}.csv"

    # New CSV name with run number
    FINAL_CSV_NAME="image_${WIDTH}_${SCENE_ID}_run${i}.csv"

    # Move and rename CSV into structured folder
    if [ -f "$GENERATED_CSV" ]; then
        mv "$GENERATED_CSV" "${CSV_OUTPUT_DIR}/${FINAL_CSV_NAME}"
    else
        echo "Warning: Expected CSV '$GENERATED_CSV' not found for run $i"
    fi

    echo "Finished run $i."
done

echo "Finished all runs."
