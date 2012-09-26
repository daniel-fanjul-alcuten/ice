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
#include <string>

#include "src/berg_writer.h"
#include "gtest/gtest.h"

TEST(BergWriterTest, TestCreation) {
  Digest d;

  char* tmp_name = new char[11];
  GenRandom(tmp_name, 10);
  BergWriter bw(tmp_name, d);

  char* contents1 = new char[12];
  char* contents2 = new char[18];
  strcpy(contents1, "hostia puta");
  Chunk c1(ChunkData(contents1, 11));

  strcpy(contents2, "sharmuta mitmara");
  Chunk c2(ChunkData(contents2, 17));

  bw.WriteChunk(c1);
  bw.WriteChunk(c2);
  bw.Close();

  remove(tmp_name);
  ASSERT_NO_FATAL_FAILURE();
}

TEST(BergWriterTest, TestBulk) {
  Digest d;

  char* tmp_name = new char[11];
  GenRandom(tmp_name, 10);
  BergWriter bw(tmp_name, d);

  char* contents1 = new char[12];
  char* contents2 = new char[18];
  strcpy(contents1, "hostia puta");
  Chunk c1;
  c1.Create(ChunkData(contents1, 11));

  strcpy(contents2, "sharmuta mitmara");
  Chunk c2(ChunkData(contents2, 17));

  Chunk *c = new Chunk[2];
  c[0] = c1;
  c[1] = c2;

  bw.WriteChunks(c, 2);
  bw.Close();

  remove(tmp_name);
  ASSERT_NO_FATAL_FAILURE();
}

