/// Copyright 2012, (c) Daniel Fanjul Alcuten, Goran Petrovic

/// This file is part of ice.
/// ice is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// ice is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with ice.  If not, see <http://www.gnu.org/licenses/>.
#ifndef SRC_BERG_READER_H_
#define SRC_BERG_READER_H_

#include <stdio.h>
#include <string.h>
#include <glog/logging.h>
#include <boost/shared_ptr.hpp>

#include <string>
#include <map>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "src/digest.h"
#include "src/chunk.h"

using std::string;
using std::ifstream;
using std::ios;
using std::map;
using boost::shared_ptr;

typedef shared_ptr<map<Sha, size_t> > ShaMap;
typedef map<Sha, size_t>::const_iterator ShaMapper;

class BergReader {
 public:
  BergReader(string file_name, Digest d);
  ~BergReader();
  Chunk ReadByOffset(size_t offset);
  size_t ChunkCount();
  bool CheckOffset(Sha sha, size_t offset);
  ShaMap ListHashes();
  void Close();
  //ChunkIterator GetIterator();

 private:
  static const int kPreambuleLength = SHA256_DIGEST_LENGTH + 2;
  ifstream file_;
  Digest digest_;
};
#endif  // SRC_BERG_READER_H_
