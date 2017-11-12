#include <vector>

#ifndef PROYECTO_BLOOM_FILTER_H
#define PROYECTO_BLOOM_FILTER_H

class bloom_filter {
  // k: k hash functions to get k array positions.
  // m: m bits of the bit array
  // n: n number of elements
  // p: error rate

 private:
  std::vector<bool> filter_bits_;
  int k_hashes_;
  uint64_t m_bits_; // special type for double hashing
  int n_elements_;
  float p_error_;

 public:
  bloom_filter(int m_bits, int k_hashes);
  void add(int * data, std::size_t length);
  bool possibly_contained(int * data, std::size_t length);
  float error_rate(void);
  std::vector<int> double_hash_dbg(int * data,
				   std::size_t length);
  void print_bits_dbg(void);
};

#endif // PROYECTO_BLOOM_FILTER_H
