#!/bin/bash



python3 gesto.py &
PID_GESTO=$!

echo "Premi 'z' per terminare i processi."

# Attendi il carattere 'q' in input
read -n1 carattere
if [ $carattere == "z" ]; then
    # Kill dei processi Python quando viene ricevuto 'q'
    kill  $PID_GESTO
fi

