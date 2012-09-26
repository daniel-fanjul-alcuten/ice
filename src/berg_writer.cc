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
#include "src/berg_writer.h"

BergWriter::BergWriter(string file_name, Digest d) : digest_(d) {
  file_.open(file_name.c_str(), ios::out | ios::binary);
  assert(file_.is_open());

  LOG(INFO) << "Write magic " << BERG_MAGIC_HEADER;
  file_.put(BERG_MAGIC_HEADER);
}

BergWriter::~BergWriter() {
  if (file_.is_open()) {
    file_.close();
  }
}

Sha BergWriter::Close() {
  unsigned char *hash = new unsigned char[SHA256_DIGEST_LENGTH];
  digest_.Final(hash);
  LOG(INFO) << "Write final hash " << Digest::ToString(hash);
  file_.write((const char*)hash, SHA256_DIGEST_LENGTH);
  file_.flush();
  return Sha(hash);
}

size_t BergWriter::WriteChunk(Chunk c) {
  std::cout << Digest::ToString(c.hash().get()) << std::endl;
  if (seen_hashes.find(c.hash()) != seen_hashes.end()) {
    return -1;
  }

  file_.write((const char*)c.hash().get(), SHA256_DIGEST_LENGTH);
  size_t len = c.length();
  file_.write(reinterpret_cast<const char*>(&len), CHUNK_LENGTH_BYTE_SIZE);
  file_.write(c.data().data.get(), c.data().length);
  LOG(INFO) << "Write sha: " << Digest::ToString(c.hash().get())
    << " len: " << c.length() << " data: " << c.data().data.get();
  digest_.Update(c.hash().get(), SHA256_DIGEST_LENGTH);
  digest_.Update(reinterpret_cast<unsigned char*>(&len),
      CHUNK_LENGTH_BYTE_SIZE);
  digest_.Update(c.data());
  seen_hashes.insert(c.hash());
  return c.length();
}

size_t BergWriter::WriteChunks(Chunk c[], size_t count) {
  size_t length = 0;
  size_t len;
  for (int i = 0; i < count; ++i) {
    std::cout << Digest::ToString(c[i].hash().get()) << std::endl;
    if (seen_hashes.find(c[i].hash()) != seen_hashes.end()) {
      continue;
    }
    file_.write((const char*)c[i].hash().get(), SHA256_DIGEST_LENGTH);
    len = c[i].length();
    file_.write(reinterpret_cast<const char*>(&len), CHUNK_LENGTH_BYTE_SIZE);
    file_.write(c[i].data().data.get(), c[i].data().length);
    LOG(INFO) << "Write sha: " << Digest::ToString(c[i].hash().get())
      << " len: " << c[i].length() << " data: " << c[i].data().data.get();
    digest_.Update(c[i].hash().get(), SHA256_DIGEST_LENGTH);
    digest_.Update(reinterpret_cast<unsigned char*>(&len),
        CHUNK_LENGTH_BYTE_SIZE);
    digest_.Update(c[i].data());
    seen_hashes.insert(c[i].hash());
    length += c[i].length();
  }
  file_.flush();
  return length;
}
