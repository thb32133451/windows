#pragma once

struct job {
	char name[40];
	double salary;
	int floor;
};

template <typename T> void Swap(T &a, T &b);

template <> void Swap<job>(job &j1, job &j2);

void show(job &j);