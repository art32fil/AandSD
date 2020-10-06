#include "../Headers/Recursion.h"

Recursion::Recursion(){}

bool Recursion::Run(string line, int position, int depth, bool showDepth){
    isBrackets = false;
    if (showDepth) cout << string(depth,' ') << "Depth " << depth << " - joining" << endl;
    switch(line[position]){
        case 'A':
            if (line.length() == 1) {
                isBrackets = true;
                break;
            }
            if (line[position + 1] == '\0') {
                isBrackets = true;
                break;
            }
            if (line[position + 1] != '(' && line[position + 1] != 'B' && line[position + 1] != 'A') {
                isBrackets = Recursion::Run(line, position + 1, depth + 1, showDepth);
            }
            break;
        case '(':
            if (line[position+1] == 'B'){
                isBrackets = Recursion::Run(line, position + 1, depth + 1, showDepth);
            }
            break;
        case 'B':
            if (line[position + 1] != 'B'){
                isBrackets = Recursion::Run(line, position + 1, depth + 1, showDepth);
            }
            break;
        case ')':
            if (line[position + 1] != 'B'){
                isBrackets = Recursion::Run(line, position + 1, depth + 1, showDepth);
            }
            break;
        default:
            isBrackets = false;
            break;
    }
    if (showDepth) cout << string(depth,' ') << "Depth " << depth << " - exiting" << endl;
    return isBrackets;
}
