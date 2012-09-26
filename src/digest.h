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
#ifndef SRC_SHA_H_
#define SRC_SHA_H_

#include <openssl/sha.h>

#include <string>
#include <sstream>
#include <boost/shared_array.hpp>
#include <iomanip>

using std::string;
using std::stringstream;
using std::hex;
using std::setw;
using std::setfill;
using boost::shared_array;
using std::lexicographical_compare;

typedef shared_array<unsigned char> Sha;

typedef struct _ChunkData {
  shared_array<char> data;
  size_t length;

  _ChunkData(char* pdata, size_t len)
    : data(pdata),
      length(len) {
  }

  _ChunkData() {
  }
} ChunkData;

struct lex_compare {
  bool operator() (const Sha& lhs, const Sha& rhs) const{
    return lexicographical_compare(lhs.get(), lhs.get() + SHA256_DIGEST_LENGTH,
           rhs.get(), rhs.get() + SHA256_DIGEST_LENGTH);
  }
};

class Digest {
 public:
  static string ToString(Sha);
  static string ToString(unsigned char* hash);
  Digest();
  void Update(unsigned char* data, size_t length);
  void Update(ChunkData);
  Sha Final();
  void Final(unsigned char* hash);

 private:
  SHA256_CTX sha256_;
};

#endif  // SRC_SHA_H_
