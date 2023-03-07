#include <iostream>
#include <limits>

int main()
{
    double max_val = std::numeric_limits<double>::max();
    double min_val = std::numeric_limits<double>::lowest();
    double abs_min_val = std::numeric_limits<double>::epsilon();

    std::cout << "Größte double-Zahl: " << max_val << std::endl;
    std::cout << "Kleinste double-Zahl: " << min_val << std::endl;
    std::cout << "Absolutbetrag-kleinste double-Zahl: " << abs_min_val << std::endl;

    return 0;
}