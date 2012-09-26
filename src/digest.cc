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
#include "src/digest.h"

#include <openssl/sha.h>

Digest::Digest() {
  SHA256_Init(&sha256_);
}

void Digest::Update(ChunkData data) {
  SHA256_Update(&sha256_, &data.data[0], data.length);
}

void Digest::Update(unsigned char* data, size_t length) {
  SHA256_Update(&sha256_, data, length);
}

Sha Digest::Final() {
  unsigned char *hash = new unsigned char[SHA256_DIGEST_LENGTH];
  SHA256_Final(hash, &sha256_);
  return Sha(hash);
}

void Digest::Final(unsigned char* hash) {
  SHA256_Final(hash, &sha256_);
}

string Digest::ToString(Sha hash) {
  return ToString(hash.get());
}

string Digest::ToString(unsigned char* hash) {
  stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    ss << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
  }
  return ss.str();
}
