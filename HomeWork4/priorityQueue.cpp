#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <ctime>
#include <fstream>
#include <random>
#include <map>
#include <algorithm>

using namespace std;
// global variables
double timeSpentOnQuestions = 0;
double timeSpentBeyondHour = 0;

class Student
{
public:
    Student(double x) : serviceTime(x) {}
    Student(double x, double y) : serviceTime(x), priority(y) {}
    double getServiceTime() const { return serviceTime; }
    double getPriority() const { return priority; }

    friend std::ostream &operator<<(std::ostream &os, const Student &student)
    {
        os << "Service Time: " << student.serviceTime
           << ", Priority: " << student.priority;
        return os;
    }
    friend bool operator<(const Student &lhs, const Student &rhs)
    {
        return lhs.priority < rhs.priority;
    }

private:
    double serviceTime;
    double priority;
};

bool studentArrival() { return (rand() % 3 == 0); }
void populateQueue(priority_queue<Student> &studentLine);
double avgTimeSpentWaiting(priority_queue<Student> &studentLine);
void officeHours(priority_queue<Student> &studentLine, double &avgWaitingTime, double &avgTimeWithProfessor, double &avgTimeBeyondHour, multimap<string, set<string>> &officeHoursReport);
string getRandomName(const string &fileName);
string getRandomTopic(const string &fileName);
set<string> readTopicsFromFile(const string &fileName, int numTopics);
void outputMapToFile(const multimap<string, set<string>> &officeHoursReport);
int numberOfAppearences(const multimap<string, set<string>> &officeHoursMap, string studentName);
int main()
{
    multimap<string, set<string>> officeHoursReport;
    double avgWaitingTime = 0;
    double avgTimeWithProfessor = 0;
    double avgTimeBeyondHour = 0;
    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        int numTopics = rand() % 12 + 1;
        priority_queue<Student> officeHoursLine;
        populateQueue(officeHoursLine);
        officeHours(officeHoursLine, avgWaitingTime, avgTimeWithProfessor, avgTimeBeyondHour, officeHoursReport);
        outputMapToFile(officeHoursReport);

        // set<string> topics = readTopicsFromFile("csTopics.txt", numTopics);
        // // ofstream outFile("office_hour_" + to_string(i + 1) + ".txt");
        // // if (outFile.is_open())
        // // {
        // //     for (const auto &question : topics)
        // //     {
        // //         outFile << question << endl;
        // //     }
        // //     outFile.close();
        // // }
    }

    avgWaitingTime /= 100;
    avgTimeWithProfessor /= 100;
    avgTimeBeyondHour /= 100;

    cout << "Average time spent waiting: " << avgWaitingTime << " minutes" << endl;
    cout << "Average time spent with the professor: " << avgTimeWithProfessor << " minutes" << endl;
    cout << "Average time the professor spends beyond 1 hour: " << avgTimeBeyondHour << " minutes" << endl;

    return 0;
}
void populateQueue(priority_queue<Student> &studentLine)
{
    // srand(time(NULL));
    for (int i = 0; i < 60; i++)
    {
        if (studentArrival())
        {
            double timeForService = rand() % 10 + 1;
            // priority made with 15 being the highest, 1 being the lowest
            double priorityInQueue = rand() % 15 + 1;
            Student newStudent = Student(timeForService, priorityInQueue);
            studentLine.push(newStudent);
        }
    }
}
double avgTimeSpentWaiting(priority_queue<Student> &studentLine)
{
    // get the running sum of the queue
    // push each iteration into vector
    vector<double> runningSum;
    double sum = 0;
    while (!studentLine.empty())
    {
        Student currentStudent = studentLine.top();
        sum += currentStudent.getServiceTime();
        studentLine.pop();
        runningSum.push_back(sum);
    }
    double vectorSum = 0;
    // return avg from the vector of running sums
    for (auto e : runningSum)
    {
        vectorSum += e;
    }
    double n = runningSum.size();
    return vectorSum / n;
}
void officeHours(priority_queue<Student> &studentLine, double &avgWaitingTime, double &avgTimeWithProfessor, double &avgTimeBeyondHour, multimap<string, set<string>> &officeHoursReport)
{
    double totalTimeLeft = 60;
    double studentCountBeyondHour = 0;
    double studentCount = 0;
    double totalWaitingTime = 0;
    double totalProfessorTime = 0;
    double totalBeyondHourTime = 0;
    while (!studentLine.empty() && totalTimeLeft > 0)
    {
        Student currentStudent = studentLine.top();
        studentLine.pop();

        if (currentStudent.getServiceTime() <= totalTimeLeft)
        {
            totalTimeLeft -= currentStudent.getServiceTime();
            totalWaitingTime += currentStudent.getServiceTime();
            totalProfessorTime += currentStudent.getServiceTime();
        }
        else
        {
            double timeBeyondHour = currentStudent.getServiceTime() - totalTimeLeft;
            totalWaitingTime += currentStudent.getServiceTime();
            totalBeyondHourTime += timeBeyondHour;
            studentCountBeyondHour++;
            totalTimeLeft = 0;
        }
        studentCount++;
        // push the students name and they're topic to the multi-map
        string studentName = getRandomName("namesOfStudent.txt");
        string studentTopic = getRandomTopic("csTopics.txt");
        // if student name is not in map insert new key and topic
        auto range = officeHoursReport.equal_range(studentName);
        // Check if any matching student name is found in the multimap
        bool foundMatchingStudent = false;
        for (auto it = range.first; it != range.second; ++it)
        {
            if (it->first == studentName)
            {
                it->second.insert(studentTopic);
                foundMatchingStudent = true;
                break;
            }
        }
        // If no matching student name is found, insert a new key and topic
        if (!foundMatchingStudent)
        {
            officeHoursReport.insert({studentName, {studentTopic}});
        }
        // else find matching student name and insert topic into their unique set
    }
    avgWaitingTime += totalWaitingTime / studentCount;
    avgTimeWithProfessor += totalProfessorTime / studentCount;
    avgTimeBeyondHour += totalBeyondHourTime / studentCountBeyondHour;
}
// set<string> readTopicsFromFile(const string &fileName, int numTopics)
// {
//     ifstream inputFile(fileName);
//     set<string> allTopics;
//     // read in topics from the file. Only read in one topic for each student
//     if (inputFile.is_open())
//     {
//         string line;
//         while (getline(inputFile, line))
//         {
//             allTopics.insert(line);
//         }
//         inputFile.close();
//     }
//     // makes sure all the topics are different for each office hours
//     vector<string> allTopicsVector(allTopics.begin(), allTopics.end());
//     random_device rd;
//     mt19937 generator(rd());
//     shuffle(allTopicsVector.begin(), allTopicsVector.end(), generator);
//     set<string> topics;
//     for (int i = 0; i <= numTopics && i < allTopicsVector.size(); i++)
//     {
//         topics.insert(allTopicsVector[i]);
//     }
//     return topics;
// }
// helper function to randomly decide which student shows up and what topic they discuss
string getRandomName(const string &fileName)
{
    vector<string> names;
    ifstream inputFile(fileName);

    if (inputFile.is_open())
    {
        string name;
        while (getline(inputFile, name))
        {
            names.push_back(name);
        }
        inputFile.close();

        if (!names.empty())
        {
            random_device rd;
            mt19937 generator(rd());
            uniform_int_distribution<int> distribution(0, names.size() - 1);
            int randomIndex = distribution(generator);
            return names[randomIndex];
        }
    }
    return ""; // Return an empty string if the file is empty or cannot be opened
}
string getRandomTopic(const string &fileName)
{
    vector<string> topics;
    ifstream inputFile(fileName);

    if (inputFile.is_open())
    {
        string name;
        while (getline(inputFile, name))
        {
            topics.push_back(name);
        }
        inputFile.close();

        if (!topics.empty())
        {
            random_device rd;
            mt19937 generator(rd());
            uniform_int_distribution<int> distribution(0, topics.size() - 1);
            int randomIndex = distribution(generator);
            return topics[randomIndex];
        }
    }
    return ""; // Return an empty string if the file is empty or cannot be opened
}
int numberOfAppearences(const multimap<string, set<string>> &officeHoursMap, string studentName)
{
    auto range = officeHoursMap.equal_range(studentName);
    int count = distance(range.first, range.second);
    return count;
}
void outputMapToFile(const multimap<string, set<string>> &officeHoursMap)
{
    for (const auto &entry : officeHoursMap)
    {
        ofstream outputfile(entry.first + ".txt");
        outputfile << entry.first << " showed up " << numberOfAppearences(officeHoursMap, entry.first) << " time(s)" << endl
                   << "Topics they discussed: ";
        for (const auto &topic : entry.second)
        {

            outputfile << topic << ", ";
        }
        outputfile << endl;
        outputfile.close();
    }
}
