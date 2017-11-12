#include <iostream>
#include "bloom_filter.h"

int main(void) {
  std::cout << "Testing and addition to the bloom filter..." << std::endl;
  bloom_filter filter(10, 2);
  uint8_t * test = new uint8_t(2);
  filter.add(test, 3);
  std::cout << filter.possibly_contained(new uint8_t(2), 3) << std::endl;
  std::cout << filter.possibly_contained(new uint8_t(3), 3) << std::endl;
}
