#!/bin/bash
g++ -Wno-write-strings MainCliente.cpp Cliente.cpp ../Common/*.cpp ../Common/Signals/SignalHandler.cpp ../Common/Signals/SIGINT_Client_Handler.h ../Common/Signals/EventHandler.h -o MainCliente
