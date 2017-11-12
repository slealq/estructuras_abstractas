#include <array>
#include <math.h>
#include <iostream> // for print dbg
#include "bloom_filter.h"
#include "smhasher/src/MurmurHash3.h"

bloom_filter::bloom_filter(int m_bits, int k_hashes) {
  filter_bits_.resize(m_bits, false);
  k_hashes_ = k_hashes;
  m_bits_ = m_bits;
  n_elements_ = 0;
}//bloom_filter constructor

//helper 164 bit hashing function with murmurhash3
std::array<uint64_t, 2> hash(const int * data,
			     std::size_t length=2) {
  // array of unsigned ints of 64 bits is the output
  std::array<uint64_t, 2> hash_value;
  MurmurHash3_x64_128(data, length, 0, hash_value.data());

  return hash_value;

}// hash

//helper double hashing function for 0 to k different hashes
uint64_t ith_hash(uint8_t i,
		  uint64_t hash_a,
		  uint64_t hash_b,
		  uint64_t m_bits_) {
  // --> formula: hash_i(x, m) = { hash_a(x) + i*hash_b(x)  } % m
  // --> i is the iest from 0 to k
  // --> m is the maximum result the hash should give
  // --> hash_a and hash_b are two different hashes for x

  return (hash_a + i*hash_b) % m_bits_;

} // double hashing

void bloom_filter::add(int * data, std::size_t length=2) {
  // auto for automatic type 
  auto hash_values = hash(data, length);

  for( int i = 0; i < k_hashes_; i++) {
    // until all k_hahes_ positions are filled
    filter_bits_[ith_hash(i,
			  hash_values[0],
			  hash_values[1],
			  m_bits_)] = true;
  }// for

  // add to n_elements_ count
  n_elements_ += 1;
  
}//add function

bool bloom_filter::possibly_contained(int * data,
				      std::size_t length) {
  // auto for automatic type
  auto hash_values = hash(data, length);

  for( int i = 0; i < k_hashes_; i++) {
    // check that all bits from the hashes are true
    if(!filter_bits_[ith_hash(i,
			     hash_values[0],
			     hash_values[1],
			      m_bits_)]) {
	 return false;
      }//if
  }//for

  // if all are high return true
  return true; // might be in the filter

}// possibly contained function

float bloom_filter::error_rate(void) {
  // formula -> p = (1-e^{-kn/m})^k
  p_error_ = pow( (1.0 - exp(float(-k_hashes_* n_elements_) /
			   float(m_bits_)) ) ,
		  float(k_hashes_) );
  return p_error_;
}// error rate

std::vector<int> bloom_filter::double_hash_dbg(int * data,
					       std::size_t length) {
  // auto for automatic type
  auto hash_values = hash(data, length);

  std::vector<int> hashes_result(k_hashes_);
  
  for( int i = 0; i < k_hashes_; i++) {
    hashes_result[i] = ith_hash(i,
				hash_values[0],
				hash_values[1],
				m_bits_ );
  }//for

  return hashes_result;

}// double hash debugger

void bloom_filter::print_bits_dbg(void) {

  std::cout << "DEBUGGER: Printing filter bits : " << std::endl;

  std::cout << "[ ";
  for(int i = 0; i<m_bits_; i++) {
    std::cout << filter_bits_[i] << " ";
  }// for

  std::cout << "]" << std::endl;
  
} // print bits debugger
