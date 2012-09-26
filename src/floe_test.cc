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
#include <vector>

#include "gtest/gtest.h"

#include "src/floe.h"
#include "src/berg_writer.h"

// ASSERT_EQ(1, 1);
// ASSERT_NO_FATAL_FAILURE();

TEST(FloeTest, TestFloe) {
  unsigned char* foo = new unsigned char[4];
  strcpy(reinterpret_cast<char*>(foo), "foo");
  Sha sha(foo);
  Floe floe;

  ASSERT_EQ(NULL, floe.sha().get());
  ASSERT_EQ(NULL, floe.Get(sha).get());
  ASSERT_EQ(0, floe.Size());
}

TEST(FloeTest, TestFloeSha) {
  unsigned char* foo = new unsigned char[4];
  strcpy((char*)foo, "foo");
  Sha sha(foo);
  Floe floe(sha);

  ASSERT_EQ(foo, floe.sha().get());
  ASSERT_EQ(NULL, floe.Get(sha).get());
  ASSERT_EQ(0, floe.Size());
}

TEST(FloeTest, TestSetSha) {
  unsigned char* foo = new unsigned char[4];
  strcpy((char*)foo, "foo");
  Sha sha(foo);
  Floe floe;
  floe.set_sha(sha);

  ASSERT_EQ(foo, floe.sha().get());
  ASSERT_EQ(NULL, floe.Get(sha).get());
  ASSERT_EQ(0, floe.Size());
}

TEST(FloeTest, TestPut) {
  unsigned char* foo = new unsigned char[4];
  strcpy((char*)foo, "foo");
  Sha sha(foo);
  Floe floe;
  floe.Put(sha, 1, 2);

  ASSERT_EQ(NULL, floe.sha().get());
  ASSERT_EQ(1, floe.Get(sha)->offset);
  ASSERT_EQ(2, floe.Get(sha)->length);
  ASSERT_EQ(1, floe.Size());
}

TEST(FloeTest, TestPutLocation) {
  unsigned char* foo = new unsigned char[4];
  strcpy((char*)foo, "foo");
  Sha sha(foo);
  Floe floe;
  Location *location = new Location(1, 2);
  floe.Put(sha, location);

  ASSERT_EQ(NULL, floe.sha().get());
  ASSERT_EQ(1, floe.Get(sha)->offset);
  ASSERT_EQ(2, floe.Get(sha)->length);
  ASSERT_EQ(1, floe.Size());
}

TEST(FloeTest, TestList) {
  unsigned char* foo = new unsigned char[4];
  strcpy((char*)foo, "foo");
  Sha sha1(foo);
  unsigned char* bar = new unsigned char[4];
  strcpy((char*)bar, "bar");
  Sha sha2(bar);
  Floe floe;
  floe.Put(sha1, 1, 2);
  floe.Put(sha2, 3, 4);

  ASSERT_EQ(NULL, floe.sha().get());
  ASSERT_EQ(1, floe.Get(sha1)->offset);
  ASSERT_EQ(2, floe.Get(sha1)->length);
  ASSERT_EQ(3, floe.Get(sha2)->offset);
  ASSERT_EQ(4, floe.Get(sha2)->length);
  ASSERT_EQ(2, floe.Size());

  map<Sha, LocationView> list = floe.List();
  map<Sha, LocationView>::const_iterator it = list.begin();

  lex_compare cmp;
  ASSERT_FALSE(cmp(sha1, it->first));
  ASSERT_EQ(1, it->second->offset);
  ASSERT_EQ(2, it->second->length);
  it++;

  ASSERT_FALSE(cmp(sha2, it->first));
  ASSERT_EQ(3, it->second->offset);
  ASSERT_EQ(4, it->second->length);
}

TEST(FloeTest, TestRead) {
  char* tmp_name = new char[11];
  GenRandom(tmp_name, 10);
  Digest d;
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

  Floe f;
  f.Write(tmp_name);

  remove(tmp_name);
}

TEST(FloeTest, TestWrite) {
  // TODO(dfanjul): test
}
