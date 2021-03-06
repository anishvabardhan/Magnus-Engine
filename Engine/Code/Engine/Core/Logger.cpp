#include "Logger.h"

#include "Engine/Platform/WindowsH.h"
#include "LogMessage.h"

static Logger* s_Logger = nullptr;
static FILE* s_LogFile = nullptr;

Logger::Logger()
{
}

Logger::~Logger()
{
}

void LogStartup()
{
	Logger::CreateInstance();

	String logFileName = "Log/";
	logFileName.append("Log");

	String defaultLogFile = logFileName.append(".txt");

	if (!CreateDirectoryA("Log/", NULL))
	{
	}

	fopen_s(&s_LogFile, "Log/Log.txt", "w");

	s_Logger->AddSink(LogToIDE);
	s_Logger->AddSink(s_Logger->LogToFile);
}

void LogShutdown()
{
	s_Logger->Flush();
	fclose(s_LogFile);
	Logger::DestroyInstance();
}

void LogPrint(const char* format, ...)
{
	char text[2048];
	va_list args;
	va_start(args, format);
	vsnprintf_s(text, 2048, _TRUNCATE, format, args);
	text[2047] = '\0';
	va_end(args);

	s_Logger->AddLogMessage(text);
}

void LogFlush()
{
	s_Logger->Flush();
}

void Logger::AddSink(LogCallback cb)
{
	m_Sinks.push_back(cb);
}

void Logger::RemoveSink(LogCallback cb)
{
	for (int i = 0; i < m_Sinks.size(); i++)
	{
		if (m_Sinks[i] == cb)
		{
			m_Sinks.erase(m_Sinks.begin() + i);
			break;
		}
	}
}

void Logger::AddLogMessage(const String& msg)
{
	m_LogQueue.push(msg);
}

void Logger::Flush()
{
	String msg;

	while (!m_LogQueue.empty())
	{
		msg = m_LogQueue.front();
		m_LogQueue.pop();

		for (int i = 0; i < m_Sinks.size(); i++)
		{
			m_Sinks[i](msg);
		}
	}
}

void Logger::LogToFile(const String& msg)
{
	fprintf(s_LogFile, "%s", msg.c_str());
}

Logger* Logger::CreateInstance()
{
	s_Logger = new Logger();

	return s_Logger;
}

void Logger::DestroyInstance()
{
	delete s_Logger;
	s_Logger = nullptr;
}