#include <vector>
#include <string>

/**
 * Event class.
 */
class Event
{
public:
	static const std::string EVENT = "event";

	Event(std::string type, std::vector<Object*> args);

    public std::string getType();
    public std::vector<Object*> getArgs();

protected:
	/** The type of the Event **/
    std::string type;			
    /** Arguments of the Event **/
    std::vector<Object*> args;
};