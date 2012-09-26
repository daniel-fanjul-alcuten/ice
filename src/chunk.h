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
#ifndef SRC_CHUNK_H_
#define SRC_CHUNK_H_

#include "src/digest.h"

#define MAX_CHUNK_SIZE 65535
#define CHUNK_LENGTH_BYTE_SIZE 2

class Chunk {
 public:
  Chunk();
  explicit Chunk(ChunkData data);
  Chunk(ChunkData data, Sha hash);
  void Create(ChunkData data);
  void Create(ChunkData data, Sha hash);

  Sha hash();
  size_t length();
  ChunkData data();

 private:
  Sha hash_;
  ChunkData data_;

  void CalculateHash();
};
#endif  // SRC_CHUNK_H_
