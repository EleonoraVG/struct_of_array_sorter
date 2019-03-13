#include "soa_sort.h"
#include "utility.h"
#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <random>

using size_type = std::vector<char>::size_type;

struct Vector {
  float x, y, z;
};

struct Color {
  uint8_t r, g, b, a;
};

class Particles {
  public:
  std::vector<Vector> positions;
  std::vector<Vector> velocities;
  std::vector<int> masses;
  std::vector<Color> colors;
  std::vector<uint8_t> indices; // stride 2 (2 indices per element)

  void reserve(size_type count)
  {
    positions.reserve(count);
    velocities.reserve(count);
    masses.reserve(count);
    colors.reserve(count);
    indices.reserve(count * 2);
  }

  void add_particle(Vector pos, Vector velocity, int mass, Color col, int indexA = 0, int indexB = 0)
  {
    positions.push_back(pos);
    velocities.push_back(velocity);
    masses.push_back(mass);
    colors.push_back(col);
    indices.push_back(indexA);
    indices.push_back(indexB);
  }
};

Particles create_random_particles(size_type nbOfParticles)
{
  std::random_device rd;
  std::uniform_real_distribution<float> randFloat {};
  std::uniform_int_distribution<int> randInt {};
  std::uniform_int_distribution<short> randByte(0, 255);

  Particles result;
  result.reserve(nbOfParticles);
  for (size_type i = 0; i < nbOfParticles; i++) {
    Vector pos { randFloat(rd), randFloat(rd), randFloat(rd) };
    Vector velocity { randFloat(rd), randFloat(rd), randFloat(rd) };
    int mass = randInt(rd);
    Color color { static_cast<uint8_t>(randByte(rd)), static_cast<uint8_t>(randByte(rd)), static_cast<uint8_t>(randByte(rd)), static_cast<uint8_t>(randByte(rd)) };
    /*auto indexA = randInt(rd);
		auto indexB = randInt(rd);*/
    result.add_particle(pos, velocity, mass, color /*, indexA, indexB*/);
  }
  return result;
}

struct IterationResult {
  int pos_x = 0;
  int vel_y = 0;
  int mass = 0;
  int color_alpha = 0;
};

void write_to_csv(std::vector<IterationResult> iteration_results, std::string test_name)
{
  std::ofstream csv_file;
  csv_file.open("../output/" + test_name + "_results.csv", std::ios_base::app);
  if (csv_file.is_open()) {
    csv_file << test_name << "\n";
    csv_file << "pos_x"
             << ","
             << "vel_y"
             << ","
             << "mass "
             << ","
             << "color_alpha "
             << "\n";

    for (auto result : iteration_results) {
      csv_file << result.pos_x << "," << result.vel_y << "," << result.mass << "," << result.color_alpha << "\n";
    }
    csv_file.flush();
    csv_file.close();
  } else {
    std::cout << "Failed to write to csv_file"
              << "\n";
  }
}

int main()
{
  const auto particleCount = 10000000;
  const auto iterations = 10;
  std::vector<IterationResult> results = {};
  std::cout << "Baseline memory usage: " << getMemoryUsage() << " bytes." << std::endl;

  std::cout << "Creating " << particleCount << " random particles" << std::endl;
  auto particles = create_random_particles(particleCount);

  std::cout << "New memory usage: " << getMemoryUsage() << " bytes." << std::endl;

  for (int i = 0; i < iterations; i++) {
    IterationResult result;
    std::cout << "Iteration " << (i + 1) << std::endl;

    {
      std::cout << "Sorting by position x coordinate" << std::endl;

      auto start = std::chrono::high_resolution_clock::now();
      soa::SoaSort::sort_cmp(
          particles.positions.begin(), particles.positions.end(),
          [](const auto& a, const auto& b) { return a.x < b.x; },
          particles.masses.begin(), particles.colors.begin(), particles.velocities.begin());
      auto finish = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
      std::cout << "Sorted in " << duration << " milliseconds" << std::endl;
      result.pos_x = duration;
    }

    {
      std::cout << "Sorting by velocity y value" << std::endl;

      auto start = std::chrono::high_resolution_clock::now();
      soa::SoaSort::sort_cmp(
          particles.velocities.begin(), particles.velocities.end(),
          [](const auto& a, const auto& b) { return a.y < b.y; },
          particles.masses.begin(), particles.colors.begin(), particles.positions.begin());
      auto finish = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
      std::cout << "Sorted in " << duration << " milliseconds" << std::endl;
      result.vel_y = duration;
    }

    {
      std::cout << "Sorting by mass" << std::endl;

      auto start = std::chrono::high_resolution_clock::now();
      soa::SoaSort::sort(
          particles.masses.begin(), particles.masses.end(),
          particles.positions.begin(), particles.colors.begin(), particles.velocities.begin());
      auto finish = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
      std::cout << "Sorted in " << duration << " milliseconds" << std::endl;
      result.mass = duration;
    }

    {
      std::cout << "Sorting by color alpha value" << std::endl;

      auto start = std::chrono::high_resolution_clock::now();
      soa::SoaSort::sort_cmp(
          particles.colors.begin(), particles.colors.end(),
          [](const auto& a, const auto& b) { return a.a < b.a; },
          particles.positions.begin(), particles.masses.begin(), particles.velocities.begin());
      auto finish = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
      std::cout << "Sorted in " << duration << " milliseconds" << std::endl;
      result.color_alpha = duration;
    }

    results.push_back(result);
    std::cout << std::endl;
  }
  write_to_csv(results, "threading_on");
  std::cout << "Done!" << std::endl;
  std::cin.get();

  return 0;
}
