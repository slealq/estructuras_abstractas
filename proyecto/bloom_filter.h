#include <vector>

#ifndef PROYECTO_BLOOM_FILTER_H
#define PROYECTO_BLOOM_FILTER_H

class bloom_filter {
  // k: k hash functions to get k array positions.
  // m: m bits of the bit array
  // n: n number of elements
  // p: error rate

 public:
  bloom_filter(uint64_t size, uint8_t k_hashes);
  void add(uint8_t * data, std::size_t length);
  bool possibly_contained(uint8_t * data, std::size_t length);
 private:
  std::vector<bool> filter_bits_;
  uint8_t k_hashes_;
  uint64_t m_bits_;
  int n_elements_;
  int p_error_;
};

#endif // PROYECTO_BLOOM_FILTER_H
