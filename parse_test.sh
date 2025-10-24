#!/usr/bin/env bash
# Ejecuta ./miniRT sobre archivos o carpetas, registra salida en log.txt y reporta códigos de salida != 0.
# Uso:
#   ./scripts/run_minirt_tests.sh [path1 path2 ...]
# Si no se pasan argumentos, busca archivos *.rt en ./scenes

LOG="log.txt"
BIN="./miniRT"
declare -a targets
declare -a failed

# Comprobar binario
if [ ! -x "$BIN" ]; then
    printf "Error: %s no existe o no es ejecutable\n" "$BIN" >&2
    exit 1
fi

# Limpiar log
: > "$LOG"

# Recolectar targets
if [ "$#" -gt 0 ]; then
    for p in "$@"; do
        if [ -d "$p" ]; then
            while IFS= read -r -d $'\0' f; do targets+=("$f"); done < <(find "$p" -type f -print0)
        else
            targets+=("$p")
        fi
    done
else
    if [ -d "./scenes/invalid" ]; then
        while IFS= read -r -d $'\0' f; do targets+=("$f"); done < <(find ./scenes/invalid -type f -name "*.rt" -print0)
    fi
fi

if [ "${#targets[@]}" -eq 0 ]; then
    echo "No se encontraron archivos para ejecutar." | tee -a "$LOG"
    exit 1
fi

# Ejecutar cada target
for t in "${targets[@]}"; do
    printf "===== %s %s =====\n" "$BIN" "$t" | tee -a "$LOG"
    printf "Timestamp: %s\n" "$(date '+%F %T')" | tee -a "$LOG"
    # Ejecutar y registrar salida (stdout+stderr)
    "$BIN" "$t" >>"$LOG" 2>&1
    rc=$?
    if [ $rc -ne 0 ]; then
        printf "RESULT: EXIT %d -> FAILURE for %s\n\n" "$rc" "$t" | tee -a "$LOG"
        failed+=("$t:$rc")
    else
        printf "RESULT: EXIT %d -> OK for %s\n\n" "$rc" "$t" | tee -a "$LOG"
    fi
done

# Resumen
echo "===== Summary =====" | tee -a "$LOG"
echo "Total run: ${#targets[@]}" | tee -a "$LOG"
echo "Failures: ${#failed[@]}" | tee -a "$LOG"
if [ "${#failed[@]}" -gt 0 ]; then
    echo "Failed items (path:exit_code):" | tee -a "$LOG"
    for f in "${failed[@]}"; do
        echo " - $f" | tee -a "$LOG"
    done
    exit 2
fi

exit 0