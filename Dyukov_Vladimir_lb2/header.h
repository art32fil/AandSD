#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <conio.h>
#include <string>

struct rocker_arm;
struct cargo {

	int weight;
	rocker_arm* next_ra;
	cargo() : next_ra(nullptr), weight(-1) {}
};
struct arm {

	int lenght;
	cargo* next_c;
	arm() : next_c(nullptr), lenght(-1) {}
};
struct rocker_arm {

	arm* left_arm;
	arm* right_arm;
	rocker_arm() : left_arm(nullptr), right_arm(nullptr) {}
};
struct node {

	node* next;
	rocker_arm* data;
	std::string path;
};
struct s_string {

	std::string str;
};

typedef node* list;

enum flags {F_EXIT, F_START, F_CONSOL, F_FILE, F_RESULT_S, F_FRES, F_CRES};

bool operator==(const rocker_arm& first, const rocker_arm& second);
bool operator==(const arm& first, const arm& second);
bool operator==(const cargo& first, const cargo& second);

std::istream& operator>>(std::istream& in, rocker_arm& data);
std::istream& operator>>(std::istream& in, arm& data);
std::istream& operator>>(std::istream& in, cargo& data);

void rocker_arm_del(rocker_arm& data);
void arm_del(arm& data);
void cargo_del(cargo& data);