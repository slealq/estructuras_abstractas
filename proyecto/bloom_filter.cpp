#include <array>
#include "bloom_filter.h"
#include "smhasher/src/MurmurHash3.h"

bloom_filter::bloom_filter(int m_bits, int k_hashes){
  filter_bits_.resize(m_bits, false);
  k_hashes_ = k_hashes; // fancy way to initialize
  m_bits_ = m_bits;
}//bloom_filter constructor

//helper 164 bit hashing function with murmurhash3
std::array<uint64_t, 2> hash(const int *data, std::size_t length){
  // array of unsigned ints of 64 bits is the output
  std::array<uint64_t, 2> hash_value;
  MurmurHash3_x64_128(data, length, 0, hash_value.data());

  return hash_value;

}// hash

//helper double hashing function for 0 to k different hashes
uint64_t ith_hash(int i, int hash_a, int hash_b, int m_bits_){
  // --> formula: hash_i(x, m) = { hash_a(x) + i*hash_b(x)  } % m
  // --> i is the iest from 0 to k
  // --> m is the maximum result the hash should give
  // --> hash_a and hash_b are two different hashes for x

  return (hash_a + i*hash_b) % m_bits_;

} // double hashing

void bloom_filter::add(int * data, std::size_t length){
  // auto for automatic type 
  auto hash_values = hash(data, length);

  for( int i = 0; i < k_hashes_; i++){
    // until all k_hahes_ positions are filled
    filter_bits_[ith_hash(i,
			  hash_values[0],
			  hash_values[1],
			  m_bits_)] = true;
  }// for
  
}//add function
