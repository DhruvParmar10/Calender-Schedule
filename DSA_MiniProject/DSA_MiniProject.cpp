#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
using namespace std;

class Event {
public:
    string name;
    string date;
    string time;
    bool isDone;

    Event(const string& name, const string& date, const string& time){
        this->name = name;
        this->date = date;
        this->time = time;
        this->isDone = false;
    }
    bool hasPassed() const {
        time_t now;
        struct tm ltm;
        std::time(&now);
        localtime_s(&ltm, &now);

        int currentYear = 1900 + ltm.tm_year;
        int currentMonth = 1 + ltm.tm_mon;
        int currentDay = ltm.tm_mday;
        int currentHour = ltm.tm_hour;
        int currentMinute = ltm.tm_min;

        int eventYear, eventMonth, eventDay, eventHour, eventMinute;
        sscanf_s(date.c_str(), "%d-%d-%d", &eventYear, &eventMonth, &eventDay);
        sscanf_s(time.c_str(), "%d:%d", &eventHour, &eventMinute);

        if (eventYear < currentYear) {
            return true;
        }
        else if (eventYear == currentYear) {
            if (eventMonth < currentMonth) {
                return true;
            }
            else if (eventMonth == currentMonth) {
                if (eventDay < currentDay) {
                    return true;
                }
                else if (eventDay == currentDay) {
                    if (eventHour < currentHour) {
                        return true;
                    }
                    else if (eventHour == currentHour) {
                        if (eventMinute <= currentMinute) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }
};

class CalendarNode {
public:
    Event event;
    CalendarNode* left;
    CalendarNode* right;

    CalendarNode(const Event& e) : event(e), left(nullptr), right(nullptr) {}
};

class Calendar {
private:
    CalendarNode* root;

public:
    Calendar(){
        root = nullptr;
    }

    void insertEvent(const Event& event) {
        root = insert(root, event);
    }

    void displayEventsInOrder(int val) {
        displayInOrder(root, val);
    }

    /*void displayEventsPassedInOrder() {
        displayDoneInOrder(root);
    }*/

    void findEventsOnDate(const std::string& date) {
        findEvents(root, date);
    }

private:
    CalendarNode* insert(CalendarNode* node, const Event& event) {
        if (node == nullptr) {
            return new CalendarNode(event);
        }

        if (event.date < node->event.date) {
            node->left = insert(node->left, event);
        }
        else if (event.date > node->event.date) {
            node->right = insert(node->right, event);
        }
        else {
            if (event.time < node->event.time) {
                node->left = insert(node->left, event);
            }
            else {
                node->right = insert(node->right, event);
            }
        }

        return node;
    }

    void displayInOrder(CalendarNode* node, int val) {
        if (node) {
            displayInOrder(node->left, val);
            if (val == 1)
            {
                if (node->event.hasPassed()) {
                    std::cout << "Event: " << node->event.name << ", Date: " << node->event.date << ", Time: " << node->event.time << " **DONE**";
                }
            }
            else if (val == 2)
            {
                if(!node->event.hasPassed()) {
                    std::cout << "Upcoming Event: " << node->event.name << ", Date: " << node->event.date << ", Time: " << node->event.time;
                }
            }
            else
            {
                if (node->event.hasPassed()) {
                    std::cout << "Event: " << node->event.name << ", Date: " << node->event.date << ", Time: " << node->event.time << " **DONE**";
                }
                if (!node->event.hasPassed()) {
                    std::cout << "Upcoming Event: " << node->event.name << ", Date: " << node->event.date << ", Time: " << node->event.time;
                }
            }
            cout << endl;
            displayInOrder(node->right, val);
        }
    }

    /*void displayDoneInOrder(CalendarNode* node) {
        if (node) {
            displayInOrder(node->left);
            if (node->event.hasPassed()) {
                std::cout << "Event: " << node->event.name << ", Date: " << node->event.date << ", Time: " << node->event.time << " **DONE**";
            }
            if (!node->event.hasPassed()) {
                std::cout << "Upcoming Event: " << node->event.name << ", Date: " << node->event.date << ", Time: " << node->event.time;
            }
            std::cout << std::endl;
            displayInOrder(node->right);
        }
    }*/

    void findEvents(CalendarNode* node, const std::string& date) {
        if (node) {
            findEvents(node->left, date);
            if (node->event.date == date) {
                std::cout << "Event: " << node->event.name << ", Date: " << node->event.date << ", Time: " << node->event.time;
                if (node->event.hasPassed()) {
                    std::cout << " (Done)";
                }
                std::cout << std::endl;
            }
            findEvents(node->right, date);
        }
    }
};

int main() {
    Calendar calendar;
    calendar.insertEvent(Event("Meeting 1", "2023-11-01", "10:00 AM"));
    calendar.insertEvent(Event("Gaming Time", "2023-11-01", "3:30 PM"));
    calendar.insertEvent(Event("Lunch", "2023-11-01", "12:30 PM"));
    calendar.insertEvent(Event("Lunch", "2023-11-02", "12:30 PM"));
    calendar.insertEvent(Event("Conference Call", "2023-11-02", "3:00 PM"));
    calendar.insertEvent(Event("Project Deadline", "2023-11-03", "11:59 PM"));
    calendar.insertEvent(Event("Team Meeting", "2023-11-04", "2:30 PM"));

    
    //calendar.displayEventsPassedInOrder();
    //calendar.displayEventsInOrder();
    

    /*cout << "\nEvents on 2023-11-01:" << endl;
    calendar.findEventsOnDate("2023-11-01");*/

    /*cout << "\nEvents on 2023-11-02:" << endl;
    calendar.findEventsOnDate("2023-11-02");*/

    int n = 0;
    while (n != -1)
    {   
        cout << "----------------------------------------" << endl;
        cout << "1.Check Schedule" << endl;
        cout << "2.Arrage a schedule" << endl;
        cout << "3.Check Schedule on Specific date" << endl;
        cout << "4.Upcoming Schedule" << endl;
        cout << "5.Done Schedule" << endl;
        cout << "-1.Exit" << endl;
        cout << "----------------------------------------" << endl;
        cin >> n;
        string name;
        string date;
        string time;
        string test;
        switch (n)
        {
        case 1:
            cout << "----------------------------------------" << endl;
            calendar.displayEventsInOrder(3);
            break;
        case 2:
            cout << "----------------------------------------" << endl;
            getline(cin, test);
            cout << "Enter event NAME: ";
            getline(cin, name);
            cout << "Enter event DATE(YYYY-MM-DD): ";
            getline(cin, date);
            cout << "Enter even TIME(HH:MM AM/PM): ";
            getline(cin, time);
            calendar.insertEvent(Event(name, date, time));
            break;
        case 3:
            cout << "Enter event DATE(YYYY-MM-DD): ";
            cin >> date;
            cout << "----------------------------------------" << endl;
            cout << "Events on "<<date<<":" << endl;
            calendar.findEventsOnDate(date);
            break;
        case 4:
            cout << "----------------------------------------" << endl;
            calendar.displayEventsInOrder(2);
            break;
        case 5:
            cout << "----------------------------------------" << endl;
            calendar.displayEventsInOrder(1);
            break;
        default:
            break;
        }
    }


    return 0;
}
