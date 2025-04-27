#!/bin/bash

# Configurable parameters
SCENE_ID=1
WIDTHS=(340 640 800 1920 3840)
RUNS=10

# Executables
SERIAL_EXE=build/Release/inOneWeekend
OPENMP_EXE=build/Release/inOneWeekend_openmp

# Directories
mkdir -p produced_images
mkdir -p csv

# Loop through each width
for WIDTH in "${WIDTHS[@]}"; do
    CSV_FOLDER_NAME="images_${WIDTH}_scene${SCENE_ID}"
    CSV_OUTPUT_DIR="csv/${CSV_FOLDER_NAME}"
    mkdir -p "$CSV_OUTPUT_DIR"

    echo "============================="
    echo "Starting WIDTH: $WIDTH"
    echo "============================="

    for RUN in $(seq 1 $RUNS); do
        echo ">>> RUN $RUN for WIDTH $WIDTH"

        ##########################
        # SERIAL VERSION
        ##########################
        echo "[Serial] Rendering..."
        IMAGE_NAME="image_${WIDTH}_${SCENE_ID}_run${RUN}_serial.ppm"
        time WIDTH=$WIDTH SCENE_ID=$SCENE_ID $SERIAL_EXE > "produced_images/${IMAGE_NAME}"

        GENERATED_CSV="image_${WIDTH}_scene${SCENE_ID}.csv"
        FINAL_CSV_NAME="image_${WIDTH}_${SCENE_ID}_run${RUN}_serial.csv"
        if [ -f "$GENERATED_CSV" ]; then
            mv "$GENERATED_CSV" "${CSV_OUTPUT_DIR}/${FINAL_CSV_NAME}"
        else
            echo "⚠️  Warning: Serial CSV not found for run $RUN"
        fi

        ##########################
        # OPENMP - STATIC
        ##########################
        echo "[OpenMP - static] Rendering..."
        time WIDTH=$WIDTH SCENE_ID=$SCENE_ID $OPENMP_EXE $SCENE_ID static

        STATIC_PPM="openMP_${WIDTH}_scene${SCENE_ID}.ppm"
        STATIC_CSV="openMP_${WIDTH}_scene${SCENE_ID}_static.csv"
        FINAL_PPM="image_${WIDTH}_${SCENE_ID}_run${RUN}_static.ppm"
        FINAL_CSV="image_${WIDTH}_${SCENE_ID}_run${RUN}_static.csv"

        if [ -f "$STATIC_PPM" ]; then
            mv "$STATIC_PPM" "produced_images/${FINAL_PPM}"
        else
            echo "⚠️  Warning: Static PPM not found"
        fi

        if [ -f "$STATIC_CSV" ]; then
            mv "$STATIC_CSV" "${CSV_OUTPUT_DIR}/${FINAL_CSV}"
        else
            echo "⚠️  Warning: Static CSV not found"
        fi

        ##########################
        # OPENMP - DYNAMIC
        ##########################
        echo "[OpenMP - dynamic] Rendering..."
        time WIDTH=$WIDTH SCENE_ID=$SCENE_ID $OPENMP_EXE $SCENE_ID dynamic

        DYNAMIC_PPM="openMP_${WIDTH}_scene${SCENE_ID}.ppm"
        DYNAMIC_CSV="openMP_${WIDTH}_scene${SCENE_ID}_dynamic.csv"
        FINAL_PPM="image_${WIDTH}_${SCENE_ID}_run${RUN}_dynamic.ppm"
        FINAL_CSV="image_${WIDTH}_${SCENE_ID}_run${RUN}_dynamic.csv"

        if [ -f "$DYNAMIC_PPM" ]; then
            mv "$DYNAMIC_PPM" "produced_images/${FINAL_PPM}"
        else
            echo "⚠️  Warning: Dynamic PPM not found"
        fi

        if [ -f "$DYNAMIC_CSV" ]; then
            mv "$DYNAMIC_CSV" "${CSV_OUTPUT_DIR}/${FINAL_CSV}"
        else
            echo "⚠️  Warning: Dynamic CSV not found"
        fi

        echo ">>> Finished RUN $RUN"
        echo ""
    done
done

echo "============================="
echo "✅ All runs completed!"
echo "============================="
