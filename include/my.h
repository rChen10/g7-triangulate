#ifndef __MY_H__
#define __MY_H__

#include <vector>

namespace my{
	class vector : public std::vector<double>{
		//std::vector doesnt implement dot or cross, but still using its memory management

		public:

		vector();

		vector(double, double, double, double);

		vector(std::vector<double>& v1, std::vector<double>& v2);

		double dot(std::vector<double>& v);
		

		my::vector cross(std::vector<double>& v);

	};
}

#endif
