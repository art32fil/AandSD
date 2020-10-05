#include <iostream>
#include <fstream>

static int current_index = 0;

bool is_operation_sign(std::string &str, std::ofstream &file);
bool is_row_of_numbers(std::string &str, std::ofstream &file);
bool analyzer(std::string &str, std::ofstream &file);
void Errors(int error, std::string &str, std::ofstream &file);

int main(){
    std::string file_name, parsed_string;
    std::cin >> file_name;
    std::fstream input_file(file_name);
    std::ofstream out;
    out.open("Output.txt");

    if (input_file.is_open())
        std::cout << "Success! File open!" << std::endl;
    else{
        std::cout << "Error! Wrong name of input file!!" << std::endl;
        return 0;
    }

    while(getline(input_file, parsed_string)){
        current_index = 0;
        out << "\"" << parsed_string << "\":\n";
        std::cout << "\"" << parsed_string << "\":\n";
        if (analyzer(parsed_string, out)){
            out << "Wow! Expression \"" << parsed_string << "\" is a constant expression!\n\n";
            std::cout << "Wow! Expression \"" << parsed_string << "\" is a constant expression!\n\n";
        }
    }
    out.close();
    return 0;
}

bool analyzer(std::string &str, std::ofstream &file){
    if(!isdigit(str[0])){
        Errors(3, str, file);
        return false;
    }
    else
        return is_row_of_numbers(str, file);
}

bool is_operation_sign(std::string &str, std::ofstream &file){
    if ((str[current_index] == '*') || (str[current_index] == '+') || (str[current_index] == '-')) {
        std::cout << "Current symbol: operation sign \"" << str[current_index] << "\"\n";
        file << "Current symbol: operation sign \"" << str[current_index] << "\"\n";
        if((str[current_index - 1] == '*') || (str[current_index - 1] == '+') || (str[current_index - 1] == '-')){
            Errors(1, str, file);
            return false;
        }
        current_index += 1;
        if(current_index == str.length()){
            Errors(2, str, file);
            return false;
        }
        return is_row_of_numbers(str, file);
    }
    else{
        file << "Current symbol: unknown symbol \"" << str[current_index] << "\"\n";
        std::cout << "Current symbol: unknown symbol \"" << str[current_index] << "\"\n";
        Errors(3, str, file);
        return false;
    }
}

bool is_row_of_numbers(std::string &str, std::ofstream &file){
    if(current_index == str.length())
        return true;
    if(isdigit(str[current_index])){
        file << "Current symbol: numeral \"" << str[current_index] << "\"\n";
        std::cout << "Current symbol: numeral \"" << str[current_index] << "\"\n";
        current_index += 1;
        return is_row_of_numbers(str, file);
    }
    else
        return is_operation_sign(str, file);
}

void Errors(int error, std::string &str, std::ofstream &file){
    switch(error){
        case 1:
            file << "Error! Two signs of operation in a row!\n\n";
            std::cout << "Error! Two signs of operation in a row!\n\n";
            break;
        case 2:
            file << "Error! The expression ends with an operation character!\n\n";
            std::cout << "Error! The expression ends with an operation character!\n\n";
            break;
        default:
            file << "Error! An unknown symbol has been encountered!\n\n";
            std::cout << "Error! An unknown symbol has been encountered!\n\n";
    }
}

