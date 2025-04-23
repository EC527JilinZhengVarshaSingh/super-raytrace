#!/bin/bash

echo "=== CPU Info ==="
echo "CPU Brand String: $(sysctl -n machdep.cpu.brand_string)"
echo "Physical CPUs:    $(sysctl -n hw.physicalcpu)"
echo "Logical CPUs:     $(sysctl -n hw.logicalcpu)"
echo "CPU Frequency:    $(sysctl -n hw.cpufrequency) Hz"

echo
echo "=== System Info ==="
echo "Kernel Info: $(uname -a)"

echo
echo "=== RAM Info ==="
mem_bytes=$(sysctl -n hw.memsize)
mem_gb=$(echo "scale=2; $mem_bytes / (1024^3)" | bc)
echo "RAM: ${mem_gb} GB"

echo
echo "=== Cache Info (from sysctl -a | grep cache) ==="
sysctl -a | grep cache

echo
echo "=== Done ==="
