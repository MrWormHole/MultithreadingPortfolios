#!/bin/bash
if ["$1" == ""]; then
  echo "Parameter 1 is empty"
else
  mpirun -machinefile /etc/pdsh/machines -np 11 -map-by ppr:1:node $1
fi
