#!/bin/bash

echo "-------------------- COMPILACION DEL Servidor --------------------"
cd Servidor
./compilar.sh

echo "-------------------- COMPILACION DEL Cliente --------------"
cd ../Cliente/
./compilar.sh