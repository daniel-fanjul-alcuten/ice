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

#include "src/digest.h"
#include "gtest/gtest.h"

TEST(DigestTest, TestSha256) {
  string hash =
    "64979ba88eedd3a80c88db150706fc0956f43e969e37a48a12ba4560b7e9fd84";

  char* hostia = new char[8];
  char* puta = new char[5];
  char* hostiaputa = new char[12];

  strcpy(hostia, "hostia ");
  strcpy(puta, "puta");
  strcpy(hostiaputa, "hostia puta");

  Digest d1, d2;

  d1.Update(ChunkData(hostia, 7));
  d1.Update(ChunkData(puta, 4));

  d2.Update(ChunkData(hostiaputa, 11));

  ASSERT_EQ(hash, Digest::ToString(d1.Final()));
  ASSERT_EQ(hash, Digest::ToString(d2.Final()));

  ASSERT_NO_FATAL_FAILURE();
}
