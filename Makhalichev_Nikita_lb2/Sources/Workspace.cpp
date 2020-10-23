#include "../Headers/Workspace.h"

Workspace::Workspace(){}

string Workspace::TransformLine(string line){
    reverse(line.begin(), line.end());
    line = ClearSymbols(line);
    return line;
}

void Workspace::ChooseInput(){
    Workspace method;
    cout << "Please select a data entry method" << endl;
    cout << "Press \"1\" if the console" << endl;
    cout << "Press \"2\" if the file" << endl;
    string choice;
    getline(cin, choice);
    switch (choice[0]){
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
    string out_line;
    cout << "Enter the line: ";
    getline(cin, line);
    string copy = TransformLine(line);
    read_lisp(x, &copy);
    write_lisp(x, out_line);
    int res = depth_search(x);
    destroy(x);
    cout << "List is:" << out_line << " - " << res;
    cout << endl;
}

void Workspace::File(string inputFile){
    input.open(inputFile);
    output.open("output.txt");
    if (input.is_open() && output.is_open()){
        while (getline(input, line)){
            string out_line;
            string copy = TransformLine(line);
            read_lisp(x, &copy);
            write_lisp(x, out_line);
            int res = depth_search(x);
            destroy(x);
            output << out_line << " - " << res << endl;
            cout << "List is:" << out_line << " - " << res;
            cout << endl;
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
