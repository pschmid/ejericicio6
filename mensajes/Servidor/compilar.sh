#!/bin/bash
g++ -Wno-write-strings BaseDeDatos.cpp Registro.cpp  MainServer.cpp Servidor.cpp ../Common/*.cpp ../Common/Constants.h  ../Common/Mensaje.h  ../Common/Signals/SignalHandler.cpp ../Common/Signals/SIGINT_Handler.h ../Common/Signals/EventHandler.h -o MainServer

