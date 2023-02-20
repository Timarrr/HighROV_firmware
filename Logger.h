#pragma once

#include <sys/_intsup.h>
enum Severity{
    DEBUG = 0,
    INFO,
    WARNING,
    ERROR
};
struct Message{
    char* message;
    unsigned long long timestamp;
    Severity severity;
    Message(char* m, unsigned long long t, Severity s): message(m), timestamp(t), severity(s){};
};

class Logger{
    public:
        void debug(char*);
        void info(char*);
        void warn(char*);
        void error(char*);
        void update();
    private:
        short status;

        Message *queue[1024];
        int position;
};