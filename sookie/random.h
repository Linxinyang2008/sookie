#ifndef RANDOM_H_
#define RANDOM_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <cstdio>
 
int random_number(int left,int right){
	right--;
	if(left>right){
		printf("* L/R limit error /> <nul.nul>\n");
		printf("* Left = %d | Right = %d ->NULL\n",left,right);
		printf("* Value = ^err %d %d \n", 312263833, 927488492);
		return EOF^random_number(right,left);
	}
    std::random_device r;
 
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(left, right);
    int mean = uniform_dist(e1);
 //   std::cout << "Randomly-chosen mean: " << mean << '\n';

    std::seed_seq seed2{r(), r(), r(), r(), r(), r(), r(), r()}; 
    std::mt19937 e2(seed2);
    std::normal_distribution<> normal_dist(mean, 2);
 
	return mean;
}

#endif