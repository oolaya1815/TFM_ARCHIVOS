#!/bin/bash
cd /home/user/contiki/tools
echo "Iniciando tuneles"
./tunslip6 -v2 -t tun0 -a localhost -p 60018 fd00::1/64 &
./tunslip6 -v2 -t tun1 -a localhost -p 60019 fd01::1/64 &
./tunslip6 -v2 -t tun2 -a localhost -p 60020 fd02::1/64 &
./tunslip6 -v2 -t tun3 -a localhost -p 60021 fd03::1/64 &
echo "finalizado"
