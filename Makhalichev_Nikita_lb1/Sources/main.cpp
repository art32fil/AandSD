#include "../Headers/Workspace.h"
#include "../Headers/Test.h"

int main(int argc, char **argv){
    string arg;
    if (argc == 2){
        arg = argv[1];
    }
    if (arg == "test"){
        Test::Run();
    } else {
        Workspace a;
        a.ChooseInput();
    }
    return 0;
}
