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

#include "src/floe.h"
#include "gtest/gtest.h"

// ASSERT_EQ(1, 1);
// ASSERT_NO_FATAL_FAILURE();

TEST(FloeTest, TestFloe) {
  unsigned char* foo = new unsigned char[4];
  strcpy(reinterpret_cast<char*>(foo), "foo");
  Sha sha(foo);
  Floe floe;

  ASSERT_EQ(NULL, floe.sha().get());
  ASSERT_EQ(0, floe.get(sha).offset);
  ASSERT_EQ(0, floe.get(sha).length);
  ASSERT_EQ(0, floe.size());
}

TEST(FloeTest, TestFloeSha) {
  unsigned char* foo = new unsigned char[4];
  strcpy((char*)foo, "foo");
  Sha sha(foo);
  Floe floe(sha);

  ASSERT_EQ(foo, floe.sha().get());
  ASSERT_EQ(0, floe.get(sha).offset);
  ASSERT_EQ(0, floe.get(sha).length);
  ASSERT_EQ(0, floe.size());
}

TEST(FloeTest, TestSetSha) {
  unsigned char* foo = new unsigned char[4];
  strcpy((char*)foo, "foo");
  Sha sha(foo);
  Floe floe;
  floe.set_sha(sha);

  ASSERT_EQ(foo, floe.sha().get());
  ASSERT_EQ(0, floe.get(sha).offset);
  ASSERT_EQ(0, floe.get(sha).length);
  ASSERT_EQ(0, floe.size());
}

TEST(FloeTest, TestPut) {
  unsigned char* foo = new unsigned char[4];
  strcpy((char*)foo, "foo");
  Sha sha(foo);
  Floe floe;
  floe.put(sha, 1, 2);

  ASSERT_EQ(NULL, floe.sha().get());
  ASSERT_EQ(1, floe.get(sha).offset);
  ASSERT_EQ(2, floe.get(sha).length);
  ASSERT_EQ(1, floe.size());
}

TEST(FloeTest, TestPutLocation) {
  unsigned char* foo = new unsigned char[4];
  strcpy((char*)foo, "foo");
  Sha sha(foo);
  Floe floe;
  Location location = {1, 2};
  floe.put(sha, location);

  ASSERT_EQ(NULL, floe.sha().get());
  ASSERT_EQ(1, floe.get(sha).offset);
  ASSERT_EQ(2, floe.get(sha).length);
  ASSERT_EQ(1, floe.size());
}

TEST(FloeTest, TestList) {
  unsigned char* foo = new unsigned char[4];
  strcpy((char*)foo, "foo");
  Sha sha1(foo);
  unsigned char* bar = new unsigned char[4];
  strcpy((char*)bar, "bar");
  Sha sha2(bar);
  Floe floe;
  floe.put(sha1, 1, 2);
  floe.put(sha2, 3, 4);

  ASSERT_EQ(NULL, floe.sha().get());
  ASSERT_EQ(1, floe.get(sha1).offset);
  ASSERT_EQ(2, floe.get(sha1).length);
  ASSERT_EQ(3, floe.get(sha2).offset);
  ASSERT_EQ(4, floe.get(sha2).length);
  ASSERT_EQ(2, floe.size());

  map<Sha, Location>::const_iterator it = floe.list();
  // ASSERT_EQ(sha2, it->first);
  // ASSERT_EQ(3, it->second.offset);
  // ASSERT_EQ(4, it->second.length);
  it++;
  // ASSERT_EQ(sha1, it->first);
  // ASSERT_EQ(1, it->second.offset);
  // ASSERT_EQ(2, it->second.length);
  it++;
  // TODO(dfanjul): how can I detect the end of the iteration?
}

TEST(FloeTest, TestRead) {
  // TODO(dfanjul): test
}

TEST(FloeTest, TestWrite) {
  // TODO(dfanjul): test
}
