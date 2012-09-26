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
#include "src/berg_reader.h"

BergReader::BergReader(string file_name, Digest d) : digest_(d) {
  file_.open(file_name.c_str(), ios::binary);
  assert(file_.is_open());
}

BergReader::~BergReader() {
  Close();
}

void BergReader::Close() {
  if (file_.is_open()) {
    file_.close();
  }
}

Chunk BergReader::ReadByOffset(size_t offset) {
  file_.seekg(offset, ios::beg);

  char* buffer = new char[kPreambuleLength];
  file_.read(buffer, kPreambuleLength);

  unsigned short length = (buffer[SHA256_DIGEST_LENGTH + 1] << 8)
    | buffer[SHA256_DIGEST_LENGTH];

  LOG(INFO) << "read length: " << length;

  unsigned char* hash = new unsigned char[SHA256_DIGEST_LENGTH];
  memcpy(hash, buffer, SHA256_DIGEST_LENGTH);

  LOG(INFO) << "read hash: " << Digest::ToString(hash);

  delete[] buffer;
  buffer = new char[length];
  file_.read(buffer, length);
  LOG(INFO) << "read data: " << buffer;

  Chunk result(ChunkData(buffer, length), Sha(hash));

  return result;
}

size_t BergReader::ChunkCount() {
  file_.seekg(0, ios::end);
  size_t end = file_.tellg();
  file_.seekg(1, ios::beg);
  size_t count = 0;
  char* buffer = new char[2];
  unsigned short length;

  while (file_.tellg() < end - SHA256_DIGEST_LENGTH) {
    file_.seekg(SHA256_DIGEST_LENGTH, ios::cur);
    file_.read(buffer, 2);
    length = (buffer[1] << 8) | buffer[0];
    file_.seekg(length, ios::cur);
    ++count;
  }

  delete[] buffer;
  return count;
}

ShaMap BergReader::ListHashes() {
  ShaMap hashes(new map<Sha, size_t, lex_compare>);

  file_.seekg(0, ios::end);
  size_t end = file_.tellg();
  file_.seekg(1, ios::beg);

  char buffer[kPreambuleLength];

  while (file_.tellg() < end - SHA256_DIGEST_LENGTH) {
    file_.read(buffer, kPreambuleLength);

    unsigned short length = (buffer[SHA256_DIGEST_LENGTH + 1] << 8)
      | buffer[SHA256_DIGEST_LENGTH];

    unsigned char* hash = new unsigned char[SHA256_DIGEST_LENGTH];
    memcpy(hash, buffer, SHA256_DIGEST_LENGTH);
    hashes->insert(std::pair<Sha, size_t>(Sha(hash), length));

    file_.seekg(length, ios::cur);
  }

  return hashes;
}

Sha BergReader::ReadHash() {
  file_.seekg(SHA256_DIGEST_LENGTH, ios::end);
  unsigned char* hash = new unsigned char[SHA256_DIGEST_LENGTH];
  file_.read((char*)hash, SHA256_DIGEST_LENGTH);
  return Sha(hash);
}
