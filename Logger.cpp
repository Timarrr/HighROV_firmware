#include "Logger.h"
#include <Arduino.h>
#include <cstdlib>
void Logger::debug(char* message){
    position++;
    free(this->queue[position]);
    this->queue[position] = new Message(message, millis(), Severity::DEBUG);
}

void Logger::info(char * message){
    position++;
    free(this->queue[position]);
    this->queue[position] = new Message(message, millis(), Severity::INFO);
}

void Logger::warn(char * message){
    position++;
    free(this->queue[position]);
    this->queue[position] = new Message(message, millis(), Severity::WARNING);
}

void Logger::error(char * message){
    position++;
    free(this->queue[position]);
    this->queue[position] = new Message(message, millis(), Severity::ERROR);
}

void Logger::update(){
    if (!SerialUSB) {
        // no connecion
        if(position > output_position){

        }
    }
}