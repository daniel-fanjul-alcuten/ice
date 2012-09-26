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
#include "src/chunk.h"

Chunk::Chunk() {
}

Chunk::Chunk(ChunkData data) : data_(data) {
}

Chunk::Chunk(ChunkData data, Sha hash) : data_(data), hash_(hash) {
}

void Chunk::Create(ChunkData data) {
  data_ = data;
}

void Chunk::Create(ChunkData data, Sha hash) {
  data_ = data;
  hash_ = hash;
}

void Chunk::CalculateHash() {
  Digest d;
  d.Update(data_);
  hash_ = d.Final();
}

Sha Chunk::hash() {
  if (! hash_) {
    CalculateHash();
  }

  return hash_;
}

size_t Chunk::length() {
  return data_.length;
}

ChunkData Chunk::data() {
  return data_;
}
