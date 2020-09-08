#include <fstream>
#include <cstdint>
#include <stdexcept>
#include <ctime>

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

class Timer {
  timespec m_start;
public:
  Timer() {
    clock_gettime(CLOCK_MONOTONIC_RAW, &m_start);
  }
  double get_time() const {
    timespec now;
    clock_gettime(CLOCK_MONOTONIC_RAW, &now);
    return now.tv_sec-m_start.tv_sec + 0.000000001*(now.tv_nsec-m_start.tv_nsec);
  }
};

int main() {
  std::uint64_t accuracy;
  std::ifstream fin("input.txt");
  fin >> accuracy;
  fin.close();

  Timer timer;
  double const pi = pi::compute(accuracy);
  double const timeComputing = timer.get_time();

  std::ofstream fout("output.txt");
  fout << pi << std::endl << "Time spent: " << timeComputing << std::endl ;
  fout.close();
  return 0;
}
