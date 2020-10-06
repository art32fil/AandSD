#include "../Headers/Workspace.h"

Workspace::Workspace(){}

void Workspace::ChooseInput(){
    Workspace method;
    cout << "Please select a data entry method" << endl;
    cout << "Press \"1\" if the console" << endl;
    cout << "Press \"2\" if the file" << endl;
    string choice;
    getline(cin, choice);
    switch (choice[0]) {
        case '1':
            method.Console();
            break;
        case '2':
            cout << "Please enter filename: ";
            getline(cin, inputFile);
            method.File(inputFile);
            break;
        default:
            cout << "The entered digit does not match the input options" << endl;
            break;
    }
}

void Workspace::Console(){
    cout << "Enter the line: ";
    getline(cin, line);
    cout << Workspace::Output(line, recursion.Run(Workspace::ClearSymbols(line))) << endl;
}

void Workspace::File(string inputFile, bool showDepth){
    input.open(inputFile);
    output.open("output.txt");
    if (input.is_open() && output.is_open()){
        while (getline(input, line)){
            cout << "Checking line: " << line << endl;
            output << Workspace::Output(line, isBrackets = recursion.Run(Workspace::ClearSymbols(line), 0, 0, showDepth)) << endl;
            cout << Workspace::Output(line, isBrackets) << endl;
        }
        cout << "The program has been completed. The result is written to the file \"output.txt\"" << endl;
    } else {
        cout << "Can't open file" << endl;
    }
    input.close();
    output.close();
}

string Workspace::ClearSymbols(string line){
    for (int i = 0; i < line.length(); i++){
        if ((line[i] == ' ') || (line[i] == '\t')) {
            line.erase(i, 1);
            i--;
        }
    }
    return line;
}

string Workspace::Output(string line, bool isBrackets){
    if (isBrackets){
        return line + " - THIS IS A BRACKETS";
    } else {
        return line + " - THIS IS NOT A BRACKETS";
    }
}
