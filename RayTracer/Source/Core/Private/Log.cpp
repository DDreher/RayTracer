#include "Log.h"

#pragma warning(push, 0)
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#pragma warning(pop)

SharedPtr<spdlog::logger> Log::logger_;

void Log::Init(const char* log_category)
{
    std::vector<spdlog::sink_ptr> log_sinks;

    // Write log to stdout
    log_sinks.emplace_back(MakeShared<spdlog::sinks::stdout_color_sink_mt>());
    log_sinks[0]->set_pattern("%^[%T] %n: %v%$");

    // Write log to file
    log_sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Saved/Logs/Log.txt", true));
    log_sinks[1]->set_pattern("[%T] [%l] %n: %v");

    logger_ = MakeShared<spdlog::logger>(log_category, begin(log_sinks), end(log_sinks));
    spdlog::register_logger(logger_);
    logger_->set_level(spdlog::level::trace);
    logger_->flush_on(spdlog::level::trace);
}
