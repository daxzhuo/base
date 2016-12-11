

#ifndef BITMAP_H
#define BITMAP_H

#include <bitset>

inline uint64 BitLength64(uint64 size) { return ((size + 63) >> 6); }
inline uint32 BitLength32(uint32 size) { return ((size + 31) >> 5); }

class BitMap {
public:
	explicit BitMap(uint32_t size, bool fill = false)
						: max_size_(size),
							array_size_(BitLength64(size)),
							map_(new uint64[array_size_]) {
								SetAll(fill);
	}

	~BitMap() { delete[] map_; }

	// Resize the bitmap
	// If size < bits(), the extra bits will be discarded.
	// If size > bits(), the extra bits will be filled with the fill value
	void Resize(uint32_t size, bool fill = false);

	bool Get(uint32_t index) const {
		assert(max_size_ == 0 || index < max_size_);
		return IsBitSet64(map_, index);
	}

	void Set(uint32_t index, bool value) {
		assert(max_size_ == 0 || index < max_size_);
		if (value) {
			SetBit64(map_, index);
		} else {
			ClearBit64(map_, index);
		}
	}

	void SetAll(bool value) {
		memset(map_, (value ? 0xFF:0x00), array_size_ * sizeof(*map_));		
	}

	void Clear() {
		SetAll(false);
	}

private:
	uint32_t max_size_;
	uint32_t array_size_;
	uint64_t map_;
};

void BitMap::Resize(uint32_t size, bool fill) {
	const uint32_t new_array_size = BitLength64(size);
	const uint32_t old_max_size = max_size_;
	if (new_array_size < old_max_size) {
		max_size_ = size;
	} else {
		const uint32_t old_array_size = array_size_;
		array_size_ = new_array_size;
		max_size_ = size;
		uint64_t* new_map = new uint64[array_size_];
		memcpy(new_map, map_, old_array_size*sizeof(*map_));
		delete[] map_;
		map_ = new_map;
	}
	for (uint32 index = old_max_size; index < size; ++index) {
    Set(index, fill);
  }
}

#endif