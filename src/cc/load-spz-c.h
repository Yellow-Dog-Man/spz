
#include "splat-c-types.h"
#include "splat-types.h"
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

	void loadSpz(const uint8_t *data, size_t size, void* callback);
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
		void* callback);


	void loadSplatFromPly(const char* filename, void* callback);
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
		char* filename);

#ifdef __cplusplus
}
#endif
