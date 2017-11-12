#include <vector>
#include <stdlib.h> // rand
#include <iostream>
#include "bloom_filter.h"

int main(void) {
  std::cout << "Testing an addition (2) to the bloom filter..." << std::endl;
  bloom_filter filter(10, 5);

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

  // big data testing
  /*  
      HOW TO CHOSE M AND K
      Let's say we want p = 0.05 (5%)
      then:
      m = {-n * ln p } / {ln 2} ^ 2
      k = m/n * ln2
      this means that for n = 1000, p = 0.05:
      m = 6235 ~ 6300
      k = 13 
  */

  std::cout << std::endl << "\t FALSE POSITIVE RATE ASSERTION: " << std::endl << std::endl;
  
  bloom_filter big_filter(6300, 13); 
  
  std::vector<int> insertions;
  int b_positives = 0;// false positives
  int true_positives = 0;// true positives
  
  insertions.resize(1000, 0); // n = 10

  for(int i = 0; i<1000; i++) {
    insertions[i] = rand() % 1024; // between 0 and 1024
    big_filter.add( new int(insertions[i]), sizeof(int) );
  }// for

  // now let's count assertions

  for(int i = 0; i<=1024; i++) {
    int is_inserted = false;
    for(int n = 0; n<1000; n++) {
      if(i == insertions[n]){
	// the i is one of the inserted numbers
	is_inserted = true;
      }//if
      
    }//for n

    if(is_inserted) {
      true_positives += 1;
      is_inserted = false; // return to false
      continue;
    } // if inserted

    if(big_filter.possibly_contained(new int(i), sizeof(int) ) ) {
	b_positives += 1;
    }// if possibly contained
    
  }// for i

  std::cout << "Test with m = 6300, n = 1000, k = 13, range from 0 to 1024" << std::endl;
  std::cout << "False Positive assertions: " << b_positives << std::endl;
  std::cout << "Real Positive assertions: " << true_positives << std::endl;
  std::cout << "Rate: " << float(float(b_positives) / (float(b_positives) + float(true_positives))) << std::endl;
  std::cout << "Expected Rate: " << big_filter.error_rate() << std::endl;
}// main
