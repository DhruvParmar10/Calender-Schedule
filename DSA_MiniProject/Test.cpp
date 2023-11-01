//#include <iostream>
//#include <string>
//#include <vector>
//#include <ctime>
//#include <iomanip>
//using namespace std;
//
//class Event {
//public:
//    std::string name;
//    std::string date;
//    std::string tiime;
//
//    Event(const std::string& name, const std::string& date, const std::string& tiime)
//        : name(name), date(date), tiime(tiime) {}
//
//    // Check if the event has passed
//    bool hasPassed() const {
//        char str[26];
//        time_t now;
//        struct tm ltm;
//        time(&now);
//        localtime_s(&ltm, &now);
//
//        int currentYear = 1900 + ltm.tm_year;
//        int currentMonth = 1 + ltm.tm_mon;
//        int currentDay = ltm.tm_mday;
//        int currentHour = ltm.tm_hour;
//        int currentMinute = ltm.tm_min;
//
//        int eventYear, eventMonth, eventDay, eventHour, eventMinute;
//        sscanf_s(date.c_str(), "%d-%d-%d", &eventYear, &eventMonth, &eventDay);
//        sscanf_s(tiime.c_str(), "%d:%d", &eventHour, &eventMinute);
//
//        if (eventYear < currentYear) {
//            return true;
//        }
//        else if (eventYear == currentYear) {
//            if (eventMonth < currentMonth) {
//                return true;
//            }
//            else if (eventMonth == currentMonth) {
//                if (eventDay < currentDay) {
//                    return true;
//                }
//                else if (eventDay == currentDay) {
//                    if (eventHour < currentHour) {
//                        return true;
//                    }
//                    else if (eventHour == currentHour) {
//                        if (eventMinute <= currentMinute) {
//                            return true;
//                        }
//                    }
//                }
//            }
//        }
//
//        return false;
//    }
//};
//
//class CalendarNode {
//public:
//    Event event;
//    CalendarNode* left;
//    CalendarNode* right;
//
//    CalendarNode(const Event& e) : event(e), left(nullptr), right(nullptr) {}
//};
//
//class Calendar {
//private:
//    CalendarNode* root;
//
//public:
//    Calendar() : root(nullptr) {}
//
//    // Insert an event into the calendar
//    void insertEvent(const Event& event) {
//        root = insert(root, event);
//    }
//
//    // In-order traversal to display events in chronological order
//    void displayEventsInOrder() {
//        displayInOrder(root);
//    }
//
//    // Search for events on a specific date
//    void findEventsOnDate(const std::string& date) {
//        findEvents(root, date);
//    }
//
//private:
//    CalendarNode* insert(CalendarNode* node, const Event& event) {
//        if (node == nullptr) {
//            return new CalendarNode(event);
//        }
//
//        // Compare event dates to decide the placement in the BST
//        if (event.date < node->event.date) {
//            node->left = insert(node->left, event);
//        }
//        else if (event.date > node->event.date) {
//            node->right = insert(node->right, event);
//        }
//        else {
//            // If dates are the same, compare event times
//            if (event.tiime < node->event.tiime) {
//                node->left = insert(node->left, event);
//            }
//            else {
//                node->right = insert(node->right, event);
//            }
//        }
//
//        return node;
//    }
//
//    void displayInOrder(CalendarNode* node) {
//        if (node) {
//            displayInOrder(node->left);
//            if (node->event.hasPassed()) {
//                std::cout << "Event: " << node->event.name << ", Date: " << node->event.date << ", Time: " << node->event.tiime << "(Done)";
//            }
//            if (!node->event.hasPassed()) {
//                std::cout << "Upcoming Event: " << node->event.name << ", Date: " << node->event.date << ", Time: " << node->event.tiime;
//            }
//            std::cout << std::endl;
//            displayInOrder(node->right);
//        }
//    }
//
//    void findEvents(CalendarNode* node, const std::string& date) {
//        if (node) {
//            findEvents(node->left, date);
//            if (node->event.date == date) {
//                std::cout << "Event: " << node->event.name << ", Date: " << node->event.date << ", Time: " << node->event.tiime;
//                if (node->event.hasPassed()) {
//                    std::cout << " (Done)";
//                }
//                std::cout << std::endl;
//            }
//            findEvents(node->right, date);
//        }
//    }
//};
//
//int main() {
//    Calendar calendar;
//    calendar.insertEvent(Event("Meeting 1", "2023-11-01", "10:00 AM"));
//    calendar.insertEvent(Event("Lunch", "2023-11-01", "12:30 PM"));
//    calendar.insertEvent(Event("Conference Call", "2023-11-02", "3:00 PM"));
//    calendar.insertEvent(Event("Project Deadline", "2023-11-03", "11:59 PM"));
//    calendar.insertEvent(Event("Team Meeting", "2023-11-04", "2:30 PM"));
//
//    
//    calendar.displayEventsInOrder();
//
//    std::cout << "\nEvents on 2023-11-01:" << std::endl;
//    calendar.findEventsOnDate("2023-11-01");
//
//    return 0;
//}