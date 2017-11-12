#include <vector>
#include <iostream>
#include "bloom_filter.h"

int main(void) {
  std::cout << "Testing an addition (2) to the bloom filter..." << std::endl;
  bloom_filter filter(5, 2);

  filter.add(new int(2), sizeof(int));

  std::cout << std::endl;
  
  std::cout << "Result in the filter bits: " << std::endl;
  filter.print_bits_dbg();

  std::cout << std::endl;
  
  std::cout << "Error rate: "
	    << filter.error_rate() << std::endl;

  std::cout << std::endl;

  int positives = 0;
  
  for(int n = 0; n<10; n++) {
    std::vector<int> hashes = filter.double_hash_dbg( new int(n), sizeof(int) );

    std::cout << "--> Hashes for number: "
	      << n
	      << std::endl;

    for(int i = 0; i<hashes.size(); i++) {
      std::cout << hashes[i] << std::endl;
    }// for

    std::cout << "Possible contained? : "
      << filter.possibly_contained(new int(n),	sizeof(int));

    if(filter.possibly_contained(new int(n), sizeof(int)) ) {
      positives +=1;
    }//if
      
    std::cout << "\t <--"<< std::endl;

    std::cout << std::endl;
  }//for

  std::cout << "Total positives: " << positives << std::endl;
  
}// main
