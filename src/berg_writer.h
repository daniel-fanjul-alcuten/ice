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
#ifndef SRC_BERG_WRITER_H_
#define SRC_BERG_WRITER_H_

#include <glog/logging.h>

#include <stdio.h>
#include <cstring>
#include <cassert>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>

#include "src/magic.h"
#include "src/digest.h"
#include "src/chunk.h"

using std::string;
using std::ofstream;
using std::ios;
using std::set;
using std::lexicographical_compare;

struct lex_compare {
  bool operator() (const Sha& lhs, const Sha& rhs) const{
    return lexicographical_compare(lhs.get(), lhs.get() + SHA256_DIGEST_LENGTH,
           rhs.get(), rhs.get() + SHA256_DIGEST_LENGTH);
  }
};

class BergWriter {
 public:
  BergWriter(string file_name, Digest d);
  ~BergWriter();
  size_t WriteChunk(Chunk c);
  size_t WriteChunks(Chunk c[], size_t count);
  Sha Close();

 private:
  ofstream file_;
  Digest digest_;
  set<Sha, lex_compare> seen_hashes;
};

#endif  // SRC_BERG_WRITER_H_
