#!/bin/bash

# Configurable parameters
SCENE_IDS=(1 2 3)
WIDTHS=(320 640 1280 2560)
THREADS=(1 2 4 8)
RUNS=5
SAMPLES=(10 100)
BOUNCES=(25 50)

# Executables
SERIAL_EXE=build/Debug/inOneWeekend
OPENMP_EXE=build/Debug/inOneWeekend_openmp

# Directories
mkdir -p produced_images
mkdir -p csv

for SCENE_ID in "${SCENE_IDS[@]}"; do
    for WIDTH in "${WIDTHS[@]}"; do
        for SAMPLE in "${SAMPLES[@]}"; do
            for BOUNCE in "${BOUNCES[@]}"; do

                CSV_FOLDER_NAME="images_${WIDTH}_scene${SCENE_ID}_samples${SAMPLE}_bounces${BOUNCE}"
                CSV_OUTPUT_DIR="csv/${CSV_FOLDER_NAME}"
                mkdir -p "$CSV_OUTPUT_DIR"

                echo "======================================"
                echo "Starting WIDTH: $WIDTH, SCENE: $SCENE_ID, SAMPLES: $SAMPLE, BOUNCES: $BOUNCE"
                echo "======================================"

                for RUN in $(seq 1 $RUNS); do
                    echo ">>> RUN $RUN"

                    ##########################
                    # SERIAL VERSION
                    ##########################
                    echo "[Serial] Rendering..."
                    IMAGE_NAME="image_${WIDTH}_${SCENE_ID}_run${RUN}_serial_s${SAMPLE}_b${BOUNCE}.ppm"
                    WIDTH=$WIDTH SCENE_ID=$SCENE_ID SAMPLES=$SAMPLE BOUNCES=$BOUNCE $SERIAL_EXE > "produced_images/${IMAGE_NAME}"

                    GENERATED_CSV="image_${WIDTH}_scene${SCENE_ID}.csv"
                    FINAL_CSV_NAME="image_${WIDTH}_${SCENE_ID}_run${RUN}_serial_s${SAMPLE}_b${BOUNCE}.csv"
                    if [ -f "$GENERATED_CSV" ]; then
                        mv "$GENERATED_CSV" "${CSV_OUTPUT_DIR}/${FINAL_CSV_NAME}"
                    else
                        echo "Warning: Serial CSV not found for run $RUN"
                    fi

                    ##########################
                    # OPENMP VERSIONS
                    ##########################
                    for THREAD_COUNT in "${THREADS[@]}"; do
                        for SCHEDULE in static dynamic; do
                            echo "[OpenMP - $SCHEDULE, threads=$THREAD_COUNT] Rendering..."

                            WIDTH=$WIDTH SCENE_ID=$SCENE_ID SAMPLES=$SAMPLE BOUNCES=$BOUNCE THREADS=$THREAD_COUNT \
                            $OPENMP_EXE $SCENE_ID $SCHEDULE $THREAD_COUNT

                            PPM_FILE="openMP_${WIDTH}_scene${SCENE_ID}.ppm"
                            CSV_FILE="openMP_${WIDTH}_scene${SCENE_ID}_${SCHEDULE}.csv"
                            FINAL_PPM="image_${WIDTH}_${SCENE_ID}_run${RUN}_${SCHEDULE}_${THREAD_COUNT}t_s${SAMPLE}_b${BOUNCE}.ppm"
                            FINAL_CSV="image_${WIDTH}_${SCENE_ID}_run${RUN}_${SCHEDULE}_${THREAD_COUNT}t_s${SAMPLE}_b${BOUNCE}.csv"

                            if [ -f "$PPM_FILE" ]; then
                                mv "$PPM_FILE" "produced_images/${FINAL_PPM}"
                            else
                                echo "Warning: $SCHEDULE PPM not found for threads=$THREAD_COUNT"
                            fi

                            if [ -f "$CSV_FILE" ]; then
                                mv "$CSV_FILE" "${CSV_OUTPUT_DIR}/${FINAL_CSV}"
                            else
                                echo "Warning: $SCHEDULE CSV not found for threads=$THREAD_COUNT"
                            fi
                        done
                    done

                    echo ">>> Finished RUN $RUN"
                    echo ""
                done
            done
        done
    done
done

echo "============================="
echo "All runs completed!"
echo "============================="
