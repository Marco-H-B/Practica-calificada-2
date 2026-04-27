#!/usr/bin/env bash
set -euo pipefail
# Placeholder benchmark: compila y ejecuta una vez.
ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
cmake -S "$ROOT_DIR" -B "$ROOT_DIR/build"
cmake --build "$ROOT_DIR/build"
# Aquí puede agregar generación de entradas grandes y medir tiempos.
"$ROOT_DIR/build/pc2_main" < "$ROOT_DIR/demos/input1.txt"
