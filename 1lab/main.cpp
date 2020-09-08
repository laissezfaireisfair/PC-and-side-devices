#include <fstream>
#include <cstdint>
#include <stdexcept>

namespace pi {
  using usInt = std::uint64_t;

  double compute(std::uint64_t const accuracy) {
    if (accuracy == 0)
      throw std::invalid_argument ("Try to use null accuracy");
    double accumulator = 0;
    for (usInt i = 0; i <= accuracy; ++i) {
      const int sign = 1 - 2 * (i % 2);
      accumulator += sign / (2. * i + 1.);
    }
    return 4. * accumulator;
  }
}

int main() {
  std::uint64_t accuracy;
  std::ifstream fin("input.txt");
  fin >> accuracy;
  fin.close();

  double const pi = pi::compute(accuracy);

  std::ofstream fout("output.txt");
  fout << pi << std::endl;
  fout.close();
  return 0;
}
