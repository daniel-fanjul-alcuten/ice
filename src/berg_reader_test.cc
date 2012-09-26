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
#include "gtest/gtest.h"

#include "src/berg_reader.h"
#include "src/berg_writer.h"

TEST(BergReaderTest, TestReadSuccessfull) {
  Digest d;

  char* tmp_name = new char[11];
  GenRandom(tmp_name, 10);
  BergWriter bw(tmp_name, d);

  char* contents1 = new char[12];
  char* contents2 = new char[18];
  snprintf(contents1, 12, "hostia puta");
  Chunk c1(ChunkData(contents1, 11));

  snprintf(contents2, 18, "sharmuta mitmara");
  Chunk c2(ChunkData(contents2, 17));

  bw.WriteChunk(c1);
  bw.WriteChunk(c2);
  bw.Close();

  BergReader r(tmp_name, d);
  Chunk c = r.ReadByOffset(1);

  ASSERT_EQ(11, c.length());
  ASSERT_EQ(2, r.ChunkCount());
  ASSERT_EQ("64979ba88eedd3a80c88db150706fc0956f43e969e37a48a12ba4560b7e9fd84",
      Digest::ToString(c.hash()));

  char expected[12] = "hostia puta";
  for (int i = 0; i < c.length(); ++i) {
    ASSERT_EQ(expected[i], c.data().data[i]);
  }

  remove(tmp_name);
}

TEST(BergReaderTest, TestListing) {
  Digest d;

  char* tmp_name = new char[11];
  GenRandom(tmp_name, 10);
  BergWriter bw(tmp_name, d);

  char* contents1 = new char[12];
  char* contents2 = new char[18];
  snprintf(contents1, 12, "hostia puta");
  Chunk c1(ChunkData(contents1, 11));

  snprintf(contents2, 18, "sharmuta mitmara");
  Chunk c2(ChunkData(contents2, 17));

  bw.WriteChunk(c1);
  bw.WriteChunk(c2);
  bw.Close();
  BergReader r(tmp_name, d);

  ASSERT_EQ(2, r.ChunkCount());
  ShaMap hashes = r.ListHashes();
  ShaMapper it = hashes->begin();

  ASSERT_EQ(Digest::ToString(it->first),
      "64979ba88eedd3a80c88db150706fc0956f43e969e37a48a12ba4560b7e9fd84");
  ++it;
  ASSERT_EQ(Digest::ToString(it->first),
      "d802c0d00510f450a335bbf0a8b470b6e3491523550c834d1eef884ee718bb8b");

  remove(tmp_name);
}

