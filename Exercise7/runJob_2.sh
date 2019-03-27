#!/bin/bash
if ["$1" == ""]; then
  echo "Parameter 1 is empty"
else 
  mpirun -machinefile /etc/pdsh/machines -np 22 -map-by ppr:2:node $1
fi
