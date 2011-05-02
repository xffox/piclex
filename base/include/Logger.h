#ifndef LOGGER_H
#define LOGGER_H

#include <cstdarg>
#include <cstddef>
#include <fstream>

#include "Mutex.h"

namespace base
{
class InternalLoggerError
{
public:
    InternalLoggerError()
    {
    }
};

class LogWriter
{
public:
    virtual ~LogWriter() = 0;

    virtual void write(const char *message) = 0;
};

class Logger
{
    friend Logger &Log();

    static const size_t BUF_SIZE;

public:
    enum Severity {DEBUG, INFO, WARNING, ERROR};

    ~Logger();

    // take care of the deletion
    void setLogWriter(LogWriter *logWriter);
    void setSeverity(Severity severity);

    void write(Severity severity, const char *msg, va_list ap);
    void write(Severity severity, const char *msg, ...);

    void error(const char *msg, ...);
    void warning(const char *msg, ...);
    void info(const char *msg, ...);
    void debug(const char *msg, ...);

private:
    Logger();
    const char *getSeverityStr(Severity severity);

    Severity mSeverity;
    LogWriter *mLogWriter;

    Mutex *mMutex;
};

Logger &Log();

class TimestampedLogWriter: public LogWriter
{
    static const size_t BUF_SIZE;

public:
    TimestampedLogWriter(LogWriter *proxedLogWriter);

    virtual ~TimestampedLogWriter();

    virtual void write(const char *message);

private:
    LogWriter *mProxedLogWriter;
};

class FileLogWriter: public LogWriter
{
public:
    FileLogWriter(const std::string &path);

    virtual ~FileLogWriter();

    virtual void write(const char *message);

private:
    std::string mPath;
    std::ofstream mFileStream;

    Mutex *mMutex;
};

}

#endif//LOGGER_H
