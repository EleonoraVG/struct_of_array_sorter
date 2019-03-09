#include "soa_sort.h"
#include <random>
#include <chrono>

using size_type = std::vector<char>::size_type;

struct Vector
{
	float x, y, z;
};

struct Color
{
	uint8_t r, g, b, a;
};

class Particles
{
public:
	std::vector<Vector> positions;
	std::vector<Vector> velocities;
	std::vector<int> masses;
	std::vector<Color> colors;
	std::vector<int> indices; // stride 2 (2 indices per element)

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
	std::uniform_real<float> randFloat{};
	std::uniform_int<int> randInt{};
	std::uniform_int<uint8_t> randByte{};

	Particles result;
	result.reserve(nbOfParticles);
	for(size_type i = 0; i < nbOfParticles; i++)
	{
		Vector pos { randFloat(rd), randFloat(rd), randFloat(rd) };
		Vector velocity { randFloat(rd), randFloat(rd), randFloat(rd) };
		int mass = randInt(rd);
		Color color { randByte(rd), randByte(rd), randByte(rd), randByte(rd) };
		/*auto indexA = randInt(rd);
		auto indexB = randInt(rd);*/
		result.add_particle(pos, velocity, mass, color /*, indexA, indexB*/);
	}
	return result;
}

int main()
{
	const auto particleCount = 10000000;

	std::cout << "Creating " << particleCount << " random particles" << std::endl;
	auto particles = create_random_particles(particleCount);

	/*{
		std::cout << "Sorting by position" << std::endl;

		auto start = std::chrono::high_resolution_clock::now();
		soa::SoaSort::sort(
			particles.positions.begin(), particles.positions.end(),
			particles.masses.begin(), particles.colors.begin(), particles.velocities.begin());
		auto finish = std::chrono::high_resolution_clock::now();

		std::cout << "Sorted in " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << " milliseconds" << std::endl;
	}

	{
		std::cout << "Sorting by velocity" << std::endl;

		auto start = std::chrono::high_resolution_clock::now();
		soa::SoaSort::sort(
			particles.velocities.begin(), particles.velocities.end(),
			particles.masses.begin(), particles.colors.begin(), particles.positions.begin());
		auto finish = std::chrono::high_resolution_clock::now();

		std::cout << "Sorted in " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << " milliseconds" << std::endl;
	}*/

	{
		std::cout << "Sorting by mass" << std::endl;

		auto start = std::chrono::high_resolution_clock::now();
		soa::SoaSort::sort(
			particles.masses.begin(), particles.masses.end(),
			particles.positions.begin(), particles.colors.begin(), particles.velocities.begin());
		auto finish = std::chrono::high_resolution_clock::now();

		std::cout << "Sorted in " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << " milliseconds" << std::endl;
	}

	/*{
		std::cout << "Sorting by color alpha value" << std::endl;

		auto start = std::chrono::high_resolution_clock::now();
		soa::SoaSort::sort(
			particles.colors.begin(), particles.colors.end(),
			particles.positions.begin(), particles.masses.begin(), particles.velocities.begin());
		auto finish = std::chrono::high_resolution_clock::now();

		std::cout << "Sorted in " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << " milliseconds" << std::endl;
	}*/

	std::cout << "Done!" << std::endl;
	std::cin.get();

	return 0;
}
