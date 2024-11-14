#include "logger.h"
#include <cstdarg>
#include <QString>

Logger::Logger(const QString& strFileName):m_logFile(strFileName)
{

    if (!m_logFile.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "无法打开日志文件";
        return;
    }
    m_logStream.setDevice(&m_logFile);
    m_LogFlag[LOGGER_STATS] = "STATS";
    m_LogFlag[LOGGER_ERROR] = "ERROR";
    m_LogFlag[LOGGER_WARN] = "WARN";
    m_LogFlag[LOGGER_INFO] = "INFO";
    m_LogFlag[LOGGER_DEBUG] = "DEBUG";

}

Logger::~Logger()
{
    m_logFile.close();
}

void Logger::writeLog(int iLogLevel ,const char* format, ...)
{
    if(iLogLevel > LOGGER_DEBUG)
    {
        iLogLevel = LOGGER_DEBUG;
    }
    // 安全地格式化字符串
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, BUFFER_SIZE, format, args); // 使用 vsnprintf 以避免缓冲区溢出
    va_end(args);

    QString strMessage = QString::fromUtf8(buffer); // 将缓冲区内容转换为 QString

    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    m_logStream << timestamp << " - " << m_LogFlag[iLogLevel] <<" - "<< strMessage << "\n";
    m_logStream.flush();
}

void Logger::writeLog(int iLogLevel ,QString &strMessage)
{
    if(iLogLevel > LOGGER_DEBUG)
    {
        iLogLevel = LOGGER_DEBUG;
    }
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    m_logStream << timestamp << " - " << m_LogFlag[iLogLevel]<< " - " << strMessage << "\n";
    m_logStream.flush();
}
