#include "../Headers/Test.h"

Test::Test(){}

void Test::Run(){
    Test test;
    DIR *myDir = opendir("./Tests/ToCheck");
    if(myDir == NULL) {
        perror("Unable to open directory ./Tests/ToCheck");
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(myDir)) != nullptr){
        test.File(entry->d_name);
    }
    closedir(myDir);
}

void Test::File(char *name){
    inputFile = name;
    if ((inputFile != ".") && (inputFile != "..")){
        directory = "./Tests/ToCheck/";
        cout << ORANGE "Comparing file " RESET << inputFile << endl;
        workspace.File(directory + inputFile, false);
        Test::Compare(inputFile);
    }
}

void Test::Compare(string inputFile){
    inputFromOutput.open("output.txt");
    inputFromAnswers.open("./Tests/Answers/" + inputFile);
    if (inputFromOutput.is_open() && inputFromAnswers.is_open()){
        while (getline(inputFromOutput, lineOutput) && getline(inputFromAnswers, lineAnswers)){
            if (lineOutput == lineAnswers){
                cout << GREEN "Correct answer - " RESET << lineAnswers << endl;
            } else {
                cout << RED "Not correct answer - " RESET << lineAnswers << RED "\n - Program response - " RESET << lineOutput << endl;
            }
        }
    }
    inputFromOutput.close();
    inputFromAnswers.close();
}
