/**
 * @cite Multiton Pattern is a variation of Singleton Pattern where multiple singleton objects of a class are created that are uniquely identifiable.
 *
 * @brief Multiton Pattern can be exemplified by an EventLogger class that stores Events in different files based on their severity i.e. High, Medium, Low etc.
 */

#include <iostream>
#include <map>
#include <string>

/**
 * @brief Stores the Severity of Events on the basis of which Event Logger Singleton Objects are created.
 */
enum EventSeverity
{
    Critical,
    Warning,
    Normal
};

/**
 * @brief Multiple Singleton Objects of EventLogger are created.
 */
class EventLogger
{
    static int id;

    // Contructor is private so that only friend class EventLoggerMultiton can create the objects of Event Logger.
    EventLogger() {
        std::cout << ++id << " Loggers created so far...\n";
    }
    friend class EventLoggerMultiton;

    // Stores event to a EventLogger.
    void add_event(std::string event)
    {
        std::cout << "Event \"" << event << "\" Logged ";
    }
    
};

int EventLogger::id = 0;

/**
 * @brief Stores Multiple Singleton Objects of EventLogger based on the EventSeverity.
 */
class EventLoggerMultiton
{
    // Stores the Singleton Objects of EventLogger.
    static std::map<EventSeverity, EventLogger *> loggers;

public:
    // Adds event to appropriate EventLogger Singleton Object.
    static void add_event(std::string event_desc, EventSeverity severity = EventSeverity::Normal)
    {
        if (loggers.find(severity) == loggers.end())
        {
            loggers[severity] = new EventLogger();
        }

        loggers[severity]->add_event(event_desc);
        
        std::cout << " to " << get_severity(severity) << " Logger.\n";
    }
    
    // Converts EventSeverity enum values to strings.
    static std::string get_severity(EventSeverity severity) {
        std::string severity_str = "";
        switch (severity)
        {
        case EventSeverity::Critical:
            severity_str = "Critical";
            break;
        case EventSeverity::Warning:
            severity_str = "Warning";
            break;
        case EventSeverity::Normal:
            severity_str = "Normal";
            break;

        default:
            break;
        }
        return severity_str;
    }
};

// Initialization of static logers' list
std::map<EventSeverity, EventLogger *> EventLoggerMultiton::loggers;

int main()
{
    // Replicates the Event Logging in Real-World Systems.
    EventLoggerMultiton::add_event("System Booted", EventSeverity::Normal);
    EventLoggerMultiton::add_event("Data Copy couldn't complete", EventSeverity::Warning);
    EventLoggerMultiton::add_event("USB device not recognized", EventSeverity::Warning);
    EventLoggerMultiton::add_event("System not responding", EventSeverity::Critical);
    EventLoggerMultiton::add_event("System Crashed", EventSeverity::Critical);

    return 0;
}
