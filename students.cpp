
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <math.h>

using namespace std;

class Student
{
    public:
        int ID,age;
        string Name,Major;
        float GPA;
    Student(int id,int a,string name,string major,float gpa)
    {
        ID=id;
        age=a;
        Name=name;
        Major=major;
        GPA=gpa;
    }
    Student(vector<string> inp)
    {
        ID = stoi(inp[0]);
        Name = inp[1];
        age = stoi(inp[2]);
        Major = inp[3];
        GPA = stof(inp[4]);
    }
};

vector<Student> students;   

void read(string filename="students.csv")
{
    string line,val;
    fstream file;
    file.open(filename,ios::in);
    bool firstLine = true;  // To avoid reading the column names
    if (file)
    {
        while(getline(file,line))
        {
            if (firstLine)
            {
                firstLine=false;
                continue;
            }

            vector<string> vals;
            stringstream ss(line);
            while (getline(ss,val,',')){
                vals.push_back(val);
            }
            Student stu(vals);
            students.push_back(stu);    
        }
    }
    file.close();
}

void display(vector<Student> stu=students)
{
    cout << left << setw(10) << "ID"
         << setw(15) << "Name"
         << setw(10) << "Age"
         << setw(20) << "Major"
         << setw(5) << "GPA" << endl;
    for (Student student : stu)
    {
        cout << left << setw(10) << student.ID
             << setw(15) << student.Name
             << setw(10) << student.age
             << setw(20) << student.Major
             << setw(5) << student.GPA << endl;
    }
}

vector<Student> filterGPA(float n)
{
    vector<Student> filtered;
    filtered.clear();
    for (Student student : students)
    {
        if (student.GPA > n)
        {
            filtered.push_back(student);
        }
    }
    return filtered;
}

float avgAge()
{
    int sum=0, count=0;
    for (Student student : students)
    {
        sum+=student.age;
        count++;
    }
    return float(sum)/count;
}

void write(string filename="filtered_students.csv", vector<Student> stu=students)
{
    fstream file;
    file.open(filename,ios::out);
    file << "ID,Name,Age,Major,GPA" << endl;
    if (file)
    {
        for (Student student : stu)
        {
            file << student.ID << ","
                << student.Name << ","
                << student.age << ","
                << student.Major << ","
                << student.GPA << endl;
        }
        cout << "Data written successfully to " << filename << endl;
    }
    file.close();
}

int main()
{
    read();
    display(); // Displaying All Students
    cout << endl;
    display(filterGPA(3.0)); // Displaying only Students with GPA Higher than 3.0
    cout << endl;
    cout << "Average Age: " << avgAge() << endl; //Displaying Average Age
    write("filtered_students.csv", filterGPA(3.0)); // Writing to CSV
    return 0;
}
