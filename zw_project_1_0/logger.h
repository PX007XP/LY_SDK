#ifndef LOGGER_H
#define LOGGER_H
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QDebug>
#include <QDateTime>
#include <QTimer>


enum LOGGER_LEVEL
{
    LOGGER_STATS = 0,
    LOGGER_ERROR = 1,
    LOGGER_WARN = 2,
    LOGGER_INFO = 3,
    LOGGER_DEBUG = 4
};

class Logger
{
public:
    Logger(const QString& strFileName);
    ~Logger();

    void writeLog(int iLogLevel ,const char* format, ...);
    void writeLog(int iLogLevel , QString & strMessage);


private:
    QFile m_logFile;
    QTextStream m_logStream;
    QHash<int ,QString> m_LogFlag;
};

extern Logger* g_pLogger;
extern int g_iLogLevel;



#define LOG_DEBUG(_fmt_, ...) \
    if(g_iLogLevel >= LOGGER_DEBUG && g_pLogger) \
    {\
        g_pLogger->writeLog(LOGGER_DEBUG ,_fmt_ ,__VA_ARGS__ );\
    }
#define LOG_INFO(_fmt_, ...)\
    if(g_iLogLevel >= LOGGER_INFO && g_pLogger) \
    {\
        g_pLogger->writeLog(LOGGER_INFO ,_fmt_ ,__VA_ARGS__ );\
    }
#define LOG_WARN(_fmt_, ...)\
    if(g_iLogLevel >= LOGGER_WARN && g_pLogger) \
    {\
        g_pLogger->writeLog(LOGGER_WARN ,_fmt_ ,__VA_ARGS__ );\
    }
#define LOG_ERROR(_fmt_, ...)\
    if(g_iLogLevel >= LOGGER_ERROR && g_pLogger) \
    {\
        g_pLogger->writeLog(LOGGER_ERROR ,_fmt_ ,__VA_ARGS__ );\
    }
#define LOG_STATS(_fmt_, ...)\
    if(g_iLogLevel >= LOGGER_STATS && g_pLogger) \
    {\
        g_pLogger->writeLog(LOGGER_STATS ,_fmt_ ,__VA_ARGS__ );\
    }

#endif // LOGGER_H
