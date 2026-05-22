#include "load-spz.h"
#include "splat-types.h"
#include "load-spz-c.h"

#ifdef __cplusplus
extern "C" {
#endif
	using loadCallback = void(int32_t, int32_t, uint8_t, float*, float*, float*, float*, float*, float*, void*);
	using saveCallback = void(uint8_t*, size_t);

	void loadSpz(const uint8_t *data, size_t size, void* callback)
	{
		spz::UnpackOptions defaultOpts;
		spz::GaussianCloud loaded = loadSpz(data, size, defaultOpts);
		void* extensions;
		#ifdef SPZ_BUILD_EXTENSIONS
			extensions = loaded.extensions;
		#else
			extensions = nullptr;
		#endif


		reinterpret_cast<loadCallback*>(callback)(
			loaded.numPoints,
			loaded.shDegree,
			loaded.antialiased,
			&loaded.positions[0],
			&loaded.scales[0],
			&loaded.rotations[0],
			&loaded.alphas[0],
			&loaded.colors[0],
			&loaded.sh[0],
			extensions);
	}


	uint8_t saveSpz(
		int32_t numPoints,
		int32_t shDegree,
		uint8_t antialiased,
		float* positions,
		float* scales,
		float* rotations,
		float* alphas,
		float* colors,
		float* sh,
		void* extensions,
		void* callback)
	{
		spz::GaussianCloud splat;

		splat.numPoints = numPoints;
		splat.shDegree = shDegree;
		splat.antialiased = antialiased;

		int dim;

		switch (shDegree) {
			case 0:
				dim = 0;
				break;
			case 1:
				dim = 3;
				break;
			case 2:
				dim = 8;
				break;
			case 3:
				dim = 15;
				break;
			case 4:
				dim = 24;
				break;
			default:
				dim = 0;
				break;
		}

		splat.positions.resize(numPoints * 3);
		splat.scales.resize(numPoints * 3);
		splat.rotations.resize(numPoints * 4);
		splat.alphas.resize(numPoints);
		splat.colors.resize(numPoints * 3);
		splat.sh.resize(numPoints * dim * 3);

		memcpy(&splat.positions[0], positions,	numPoints * sizeof(float) * 3);
		memcpy(&splat.scales[0], 	scales,		numPoints * sizeof(float) * 3);
		memcpy(&splat.rotations[0], rotations,	numPoints * sizeof(float) * 4);
		memcpy(&splat.alphas[0], 	alphas,	 	numPoints * sizeof(float));
		memcpy(&splat.colors[0], 	colors,	 	numPoints * sizeof(float) * 3);
		memcpy(&splat.sh[0], 		sh,	 		numPoints * sizeof(float) * dim * 3);


		spz::PackOptions defaultOpts;
		std::vector<uint8_t> data;
		if (spz::saveSpz(splat, defaultOpts, &data)) {
			reinterpret_cast<saveCallback*>(callback)(&data[0], data.size());
			return true;
		}
		else { return false; }
	}

	void loadSplatFromPly(const char* filename, void* callback)
	{
		spz::UnpackOptions defaultOpts;
		spz::GaussianCloud loaded = spz::loadSplatFromPly(filename, defaultOpts);

		void* extensions;
		#ifdef SPZ_BUILD_EXTENSIONS
			extensions = loaded.extensions;
		#else
			extensions = nullptr;
		#endif


		reinterpret_cast<loadCallback*>(callback)(
			loaded.numPoints,
			loaded.shDegree,
			loaded.antialiased,
			&loaded.positions[0],
			&loaded.scales[0],
			&loaded.rotations[0],
			&loaded.alphas[0],
			&loaded.colors[0],
			&loaded.sh[0],
			extensions);
	}

	uint8_t saveSplatToPly(
		int32_t numPoints,
		int32_t shDegree,
		bool antialiased,
		float* positions,
		float* scales,
		float* rotations,
		float* alphas,
		float* colors,
		float* sh,
		void* extensions,
		char* filename)
	{
		spz::GaussianCloud splat;

		splat.numPoints = numPoints;
		splat.shDegree = shDegree;
		splat.antialiased = antialiased;

		int dim;

		switch (shDegree) {
			case 0:
				dim = 0;
				break;
			case 1:
				dim = 3;
				break;
			case 2:
				dim = 8;
				break;
			case 3:
				dim = 15;
				break;
			case 4:
				dim = 24;
				break;
			default:
				dim = 0;
				break;
		}

		splat.positions.resize(numPoints * 3);
		splat.scales.resize(numPoints * 3);
		splat.rotations.resize(numPoints * 4);
		splat.alphas.resize(numPoints);
		splat.colors.resize(numPoints * 3);
		splat.sh.resize(numPoints * dim * 3);

		memcpy(&splat.positions[0], positions,	numPoints * sizeof(float) * 3);
		memcpy(&splat.scales[0], 	scales,		numPoints * sizeof(float) * 3);
		memcpy(&splat.rotations[0], rotations,	numPoints * sizeof(float) * 4);
		memcpy(&splat.alphas[0], 	alphas,	 	numPoints * sizeof(float));
		memcpy(&splat.colors[0], 	colors,	 	numPoints * sizeof(float) * 3);
		memcpy(&splat.sh[0], 		sh,	 		numPoints * sizeof(float) * dim * 3);

		spz::PackOptions defaultOpts;
		return spz::saveSplatToPly(splat, defaultOpts, filename);
	}

#ifdef __cplusplus
}
#endif
