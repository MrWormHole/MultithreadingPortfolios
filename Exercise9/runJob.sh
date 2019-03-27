#!/bin/bash
if ["$1" == ""]; then
 echo "First parameter is empty"
else
 mpirun -machinefile /etc/pdsh/machines -np 11 --map-by ppr:1:node $1
fi
