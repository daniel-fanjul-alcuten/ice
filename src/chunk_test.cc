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

#include "src/chunk.h"
#include "gtest/gtest.h"

TEST(ChunkTest, TestCreation) {
  char* contents = new char[12];
  char* hash = new char[65];
  strcpy(hash,
      "64979ba88eedd3a80c88db150706fc0956f43e969e37a48a12ba4560b7e9fd84");
  strcpy(contents, "hostia puta");

  Chunk c(ChunkData(contents, 11));

  ASSERT_EQ(hash, Digest::ToString(c.hash()));
  ASSERT_EQ(11, c.length());

  ChunkData data = c.data();
  for (int i = 0; i < data.length; ++i) {
    ASSERT_EQ(contents[i], data.data[i]) << "Data differs at index " << i;
  }

  ASSERT_NO_FATAL_FAILURE();
}

TEST(ChunkTest, TestCreationWithWrongSha) {
  char* contents = new char[12];
  strcpy(contents, "hostia puta");
  char* hash = new char[65];
  strcpy(hash,
      "64979ba88eedd3a80c88db150706fc0956f43e969e37a48a12ba4560b7e9fd84");
  strcpy(contents, "hostia puta");

  Chunk c;
  c.Create(ChunkData(contents, 11),
      Sha((unsigned char*)hash));

  ASSERT_NE(hash, Digest::ToString(c.hash()));

  ASSERT_NO_FATAL_FAILURE();
}

TEST(ChunkTest, TestEmpty) {
  char* contents = new char[1];
  strcpy(contents, "");
  char* hash = new char[65];
  strcpy(hash,
      "64979ba88eedd3a80c88db150706fc0956f43e969e37a48a12ba4560b7e9fd84");
  strcpy(contents, "hostia puta");

  Chunk c(ChunkData(contents, 0));

  ASSERT_EQ("e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
      Digest::ToString(c.hash()));

  ASSERT_NO_FATAL_FAILURE();
}
