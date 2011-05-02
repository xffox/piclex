#include "Logger.h"

#include <cstdio>
#include <cassert>

namespace base
{
const size_t Logger::BUF_SIZE = 4096;

LogWriter::~LogWriter()
{
}

Logger::Logger()
    :mSeverity(DEBUG), mMutex(NULL)
{
    try
    {
        mMutex = new Mutex();
    }
    catch(...)
    {
        throw InternalLoggerError();
    }
}

Logger::~Logger()
{
    delete mLogWriter;

    delete mMutex;
}

void Logger::setLogWriter(LogWriter *logWriter)
{
    assert(mMutex);
    try
    {
        mMutex->lock();
    }
    catch(...)
    {
        throw InternalLoggerError();
    }

    if(mLogWriter)
        delete mLogWriter;
    mLogWriter = logWriter;

    try
    {
        mMutex->unlock();
    }
    catch(...)
    {
        throw InternalLoggerError();
    }
}

void Logger::setSeverity(Severity severity)
{
    assert(mMutex);
    try
    {
        mMutex->lock();
    }
    catch(...)
    {
        throw InternalLoggerError();
    }

    mSeverity = severity;

    try
    {
        mMutex->unlock();
    }
    catch(...)
    {
        throw InternalLoggerError();
    }
}

void Logger::write(Severity severity, const char *msg, va_list ap)
{
    if(!mLogWriter)
        return;

    if(severity < mSeverity)
        return;

    char messageBuf[BUF_SIZE];
    vsnprintf(messageBuf, BUF_SIZE, msg, ap);
    char formatedMessageBuf[BUF_SIZE];
    snprintf(formatedMessageBuf, BUF_SIZE, "[%s] %s\n", getSeverityStr(severity),
            messageBuf);

    mLogWriter->write(formatedMessageBuf);
}

void Logger::write(Severity severity, const char *msg, ...)
{
    va_list ap;

    va_start(ap, msg);
    write(severity, msg, ap);
    va_end(ap);
}

void Logger::error(const char *msg, ...)
{
    va_list ap;

    va_start(ap, msg);
    write(ERROR, msg, ap);
    va_end(ap);
}

void Logger::warning(const char *msg, ...)
{
    va_list ap;

    va_start(ap, msg);
    write(WARNING, msg, ap);
    va_end(ap);
}

void Logger::info(const char *msg, ...)
{
    va_list ap;

    va_start(ap, msg);
    write(INFO, msg, ap);
    va_end(ap);
}

void Logger::debug(const char *msg, ...)
{
    va_list ap;

    va_start(ap, msg);
    write(DEBUG, msg, ap);
    va_end(ap);
}

const char *Logger::getSeverityStr(Severity severity)
{
    switch(severity)
    {
        case DEBUG:
            return "D";
        case INFO:
            return "I";
        case WARNING:
            return "W";
        case ERROR:
            return "E";
        default:
            return "?";
    }
    return "?";
}

Logger &Log()
{
    // TODO: try to get rid of static destruction problem
    static Logger logger;
    return logger;
}

const size_t TimestampedLogWriter::BUF_SIZE = 4096;

TimestampedLogWriter::TimestampedLogWriter(LogWriter *proxedLogWriter)
    :mProxedLogWriter(proxedLogWriter)
{
}

TimestampedLogWriter::~TimestampedLogWriter()
{
    delete mProxedLogWriter;
}

void TimestampedLogWriter::write(const char *message)
{
    if(mProxedLogWriter)
    {
        char messageBuf[BUF_SIZE];
        snprintf(messageBuf, BUF_SIZE, "[%lu] %s", time(NULL), message);
        mProxedLogWriter->write(messageBuf);
    }
}

FileLogWriter::FileLogWriter(const std::string &path)
    :mPath(path), mMutex(NULL)
{
    // TODO: parameter check
    try
    {
        mMutex = new Mutex();
    }
    catch(...)
    {
        throw InternalLoggerError();
    }

    // unbuffered
    mFileStream.rdbuf()->pubsetbuf(NULL, 0);
}

FileLogWriter::~FileLogWriter()
{
    mFileStream.close();

    delete mMutex;
}

void FileLogWriter::write(const char *message)
{
    assert(mMutex);
    try
    {
        mMutex->lock();
    }
    catch(...)
    {
        throw InternalLoggerError();
    }

    if(!mFileStream.is_open())
        mFileStream.open(mPath.c_str());
    mFileStream<<message;

    try
    {
        mMutex->unlock();
    }
    catch(...)
    {
        throw InternalLoggerError();
    }
}

}
