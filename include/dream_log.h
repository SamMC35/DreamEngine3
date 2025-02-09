#ifndef LOG_H
#define LOG_H

#include<iostream>

typedef enum LoggingLevel{
  INFO,
  DEBUG,
  WARN,
  ERROR
};

void setLoggingLevel();


#endif
