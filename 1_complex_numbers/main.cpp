#include "complex.h"
#include <vector>

// implementing sorting algorithm for Complex objects
void sort(std::vector<Complex>& arr){
	for(int i = 1; i < arr.size(); ++i){
		for(int j = i; j > 0; --j){
			if(arr[j].abs() < arr[j - 1].abs()){
				std::swap(arr[j - 1], arr[j]);
			}
			else{
				break;
			}
		}
	}
}

int main()
{
	// creating Complex objects for checking overloaded operators
	Complex num;
	std::cout << "num looks: " << num << std::endl;
	std::cout << "num.abs(): " << num.abs() << std::endl;

	Complex num_1(2, -8);
	Complex num_2(0, 7);

	std::cout << "first looks : " << num_1 << std::endl;
	std::cout << "second looks: " << num_2 << std::endl;
	std::cout << "first + second: " << num_1 + num_2 << std::endl;
	std::cout << "first - second: " << num_1 - num_2 << std::endl;
	std::cout << "first * 6     : " << num_1 * 6 << std::endl;

	Complex num_3(6, -1);
	Complex num_4(3, 0);
	Complex num_5(-6, 8);
	Complex num_6(-2, 12);
	Complex num_7(4, -7);
	Complex num_8(-3, 3);
	Complex num_9(4, 3);
	Complex num_10(2, 3);

	// creating vector arr of Complex objects
	std::vector<Complex> arr{num_1, num_2, num_3, num_4, num_5, num_6, num_7, num_8, num_9, num_10};


	// printing Complex vector before sorting
	std::cout << "Before sorting:" << std::endl;
	for(const auto& x: arr){
		std::cout << x << " ";
	}
	std::cout << std::endl;

	// calling sort function for Complex vector
	sort(arr);

	// printing sorted Complex vector
	std::cout << "After sorting:" << std::endl;
	for(const auto& x: arr){
		std::cout << x << " ";
	}
	std::cout << std::endl;

	return 0;
}

