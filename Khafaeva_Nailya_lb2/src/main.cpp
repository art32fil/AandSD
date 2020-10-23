#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct BinRocker;
struct Shoulder;
struct Cargo;

void start_read_from_file(BinRocker* rocker, ifstream& input_file);
void read_BinRocker_from_file(char prev, BinRocker* rocker, ifstream& input_file);
Shoulder* read_shoulder_from_file(ifstream& input_file);
void detour_shoulder(Shoulder* sh, int& result, int& level);
void detour_rocker(BinRocker* rocker, int& result, int& level);
void output_result(const int level, const int result);
unsigned int numbers (const BinRocker* rocker);
void Destroy(BinRocker* rocker);
void Destroy_shoulder(Shoulder* sh);
void write_shoulder(Shoulder* sh);
void write_binR(BinRocker* rocker);

struct BinRocker {  // коромысло
    Shoulder *sh1 = nullptr;
    Shoulder *sh2 = nullptr;

};

struct Shoulder {   // плечо
    int length = 0;
    Cargo *obj = nullptr;
    bool cond = false;
};

struct Cargo {    //объект
    int weight = 0;
    BinRocker *binR = nullptr;
};

int main() {
    string input_file;
    BinRocker *rocker = new BinRocker;
    cout << "Enter file name: " << endl;
    getline(cin, input_file);
    ifstream input(input_file);

    if (!input) {
        cout << "Input file is invalid." << endl;
        return 0;
    } else {
        start_read_from_file(rocker, input);
    }

    write_binR(rocker);
    cout << endl;
    int k = numbers(rocker);

    cout << "numbers = " << k << endl;

    return 0;

}

void start_read_from_file(BinRocker* rocker, ifstream& input_file) {
    char buf;
    input_file.get(buf);
    if (buf == '(') {
        read_BinRocker_from_file(buf, rocker, input_file);
    }

}

void read_BinRocker_from_file(char prev, BinRocker* rocker, ifstream& input_file) {
    if (prev == '(') {
        rocker->sh1 = read_shoulder_from_file(input_file);
        if (rocker->sh1 == nullptr) {
            cout << "Error." << endl;
            exit(0);
        }
        char buf;
        input_file.get(buf);

        rocker->sh2 = read_shoulder_from_file(input_file);
        if (rocker->sh2 == nullptr) {
            cout << "Error." << endl;
            exit(0);
        }
        input_file.get(buf);
        if (buf != ')') {
            cout << "Error." << endl;
            exit(0);
        }
    }
    else {
        cout << "Error." << endl;
        exit(0);
    }
}

Shoulder* read_shoulder_from_file(ifstream& input_file) {
    char buf;
    Shoulder* sh = new Shoulder;
    input_file.get(buf);
    if (buf == '(') {
        input_file >> sh->length;
        input_file.get(buf);
        if (buf == '(') {
            sh->cond = true;
            Cargo* cr = new Cargo;
            sh->obj = cr;
            BinRocker* binR = new BinRocker;
            sh->obj->binR = binR;
            read_BinRocker_from_file(buf, sh->obj->binR, input_file);
        }
        else if (buf == ',') {
            sh->cond = false;
            Cargo* cr = new Cargo;
            sh->obj = cr;
            input_file >> sh->obj->weight;
        }
        input_file.get(buf);

        if (buf != ')') {
            return nullptr;
        }
    }
    else {
        return nullptr;
    }

    return sh;
}

void detour_shoulder(Shoulder* sh, int& result, int& level) {
    level += 1;
    if (!sh->cond) {
        result += 1;
    }
    output_result(level,  result);
    if (sh->cond) {
        detour_rocker(sh->obj->binR, result, level);
    }
    level -= 1;
}

void detour_rocker(BinRocker* rocker, int& result, int& level) {
    detour_shoulder(rocker->sh1, result, level);
    detour_shoulder(rocker->sh2, result, level);
}

unsigned int numbers (const BinRocker* rocker) {
    int result = 0;
    int level = 0;
    detour_shoulder(rocker->sh1, result, level);
    detour_shoulder(rocker->sh2, result, level);
    return result;
}

void output_result(const int level, const int result) {
    for (int i = 0; i < level; i++)
        cout << ' ';
    cout << "rocker depth = " << level << endl;
}

void Destroy(BinRocker* rocker) {
	if (rocker->sh1 != nullptr)
		Destroy_shoulder(rocker->sh1);
	if (rocker->sh2 != nullptr)
		Destroy_shoulder(rocker->sh2);
	delete rocker;
}

void Destroy_shoulder(Shoulder* sh) {
	if (sh->cond == true)
		Destroy(sh->obj->binR);
	delete sh->obj;
	delete sh;
}

void write_shoulder(Shoulder* sh) {
	if (sh == nullptr) {
		cout << "Error." << endl;
		return;
	}
	cout << '(';
	cout << sh->length;
	if (sh->cond == false) {
		cout << ',';
		cout << sh->obj->weight;
	}
	else {
		write_binR(sh->obj->binR);
    }
	cout << ')';
}

void write_binR(BinRocker* rocker) {
	if (rocker == nullptr) {
        cout << "Error." << endl;
        return;
    }
	cout << '(';
	write_shoulder(rocker->sh1);
	cout << ' ';
	write_shoulder(rocker->sh2);
	cout << ')';
}
