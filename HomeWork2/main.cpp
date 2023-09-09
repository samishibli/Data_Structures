#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// needs to be compiled with c++11

class Student
{
public:
    Student(double x) : serviceTime(x) {}
    double getServiceTime() const { return serviceTime; }

private:
    double serviceTime;
};
// 20% chance student arrives
bool studentArrival() { return (rand() % 5 == 0); }

// populate queue with students
void studentLine(queue<Student> &line)
{
    for (int i = 0; i < 60; i++)
    {
        if (studentArrival())
        {
            // give student time for how long question will be
            Student s = Student(rand() % 10 + 1);
            line.push(s);
        }
    }
}
double avgTimeSpentWaiting(queue<Student> &line)
{
    // get the running sum of the queue
    // push each iteration into vector
    vector<double> runningSum;
    double sum = 0;
    while (!line.empty())
    {
        Student currentStudent = line.front();
        sum += currentStudent.getServiceTime();
        line.pop();
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
double avgTimeSpentForQuestion(queue<Student> &line)
{
    double sum = 0;
    double count = line.size();
    // sum the values of the queue and divide by size
    while (!line.empty())
    {
        Student currentStudent = line.front();
        line.pop();
        sum += currentStudent.getServiceTime();
    }

    double avg = sum / count;
    return avg;
}

double totalTimeLeft = 60;
double officeHourSimulation(queue<Student> &line)
{
    // serve students within 1 hour period
    while (totalTimeLeft > 0)
    {
        Student currentStudent = line.front();
        totalTimeLeft -= currentStudent.getServiceTime();
        line.pop();
    }
    double n = line.size();
    double extraTime = 0;
    // seperate loop to determine the average time helping beyond 1 hour
    while (totalTimeLeft <= 0 && !line.empty())
    {
        Student remainingStudent = line.front();
        extraTime += remainingStudent.getServiceTime();
        line.pop();
    }
    double avgExtraTime = 0;
    if (extraTime == 0)
        return avgExtraTime;
    else
        avgExtraTime = extraTime / n;
    return avgExtraTime;
}

int main()
{
    srand(time(NULL));
    vector<double> timeWaiting;
    for (int i = 0; i <= 100; i++)
    {
        queue<Student> line;
        studentLine(line);
        timeWaiting.push_back(avgTimeSpentWaiting(line));
    }
    double avgTime = 0;
    for (auto k : timeWaiting)
    {
        avgTime += k;
    }
    avgTime /= timeWaiting.size();
    cout << endl;
    cout << "Average time spent Waiting: " << avgTime << " minutes!" << endl
         << endl;

    vector<double> timeForQuestions;
    for (int i = 0; i <= 100; i++)
    {
        queue<Student> line2;
        studentLine(line2);
        timeForQuestions.push_back(avgTimeSpentForQuestion(line2));
    }
    double avgQuestionTime = 0;
    for (auto k : timeForQuestions)
    {
        avgQuestionTime += k;
    }
    avgQuestionTime /= timeForQuestions.size();
    cout << "Average time students spend on questions: " << avgQuestionTime << " minutes!" << endl
         << endl;

    vector<double> avgExtra;
    for (int i = 0; i <= 100; i++)
    {
        queue<Student> line3;
        studentLine(line3);
        double result = officeHourSimulation(line3);
        avgExtra.push_back(result);
    }
    double avgResult = 0;
    for (auto e : avgExtra)
    {
        avgResult += e;
    }
    avgResult /= avgExtra.size();
    cout << "Average time professor spends beyond 1 hour period: " << avgResult << " minutes!" << endl
         << endl;

    return 0;
}