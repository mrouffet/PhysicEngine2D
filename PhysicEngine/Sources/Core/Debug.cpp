#include <fstream>
#include <iostream>

#include <windows.h>

#include <Core/Debug.hpp>

namespace Pe
{
	namespace Debug
	{
		struct DebugLogFile : public std::fstream
		{
			DebugLogFile()
			{
				open("logFile.txt", std::ios_base::out | std::ios_base::app);
			}
			~DebugLogFile()
			{
				close();
			}
		};

		DebugLogFile sLogStream;
		HANDLE sWinConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		std::string SetDebugLevel(LogLevel _level) noexcept
		{
			switch (_level)
			{
			default:
			case LogLevel::Normal:
				SetConsoleTextAttribute(sWinConsole, 15); // Set White.
				return "[LOG]\t\t";
			case LogLevel::Info:
				SetConsoleTextAttribute(sWinConsole, 11); // Set Cyan.
				return "[INFO]\t\t";
			case LogLevel::Warning:
				SetConsoleTextAttribute(sWinConsole, 6); // Set Yellow.
				return "[WARN]\t\t";
			case LogLevel::Error:
				SetConsoleTextAttribute(sWinConsole, 12); // Set Red.
				return "[ERROR]\t";
			}
		}

		void Log(const std::string& _msg, LogLevel _level) noexcept
		{
			std::string logStr = SetDebugLevel(_level) + _msg;

			sLogStream << logStr << std::endl;
			std::cout << logStr << std::endl;
		}
		void Assert(bool predicate, const std::string& _msg, bool logOnSuccess)
		{
			if (!predicate)
			{
				SetConsoleTextAttribute(sWinConsole, 10); // Set Green.

				std::string logStr = "[ASSERT]\t" + _msg;

				sLogStream << logStr << std::endl;
				std::cout << logStr << std::endl;

				// Force flush before abort.
				sLogStream.flush();
				std::cout.flush();

				abort();
			}
			else if (logOnSuccess)
			{
				// Add Success at end of line.
				std::string successStr = _msg + ':';

				int count = successStr.length();
				while (count < 96)
				{
					successStr += "\t";
					count += 8;
				}

				Log(successStr + "Success", LogLevel::Info);
			}
		}
	}
}