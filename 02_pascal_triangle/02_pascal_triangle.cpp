#include <iostream>
#include <vector>

std::vector<int> get_next_row(std::vector<int>& last_row) {
    std::vector<int> next_row{ 1 };
    if (last_row.empty()) {
        return next_row;
    }
    else {
        for (size_t i = 0; i + 1 < last_row.size(); ++i) {
            next_row.emplace_back(last_row[i] + last_row[i + 1]);
        }
        next_row.emplace_back(1);
		return next_row;
    }
}

auto generate_triangle(int rows) {
    std::vector<std::vector<int>> triangle{ 1 };
    for (int i = 1; i < rows; i++) {
        triangle.push_back(get_next_row(triangle.back()));
    }
    return triangle;
}

int main()
{
    std::cout << "Hello World!\n";
}
