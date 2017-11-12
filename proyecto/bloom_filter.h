#include <vector>

#ifndef PROYECTO_BLOOM_FILTER_H
#define PROYECTO_BLOOM_FILTER_H

class bloom_filter {
  // k: k hash functions to get k array positions.
  // m: m bits of the bit array
  // n: n number of elements
  // p: error rate

 public:
  bloom_filter(int size, int k_hashes);
  void add(int * data, std::size_t length);
  bool possibly_contained(int * data, std::size_t length);
 private:
  std::vector<bool> filter_bits_;
  int k_hashes_;
  int m_bits_;
  int n_elements_;
  int p_error_;
};

#endif // PROYECTO_BLOOM_FILTER_H
