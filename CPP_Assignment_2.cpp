#include <iostream>
#include <fstream>
#include <string.h>


void printLines();

class Student{
    private:
        int m_rollNo;
        std::string m_name;
        float m_marks;
    public:
        Student() : m_rollNo(0), m_name("Default"), m_marks(0.0f) {}

        Student(int rollNo, std::string name, float marks) : m_rollNo(rollNo), m_name(name), m_marks(marks) {}

        void inputDetails()
        {
            std::cout << "Enter Roll No: ";
            std::cin >> m_rollNo;
            std::cout << "Enter Name: ";
            std::cin >> m_name;
            std::cout << "Enter Marks: ";
            std::cin >> m_marks;
            
            printLines();
        }

        void displayDetails()
        {
            std::cout << "Roll No => " << m_rollNo << std::endl;
            std::cout << "Name    => " << m_name << std::endl;
            std::cout << "Marks   => " << m_marks << std::endl;

            printLines();
        }

        void saveToFile(const std::string fileName)
        {
            std::ofstream fileOut(fileName, std::ios::app);
            fileOut << m_rollNo << " " << m_name << " " << m_marks << std::endl;
            fileOut.close();
        }

        void loadFromFile(const std::string fileName)
        {
            std::ifstream fileIn(fileName, std::ios::in);
            std::string lines;
            char space = ' ';
            while(getline(fileIn,lines)){
                for (int i = 0; i < lines.length(); i++){
                    if ((char)lines[i] == space){
                        if (lines.substr(0,i) == std::to_string(m_rollNo)){
                            std::string objData = lines;
                            std::cout << "Roll No => " << lines.substr(0,i) << std::endl;
                            for (int j = i+1; j < lines.length(); j++){
                                if ((char)lines[j] == space){
                                std::cout << "Name => " << lines.substr(i,j-1) << std::endl;
                                std::cout << "Marks => " << lines.substr(j,lines.length()) << std::endl;
                                printLines();
                                break;
                                }
                            }
                        }
                        break;
                    }
                }
            }
            fileIn.close();       
        }
};



void addStudent(const std::string& fileName)
{
    Student s;
    s.inputDetails();
    s.saveToFile(fileName);
    std::cout << "Student added successfully !" << std::endl;
    printLines();
}

void displayAllStudents(const std::string& fileName)
{
    std::ifstream fileIn(fileName, std::ios::in);
    std::string lines;
    char space = ' ';
    fileIn.seekg(0);
    std::cout << "Student List: " << std::endl;
    while(getline(fileIn,lines)){
        std::cout << lines << std::endl;
    }
    printLines();
}    

void searchStudent(std::string& fileName)
{
    int m_rollNo;
    std::cout << "Enter Roll No: ";
    std::cin >> m_rollNo;
    printLines();

    std::ifstream fileIn(fileName, std::ios::in);
    std::string lines;
    bool flag = false;
    char space = ' ';
    while(getline(fileIn,lines)){
        for (int i = 0; i < lines.length(); i++){
            if ((char)lines[i] == space){
                if (lines.substr(0,i) == std::to_string(m_rollNo)){
                    flag = true;
                    std::cout << "Student found: " << std::endl;
                    std::cout << "Details are as Follows: " << std::endl;
                    std::cout << "Roll No => " << lines.substr(0,i) << std::endl;
                    for (int j = i+1; j < lines.length(); j++){
                        if ((char)lines[j] == space){
                        std::cout << "Name => " << lines.substr(i,j-1) << std::endl;
                        std::cout << "Marks => " << lines.substr(j,lines.length()) << std::endl;
                        printLines();
                        break;
                        }
                    }
                }
                break;
            }
        }
    }
    if (flag == false){
        std::cout << "No Record Found !" << std::endl;
        printLines();
    }
    fileIn.close();    
}


void printLines() 
{
    for (int i = 0; i <= 30; i++) 
    std::cout << "-"; 
    std::cout << std::endl;
}


int main()
{
    std::string fileName = "testing/record.txt";
    
    int choice = 1;
    do{
        std::cout << "Student Management System (By Gunveer Singh)" << std::endl;
        std::cout << "1. Add Student" << std::endl;
        std::cout << "2. Display All Students" << std::endl;
        std::cout << "3. Search Student" << std::endl;
        std::cout << "4. Exit" << std::endl;
        
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice){
            case 1:
                addStudent(fileName);
                break;
            case 2:
                displayAllStudents(fileName);
                break;
            case 3:
                searchStudent(fileName);
                break;
            case 4:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Please Enter Valid Choice !" << std::endl;
        }
    
    } while(choice != 4);


}
